#include "WireOled.h"


WireOled::WireOled() {}
WireOled::~WireOled() {}


void WireOled::init(struct WireOledConfig config) {
    mConfig = config;
    init();
}


void WireOled::init() {
    pinMode(mConfig.pinReset, OUTPUT);
    digitalWrite(mConfig.pinReset, HIGH);

    delay(100);
    Wire.begin();

    command(0x2A);  // function set (extended command set)
    command(0x71);  // function selection A, disable internal Vdd regualtor
    data(0x00);

    command(0x28);  // function set (fundamental command set)
    command(0x08);  // display off, cursor off, blink off

    command(0x2A);  // function set (extended command set)
    command(0x79);  // OLED command set enabled
    command(0xD5);  // set display clock divide ratio/oscillator frequency
    command(0x70);  // set display clock divide ratio/oscillator frequency
    command(0x78);  // OLED command set disabled

    command(mConfig.rowMode);// extended function set (4/2-lines)
    command(0x06);  // COM SEG direction

    command(0x72);  // function selection B, disable internal Vdd regualtor
    data(0x00);         // ROM CGRAM selection

    command(0x2A);  // function set (extended command set)
    command(0x79);  // OLED command set enabled
    command(0xDA);  // set SEG pins hardware configuration

    // TODO: check other doc for other screens
    command(0x00);  // set SEG pins ... NOTE: When using NHD-0216AW-XB3 or NHD_0216MW_XB3 change to (0x00)

    command(0xDC);  // function selection C
    command(0x00);  // function selection C
    command(0x81);  // set contrast control
    command(0x7F);  // set contrast control
    command(0xD9);  // set phase length
    command(0xF1);  // set phase length
    command(0xDB);  // set VCOMH deselect level
    command(0x40);  // set VCOMH deselect level
    command(0x78);  // OLED command set disabled

    command(0x28);  // function set (fundamental command set)
    command(0x01);  // clear display
    command(0x80);  // set DDRAM address to 0x00
    command(0x0C);  // display ON

    delay(100);
}


void WireOled::setActive(bool isActive) {
    if (isActive) {
        mState |= STATE_ON;
    } else {
        mState &= ~STATE_ON;
    }
    applyState();
}


void WireOled::setContrast(uint8_t contrast) {
    command(0x2A);
    command(0x79);      // OLED command set
    command(0x81);      // contrast
    command(contrast);
    command(0x78);      // exit command set
    command(0x28);
}


void WireOled::setCursorBlinking(bool isBlinking) {
    if(isBlinking) {
        mState |= STATE_CURSOR_BLINKING;
    } else {
        mState &= ~STATE_CURSOR_BLINKING;
    }
    applyState();
}


void WireOled::clear() {
    command(0x01);
}


void WireOled::home() {
    move(0,0);
}


void WireOled::move(uint8_t row, uint8_t col) {
    int row_offset[] = { 0x00, 0x40 }; // TODO: 4 rows ?
    command(0x80 | (col + row_offset[row]));
}


void WireOled::write(char c) {
    data(c);
}


void WireOled::write(const String &s) {
    int i = 0;
    while (s[i]) {
        data(s[i]);
        i++;
    }
}


void WireOled::write(uint8_t row, uint8_t col, const String &s) {
    move(row, col);
    write(s);
}


void WireOled::command(unsigned char command) {
    Wire.beginTransmission(mConfig.addr);
    Wire.write(MODE_COMMAND);
    Wire.write(command);
    Wire.endTransmission();
}


void WireOled::data(unsigned char data) {
    Wire.beginTransmission(mConfig.addr);
    Wire.write(MODE_DATA);
    Wire.write(data);
    Wire.endTransmission();
}


void WireOled::applyState() {
    command( 0x08 | mState );
}
