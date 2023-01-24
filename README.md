# SD Card CID Reader (Arduino)
Quick and dirty SD Card CID reader. 

## Hardware
- Arduino Nano (or Uno or...)
- SD card holder (SPI interface)

## Software
- Simple Arduino .ino file
- Arduino SD Lib is necessary (included) [Arduino SD Library](https://www.arduino.cc/reference/en/libraries/sd/)

## Description
This software is based on an Arduino SD.h Library example.
The example shows how to use the utility libraries on which the
SD library is based on to get information about the SD card.
Very useful to test a card when you are not sure if it works or not.
The pin numbers reflect the standard SPI pins of the Uno and Nano models.

**Circuitry**:
The SD card is connected to the SPI bus as follows:
- SDO - Pin 11 on the Arduino Uno/Duemilanove/Diecimila.
- SDI - Pin 12 on Arduino Uno/Duemilanove/Diecimila
- CLK - pin 13 at Arduino Uno/Duemilanove/Diecimila
- CS - depends on your SD card shield or module.
