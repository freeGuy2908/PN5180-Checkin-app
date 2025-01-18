# PN5180 Checkin app
A small checkin web app that displays checkin information (ID, Name, Time and Status (IN/OUT)) via the PN5180 RFID module.
## Hardware: 
- ESP32 devkit v1, PN5180 NFC/RFID module, ISO15693 RFID tags
- ESP-32    <--> PN5180 pin mapping:
  
  3.3V      <--> 3.3V
  
  GND       <--> GND
  
  SCLK, 18   --> SCLK
  
  MISO, 19  <--  MISO
  
  MOSI, 23   --> MOSI
  
  SS,  5     --> NSS (=Not SS -> active LOW)
  
  BUSY, 16   <--  BUSY
  
  Reset, 17  --> RST
![image](https://github.com/user-attachments/assets/2febe58f-7169-4c04-ac7a-06d117632880)
