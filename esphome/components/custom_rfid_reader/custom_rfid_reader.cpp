#include "esphome/core/log.h"
#include "custom_rfid_reader.h"
#include "esphome/core/log.h"

namespace esphome {
namespace custom_rfid_reader {

static const char *TAG = "custom_rfid_reader.text_sensor";

void CustomRFIDReader::setup() {

}

void CustomRFIDReader::loop() {
    ESP_LOGI(TAG, "hey there");
}

void CustomRFIDReader::dump_config(){
    ESP_LOGCONFIG(TAG, "Empty UART sensor");
}

}  // namespace empty_UART_sensor
}  // namespace esphome