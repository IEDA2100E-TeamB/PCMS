# Parcel Condition Monitoring System (PCMS)

## Branches:
- master: stable release (PIC: Alex)
- dev: development and merging test (PIC: Alex)
- dev_sensor: Part A: sensor system (PIC: Alex)
- **TBD**: Part B: parcel to gateway communication (PIC: Tommy)
- GPS_GPRS: Part C: GNSS system & parcel to server communication (PIC: Hojin)

## Development environment:
- Board:
  - ~~Arduino UNO R3~~
  - NodeMCU-32S
  - ESP32-DevKitC
- Framework: Arduino
- IDE:
  - editor: [VSCode](https://code.visualstudio.com/)
  - extensions:
    -  [PlatformIO](https://platformio.org/)
    -  [C/C++](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)

## Useful reference websites:
- PlatformIO:
  - [Development Platform: Espressif 32](https://docs.platformio.org/en/latest/platforms/espressif32.html)
  - [Development Board: NodeMCU-32S](https://docs.platformio.org/en/latest/boards/espressif32/nodemcu-32s.html) (the variant given to Hojin)
  - [Development Board: ESP32-DevKitC](https://docs.platformio.org/en/latest/boards/espressif32/esp32dev.html) (the variant given to Tommy)
- Espressif (Official Chip Manufacturer):
  - [Development Framework: Arduino](https://docs.espressif.com/projects/arduino-esp32/en/latest/) (currently using)
  - [Development Framework: ESP-IDF](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/index.html) (**not** using but contains useful information)
  - [FAQ](https://docs.espressif.com/projects/espressif-esp-faq/en/latest/index.html)
- Ai-Thinker
  - [Development Board: NodeMCU-32S](https://docs.ai-thinker.com/en/esp32)
- HuaRobot
  - [Development Board: ESP32-DevKitC](http://www.china-legends.cn/index.php?m=content&c=index&a=show&catid=15&id=28)
