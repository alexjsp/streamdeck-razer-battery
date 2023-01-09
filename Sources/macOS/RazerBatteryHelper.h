//==============================================================================
/**
@file       RazerBatteryHelper.h

@brief		Get the Razer device battery status

**/
//==============================================================================

#pragma once

#include <sys/sysctl.h>
#include <sys/types.h>
#include <mach/mach.h>
#include <mach/processor_info.h>
#include <mach/mach_host.h>

extern "C"
{
	#include "razercommon.h"
	#include "razerdevice.h"
	#include "razermouse_driver.h"
}

class RazerBatteryHelper
{
public:
	RazerBatteryHelper();
	~RazerBatteryHelper() {};
	
	int GetCurrentBatteryValue();
	bool GetChargingState();
	void CloseOpenConnections();

private:
	RazerDevices mRazerDevices;
	
	void LoadDevices();	
	RazerDevice GetMouse();

};
