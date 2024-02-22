#include <i2c.h>
#include <lcd_driver.h>
#include <unistd.h>

#define I2C_SLAVE_ADDR 0x4E     // 7 bit address

void lcd_driver_init(){
    uint8_t LCD_ADDR = I2C_SLAVE_ADDR; 
    uint8_t i2c_write_buf[4];
    // Prepare the upper half : 0b0011 with control bits being 1100 (1=1, E = 1, RW=0, RS=0)
    // RS is set low since it's an instruction
    i2c_write_buf[0] = 0b0011 << 4 | 0b1100;
    // Repeat with E toggled to 0
    i2c_write_buf[1] = 0b0011 << 4 | 0b1000;
    i2c_master_write(i2c_write_buf, 2, LCD_ADDR);   // Function set
    i2c_master_write(i2c_write_buf, 2, LCD_ADDR);   // Function set
    i2c_master_write(i2c_write_buf, 2, LCD_ADDR);   // Function set
   
    i2c_write_buf[0] = 0b0010 << 4 | 0b1100;
    i2c_write_buf[1] = 0b0010 << 4 | 0b1000;
    i2c_master_write(i2c_write_buf, 2, LCD_ADDR);   // Function set (set interface to 4 bits long)
   
    // clear display
    i2c_write_buf[0] = 0b0000 << 4 | 0b1100;
    i2c_write_buf[1] = 0b0000 << 4 | 0b1000;
    i2c_write_buf[2] = 0b0001 << 4 | 0b1100;
    i2c_write_buf[3] = 0b0001 << 4 | 0b1000;
    i2c_master_write(i2c_write_buf, 4, LCD_ADDR);
    }

void lcd_print(char *input){
    (void) input;
    return;
}

void lcd_set_cursor(uint8_t row, uint8_t col){
    (void) row;
    (void) col;
}

void lcd_clear(){
    return;
}
