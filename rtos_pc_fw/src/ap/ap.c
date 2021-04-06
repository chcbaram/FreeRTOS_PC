/*
 * ap.c
 *
 *  Created on: Dec 6, 2020
 *      Author: baram
 */


#include "ap.h"



static void threadLed(void const *argument);


void apInit(void)
{
  osThreadDef(threadLed, threadLed, _HW_DEF_RTOS_THREAD_PRI_LED, 0, _HW_DEF_RTOS_THREAD_MEM_LED);
  if (osThreadCreate(osThread(threadLed), NULL) != NULL)
  {
    logPrintf("threadLed \t\t: OK\r\n");
  }
  else
  {
    logPrintf("threadLed \t\t: Fail\r\n");
    while(1);
  }
}

void apMain(void)
{
  uint32_t pre_time;


  pre_time = millis();
  while(1)
  {
    if (millis()-pre_time >= 500)
    {
      pre_time = millis();
      ledToggle(_DEF_LED1);
    }
  }
}

static void threadLed(void const *argument)
{
  while(1)
  {
    ledToggle(_DEF_LED2);
    delay(100);
  }
}

void apExit(void)
{
  printf("\nexit\n");
  exit(0);
}
