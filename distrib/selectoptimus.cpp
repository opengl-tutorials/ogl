#include "nvapi.h"
#include "NvApiDriverSettings.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/*
    This function is used to print to the command line a text message 
    describing the nvapi error and quits
*/
void PrintError(NvAPI_Status status, int line)
{
	NvAPI_ShortString szDesc = {0};
	NvAPI_GetErrorMessage(status, szDesc);
	printf(" NVAPI error line %d : %s\n", line, szDesc);
	exit(-1);
}

int main(int argc, char **argv)
{

	if (argc != 2){
		printf("Usage : \n\tselectoptimus NVIDIA\n\tselectoptimus INTEL");
		return -1;
	}
	
	bool ForceIntegrated;
	if (strcmp(argv[1],"NVIDIA") == 0) ForceIntegrated = false;
	else if (strcmp(argv[1],"INTEL") == 0) ForceIntegrated = true;
	else {
		printf("Usage : \n\tselectoptimus NVIDIA\n\tselectoptimus INTEL");
		return -1;
	}

    NvAPI_Status status;
    // (0) Initialize NVAPI. This must be done first of all
    status = NvAPI_Initialize();
    if (status != NVAPI_OK) 
        PrintError(status, __LINE__);
    // (1) Create the session handle to access driver settings
    NvDRSSessionHandle hSession = 0;
    status = NvAPI_DRS_CreateSession(&hSession);
    if (status != NVAPI_OK) 
        PrintError(status, __LINE__);
    // (2) load all the system settings into the session
    status = NvAPI_DRS_LoadSettings(hSession);
    if (status != NVAPI_OK) 
        PrintError(status, __LINE__);
    // (3) Obtain the Base profile. Any setting needs to be inside
    // a profile, putting a setting on the Base Profile enforces it
    // for all the processes on the system
    NvDRSProfileHandle hProfile = 0;
    status = NvAPI_DRS_GetBaseProfile(hSession, &hProfile);
    if (status != NVAPI_OK) 
        PrintError(status, __LINE__);


	NVDRS_SETTING drsSetting1 = {0};
	drsSetting1.version = NVDRS_SETTING_VER;
	drsSetting1.settingId = SHIM_MCCOMPAT_ID;
	drsSetting1.settingType = NVDRS_DWORD_TYPE;

	NVDRS_SETTING drsSetting2 = {0};
	drsSetting2.version = NVDRS_SETTING_VER;
	drsSetting2.settingId = SHIM_RENDERING_MODE_ID;
	drsSetting2.settingType = NVDRS_DWORD_TYPE;

	NVDRS_SETTING drsSetting3 = {0};
	drsSetting3.version = NVDRS_SETTING_VER;
	drsSetting3.settingId = SHIM_RENDERING_OPTIONS_ID;
	drsSetting3.settingType = NVDRS_DWORD_TYPE;

	if( ForceIntegrated ){
 		drsSetting1.u32CurrentValue = SHIM_MCCOMPAT_INTEGRATED;
		drsSetting2.u32CurrentValue = SHIM_RENDERING_MODE_INTEGRATED;
		drsSetting3.u32CurrentValue = SHIM_RENDERING_OPTIONS_DEFAULT_RENDERING_MODE | SHIM_RENDERING_OPTIONS_IGPU_TRANSCODING;
	}else{
 		drsSetting1.u32CurrentValue = SHIM_MCCOMPAT_ENABLE;
		drsSetting2.u32CurrentValue = SHIM_RENDERING_MODE_ENABLE;
		drsSetting3.u32CurrentValue = SHIM_RENDERING_OPTIONS_DEFAULT_RENDERING_MODE;
	}



	status = NvAPI_DRS_SetSetting(hSession, hProfile, &drsSetting1);
	if (status != NVAPI_OK) 
		PrintError(status, __LINE__);

	status = NvAPI_DRS_SetSetting(hSession, hProfile, &drsSetting2);
	if (status != NVAPI_OK) 
		PrintError(status, __LINE__);

	status = NvAPI_DRS_SetSetting(hSession, hProfile, &drsSetting3);
	if (status != NVAPI_OK) 
		PrintError(status, __LINE__);

    // (5) Now we apply (or save) our changes to the system
    status = NvAPI_DRS_SaveSettings(hSession);
    if (status != NVAPI_OK) 
        PrintError(status, __LINE__);
    // (6) We clean up. This is analogous to doing a free()
    NvAPI_DRS_DestroySession(hSession);
    hSession = 0;
    return 0;
}