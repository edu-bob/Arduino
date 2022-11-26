# Dual LED eyes pulsing and blinking
This code runs on cheap clone Arduino Pro Mini and controls two LEDs that are the eyes of my Halloween characters.
The eyes pulse at somewhat random times and rates, and occasionally blink once or twice.
 For a Arduino Pro Micro ATmega32U4 5V/16MHz Module Board
 * https://www.amazon.com/dp/B019SXN84E for the device
 * https://learn.sparkfun.com/tutorials/qwiic-pro-micro-usb-c-atmega32u4-hookup-guide/setting-up-arduino for the board defs
 
 Normally, in idle state, the eyes pulse at somewhat random intervals.  Occasionally they blink once or twice.
 
 Structure:
 * Eye objects = independent control of each eye.  In hindsight, having independent eyes was a hassle
 * RandCache - a chaching layer for random numbers, so that each eye can get the same random timing value.
