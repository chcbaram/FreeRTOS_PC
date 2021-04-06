/*
 * main.c
 *
 *  Created on: Dec 6, 2020
 *      Author: baram
 */


#include "main.h"


static void threadMain(void const *argument);


void exitISR(int sig)
{
  apExit();
}

int main(void)
{
  signal(SIGINT, exitISR);
  setbuf(stdout, NULL);

  vTraceEnable( TRC_START );

  hwInit();
  apInit();


  osThreadDef(threadMain, threadMain, _HW_DEF_RTOS_THREAD_PRI_MAIN, 0, _HW_DEF_RTOS_THREAD_MEM_MAIN);
  if (osThreadCreate(osThread(threadMain), NULL) != NULL)
  {
    logPrintf("threadMain \t\t: OK\r\n");
  }
  else
  {
    logPrintf("threadMain \t\t: Fail\r\n");
    while(1);
  }

  osKernelStart();

  return 0;
}

static void threadMain(void const *argument)
{
  apMain();
}
