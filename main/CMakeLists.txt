idf_component_register(
                SRCS
                	main.c
                	"ui/ui.c"
                	"ui/ui_helpers.c"
                	open62541/open62541.c
                	wifi/wifi.c
                	open62541/opc.c
                	ui/images/hyrel-mark.c
                	ui/images/img-splash.c
                	devices/display.c
                	K_Core/K_Core.c
                	K_Core/GPIO.c
                	K_Core/taskmanager.c
                	K_Core/GPIO.c
                	K_Core/K_Core.c
                	K_Core/taskmanager.c
                	K_Core/DisplayList.c
                INCLUDE_DIRS "." "devices" "ui"
                REQUIRES
                	LovyanGFX
                	lvgl
                	app_update
                	esp_https_ota
                	esp_event
                	esp_timer
                	spi_flash
                	esp_wifi
                	esp_partition
                	esp_hw_support)
component_compile_options(-fexceptions -x c++)
set_property(TARGET ${COMPONENT_TARGET} PROPERTY CXX_STANDARD 17)
