#include "pwm_raw_RGB_demo.h"
#include "FreeRTOS.h"
#include "task.h"

#define TAG     "app_main" 
void app_example(void)
{
	RTK_LOGI("TAG", "pwm_raw_RGB_demo start!\r\n");
	if (RTK_SUCCESS != rtos_task_create(NULL, "pwm_raw_RGB_demo", (rtos_task_t)pwm_raw_RGB_demo, (void *)NULL, (2048), tskIDLE_PRIORITY)) {
		printf("Create pwm_raw_RGB_demo Err!!\n");
	}
}