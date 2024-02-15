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

  // Test: one LED
  //gpio_init(GPIO_A, 8, MODE_GP_OUTPUT, OUTPUT_PUSH_PULL, OUTPUT_SPEED_LOW, PUPD_PULL_UP, ALT0);
  //gpio_set(GPIO_A, 8);

  // Test: button input
  // gpio_init(GPIO_A, 8, MODE_GP_OUTPUT, OUTPUT_PUSH_PULL, OUTPUT_SPEED_LOW, PUPD_PULL_UP, ALT0); 
  // gpio_set(GPIO_A, 8); //set PA_A into high
  // gpio_init(GPIO_A, 9, MODE_INPUT, OUTPUT_PUSH_PULL, OUTPUT_SPEED_LOW, PUPD_PULL_DOWN, ALT0); // Read the input
  // while(1){
  //   int read_value = gpio_read(GPIO_A, 9);
  //   printk("%d\n",read_value);
  // }
  
  // 
  
  // while(1) {
  //   char test = uart_polling_get_byte();
  //   uart_polling_put_byte(test);
  // }

  return 0;
}
