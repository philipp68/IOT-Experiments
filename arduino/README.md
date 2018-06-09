# Arduino
Arduino is an amazing maker platform. Lot's of hardware and software componets exist that you can use for your projects.
## Components
### Real Time Clock
If you need to keep track of time, a real time clock is the way to go. Thanks to it's own cell battery, the the real time clock will continue to keep track of time, even if you power down the arduino (ie to save power). When the arduino boots back up it can ask the RTC for the current time, without having to retrieve the time from a time service running in the cloud.
#### DS 1307
The DS 1307 is a handy RTC circuit that offers an I2C interface. Several libraries to connect to this type of RTC exist.
* [Adafruit RTC Lib](https://github.com/adafruit/RTClib)
### Liquid Cristal Display's (LCDs)
Displays are almost always a part of any microcontroller project or embedded system. Fortunately, there are cheap LCDs available with a wide support for multiple microcontroller devices.
#### Nokia 5510/3310
A cheap, popular display is the Nokia 5110/3310 LCD. You might still remember it from the era before smart phones took over the world. These displays are PCD8544-based.
* [Adafruit PCD8554-Nokia-5110 LCD Lib](https://github.com/adafruit/Adafruit-PCD8544-Nokia-5110-LCD-library)
* [Adafruit Core Graphics Library](https://github.com/adafruit/Adafruit-GFX-Library)
