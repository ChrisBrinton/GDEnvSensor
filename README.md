# GDEnvSensor
An ESP8266 based wifi/RFM69 gateway with a display and sensor nodes

This is yet another ESP8266/RFM69 (HCW in this case) gateway type project. It heavily utilizes the excellent work done by 
Xose Perez (https://bitbucket.org/xoseperez/rfm69gw) and Felix Rusu and his Low Power Lab (https://github.com/LowPowerLab).

My main contribution is to add a 128x32 OLED display and create a compact PCB to create a gateway/desk clock device as well
as to compact Felix's Moteino/WeatherMote into a single small device powered either by a 3.7V LIon battery or a AA battery
(with the appropriate 3.3V boost pump).
The diplay code is uses the Adafruit GFX library and Ive modified their SSD1306 driver to support the SSD1305 that this device uses
