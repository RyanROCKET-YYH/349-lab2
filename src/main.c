#include <gpio.h>
#include <i2c.h>
#include <printk.h>
#include <uart_polling.h>
#include <unistd.h>
#include <lcd_driver.h>
#include <keypad_driver.h>


#define CORRECT_PASSCODE '#349'
#define PASSCODE_LENGTH   (4)

void lazy_delay(unsigned int milliseconds) {
  volatile unsigned int i, j;
  for (i = 0; i < milliseconds; i++) {
    for (j = 0; j < 10000; j++) {
      __asm("NOP");
    }
  }
}

int strcmp(const char *s1, const char *s2) {
  while (*s1 && (*s1 == *s2)) {
    s1++;
    s2++;
  }
  return *(const unsigned char*)s1 - *(const unsigned char*)s2;

}

int main() {
  uart_polling_init(115200);
  keypad_init();
  //printk("hello world");
  // BLUE LED (D2)
  gpio_init(GPIO_A, 10, MODE_GP_OUTPUT, OUTPUT_PUSH_PULL, OUTPUT_SPEED_LOW, PUPD_NONE, ALT0);
  // RED LED (D4)
  gpio_init(GPIO_B, 5, MODE_GP_OUTPUT, OUTPUT_PUSH_PULL, OUTPUT_SPEED_LOW, PUPD_NONE, ALT0);
  // "ENTER" BUTTON (D6)
  gpio_init(GPIO_B, 10, MODE_INPUT, OUTPUT_PUSH_PULL, OUTPUT_SPEED_LOW, PUPD_PULL_UP, ALT0);
  // "LOCK" BUTTON (B1)
  gpio_init(GPIO_C, 13, MODE_INPUT, OUTPUT_PUSH_PULL, OUTPUT_SPEED_LOW, PUPD_PULL_UP, ALT0);
  // keypad_init();
  i2c_master_init(80);
  lcd_driver_init();
  lcd_clear();
  printk("Enter 'Start' to begin:\n");
  uint8_t start = 0;
  while(!start) {
    char input[5] = {0}; // buffer for start
    for (int i = 0; i < 5; i++) {
      input[i] = uart_polling_get_byte();
      uart_polling_put_byte(input[i]);
    }
    input[5] = '\0';
    if (strcmp(input, "Start") == 0) {
      start = 1;
      printk("\n What's your password?\n");
    } else {
      start = 0;
      printk("\n Enter 'Start' to begin:\n");
    }
  }

  char passcode[PASSCODE_LENGTH] = {0};
  uint8_t index = 0;
  uint8_t is_locked = 1;
  while(1) {
    gpio_set(GPIO_B, 5);
    char key = keypad_read();
    if (key != '\0') {
      char key_pressed[2] = {key, '\0'};
      lcd_print(key_pressed);
    }
    
    // Turn on the LEDs
    // gpio_set(GPIO_A, 10);
    // gpio_set(GPIO_B, 5);
    // printk("LEDs ON\n");
    // lazy_delay(1000); // 1 second delay
    // // Turn off the LEDs
    // gpio_clr(GPIO_A, 10);
    // gpio_clr(GPIO_B, 5);
    // printk("LEDs OFF\n");
    // lazy_delay(1000); // 1 second delay

    
    // int button1_state = gpio_read(GPIO_B, 10);
    // int button2_state = gpio_read(GPIO_C, 13);
    // printk("BUTTON1 State:%d\n", button1_state);  // pull up too
    // printk("BUTTON2 State:%d\n", button2_state); // 1 when not pressed, 0 pressed pull up
    // lazy_delay(100);
    // char input = uart_polling_get_byte();
//     uart_polling_put_byte(input);
    
   
  }
  return 0;
}
