#include "defines.h"

/********************************/
// RCC
/********************************/
#define REG_RCC_AHB1ENR		((volatile uint32_t *)0x40023830UL)
#define RCC_AHB1ENR_GPIODEN	(0x8U)


/********************************/
// GPIO
/********************************/
typedef struct {
  uint32_t MODER;   // Port mode Register
  uint32_t OTYPER;  // Port output type Register
  uint32_t OSPEEDR; // Port output speed Register
  uint32_t PUPDR;   // Port pull-up/pull-down
  uint32_t IDR;     // Port input data
  uint32_t ODR;     // Port output data
  uint32_t BSRR;    // Port bit set/reset
  uint32_t LCKR;    // Port configuration lock
  uint32_t AFRL;    // Alternate function low
  uint32_t AFRH;    // Alternate function high
} gpio_t;

#define REG_GPIOD			((volatile gpio_t *)0x40020C00UL)
#define GPIO_MODER_OUTPUT	(1U)
#define GPIO_OSPEEDR_HIGH	(2U)

void led_init(void);
void led_on(uint32_t mask);
void led_off(uint32_t mask);

#define LED_GREEN	(0x1U)
#define LED_ORANGE	(0x2U)
#define LED_RED		(0x4U)
#define LED_BLUE	(0x8U)



/********************************/
// SYSTICK
/********************************/
typedef struct {
  uint32_t CTRL;  // SysTick Control and Status
  uint32_t LOAD;  // SysTick Reload Value
  uint32_t VAL;   // SysTick Current Value
  uint32_t CALIB; // SysTick Calibration Value
} systick_t;

#define REG_SYSTICK ((volatile systick_t *)0xE000E010UL)
void systick_init(void);
void systick_handler(void);

