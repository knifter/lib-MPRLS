#include "Arduino.h"
#include <TwoWireDevice.h>

#include "MPRLS.h"
#include "MPRLS_defs.h"

bool MPRLS::begin()
{
	TwoWireDevice::begin();

	return ((readStatus() & MPRLS_STATUS_MASK) == MPRLS_STATUS_POWERED);

	// return (_wire.lastError() == 0);
};

/**************************************************************************/
/*!
    @brief Read just the status byte, see datasheet for bit definitions
    @returns 8 bits of status data
*/
/**************************************************************************/
uint8_t MPRLS::readStatus(void) 
{
	read(&_status, 1);
	return _status;
};

/**************************************************************************/
/*!
    @brief Read and calculate the pressure
    @returns The measured pressure, in hPa on success, NAN on failure
*/
/**************************************************************************/
float MPRLS::readPressurePSI() 
{
	if(!readData())
		return NAN;

	float temp = ((_temp_raw * 200) / OUTPUT_MIN) - 50;
	return ((_pres_raw - OUTPUT_MIN) * (PRES_MAX-PRES_MIN)) / (OUTPUT_MAX - OUTPUT_MIN) + PRES_MIN;
};

/**************************************************************************/
/*!
    @brief Read 24 bits of measurement data from the device
    @returns -1 on failure (check status) or 24 bits of raw ADC reading
*/
/**************************************************************************/
uint32_t MPRLS::readData() 
{
	uint8_t buffer[4] = {CMD_MEASURE, 0, 0, 0 };

	// Request data
	write(buffer, 3);

  	// Use the gpio to tell end of conversion
  	time_t start = millis();
	while((_status = readStatus()) & MPRLS_STATUS_BUSY) 
	{
		delay(1);
		// Serial.print("Status: "); Serial.println(stat, HEX);
		if (millis() - start > MPRLS_READ_TIMEOUT)
			return false;
	};

	// Read status byte and data
	uint8_t buf[7];	
	read(buf, 7);
	_status = buf[0];

	_pres_raw = buf[1] << 16 | buf[2] << 8 | buf[3];
	_temp_raw = buf[4] << 16 | buf[5] << 8 | buf[6];

	// check status byte
	if(_status & MPRLS_STATUS_MATHSAT) 
		return 0xFFFFFFFF;
	if(_status & MPRLS_STATUS_FAILED) 
		return 0xFFFFFFFF;

	// all good, return data
	return true;
};

