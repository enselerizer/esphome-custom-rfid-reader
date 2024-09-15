```yaml
# example configuration:

text_sensor:
  - platform: custom_rfid_reader
    id: rfid_text_sensor
    name: RFID Tag Code

uart:
  tx_pin: GPIO21 # not used, but must be defined or left on defaults if default pins are not assigned to something else
  rx_pin: GPIO22
  baud_rate: 9600
```