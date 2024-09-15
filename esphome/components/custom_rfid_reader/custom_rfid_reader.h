#pragma once

#include "esphome/core/component.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include "esphome/components/uart/uart.h"

namespace esphome
{
  namespace custom_rfid_reader
  {

    enum class ReaderState {NoTag, InvalidTag, ValidTag};

    class CustomRFIDReader : public text_sensor::TextSensor, public Component, public uart::UARTDevice
    {
    public:
      void setup() override;
      void loop() override;
      void dump_config() override;
    protected:
      enum ReaderState last_state_ = ReaderState::NoTag;
      enum ReaderState current_state_ = ReaderState::NoTag;
    };

  } // namespace empty_uart_sensor
} // namespace esphome