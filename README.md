# Arduino I2C US2066 OLED

Arduino library for using US2066 OLED displays through I2C

## Platform

This library is written and tested for [Arduino Pico](https://arduino-pico.readthedocs.io/en/latest/) 
with a NewHaven [NHD-0216AW-IB3](https://newhavendisplay.com/2x16-character-blue-modular-oled-arduino-ready-with-i2c-interface/) display

## Usage

```C++
// Minimal example for Raspberry Pi Pico and NHD-0216AW-IB3 Display
#include <WireOled.h>


WireOled display;


void setup() {
    if (display.detect()) {
        display.init();
        display.write("Frangitron");
        display.write(1, 0, "Hello");
    }
}


void loop() {
    display.setActive(true);
    
    display.setCursorBlinking(false);
    delay(500);
    display.setCursorBlinking(true);
    delay(500);
    display.setContrast(0);
    delay(500);
    display.setContrast(255);
    delay(500);
    
    display.setActive(false);
    delay(500);

    display.pollScreensaver();  // turns of screen if inactive for more than 30s
}
```

## Notes

This library was written from the following resources
- https://support.newhavendisplay.com/hc/en-us/articles/4414485495703--US2066
- https://newhavendisplay.com/content/specs/NHD-0216AW-IB3.pdf
- https://github.com/NewhavenDisplay/NHD_US2066

### Todo

- [ ] Use namespace and const expression instead of #define
- [ ] Allow to choose address
- [ ] Allow 4 rows displays
- [ ] Allow to change SEG pins [see issue from official lib](https://github.com/NewhavenDisplay/NHD_US2066/issues/1)
