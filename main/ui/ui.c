// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.1.1
// LVGL VERSION: 8.2.0
// PROJECT: SquareLine_Project

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "ui.h"
#include "ui_helpers.h"
#include "images/hyrel_mark.h"
#include "images/img_splash.h"
#include "open62541/opc.h"
#include "K_Core/DisplayList.h"
///////////////////// VARIABLES ////////////////////
lv_obj_t *ui_Splash_Screen;
lv_obj_t *ui_Main_Screen;
lv_obj_t *ui_Opc_Screen;
lv_obj_t *ipAddressLabel;
lv_obj_t *OpcHeartBeatLabel;
lv_obj_t *SecTimerLabel;
lv_obj_t *ledSecs;

lv_obj_t * variableContainer;
/////////////////////// TEST LVGL SETTINGS ////////////////////
//#if LV_COLOR_DEPTH != 16
//    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
//#endif
//#if LV_COLOR_16_SWAP !=1
//    #error "LV_COLOR_16_SWAP should be 1 to match SquareLine Studio's settings"
//#endif


void ui_event_start_button_handler(lv_event_t * e) {
	lv_event_code_t event_code = lv_event_get_code(e); 
	lv_obj_t * target = lv_event_get_target(e);
	if (event_code == LV_EVENT_CLICKED) {
		OpcPaused = false;
	}
}

void ui_event_stop_button_handler(lv_event_t * e) {
	lv_event_code_t event_code = lv_event_get_code(e); 
	lv_obj_t * target = lv_event_get_target(e);
	if (event_code == LV_EVENT_CLICKED) {
		OpcPaused = true;
	}
}

void ui_event_display_prev_button_handler(lv_event_t * e)
{
	lv_event_code_t event_code = lv_event_get_code(e); 
	lv_obj_t * target = lv_event_get_target(e);
	if (event_code == LV_EVENT_CLICKED) {
		DisplayIndexDecrement();
	}
}
void ui_event_display_next_button_handler(lv_event_t * e)
{
	lv_event_code_t event_code = lv_event_get_code(e); 
	lv_obj_t * target = lv_event_get_target(e);
	if (event_code == LV_EVENT_CLICKED) {
		DisplayIndexIncrement();
	}
}
static void draw_variableContainer_event_cb(lv_event_t * e)
{
	lv_obj_t * obj = lv_event_get_target(e);
	lv_obj_draw_part_dsc_t * dsc = lv_event_get_draw_part_dsc(e);
	/*If the cells are drawn...*/
	if (dsc->part == LV_PART_ITEMS) {
		uint32_t row = dsc->id /  lv_table_get_col_cnt(obj);
		uint32_t col = dsc->id - row * lv_table_get_col_cnt(obj);

		/*Make the texts in the first cell center aligned*/
		if (row == 0) {
			dsc->label_dsc->align = LV_TEXT_ALIGN_CENTER;
			dsc->rect_dsc->bg_color = lv_color_mix(lv_palette_main(LV_PALETTE_BLUE), dsc->rect_dsc->bg_color, LV_OPA_20);
			dsc->rect_dsc->bg_opa = LV_OPA_COVER;
		}
		/*In the first column align the texts to the right*/
		else if(col == 0) {
			dsc->label_dsc->align = LV_TEXT_ALIGN_LEFT;
		}

		/*MAke every 2nd row grayish*/
		if ((row != 0 && row % 2) == 0) {
			dsc->rect_dsc->bg_color = lv_color_mix(lv_palette_main(LV_PALETTE_GREY), dsc->rect_dsc->bg_color, LV_OPA_10);
			dsc->rect_dsc->bg_opa = LV_OPA_COVER;
		}
	}
}


