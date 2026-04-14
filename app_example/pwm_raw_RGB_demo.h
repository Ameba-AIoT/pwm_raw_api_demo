#ifndef _PWM_RAW_DEMO_H_
#define _PWM_RAW_DEMO_H_
#include "platform_autoconf.h"
#include "device.h"
#include "os_wrapper.h"
#include <stdio.h>


#define PWM_TIMER		8
#define PWM_RGB_CHANNEL    3

// typedef struct {
// 	u32 TIM_Prescaler;		/*!< Specifies the prescaler value used to divide the TIM clock.
// 							This parameter can be a number between 0x0 and 0xFFFF, basic timer dont care */
// 	u32 TIM_Period;			/*!< Specifies the period value to be loaded into the active
// 							Auto-Reload Register at the next update event.
// 							This parameter is 16bits for TIM8-9, and 32bits for TIM0-TIM7
// 							you can get it from SourceClock & TIM_Prescaler */
// 	u32 TIM_UpdateEvent;		/*!< Specifies whether or not to enable update event(UEV).
// 								This parameter can be ENABLE or DISABLE. ENABLE means UEV Enable, DISABLE means UEV Disable*/
// 	u32 TIM_UpdateSource;		/*!< Specifies the update request source. This parameter can be
// 								TIM_UpdateSource_Overflow or TIM_UpdateSource_Global.
// 								TIM_UpdateSource_Overflow means counter overflow generates an update event(UEV).
// 								TIM_UpdateSource_Global means both counter overflow and setting the UG bit can generate UEV.*/
// 	u32 TIM_ARRProtection;	/*!< DISABLE or ENABLE, when ENABLE: period will update when cnt = 0(counter overflow, an UEV happens),
// 							or  period will update immediatly */

// 	u8	TIM_Idx;				/*!< 0~9 */

// 	u32	TIM_SecureTimer;		/*!< Specifies the secure attribute of this timer.
// 								This parameter is used in secure world of trustzone.*/
// } RTIM_TimeBaseInitTypeDef;

#define PWM_PRESCALER	39   // 1MHz/ 1us
//#define PWM_PRESCALER (u32)(1000 * 40 / (prescaler + 1)) & 0x0000ffff
#define PWM_PERIOD		1000
#define PWM_SLEEP		PWM_PERIOD / ((PWM_PRESCALER + 1)/40)  //us



void pwm_raw_RGB_demo(void);

#endif