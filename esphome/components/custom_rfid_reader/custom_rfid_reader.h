#pragma once

#include "esphome/core/component.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include "esphome/components/uart/uart.h"

namespace esphome
{
  namespace custom_rfid_reader
  {

    class CustomRFIDReader : public text_sensor::TextSensor, public Component, public uart::UARTDevice
    {
    public:
      CustomRFIDReader(UARTComponent *parent) : UARTDevice(parent);

      void setup() override;
      void loop() override;
      void dump_config() override;
    };

  } // namespace empty_uart_sensor
} // namespace esphome