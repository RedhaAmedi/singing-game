#include <driver/adc.h>
#include <esp_timer.h>
#include <driver/gpio.h>
#include <soc/adc_channel.h>

// Include a custom header file
#include "sampler.h"

// Define a trigger level for the ADC
#define TRIGGER_LVL 1050

// Declare a timer handle and some variables for sampling
esp_timer_handle_t timerHandle;
uint32_t lastSample = 0;
uint32_t counter;
uint64_t startTime;
uint64_t stopTime;

// Define a callback method for the software timer
void callback(void *args)
{
    // Read a sample from ADC channel 4
    uint32_t sample = adc1_get_raw(ADC1_CHANNEL_4);

    // Check if the sample crosses the trigger level and update the counter
    if (lastSample < TRIGGER_LVL && sample > TRIGGER_LVL)
        counter++;
    else if (lastSample > TRIGGER_LVL && sample < TRIGGER_LVL)
        counter++;

    // Update the last sample
    lastSample = sample;
}

// Function to start the sampling process with a given frequency
void startSampling(int freq)
{
    // Initialize variables
    lastSample = 0;
    counter = 0;

    // Initialize ADC settings for channel 4
    adc_gpio_init(ADC_UNIT_1, ADC_CHANNEL_4);
    adc1_config_width(ADC_WIDTH_12Bit);
    adc1_config_channel_atten(ADC1_CHANNEL_4, ADC_ATTEN_DB_11);

    // Initialize the software timer
    esp_timer_create_args_t timerArgs = {
        .arg = NULL,
        .callback = callback,
        .dispatch_method = ESP_TIMER_TASK,
        .name = "timer",
    };

    // Calculate the sampling frequency based on the provided frequency
    uint64_t sampleFreq = (uint64_t)(1000000. / ((double)freq));

    // Create and start the timer
    ESP_ERROR_CHECK(esp_timer_create(&timerArgs, &timerHandle));
    ESP_ERROR_CHECK(esp_timer_start_periodic(timerHandle, sampleFreq));

    // Record the start time
    startTime = esp_timer_get_time();
}

// Function to stop the software timer
void stopSampling()
{
    esp_timer_stop(timerHandle);
    stopTime = esp_timer_get_time();
}

// Function to calculate and return the sampling frequency
float getFreq()
{
    return ((float)counter) / (2 * (((float)stopTime) - ((float)startTime)) / 1000000.);
}
