#include <gpio.h>
#include <i2c.h>
#include <printk.h>
#include <uart_polling.h>
#include <unistd.h>
#include <lcd_driver.h>
#include <keypad_driver.h>

#define YELLOW_LED_PORT (0)
#define YELLOW_LED_PIN  (8)
#define BLUE_LED_PORT   (0)
#define BLUE_LED_PIN    (9)

#define BUTTON1_PORT (2)		// PC_7
#define BUTTON1_PIN  (7)
#define BUTTON2_PORT (1)		// PB_6
#define BUTTON2_PIN  (6)


void lazy_delay(unsigned int milliseconds) {
  volatile unsigned int i, j;
  for (i = 0; i < milliseconds; i++) {
    for (j = 0; j < 10000; j++) {
      __asm("NOP");
    }
  }
}

int main() {
  // uart_polling_init(115200);
  //printk("hello world");

  //gpio_init(YELLOW_LED_PORT, YELLOW_LED_PIN, MODE_GP_OUTPUT, OUTPUT_PUSH_PULL, OUTPUT_SPEED_LOW, PUPD_NONE, ALT0);
  //gpio_init(BLUE_LED_PORT, BLUE_LED_PIN, MODE_GP_OUTPUT, OUTPUT_PUSH_PULL, OUTPUT_SPEED_LOW, PUPD_NONE, ALT0);

  //gpio_init(BUTTON1_PORT, BUTTON1_PIN, MODE_INPUT, OUTPUT_PUSH_PULL, OUTPUT_SPEED_LOW, PUPD_PULL_DOWN, ALT0);
  // keypad_init();
  i2c_master_init(80);
  lcd_driver_init();
  
  // printk("LCD CLR");
  // while(1) {
//     // Turn on the LEDs
//  /* gpio_set(YELLOW_LED_PORT, YELLOW_LED_PIN);
//     gpio_set(BLUE_LED_PORT, BLUE_LED_PIN);
//     printk("LEDs ON\n");
//     lazy_delay(1000); // 1 second delay
//     // Turn off the LEDs
//     gpio_clr(YELLOW_LED_PORT, YELLOW_LED_PIN);
//     gpio_clr(BLUE_LED_PORT, BLUE_LED_PIN);
//     printk("LEDs OFF\n");
//     lazy_delay(1000); // 1 second delay
//  */
    
//     //int button1_state = gpio_read(BUTTON1_PORT, BUTTON1_PIN);
//     //printk("BUTTON1 State:%d\n", button1_state);

//     //char test = uart_polling_get_byte();
//     //uart_polling_put_byte(test);
    
//     char key = keypad_read();
//     printk("%c pressed\n", key);
//     lazy_delay(10);
   
  // }
  return 0;
}
