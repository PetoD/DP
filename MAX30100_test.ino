#include <Wire.h>
#include "MAX30100.h"

#define POLL_PERIOD_US                      1E06 / 100
#define SAMPLING_RATE                       MAX30100_SAMPRATE_100HZ

//nastavenie velkosti prudu pre cervenu a infra LED
#define IR_LED_CURRENT                      MAX30100_LED_CURR_33_8MA
#define RED_LED_CURRENT                     MAX30100_LED_CURR_24MA

//#define IR_LED_CURRENT                      MAX30100_LED_CURR_50MA
//#define RED_LED_CURRENT                     MAX30100_LED_CURR_50MA

#define PULSE_WIDTH                         MAX30100_SPC_PW_1600US_16BITS
#define HIGHRES_MODE                        true

MAX30100 sensor;
uint32_t tsLastPollUs = 0;

void setup()
{
    Serial.begin(115200);
    //Serial.print("Initializing MAX30100..");
    if (!sensor.begin()) {
        //Serial.println("FAILED");
        for(;;);
    } else {
        //Serial.println("SUCCESS");
    }

    // Set up the wanted parameters
    sensor.setMode(MAX30100_MODE_SPO2_HR);
    sensor.setLedsCurrent(IR_LED_CURRENT, RED_LED_CURRENT);
    sensor.setLedsPulseWidth(PULSE_WIDTH);
    sensor.setSamplingRate(SAMPLING_RATE);
    sensor.setHighresModeEnabled(HIGHRES_MODE);
}

void loop()
{
    // Using this construct instead of a delay allows to account for the time
    // spent sending data thru the serial and tighten the timings with the sampling
    
    if (micros() < tsLastPollUs || micros() - tsLastPollUs > POLL_PERIOD_US) {
        sensor.update();
        tsLastPollUs = micros();

        Serial.print(sensor.rawIRValue);
        Serial.print('\t');
        Serial.println(sensor.rawRedValue);
        }
        /*unsigned char partID = sensor.getPartId();
        Serial.print(partID);
        Serial.print("\n");*/
}

