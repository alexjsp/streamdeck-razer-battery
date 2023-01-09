//==============================================================================
/**
@file		RazerBatteryHelper.cpp

@brief		Get the Razer device battery status

**/
//==============================================================================

#include "RazerBatteryHelper.h"

extern "C"
{
	#include "razercommon.h"
	#include "razerdevice.h"
	#include "razermouse_driver.h"
}

RazerBatteryHelper::RazerBatteryHelper() 
{
	
}

int RazerBatteryHelper::GetCurrentBatteryValue()
{
	RazerDevices rDevices = getAllRazerDevices();
	RazerDevice *devices = rDevices.devices;
	int deviceCount = rDevices.size;
		
	double batteryLevel = -1;
	for(int i = 0; i<rDevices.size; i++) {
		RazerDevice device = devices[i];
		char buf[4] = {0};
		
		razer_attr_read_get_battery(device.usbDevice, buf);
		double bufferValue = atof(buf);
				
		if (bufferValue <= 0) { continue; }
		
		batteryLevel = (bufferValue * 100.0) / 255.0;
	}
	
	closeAllRazerDevices(rDevices);
	
	return batteryLevel;
}
