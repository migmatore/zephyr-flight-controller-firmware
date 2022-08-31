#define DT_DRV_COMPAT nordic_nrf24l01

#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(nrf24l01, CONFIG_NRF24L01_LOG_LEVEL);

#include "nrf24l01.h"

struct nrf24l01_data {
    uint32_t foo;
} nrf24l01_data;

static int nrf24l01_spi_read_reg(const struct device *dev, uint8_t addr, uint8_t *out_data, uint8_t len) {
    const struct nrf24l01_config *dev_cfg = dev->config;
    int ret;

    addr |= NRF24L01_R_REGISTER;

    uint8_t cmd_buf[] = {addr};

    const struct spi_buf tx_buf = {
            .buf = cmd_buf, .len = ARRAY_SIZE(cmd_buf),
    };

    const struct spi_buf_set tx = {
            .buffers = &tx_buf, .count = 1U,
    };

    const struct spi_buf rx_buf = {
            .buf = out_data, .len = len,
    };

    const struct spi_buf_set rx = {
            .buffers = &rx_buf, .count = 1U,
    };

    if (addr == NRF24L01_STATUS) {
        cmd_buf[0] = NRF24L01_NOP;
        ret = spi_transceive_dt(&dev_cfg->spi, &tx, &rx);
    } else {
        ret = spi_transceive_dt(&dev_cfg->spi, &tx, &rx);
    }

    return ret;
}

static int nrf24l01_spi_write_reg(const struct device *dev, uint8_t addr, uint8_t data) {
    const struct nrf24l01_config *dev_cfg = dev->config;
    int ret;

    addr |= NRF24L01_W_REGISTER;

    uint8_t cmd_buf[] = {addr, data};

    const struct spi_buf tx_buf[] = {
            { .buf  = cmd_buf, .len = ARRAY_SIZE(cmd_buf), },
    };

    const struct spi_buf_set tx = {
            .buffers = tx_buf, .count = 1U,
    };

    ret = spi_write_dt(&dev_cfg->spi, &tx);

    return ret;
}

static int nrf24l01_init(const struct device *dev) {
    const struct nrf24l01_config *dev_cfg = dev->config;
    struct nrf24l01_data *dev_data = dev->data;

    printk("ce-gpio name: %s pin: %d\n", dev_cfg->ce_gpio.port->name, dev_cfg->ce_gpio.pin);
    printk("int-gpio name: %s pin: %d\n", dev_cfg->int_gpio.port->name, dev_cfg->int_gpio.pin);
    printk("spi name: %s speed: %d\n", dev_cfg->spi.bus->name, dev_cfg->spi.config.frequency);


//    gpio_pin_configure_dt(&dev_cfg->ce_gpio, GPIO_OUTPUT_HIGH);
//    gpio_pin_configure_dt(&dev_cfg->int_gpio, GPIO_OUTPUT_LOW);
    gpio_pin_configure_dt(&dev_cfg->ce_gpio, GPIO_OUTPUT_INIT_HIGH);
    gpio_pin_configure_dt(&dev_cfg->int_gpio, GPIO_OUTPUT_INIT_LOW);

    gpio_pin_set_dt(&dev_cfg->ce_gpio, GPIO_PIN_RESET);

    k_msleep(11);

    printk("ret: %d\n", nrf24l01_spi_write_reg(dev, NRF24L01_CONFIG, NRF24L01_PWR_UP << 1));

    k_msleep(2);

    printk("ret: %d\n", nrf24l01_spi_write_reg(dev, NRF24L01_EN_AA, 0x02));
    k_msleep(2);

    uint8_t d[3];

    printk("ret: %d\n", nrf24l01_spi_read_reg(dev, NRF24L01_CONFIG, d));

    for (uint8_t i = 0; i < 3; i++) {
        printk("0x%x ", d[i]);
    }

    printk("\n");

    return 0;
}

static struct nrf24l01_config nrf24l01_config = {
        .spi = SPI_DT_SPEC_INST_GET(0, SPI_WORD_SET(8), 0),
        .ce_gpio = GPIO_DT_SPEC_INST_GET(0, ce_gpios),
        .int_gpio = GPIO_DT_SPEC_INST_GET(0, int_gpios),
};

//DEVICE_DT_DEFINE(DT_NODELABEL(nrf24l01), &nrf24l01_init, NULL, &data, &nrf24l01_config, APPLICATION,
//                 CONFIG_KERNEL_INIT_PRIORITY_DEVICE, NULL);
DEVICE_DT_INST_DEFINE(0, &nrf24l01_init, NULL, &nrf24l01_data, &nrf24l01_config, APPLICATION,
                      CONFIG_KERNEL_INIT_PRIORITY_DEVICE, NULL);