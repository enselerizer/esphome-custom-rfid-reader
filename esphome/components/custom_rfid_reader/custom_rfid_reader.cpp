#include "esphome/core/log.h"
#include "custom_rfid_reader.h"

namespace esphome {
namespace custom_rfid_reader {

static const char *TAG = "custom_rfid_reader.sensor";

void CustomRFIDReader::setup() {

}

void CustomRFIDReader::update() {

}

void CustomRFIDReader::loop() {

}

void CustomRFIDReader::dump_config(){
    ESP_LOGCONFIG(TAG, "Empty UART sensor");
}

}  // namespace empty_UART_sensor
}  // namespace esphome