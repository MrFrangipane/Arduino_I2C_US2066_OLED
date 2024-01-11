#ifndef ARDUINO_I2C_US2066_OLED_WIREOLED_H
#define ARDUINO_I2C_US2066_OLED_WIREOLED_H

#include "Arduino.h"
#include "Wire.h"


#define DEFAULT_ADDRESS 0x3c
#define DEFAULT_PIN_RESET 3
#define MODE_COMMAND 0x80
#define MODE_DATA 0x40
#define ROW_MODE_2ROWS 0x08

#define STATE_ON 0x04
#define STATE_CURSOR_BLINKING 0x01


struct WireOledConfig {
    short pinReset { DEFAULT_PIN_RESET };
    uint8_t rowMode { ROW_MODE_2ROWS };
    uint8_t addr { DEFAULT_ADDRESS };
};


class WireOled {
public:
    WireOled();
    ~WireOled();

    void init();
    void init(const WireOledConfig config);
    void setActive(bool isActive);
    void setContrast(uint8_t contrast);
    void setCursorBlinking(bool isBlinking);
    void clear();
    void home();
    void move(uint8_t row, uint8_t col);
    void write(char c);
    void write(const String &s);
    void write(uint8_t row, uint8_t col, const String &s);

private:
    WireOledConfig mConfig;
    uint8_t mState = STATE_ON;

    void command(unsigned char command);
    void data(unsigned char data);
    void applyState();
};


#endif //ARDUINO_I2C_US2066_OLED_WIREOLED_H
