#ifndef __MPRLS_DEFS_H
#define __MPRLS_DEFS_H


#define MPRLS_READ_TIMEOUT 		(10)     	// millis
#define MPRLS_STATUS_POWERED 	(0x40) 	// Status SPI powered bit
#define MPRLS_STATUS_BUSY 		(0x20)    	// Status busy bit
#define MPRLS_STATUS_FAILED 	(0x04)  	// Status bit for integrity fail
#define MPRLS_STATUS_MATHSAT 	(0x01) 	// Status bit for math saturation
#define MPRLS_STATUS_MASK 		(0b01100101) 	// Sensor status mask: only these bits are set

#define CMD_MEASURE				0xAA

// Scale conversion
#define OUTPUT_MIN				1677722		// From DS
#define OUTPUT_MAX  			15099494	// From DS
#define PRES_MIN				0
#define PRES_MAX				25	

#endif // __MPRLS_DEFS_H
