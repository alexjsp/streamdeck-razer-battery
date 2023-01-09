//==============================================================================
/**
@file		RazerBatteryHelper.cpp

@brief		Get the Razer device battery status

**/
//==============================================================================

#include "RazerBatteryHelper.h"

RazerBatteryHelper::RazerBatteryHelper() 
{
	
}

void RazerBatteryHelper::LoadDevices()
{
	if (mRazerDevices.size > 0) { return; }
	
	mRazerDevices = getAllRazerDevices();
}

void RazerBatteryHelper::CloseOpenConnections()
{
	closeAllRazerDevices(mRazerDevices);
	mRazerDevices = {};
}

RazerDevice RazerBatteryHelper::GetMouse()
{
	this->LoadDevices();
	
	RazerDevice *devices = mRazerDevices.devices;
	int deviceCount = mRazerDevices.size;
		
	for (int i = 0; i<deviceCount; i++) {
	    RazerDevice device = devices[i];
		if (device.deviceType == TYPE_MOUSE) {
			return device;
		}
	}
	
	return {};
}

int RazerBatteryHelper::GetCurrentBatteryValue()
{
	RazerDevice device = this->GetMouse();
	
	if (device.usbDevice == NULL) { return -1; }
	
	char buf[4] = {0};
	
	razer_attr_read_get_battery(device.usbDevice, buf);
	double bufferValue = atof(buf);
			
	if (bufferValue <= 0) { return -1; }
	
	return (bufferValue * 100.0) / 255.0;
}

bool RazerBatteryHelper::GetChargingState()
{
	RazerDevice device = this->GetMouse();
	
	if (device.usbDevice == NULL) { return -1; }
	
	char buf[4] = {0};
	
	razer_attr_read_is_charging(device.usbDevice, buf);
	return atof(buf) != 0;
}

