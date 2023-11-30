'''
******************************************************************************
  * @file    MQ5 Gas Sensor.py
  * @author  Waveshare Team
  * @version 
  * @date    2021-02-08
  * @brief   MQ5 Gas Sensor
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, WAVESHARE SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  ******************************************************************************
'''


from machine import Pin,ADC
import utime

DIN = Pin(22,Pin.IN)

while True :
    if(DIN.value() == 1) :
        print("The Obstacles is far!")
    else :
        print("The Obstacles is near!")
     

    utime.sleep(0.5)
        
        
        
        


