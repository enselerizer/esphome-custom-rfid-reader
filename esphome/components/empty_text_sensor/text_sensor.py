import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import text_sensor

empty_text_sensor_ns = cg.esphome_ns.namespace("empty_text_sensor")
EmptyTextSensor = empty_text_sensor_ns.class_(
    "EmptyTextSensor", text_sensor.TextSensor, cg.Component
)

CONFIG_SCHEMA = text_sensor.text_sensor_schema(EmptyTextSensor).extend(
    cv.COMPONENT_SCHEMA
)


async def to_code(config):
    var = await text_sensor.new_text_sensor(config)
    await cg.register_component(var, config)