LV_IMG_DECLARE(img_hyrel_mark);
LV_IMG_DECLARE(img_hyrel_splash);
///////////////////// SCREENS ////////////////////
void ui_Splash_Screen_screen_init(void)
{
    ui_Splash_Screen = lv_obj_create(NULL);
	lv_obj_clear_flag(ui_Splash_Screen, LV_OBJ_FLAG_SCROLLABLE); /// Flags
	lv_obj_set_style_bg_color(ui_Splash_Screen, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	//lv_obj_set_style_bg_opa(ui_Splash_Screen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	
	lv_obj_t * img = lv_img_create(ui_Splash_Screen); //lv_scr_act()
	lv_img_set_src(img, &img_hyrel_mark);
	lv_obj_align(img, LV_ALIGN_CENTER, 0, -100);
	
	lv_obj_t * preload = lv_spinner_create(ui_Splash_Screen, 1000, 100);	
	lv_obj_set_size(preload, 60, 60);
	static lv_style_t style_spinner;
	lv_style_init(&style_spinner);
	lv_style_set_arc_color(&style_spinner, lv_color_hex(0x00A3FF));
	lv_style_set_bg_color(&style_spinner, lv_color_hex(0x0000ff));
	lv_obj_add_style(preload, &style_spinner, LV_PART_INDICATOR);
	lv_obj_align(preload, LV_ALIGN_CENTER, 0, 50);	
}

lv_obj_t* ui_create_label(lv_obj_t* parent, char* text, uint16_t x, uint16_t y, const lv_font_t* font)
{
	lv_obj_t* obj = lv_label_create(parent);	
	lv_obj_set_width(obj, LV_SIZE_CONTENT); /// 1
	lv_obj_set_height(obj, LV_SIZE_CONTENT); /// 1
	lv_obj_set_align(obj, LV_ALIGN_TOP_LEFT);
	lv_obj_set_pos(obj, x, y);
	lv_label_set_recolor(obj, true);
	//lv_obj_add_style(ipAddressLabel, &style_label, LV_PART_INDICATOR);	
	lv_label_set_text_fmt(obj, "%s", text);
	lv_obj_set_style_text_font(obj, font, LV_PART_MAIN | LV_STATE_DEFAULT);
	return obj;
}

lv_obj_t* ui_create_button(lv_obj_t* parent, char* text, uint16_t x, uint16_t y, uint16_t w, uint16_t h, 
	                uint16_t radius, uint32_t color,
					const lv_font_t* font,
	                lv_event_cb_t event_button_handler)
{
	lv_obj_t* button = lv_btn_create(parent);
	
	lv_obj_set_width(button, w); /// 1
	lv_obj_set_height(button, h); /// 1
	lv_obj_set_align(button, LV_ALIGN_TOP_LEFT);
	lv_obj_set_pos(button, x, y);
	
	lv_obj_add_flag(button, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
	lv_obj_clear_flag(button, LV_OBJ_FLAG_SCROLLABLE); /// Flags
	lv_obj_set_style_radius(button, radius, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(button, lv_color_hex(color), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(button, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	
	lv_obj_t* label = lv_label_create(button);	
	lv_obj_set_width(label, LV_SIZE_CONTENT); /// 1
	lv_obj_set_height(label, LV_SIZE_CONTENT); /// 1
	lv_obj_set_align(label, LV_ALIGN_CENTER);
	//lv_obj_set_pos(obj, 10, 2);
	lv_label_set_recolor(label, true);
	lv_label_set_text(label, text);
	lv_obj_set_style_text_font(label, font, LV_PART_MAIN | LV_STATE_DEFAULT);
	
	lv_obj_add_event_cb(button, event_button_handler, LV_EVENT_ALL, NULL);
	return button;
}
void ui_Opc_Screen_init(void) 
{
	ui_Opc_Screen = lv_obj_create(NULL);	
	lv_style_t style_label;
	lv_style_init(&style_label);
	//lv_style_set_text_color(&style_label, lv_color_hex(0x00ff00)); 
	
	lv_obj_clear_flag(ui_Opc_Screen, LV_OBJ_FLAG_SCROLLABLE); /// Flags
	
	lv_obj_set_style_bg_color(ui_Opc_Screen, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_Opc_Screen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	
	lv_obj_t* obj = ui_create_label(ui_Opc_Screen, "#ffff00 OPC #", 10, 10, &lv_font_montserrat_38);
	lv_obj_set_align(obj, LV_ALIGN_TOP_MID);
	
	/*Create a container with COLUMN flex direction*/
	variableContainer = lv_table_create(ui_Opc_Screen);	
	
	lv_obj_t* button = ui_create_button(ui_Opc_Screen, "<<", 10, 60, 60, 30, 6, 0x00A3FF, &lv_font_montserrat_20, ui_event_display_prev_button_handler);
	button = ui_create_button(ui_Opc_Screen, ">>", 320 - 70, 60, 60, 30, 6, 0x00A3FF, &lv_font_montserrat_20, ui_event_display_next_button_handler);
	
	lv_obj_set_size(variableContainer, 310, 320);
	//lv_obj_center(variableContainer);
	lv_obj_set_align(variableContainer, LV_ALIGN_TOP_MID);
	lv_obj_set_y(variableContainer, 100);
	//lv_obj_set_flex_flow(variableContainer, LV_FLEX_FLOW_COLUMN);
	
	lv_table_set_col_width(variableContainer, 0, 150);
	lv_table_set_row_cnt(variableContainer, 20); /*Not required but avoids a lot of memory reallocation lv_table_set_set_value*/
	lv_table_set_col_cnt(variableContainer, 2);

	lv_table_set_cell_value_fmt(variableContainer, 0, 0, "Name");
	lv_table_set_cell_value_fmt(variableContainer, 0, 1, "Value");
	
	uint32_t i;
	for (i = 1; i <= 20; i++) {
		lv_table_set_cell_value_fmt(variableContainer, i, 0, "Item %"LV_PRIu32, i + 1);
		lv_table_set_cell_value_fmt(variableContainer, i, 1, "Value %"LV_PRIu32, i + 1);
		
	}
	lv_obj_add_event_cb(variableContainer, draw_variableContainer_event_cb, LV_EVENT_DRAW_PART_BEGIN, NULL);
//	
//	
//	lv_obj_t* obj = ui_create_label(ui_Opc_Screen, "#ffff00 OPC #", 10, 10, &lv_font_montserrat_38);
//	
//	obj = ui_create_label(ui_Opc_Screen, "#ffff00 IP Address: #", 10, 50, &lv_font_montserrat_20);
//	
//	ipAddressLabel = ui_create_label(ui_Opc_Screen, "", 160, 50, &lv_font_montserrat_20);
	
	button = ui_create_button(ui_Opc_Screen, "START", 10, 430, 150, 30, 6, 0x00A3FF, &lv_font_montserrat_20, ui_event_start_button_handler);
	button = ui_create_button(ui_Opc_Screen, "STOP", 165, 430, 150, 30, 6, 0x565656, &lv_font_montserrat_20, ui_event_stop_button_handler);
//	
//	obj = ui_create_label(ui_Opc_Screen, "#ffff00 1s Timer: #", 10, 120, &lv_font_montserrat_20);
//	SecTimerLabel = ui_create_label(ui_Opc_Screen, "", 160, 120, &lv_font_montserrat_20);
	
	
//	ledSecs  = lv_led_create(ui_Opc_Screen);
//	lv_led_set_color(ledSecs, lv_color_hex(0xff0000));
//	lv_obj_set_pos(ledSecs, 250, 120);
//	lv_led_off(ledSecs);
	
	//obj = ui_create_label(ui_Opc_Screen, "#ffff00 HeartBeat: #", 10, 150, &lv_font_montserrat_20);
	//OpcHeartBeatLabel = ui_create_label(ui_Opc_Screen, "", 160, 150, &lv_font_montserrat_20);
	
}

void InitUI( void )
{
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_Splash_Screen_screen_init();
    ui_Opc_Screen_init();
    lv_disp_load_scr( ui_Splash_Screen);
	
	// Switch to the main application if OTA has not been started
	vTaskDelay(pdMS_TO_TICKS(5000));
	
	lv_scr_load(ui_Opc_Screen);
	
	
	
}
