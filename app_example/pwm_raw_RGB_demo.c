#include "pwm_raw_RGB_demo.h"

u8 PWM_GPIOx_S0[PWM_RGB_CHANNEL] = {
	//ECO EVB
	_PA_14,
	_PA_15,
	_PA_16
};
void pwm_raw_RGB_demo()
{
	RTIM_TimeBaseInitTypeDef RTIM_InitStruct;
	TIM_CCInitTypeDef TIM_CCInitStruct;
	int pwm_chan = 0;
	int i,j;
	/* close swdclk/swdio*/
	Pinmux_Swdoff();
	/* Enable TIM_PWM function & clock */
	RCC_PeriphClockCmd(APBPeriph_TIMx[PWM_TIMER], APBPeriph_TIMx_CLOCK[PWM_TIMER], ENABLE);

	RTIM_TimeBaseStructInit(&RTIM_InitStruct);
	RTIM_InitStruct.TIM_Idx = PWM_TIMER;
	RTIM_InitStruct.TIM_Prescaler = PWM_PRESCALER;
	RTIM_InitStruct.TIM_Period = PWM_PERIOD - 1;
	RTIM_TimeBaseInit(TIMx[PWM_TIMER], (&RTIM_InitStruct), TIMx_irq[PWM_TIMER], NULL, NULL);

	for (pwm_chan = 0; pwm_chan < PWM_RGB_CHANNEL; pwm_chan++) 
	{
		RTIM_CCStructInit(&TIM_CCInitStruct);
		TIM_CCInitStruct.TIM_OCPulse = PWM_PERIOD / 2;
		RTIM_CCxInit(TIMx[PWM_TIMER], &TIM_CCInitStruct, pwm_chan);
		RTIM_CCxCmd(TIMx[PWM_TIMER], pwm_chan, TIM_CCx_Enable);	
		Pinmux_Config(PWM_GPIOx_S0[pwm_chan], (PINMUX_FUNCTION_PWM0 + pwm_chan));
		RTIM_CCRxSet(TIMx[PWM_TIMER], 0, pwm_chan);
	}

	RTIM_Cmd(TIMx[PWM_TIMER], ENABLE);

	while (1) 
	{	
		for (j = 0; j < PWM_RGB_CHANNEL; j++)
		{
			RTK_LOGI("TAG", "pwm_chan_%d \r\n",j);
			for (i = 0; i <= PWM_PERIOD; i++)
			{				
				RTIM_CCRxSet(TIMx[PWM_TIMER], (uint32_t)i, j);				
				//RTK_LOGI("TAG", "pwm_chan_%d pwms = %lu\r\n",j, i);
				DelayUs(PWM_SLEEP);
			}
			DelayMs(100);		
			for (i = 0; i <= PWM_PERIOD; i++)
			{				
				RTIM_CCRxSet(TIMx[PWM_TIMER], (uint32_t)PWM_PERIOD - i, j);
				//RTK_LOGI("TAG", "pwm_chan_%d pwms = %lu\r\n",j, i);
				DelayUs(PWM_SLEEP);
			}			
		}
		
		DelayMs(1000);
	}
	rtos_task_delete(NULL);
}
