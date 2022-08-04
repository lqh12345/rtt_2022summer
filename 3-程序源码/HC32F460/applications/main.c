/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 * Copyright (c) 2022, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-04-28     CDT          first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <beep.h>

/*****************************/
//
/* defined the LED_GREEN pin: PD4 */
#define LED_BLUE_PIN GET_PIN(D, 6)
#define LED_YELLOW_PIN GET_PIN(D, 5)
#define LED_GREEN_PIN GET_PIN(D, 4)
#define LED_RED_PIN GET_PIN(D, 3)

#define beep_PIN GET_PIN(B, 14)

//#define KEYOUT1 GET_PIN(D, 39)
#define K GET_PIN(D, 13)
#define K1 GET_PIN(D, 8)
#define K2 GET_PIN(D, 9)
#define K3 GET_PIN(D, 10)
#define K4 GET_PIN(D, 11)
#define FAN GET_PIN(D, 14)

extern uint8_t temp_dht11; //在dht11_sample.c中定义，为采集到的温度数值
extern uint8_t humi_dht11; //在dht11_sample.c中定义，为采集到的湿度数值
//uint8_t new_humi_dht11;
//uint8_t new_temp_dht11;

int main(void)
{
    uint8_t a,b,c,d,k_reset;
    /* set LED_GREEN_PIN pin mode to output */
    rt_pin_mode(LED_GREEN_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(LED_RED_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(LED_YELLOW_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(LED_BLUE_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(FAN, PIN_MODE_OUTPUT);
    beep_init(beep_PIN, PIN_LOW);

//    rt_pin_mode(KEYOUT1, PIN_MODE_OUTPUT);
    rt_pin_mode(K, PIN_MODE_INPUT);
    rt_pin_mode(K1, PIN_MODE_INPUT);
    rt_pin_mode(K2, PIN_MODE_INPUT);
    rt_pin_mode(K3, PIN_MODE_INPUT);
    rt_pin_mode(K4, PIN_MODE_INPUT);

//    rt_pin_write(KEYOUT1, PIN_HIGH);

    while (1)
    {
     a = rt_pin_read(K1);
     b = rt_pin_read(K2);
     c = rt_pin_read(K3);
     d = rt_pin_read(K4);
     k_reset = rt_pin_read(K);
     rt_kprintf("a:%d,b:%d,c:%d,d:%d,k_reset:%d\n" ,a,b,c,d,k_reset);
     rt_thread_mdelay(500);
/***********************key***************************/
    if(k_reset == 0)
    {
        humi_dht11 = 50;
        temp_dht11 = 28;
        rt_kprintf("temp and humi is reset.\n");
        rt_thread_mdelay(1000);
    }
    if(a == 0)
    {
        humi_dht11 += 20;
        rt_kprintf("temp:%d, humi:%d\n" ,temp_dht11, humi_dht11);
        rt_thread_mdelay(1000);
    }
    if(b == 0)
    {
        humi_dht11 -= 20;
        rt_kprintf("temp:%d, humi:%d\n" ,temp_dht11, humi_dht11);
        rt_thread_mdelay(1000);
    }
    if(c == 0)
    {
        temp_dht11 += 10;
        rt_kprintf("temp:%d, humi:%d\n" ,temp_dht11, humi_dht11);
        rt_thread_mdelay(1000);
    }
    if(d == 0)
    {
        temp_dht11 -= 10;
        rt_kprintf("temp:%d, humi:%d\n" ,temp_dht11, humi_dht11);
        rt_thread_mdelay(1000);
    }
/***********************humi_dht11***************************/
        if (humi_dht11 >40 && humi_dht11 < 60){
            rt_pin_write(LED_YELLOW_PIN, PIN_LOW);
            rt_pin_write(LED_BLUE_PIN, PIN_LOW);
           rt_thread_mdelay(500);
           beep_stop();
       }
        else if(humi_dht11 >= 60) {
           rt_pin_write(LED_YELLOW_PIN, PIN_HIGH);
           beep(3, 1000, 50, 0);
           rt_thread_mdelay(500);
//           beep_stop();
       }
        else {
           rt_pin_write(LED_BLUE_PIN, PIN_HIGH);
           beep(3, 1000, 70, 2500);
           rt_thread_mdelay(500);
//           beep_stop();
       }
/***********************temp_dht11***************************/
        if (temp_dht11 >25 && temp_dht11 < 30){
            rt_pin_write(LED_RED_PIN, PIN_LOW);
            rt_pin_write(LED_GREEN_PIN, PIN_LOW);
            rt_pin_write(FAN, PIN_LOW);
           rt_thread_mdelay(500);
           beep_stop();
       }
        else if(temp_dht11 >= 30) {
           rt_pin_write(LED_RED_PIN, PIN_HIGH);
           rt_pin_write(FAN, PIN_HIGH);
           beep(1, 800, 100, 0);
           rt_thread_mdelay(500);
//           beep_stop();
       }
        else {
           rt_pin_write(LED_GREEN_PIN, PIN_HIGH);
           beep(20, 1000, 50, 2000);
           rt_thread_mdelay(500);
//           beep_stop();
       }
    }
}



