#include <i2c.h>
#include <lcd_driver.h>
#include <unistd.h>


#define I2C_SLAVE_ADDR_W 0x4E   // 7 bit address
#define I2C_SLAVE_ADDR_R 0x4F

void lcd_driver_init(){
    uint8_t LCD_ADDR = I2C_SLAVE_ADDR_W; 
    uint8_t i2c_write_buf[4];
    // Prepare the upper half : 0b0011 with control bits being 1100 (1=1, E = 1, RW=0, RS=0)
    // RS is set low since it's an instruction
    i2c_write_buf[0] = 0b0011 << 4 | 0b1100;
    i2c_write_buf[1] = 0b0011 << 4 | 0b1000;
    i2c_write_buf[2] = 0b0000 << 4 | 0b1100;
    i2c_write_buf[3] = 0b0000 << 4 | 0b1000;
    i2c_master_write(i2c_write_buf, 4, LCD_ADDR);   // Function set
    i2c_master_write(i2c_write_buf, 4, LCD_ADDR);   // Function set
    i2c_master_write(i2c_write_buf, 4, LCD_ADDR);   // Function set
   
    i2c_write_buf[0] = 0b0010 << 4 | 0b1100;
    i2c_write_buf[1] = 0b0010 << 4 | 0b1000;
    i2c_master_write(i2c_write_buf, 4, LCD_ADDR);   // Function set (set interface to 4 bits long)
   
    // clear display
    i2c_write_buf[0] = 0b0000 << 4 | 0b1100;
    i2c_write_buf[1] = 0b0000 << 4 | 0b1000;
    i2c_write_buf[2] = 0b0001 << 4 | 0b1100;
    i2c_write_buf[3] = 0b0001 << 4 | 0b1000;
    i2c_master_write(i2c_write_buf, 4, LCD_ADDR);

    for(int i = 1; i< 2000000; i++){}
    // Display ON/OFF Control: turn display on (D=1), cursor on (C=1), and blinking on (B=1)
    i2c_write_buf[0] = 0b0000 << 4 | 0b1100; // Prepare instruction with control bits
    i2c_write_buf[1] = 0b0000 << 4 | 0b1000; // Same as above, making sure P3=1 if using backlight
    i2c_write_buf[2] = 0b1111 << 4 | 0b1100; // Set D, C, and B bits to 1
    i2c_write_buf[3] = 0b1111 << 4 | 0b1000; // Execute instruction with control bits
    i2c_master_write(i2c_write_buf, 4, LCD_ADDR);
}

uint8_t decide_upper(char input){
    if(input == (' ' || '!' || ',')){
        return 0b0010;
    }
    else if(input == ('I' || 'L')){
        return 0b0100;
    }
    else if(input == 'U'){
        return 0b0101;
    }
    else if(input == ('a' || 'c' || 'd' || 'e' || 'g' || 'i' || 'k' || 'l' || 'n' || 'o')){
        return 0b0110;
    }
    else if( input == ('p' || 'r' || 's' || 't' || 'y') ){
        return 0b0111;
    }
    // default case: ?
    else{
        // ?
        return 0b0011;
    }
}

uint8_t decide_lower(char input){
    if(input == (' ' || 'p')){
        return 0b0000;
    }
    else if(input == ('!' || 'a')){
        return 0b0001;
    }
    else if(input == ('r')){
        return 0b0010;
    }
    else if(input == ('c' || 's')){
        return 0b0011;
    }
    else if(input == ('d' || 't')){
        return 0b0100;
    }
    else if(input == ('U' || 'e')){
        return 0b0101;
    }
    else if(input == 'g'){
        return 0b0111;
    }
    else if(input == ('I' || 'i' || 'y')){
        return 0b1001;
    }
    else if(input == 'k'){
        return 0b1011;
    }
    else if(input == (',' || 'L' || 'l')){
        return 0b1100;
    }
    else if(input == 'n'){
        return 0b1110;
    }
    else if(input == 'o'){
        return 0b1111;
    }
    // default case: ?
    else{
        // ?
        return 0b1111;
    }
}


void lcd_print(char *input){
    (void) input;
    uint8_t LCD_ADDR = I2C_SLAVE_ADDR_W; //TODO:
    uint8_t upper_bits;
    uint8_t lower_bits;
    uint8_t i2c_write_buf[4];

    // to get the upper bits and lower bits of the input character
    for (int i = 0; input[i] != '\0'; ++i) {
        upper_bits = decide_upper(input[i]);
        lower_bits = decide_lower(input[i]);
        // set the buffer
        i2c_write_buf[0] = upper_bits << 4 | 0b1101;
        i2c_write_buf[1] = upper_bits << 4 | 0b1001;
        i2c_write_buf[2] = lower_bits << 4 | 0b1101;
        i2c_write_buf[3] = lower_bits << 4 | 0b1001;
        // write
        i2c_master_write(i2c_write_buf, 4, LCD_ADDR);
    }
    return;
    
}

void lcd_set_cursor(uint8_t row, uint8_t col){
    (void) row;
    (void) col;
    // uint8_t addr;
    
}

void lcd_clear(){
    uint8_t LCD_ADDR = I2C_SLAVE_ADDR_W;    //0b0100111 R/W
    uint8_t i2c_write_buf[4];
    
    // clear display
    i2c_write_buf[0] = 0b0000 << 4 | 0b1100;
    i2c_write_buf[1] = 0b0000 << 4 | 0b1000;
    i2c_write_buf[2] = 0b0001 << 4 | 0b1100;
    i2c_write_buf[3] = 0b0001 << 4 | 0b1000;
    i2c_master_write(i2c_write_buf, 4, LCD_ADDR);

    // wait for 2 second
    for(int i = 1; i< 2000000; i++){}
    return;
}
