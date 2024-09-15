# esphome-custom-rfid-reader

This repo contains a solution for making a remote RFID reader for some ESPHome device. 

An RFID reader module itself, for example PN532, usually communicates with microcontroller over SPI or I2C bus. Those buses are not suitable for long distances (anything more than half a meter), so placing your reader module on the wall with microcontroller placed somewhere else, like on a ceiling or near the magnet lock isn't possible. 

But this problem can be solved with an additional microcontroller placed directly inside the reader box on the wall, which will send data from an RFID card over some robust data bus, for example simple current loop UART. 

In this repo you will find an example of arduino program, which sends data from Mifare Classic 1k card over UART, and an external ESPHome component for receiving and decoding data.