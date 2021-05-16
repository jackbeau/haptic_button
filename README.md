# Car Haptic Feedback Simulator

Reads value of pressure applied on force resistive sensor and applies moving average. Detects short or long press and delivers haptic feedback through linear resonant actuator.

Used to integrate force sensor in car steering wheel to explore new means of interacting with car entertainment systems.

For 2021 Imperial HCDE Design Engineering project

## Software requirements

[Arduino IDE](https://www.arduino.cc/en/software)

[movingAvg Arduino Library](https://www.arduino.cc/reference/en/libraries/movingavg/)

[Adafruit_DRV2605 Arduino Library](https://github.com/adafruit/Adafruit_DRV2605_Library)

[ESP8266 Board Manager](https://github.com/esp8266/Arduino)

## Hardware
+ ESP8266
+ [DRV2605L Haptic Motor Controller](https://coolcomponents.co.uk/products/drv2605l-haptic-motor-controller?utm_campaign=shipping-confirmation-email&utm_medium=email&utm_source=OrderlyEmails&utm_content=product)
+ [Force Sensitive Resistor](https://coolcomponents.co.uk/products/force-sensitive-resistor-0-5-inch?utm_campaign=shipping-confirmation-email&utm_medium=email&utm_source=OrderlyEmails&utm_content=product)
+ [Precision Haptic 10mm Linear Resonant Actuator](https://www.precisionmicrodrives.com/product/c10-100-10mm-linear-resonant-actuator-4mm-type)
+ 3.3 kΩ resistor
+ Breadboard

Image of hardware setup:

[Hardware Setup Picture]: https://github.com/jackbeau/haptic_button/Images/hardware_picture.jpg

Wiring diagram:

[Wiring diagram]: https://github.com/jackbeau/haptic_button/Images/hardware_picture.jpg