#include <gpio.h>
#include <i2c.h>
#include <printk.h>
#include <uart_polling.h>
#include <unistd.h>
#include <lcd_driver.h>
#include <keypad_driver.h>


int main() {
  uart_polling_init(115200);

  while(1) {
    char test = uart_polling_get_byte();
    uart_polling_put_byte(test);
  }

  return 0;
}
