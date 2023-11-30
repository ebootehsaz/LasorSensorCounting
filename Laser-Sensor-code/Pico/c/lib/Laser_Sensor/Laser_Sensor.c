#include "Laser_Sensor.h"

void Laser_Sensor()
{
    DEV_Module_Init();
    while(1)
    {
        if(DEV_Digital_Read(DOUT_PIN) == 0)
        {
            printf("The Obstacles is near!\n");      
        }
        else
           printf("The Obstacles is far!\n");
           
        DEV_Delay_ms(1000); 
    }

}
