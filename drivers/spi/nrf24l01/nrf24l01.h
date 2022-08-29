#ifndef Z_APP_NRF24L01_H
#define Z_APP_NRF24L01_H

#include <zephyr/zephyr.h>
#include <zephyr/device.h>
#include <zephyr/drivers/spi.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/types.h>

/* NRF24L01 commands */
#define NRF24L01_R_REGISTER          0x00
#define NRF24L01_W_REGISTER          0x20
#define NRF24L01_R_RX_PAYLOAD        0x61
#define NRF24L01_W_TX_PAYLOAD        0xa0
#define NRF24L01_FLUSH_TX            0xe1
#define NRF24L01_FLUSH_RX            0xe2
#define NRF24L01_REUSE_TX_PAYLOAD    0xe3
#define NRF24L01_ACTIVATE            0x50
#define NRF24L01_R_RX_PL_WID         0x60
#define NRF24L01_W_ACK_PAYLOAD       0x15
#define NRF24L01_W_TX_PAYLOAD_NO_ACK 0x58
#define NRF24L01_NOP                 0xff

/* NRF24L01 registers */
#define NRF24L01_CONFIG      0x00
#define NRF24L01_EN_AA       0X01
#define NRF24L01_EN_RXADDR   0x02
#define NRF24L01_SETUP_AW    0x03
#define NRF24L01_SETUP_RETR  0x04
#define NRF24L01_RF_CH       0x05
#define NRF24L01_RF_SETUP    0x06
#define NRF24L01_STATUS      0x07
#define NRF24L01_OBSERVE_TX  0x08
#define NRF24L01_CD          0x09
#define NRF24L01_RX_ADDR_P0  0x0a
#define NRF24L01_RX_ADDR_P1  0x0b
#define NRF24L01_RX_ADDR_P2  0x0c
#define NRF24L01_RX_ADDR_P3  0x0d
#define NRF24L01_RX_ADDR_P4  0x0e
#define NRF24L01_RX_ADDR_P5  0x0f
#define NRF24L01_TX_ADDR     0x10
#define NRF24L01_RX_PW_P0    0x11
#define NRF24L01_RX_PW_P1    0x12
#define NRF24L01_RX_PW_P2    0x13
#define NRF24L01_RX_PW_P3    0x14
#define NRF24L01_RX_PW_P4    0x15
#define NRF24L01_RX_PW_P5    0x16
#define NRF24L01_FIFO_STATUS 0x17
#define NRF24L01_DYNPD       0x1c
#define NRF24L01_FEATURE     0x1d

#define NRF24L01_PRIM_RX 0x00
#define NRF24L01_PWR_UP  0x01

#define NRF24L01_RX_DR  0x40
#define NRF24L01_TX_DS  0x20
#define NRF24L01_MAX_RT 0x10

struct nrf24l01_config {
    struct spi_dt_spec spi;
    struct gpio_dt_spec ce_gpio;
    struct gpio_dt_spec int_gpio;
};


#endif //Z_APP_NRF24L01_H
