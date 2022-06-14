# The Sanctuary Keyboard (Firmware)
A Bluetooth Wireless Mechanical Keyboard - That can be currently built!

Based on the ESP32, the Sanctuary functions as a completely wireless keyboard, that can be designed and built yourself. Rather than using obsolete BLE microcontrollers, an ESP32 was chosen, a cheap and readily available BLE microcontroller. Instructions will be available through an [instructables link](https://www.instructables.com/ESP32-Bluetooth-Mechanical-Keyboard-the-Sanctuary/)
## [Demo Video](https://youtu.be/0jshQPa9tzA)
[![TheSanctuaryDemoVideo](https://img.youtube.com/vi/0jshQPa9tzA/0.jpg)](https://youtu.be/0jshQPa9tzA)

## [Hardware Files Available Here](https://github.com/LegoRocket/Sanctuary-Keyboard-Hardware)

## [Instructions Available Here!](https://www.instructables.com/ESP32-Bluetooth-Mechanical-Keyboard-the-Sanctuary/)

## Firmware

Basic Firmware for The Santuary Wireless Keyboard. Library used for keystrokes is the [ESP32-BLE-Keyboard](https://github.com/T-vK/ESP32-BLE-Keyboard)

All code is included in the "KeyboardFirmwareRev1" folder. Yes, I used the Arduino IDE, but I've tried to document, and separate out the code for legibility.

Based on the ESP32, this is a completely wireless keyboard, to be used however you would like. 

I unfortunately don't have the ability to sell kits or keyboards, but all files and instructions are available in the repo linked above. This repo is purely for the firmware of the keyboard, to allow for others to fork, and modify their own code.

QMK and other pre-existing keyboard firmware are incompatible, leaving my programming skills up to the test. Basic functionality exists, however future features plan to be added, and as the program gets more complex, so does the ability to track changes (hence git). However, I will fully admit that I am not the greatest programmer in the world, and likely don't have time to manage this repo in full, so please feel free to fork it into your own repo.

### Features:
- Full key support
- Multimedia Keys
- Rotary Encoders
- Multiple Device Support (Currently 3)
- RGB Lighting (Currently only Cyan is set)

### TODO:
- Implement Battery monitoring (Requires additional Hardware)
- Implement Different RGB animations
- Implement Colour Brightness (and turn off)
- Implement Software Shutdown (Current solution is a hardware disconnect)

### Updates
Unfortunately I don't have a lot of time on my hands to flesh out the code. I have written enough to make it a daily driver keyboard (I'm typing on the Sanctuary right now), but it means that updates will be very infrequent. Feel free to fork and modify the code to your own ability, as long as it complies within the License provided.

## License Information

Licensed under the GNU GPLv3 license. More information available in the LICENSE.md file.
