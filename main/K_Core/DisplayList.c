#include "DisplayList.h"
#include "taskmanager.h"
#include "K_Core.h"
#include "../open62541/opc.h"
#include "../wifi/wifi.h"
#include "../ui/ui.h"
#include "RevisionHistory.h"
char* SystemInfo = "ESP32 SOC1 Plus";

DisplayVariableInfo LcdVarsTable[] = {
	{ SystemInfo, "SystemInfo", FUNC_ASCII, COLOR_WHITE, COLOR_RED, 0 },
	{ (void*)SYSTEMVERSION, "SystemInfo", FUNC_ASCII, COLOR_WHITE, COLOR_RED, 0 },
	{ ipAddress, "WIFI IP", FUNC_ASCII, COLOR_WHITE, COLOR_RED, 0 },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0 },
	{ &OpcPaused, "OPC Status", FUNC_BOOLEAN, COLOR_WHITE, COLOR_RED, 0 },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0 },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0 },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0 },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0 },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0 },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0 },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0 },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0 },
	{ 0 },
};


DisplayVariableInfo Lcd1VarsTable[] = {
	{ &ipAddress, "WIFI IP", FUNC_ASCII, COLOR_WHITE, COLOR_RED, 0 },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0 },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0 },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0 },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0 },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0 },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0 },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0 },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0 },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0 },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0 },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0 },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0 },
	{ &HeartBeat, "HB      ", FUNC_INT32, COLOR_WHITE, COLOR_RED, 0 },
	
	{ &OpcPaused, "OPC Status", FUNC_BOOLEAN, COLOR_WHITE, COLOR_RED, 0 },
	{ 0 },
};
int GetDisplayVariableSize(DisplayVariableInfo* variableInfo)
{
	int i = 0;
	while (1)
	{
		if (variableInfo[i].VariablePointer == 0) break;
		i++;
	}
	return i;
}

void SetActiveDisplayVariable(DisplayVariableInfo* variableInfo)
{
	ActiveVariableInfo = variableInfo;
	int rows =  GetDisplayVariableSize(variableInfo);
	///rows++; //it include header.
	lv_table_set_row_cnt(variableContainer, rows );
	for (int i = 0; i < rows; i++)
	{
		if (variableInfo[i].VariablePointer == 0) break;
		lv_table_set_cell_value_fmt(variableContainer, i+1, 0, "%s", variableInfo[i].Label);
	}
	
}

void UpdateDisplayVariable(DisplayVariableInfo* variableInfo)
{
	int rows = lv_table_get_row_cnt(variableContainer);
	for (int i = 0; i < rows; i++)
	{
		if (variableInfo[i].VariablePointer == 0) break;
		//lv_table_set_cell_value_fmt(variableContainer, i, 0, "#%x %s #", variableInfo[i].Label);
		switch (variableInfo[i].FuncType)
		{
		case FUNC_INT:
		case FUNC_INT16:
		case FUNC_INT32:
			lv_table_set_cell_value_fmt(variableContainer, i+1, 1, "%d", (*(int*)variableInfo[i].VariablePointer));
			break;
		case FUNC_BOOLEAN:
			lv_table_set_cell_value_fmt(variableContainer, i + 1, 1, "%s", ((bool)((int*)variableInfo[i].VariablePointer)) ? "True" : "False");
			break;
		case FUNC_ASCII:
			lv_table_set_cell_value_fmt(variableContainer, i+1, 1, "%s", variableInfo[i].VariablePointer);
			break;
		default:
			break;
		}
		
	}
}
#define NUMBER_OF_DISPLAY_LISTS 2
uint8_t DisplayIndex = 0;

void SwitchDisplayVariableList()
{
	switch (DisplayIndex)
	{
	case 0:
		SetActiveDisplayVariable(LcdVarsTable);
		break;
	case 1:
		SetActiveDisplayVariable(Lcd1VarsTable);
		break;
	default:
		break;
	}
}
void DisplayIndexIncrement()
{
	DisplayIndex++; if (DisplayIndex > NUMBER_OF_DISPLAY_LISTS) DisplayIndex = 0;
	SwitchDisplayVariableList();
}

void DisplayIndexDecrement()
{
	DisplayIndex--; if (DisplayIndex < 0) DisplayIndex = NUMBER_OF_DISPLAY_LISTS;
	SwitchDisplayVariableList();
}
