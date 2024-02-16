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

#define I2C_EN  (1 << )
void i2c_master_init(uint16_t clk){
    (void) clk; /* This line is simply here to suppress the Unused Variable Error. */
                /* You should remove this line in your final implementation */

    return;
}

void i2c_master_start(){
    return;
}

void i2c_master_stop(){
    return;
}

int i2c_master_write(uint8_t *buf, uint16_t len, uint8_t slave_addr){
    (void) buf;
    (void) len;
    (void) slave_addr;

    return 0;
}

int i2c_master_read(uint8_t *buf, uint16_t len, uint8_t slave_addr){
    (void) buf;
    (void) len;
    (void) slave_addr;

    return 0;
}
