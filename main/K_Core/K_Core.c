#include "../configure.h"
#include "../main.h"
#include "K_Core.h"
#include "GPIO.h"
#include "taskmanager.h"
#include "DisplayList.h"
#include "RevisionHistory.h"
DisplayVariableInfo *ActiveVariableInfo = NULL;
void forground_task(void* arg);
void K_Core_Main()
{
	InitGPIO();
	InitTaskManager();
	xTaskCreatePinnedToCore(forground_task, "forground_task", 1024 * 5, NULL, 10, NULL, 1);
}

void forground_task(void* arg) {
	while (1)
	{
		
		if (ActiveVariableInfo)		UpdateDisplayVariable(ActiveVariableInfo);
		vTaskDelay(50);
		
	}
}

