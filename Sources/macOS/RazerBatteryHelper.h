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

class RazerBatteryHelper
{
public:
	RazerBatteryHelper();
	~RazerBatteryHelper() {};
	
	int GetCurrentBatteryValue();

private:
	
	processor_info_array_t mProcessorInfo = nullptr;
	mach_msg_type_number_t mProcessorInfoCnt = 0;
	
	processor_info_array_t mOldProcessorInfo = nullptr;
	mach_msg_type_number_t mOldProcessorInfoCnt = 0;
	
	unsigned mNumberOfCPUs = 0;
};
