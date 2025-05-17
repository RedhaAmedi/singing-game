#include <stdio.h>
#include <stdlib.h>

#include "driver/adc.h"
#include "esp32/rom/ets_sys.h"
#include "esp_task_wdt.h"

#include "pins.h"
#include "SoundGen.h"
#include "sampler.h"
#include "random.h"

void blinkLED(int ms, int times)
{
    for (int i = 0; i < times; i++)
    {
        setLEDA(1); 
        vTaskDelay(pdMS_TO_TICKS(ms));
        setLEDA(0);
        vTaskDelay(pdMS_TO_TICKS(ms));
    }
}

float absval(float a)
{
    return a > 0 ? a :-a;
}

void app_main() 
{
    initPins();
    while(1)
    {
        printf("\nGames begins! \n");
        blinkLED(40,30);
        int randomFq = getRandomRange(300, 500);
        int actualFq = startSound(randomFq);

        vTaskDelay(pdMS_TO_TICKS(4000));
        stopSound();
        startSampling(6000);
        vTaskDelay(pdMS_TO_TICKS(1000));
        stopSampling();

        float playerFq = getFreq();

        printf("Player freq = %.2f\nActual freq = %d\n", playerFq, actualFq);

        if(absval(playerFq - (float)actualFq) < 100)
        {
            printf("Player wins\n");
            blinkLED(10,20);
        }
        else
        {
            printf("Player looses\n");
            blinkLED(1000, 2);
        }

        vTaskDelay(pdMS_TO_TICKS(3000));
    }
}

