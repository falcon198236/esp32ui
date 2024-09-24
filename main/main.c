#include "main.h"
#include "K_Core/K_Core.h"
#include "wifi/wifi.h"

#ifdef USE_OPC
#include "open62541/opc.h"
#endif
#include "devices/display.h"
#include "ui/ui.h"
#include "K_Core/DisplayList.h"
const char *TAG = "L_Core";
bool IsInitialized = false;
extern "C" void app_main(void)
{
	esp_log_level_set(TAG, ESP_LOG_DEBUG); // enable DEBUG logs for this App
    //Initialize NVS
	esp_err_t ret = nvs_flash_init();
	if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
		ESP_ERROR_CHECK(nvs_flash_erase());
		ret = nvs_flash_init();
	}
	ESP_ERROR_CHECK(ret);
	
	IsInitialized = false;
	InitWifi();
	InitOPC();
	
	InitLCDAndLVGL();
	InitUI();
	K_Core_Main();
	
	IsInitialized = true;
	
	SetActiveDisplayVariable(LcdVarsTable);
	
}
