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

/** @brief I2C clock speed: 100kHz (0x28 * 2) */
#define I2C_CCR  0x50

/** @brief Start bit mask */
#define I2C_SB  (1 << 8)

/** @brief Stop bit mask */
#define I2C_STOP  (1 << 8) //TODO:



#define I2C_EN  (1 << )
void i2c_master_init(uint16_t clk){
    (void) clk; /* This line is simply here to suppress the Unused Variable Error. */
                /* You should remove this line in your final implementation */

    struct i2c_reg_map *i2c = I2C1_BASE;

    // GPIO Pins
    gpio_init(GPIO_B, 8, MODE_ALT, OUTPUT_OPEN_DRAIN, OUTPUT_SPEED_LOW, PUPD_NONE, ALT4);        /* PB_8(D15)*/
    gpio_init(GPIO_B, 9, MODE_ALT, OUTPUT_OPEN_DRAIN, OUTPUT_SPEED_LOW, PUPD_NONE, ALT4);       /* PB_9(D14) */

    // Reset and Clock Control
    struct rcc_reg_map *rcc = RCC_BASE;
    rcc->apb1_enr |= I2C1_CLKEN;

    // Peripheral Clock Frequency: 16 Mhz
    *(uint8_t*)&i2c->CR2 = (uint8_t)I2C_CF;

    // I2C clock speed: 100kHz
    *(uint8_t*)&i2c->CR2 = (uint8_t)I2C_CCR;

    return;
}

void i2c_master_start(){
    struct i2c_reg_map *i2c = I2C1_BASE;
    // set start bit
    i2c->CR1 |= I2C_SB;
    // check if SB =1
    while(!(i2c->CR1 & I2C_SB));
    
    return;
}

void i2c_master_stop(){
    struct i2c_reg_map *i2c = I2C1_BASE;
    // set stop bit
    i2c->CR1 |= I2C_STOP;
    // check TxE and BTF bit (they should be set to 1)
    while(!((i2c->SR1 >> 7)&(i2c->SR1 >> 2)&1));
    return;
}

int i2c_master_write(uint8_t *buf, uint16_t len, uint8_t slave_addr){
    (void) buf;
    (void) len;
    (void) slave_addr;

    struct i2c_reg_map *i2c = I2C1_BASE;

    // write the address(i2c's address) of slave into data register (EV8)
    *(uint8_t*)&i2c->DR = slave_addr;

    return 0;
}

int i2c_master_read(uint8_t *buf, uint16_t len, uint8_t slave_addr){
    (void) buf;
    (void) len;
    (void) slave_addr;

    return 0;
}
