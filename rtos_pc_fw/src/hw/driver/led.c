/*
 * led.c
 *
 *  Created on: Dec 7, 2020
 *      Author: baram
 */


#include "led.h"
#include "cli.h"


#ifdef _USE_HW_LED




uint8_t led_tbl[LED_MAX_CH] = {0, };


#ifdef _USE_HW_CLI
static void cliLed(cli_args_t *args);
#endif


bool ledInit(void)
{
  bool ret = true;


#ifdef _USE_HW_CLI
  cliAdd("led", cliLed);
#endif

  return ret;
}

void ledOn(uint8_t ch)
{
  if (ch >= LED_MAX_CH) return;

  led_tbl[ch] = 1;
  printf("LED_CH%d ON\n", ch+1);
}

void ledOff(uint8_t ch)
{
  if (ch >= LED_MAX_CH) return;

  led_tbl[ch] = 0;
  printf("LED_CH%d OFF\n", ch+1);

}

void ledToggle(uint8_t ch)
{
  if (ch >= LED_MAX_CH) return;

  led_tbl[ch] ^= 1;

  if (led_tbl[ch])
  {
    printf("LED_CH%d ON\n", ch+1);
  }
  else
  {
    printf("LED_CH%d OFF\n", ch+1);
  }
}





#ifdef _USE_HW_CLI

void cliLed(cli_args_t *args)
{
  bool ret = false;


  if (args->argc == 3 && args->isStr(0, "toggle") == true)
  {
    uint8_t  led_ch;
    uint32_t toggle_time;
    uint32_t pre_time;

    led_ch      = (uint8_t)args->getData(1);
    toggle_time = (uint32_t)args->getData(2);

    if (led_ch > 0)
    {
      led_ch--;
    }

    pre_time = millis();
    while(cliKeepLoop())
    {
      if (millis()-pre_time >= toggle_time)
      {
        pre_time = millis();
        ledToggle(led_ch);
      }
    }

    ret = true;
  }


  if (ret != true)
  {
    cliPrintf("led toggle ch[1~%d] time_ms\n", LED_MAX_CH);
  }
}


#endif


#endif
