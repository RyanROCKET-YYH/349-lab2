#include <gpio.h>
#include <i2c.h>
#include <printk.h>
#include <uart_polling.h>
#include <unistd.h>
#include <lcd_driver.h>
#include <keypad_driver.h>


int main() {
  uart_polling_init(115200);
  printk("hello world");

  gpio_init(GPIO_A, 8, MODE_GP_OUTPUT, OUTPUT_PUSH_PULL, OUTPUT_SPEED_LOW, PUPD_NONE, ALT0);
  gpio_set(GPIO_A, 8);

  while(1) {
    char test = uart_polling_get_byte();
    uart_polling_put_byte(test);
  }

  return 0;
}
