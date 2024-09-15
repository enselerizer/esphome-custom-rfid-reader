import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart, text_sensor
from esphome.const import ICON_EMPTY, UNIT_EMPTY

DEPENDENCIES = ["uart"]

custom_rfid_reader_ns = cg.esphome_ns.namespace("custom_rfid_reader")
CustomRFIDReader = custom_rfid_reader_ns.class_(
    "CustomRFIDReader", text_sensor.TextSensor, cg.Component, uart.UARTDevice
)

CONFIG_SCHEMA = (
    text_sensor.text_sensor_schema(CustomRFIDReader)
    .extend(uart.UART_DEVICE_SCHEMA)
)


async def to_code(config):
    var = await text_sensor.new_text_sensor(config)
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)
