#ifndef MAX30100_H
#define MAX30100_H

#include <stdint.h>

#include "MAX30100_Registers.h"

#define DEFAULT_MODE                MAX30100_MODE_HRONLY
#define DEFAULT_SAMPLING_RATE       MAX30100_SAMPRATE_100HZ
#define DEFAULT_PULSE_WIDTH         MAX30100_SPC_PW_1600US_16BITS
#define DEFAULT_RED_LED_CURRENT     MAX30100_LED_CURR_11MA
#define DEFAULT_IR_LED_CURRENT      MAX30100_LED_CURR_11MA
#define EXPECTED_PART_ID            0x11

#define I2C_BUS_SPEED               400000UL

class MAX30100 {
public:
    MAX30100();
    bool begin();

    //set functions
    void setMode(Mode mode);
    void setLedsPulseWidth(LEDPulseWidth ledPulseWidth);
    void setSamplingRate(SamplingRate samplingRate);
    void setLedsCurrent(LEDCurrent irLedCurrent, LEDCurrent redLedCurrent);
    void setHighresModeEnabled(bool enabled);

    //get functions
    uint8_t getMode();
    
    void update();
    void startTemperatureSampling();
    bool isTemperatureReady();
    float retrieveTemperature();
    void shutdown();
    void resume();
    uint8_t getPartId();

    uint16_t rawIRValue;
    uint16_t rawRedValue;

private:
    uint8_t readRegister(uint8_t address);
    void writeRegister(uint8_t address, uint8_t data);
    void burstRead(uint8_t baseAddress, uint8_t *buffer, uint8_t length);
    void readFifoData();
};

#endif

