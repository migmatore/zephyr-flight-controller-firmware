#list(APPEND ZEPHYR_EXTRA_MODULES ${CMAKE_CURRENT_SOURCE_DIR}/drivers/)
set(ZEPHYR_EXTRA_MODULES ${CMAKE_CURRENT_SOURCE_DIR}/drivers/spi/nrf24l01)
cmake_minimum_required(VERSION 3.20.0)

#set(ZEPHYR_BASE "~/zephyrproject/zephyr/")
set(BOARD nucleo_f303re)
set(CONF_FILE prj.conf)
set(DTC_OVERLAY_FILE overlay/bme280.overlay)
list(APPEND DTC_OVERLAY_FILE overlay/nrf24l01.overlay)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(z_app)
target_sources(app PRIVATE src/main.c)
