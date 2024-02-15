#include <gpio.h>
#include <keypad_driver.h>
#include <unistd.h>


#define COL1_PORT  0
#define COL2_PORT  0
#define COL3_PORT  2
#define COL1_PIN   15
#define COL2_PIN   13
#define COL3_PIN   13

#define ROW1_PORT  0
#define ROW2_PORT  2
#define ROW3_PORT  2
#define ROW4_PORT  1
#define ROW1_PIN   14
#define ROW2_PIN   15
#define ROW3_PIN   14
#define ROW4_PIN   7

#define NUM_ROWS   4
#define NUM_COLS   3

// Placeholder for actual GPIO port and pin numbers
const int row_pins[NUM_ROWS] = {ROW1_PIN, ROW2_PIN, ROW3_PIN, ROW4_PIN};
const int col_pins[NUM_COLS] = {COL1_PIN, COL2_PIN, COL3_PIN};
const int row_ports[NUM_ROWS] = {ROW1_PORT, ROW2_PORT, ROW3_PORT, ROW4_PORT};
const int col_ports[NUM_COLS] = {COL1_PORT, COL2_PORT, COL3_PORT};

const char key_map[NUM_ROWS][NUM_COLS] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}
};

void keypad_init(){
  
    // columns as output
    gpio_init(COL1_PORT, COL1_PIN, MODE_GP_OUTPUT, OUTPUT_PUSH_PULL, OUTPUT_SPEED_LOW, PUPD_NONE, ALT0);
    gpio_init(COL2_PORT, COL2_PIN, MODE_GP_OUTPUT, OUTPUT_PUSH_PULL, OUTPUT_SPEED_LOW, PUPD_NONE, ALT0);
    gpio_init(COL3_PORT, COL3_PIN, MODE_GP_OUTPUT, OUTPUT_PUSH_PULL, OUTPUT_SPEED_LOW, PUPD_NONE, ALT0);

    //rows as input 
    gpio_init(ROW1_PORT, ROW1_PIN, MODE_INPUT, OUTPUT_PUSH_PULL, OUTPUT_SPEED_LOW, PUPD_PULL_DOWN, ALT0);
    gpio_init(ROW2_PORT, ROW2_PIN, MODE_INPUT, OUTPUT_PUSH_PULL, OUTPUT_SPEED_LOW, PUPD_PULL_DOWN, ALT0);
    gpio_init(ROW3_PORT, ROW3_PIN, MODE_INPUT, OUTPUT_PUSH_PULL, OUTPUT_SPEED_LOW, PUPD_PULL_DOWN, ALT0);
    gpio_init(ROW4_PORT, ROW4_PIN, MODE_INPUT, OUTPUT_PUSH_PULL, OUTPUT_SPEED_LOW, PUPD_PULL_DOWN, ALT0); 
    
    gpio_set(COL1_PORT, COL1_PIN);
    gpio_set(COL2_PORT, COL2_PIN);
    gpio_set(COL3_PORT, COL3_PIN);
    return;
}

char keypad_read() {
    // set all columns high
   
    for (int col = 0; col < NUM_COLS; col++) {
        // Set the current column to LOW
        gpio_clr(col_ports[col], col_pins[col]);
	for (int row = 0; row < NUM_ROWS; row++) {
	    //read the current row
	    if (gpio_read(row_ports[row], row_pins[row]) == 0) {
	        gpio_set(row_ports[row], row_pins[row]);
		return key_map[row][col];
            }
	    gpio_set(col_ports[col], col_pins[col]);
	}
    }
    return '\0';
}

