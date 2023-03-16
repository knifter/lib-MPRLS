#ifndef __MPRLS_H
#define __MPRLS_H

#include <Arduino.h>
#include <TwoWireDevice.h>

#define PSI2HPA(x) 						(x*68.947572932)

#define MPRLS_ADDRESS_DEFAULT           (0x18)

class MPRLS: public TwoWireDevice {
    public:    
        MPRLS(TwoWire& wire, const uint8_t addr = MPRLS_ADDRESS_DEFAULT) : TwoWireDevice(wire, addr) {};
        MPRLS(const uint8_t addr = MPRLS_ADDRESS_DEFAULT) : TwoWireDevice(addr) {};

        bool begin();

  		float readPressureHPA(void);
  		float readPressurePSI(void);

	private:
		uint8_t _status;
		uint32_t _pres_raw;
		uint32_t _temp_raw;

  		uint8_t readStatus(void);
  		uint32_t readData(void);

    private:
        MPRLS(const MPRLS&);
        MPRLS& operator=(const MPRLS&);
};

#endif // __INA219_H
