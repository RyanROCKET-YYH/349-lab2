#include <gpio.h>
#include <i2c.h>
#include <unistd.h>
#include <rcc.h>

// D14 I2C1_SDA & D15 I2C1_SCL
/** @brief The UART register map. */
struct i2c_reg_map {
    volatile uint32_t CR1;      /**<  Control Register 1 */
    volatile uint32_t CR2;      /**<  Control Register 2 */
    volatile uint32_t OAR1;     /**<  Own Address Register 1 */
    volatile uint32_t OAR2;     /**<  Own Address Register 2 */
    volatile uint32_t DR;       /**<  Data Register */
    volatile uint32_t SR1;      /**<  Status Register 1 */
    volatile uint32_t SR2;      /**<  Status Register 2 */
    volatile uint32_t CCR;      /**<  Clock Control Register */
    volatile uint32_t TRISE;    /**<  TRISE Register */
    volatile uint32_t FLTR;     /**<  FLTR Register */
};

/** @brief Base Address of I2C1 */
#define I2C1_BASE   (struct i2c_reg_map *) 0x40005400

/** @brief Peripheral Clock Frequency(16 MHz) of I2C */
#define I2C_CF  0b10000

/** @brief I2C clock speed: 100kHz */
#define I2C_CCR  0x50

/** @brief Start bit mask */
#define I2C_SB  (1 << 8)

/** @brief Stop bit mask */
#define I2C_CR1_STOP  (1 << 9) 
#define I2C_EN  (1)
#define I2C_CR1_SWRST (1 << 15)
#define I2C_SR1_BTF (1 << 2)
#define I2C_SR1_TXE (1 << 7)
#define I2C_SR1_ADDR (1 << 1)
#define I2C_TRISE (0x17)
#define I2C_SR2_BUSY (1 << 1)
#define I2C_CR1_ACK (1 << 10)

void i2c_master_init(uint16_t clk){
    (void) clk; /* This line is simply here to suppress the Unused Variable Error. */
                /* You should remove this line in your final implementation */
    
    struct i2c_reg_map *i2c = I2C1_BASE;
    struct rcc_reg_map *rcc = RCC_BASE;
    rcc->apb1_enr |= I2C1_CLKEN;
    // GPIO Pins
    gpio_init(GPIO_B, 8, MODE_ALT, OUTPUT_OPEN_DRAIN, OUTPUT_SPEED_LOW, PUPD_NONE, ALT4);   /* PB_8(D15)*/
    gpio_init(GPIO_B, 9, MODE_ALT, OUTPUT_OPEN_DRAIN, OUTPUT_SPEED_LOW, PUPD_NONE, ALT4);   /* PB_9(D14) */

    // Peripheral Clock Frequency: 16 Mhz
    i2c->CR2 |= I2C_CF;
    // Reset and Clock Control
    
    // i2c->TRISE |= I2C_TRISE;    // configure the rise time register
       // I2C clock speed: 100kHz
    i2c->CCR |= I2C_CCR;
    i2c->CR1 |= I2C_EN;         // enable peripheral
    i2c->CR1 |= I2C_CR1_ACK;
    return;
}

void i2c_master_start(){
    struct i2c_reg_map *i2c = I2C1_BASE;
    // set start bit
    i2c->CR1 |= I2C_SB;
    // when busy bit is cleared
    // while (!(i2c->SR2 & I2C_SR2_BUSY));
    // wait if SB =1
    while(!(i2c->SR1 & 1));
    return;
}

void i2c_master_stop(){
    struct i2c_reg_map *i2c = I2C1_BASE;

    // check TxE and BTF bit (they should be set to 1)(EV8_2)
    while ((i2c->SR1 & I2C_SR1_BTF) | (i2c-> SR1 & I2C_SR1_TXE)) {  /** @TODO:*/
        i2c->CR1 |= I2C_CR1_STOP;
    };
    return;
}

int i2c_master_write(uint8_t *buf, uint16_t len, uint8_t slave_addr){
    struct i2c_reg_map *i2c = I2C1_BASE;

    i2c_master_start();
    // generate the topmost 7 bits as slave address (the last bit (write): 0)
    slave_addr = slave_addr << 1;
    // write the address(i2c's address) of slave into data register
    i2c->DR = slave_addr; 
    while(!(i2c->SR1 & I2C_SR1_ADDR)) {
    };  
    (void)i2c->SR2;  // wait for ev6

    // check ADDR and TxE bit (they should be set to 1)(EV6, EV8_1)
    // Clear the ADDR flag by reading SR2 (EV6)

    while(!(i2c->SR1 & I2C_SR1_TXE)) {
    };   // wait ev8_1
    i2c->DR = buf[0]; 
    // Send first data byte
    // send data
    for(int i=1; i < len; i++){
        while (!(i2c->SR1 & I2C_SR1_TXE)) {
            i2c->DR = buf[i];
        }; // Wait for EV8
    }
    i2c_master_stop();
    return 0;
}

int i2c_master_read(uint8_t *buf, uint16_t len, uint8_t slave_addr){
    (void) buf;
    (void) len;
    (void) slave_addr;

    return 0;
}
