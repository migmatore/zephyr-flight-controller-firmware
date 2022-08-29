#include "nrf24l01.h"
#include <zephyr/zephyr.h>

void main() {
    const struct device *dev = DEVICE_DT_GET_ANY(nordic_nrf24l01);

    if (dev == NULL) {
        /* No such node, or the node does not have status "okay". */
        printk("\nError: no device found.\n");
        return;
    }

    if (!device_is_ready(dev)) {
        printk("\nError: Device \"%s\" is not ready; "
               "check the driver initialization logs for errors.\n",
               dev->name);
        return;
    }

    printk("Found device \"%p\", name \"%s\"\n", dev, dev->name);
}