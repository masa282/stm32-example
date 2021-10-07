#include "stdint.h"

/********************************/
// RCC
/********************************/
#define REG_RCC_APB2ENR ((volatile uint32_t *)0x40023844UL)
#define RCC_APB2ENR_USART1EN (0x1U << 4)
#define REG_RCC_AHB1ENR ((volatile uint32_t *)0x40023830UL)
#define	RCC_AHB1ENR_GPIOAEN (0x1U)


/********************************/
// GPIO
/********************************/
typedef struct {
	uint32_t MODER;
	uint32_t OTYPER;
	uint32_t OSPEEDR;
	uint32_t PUPDR;
	uint32_t IDR;
	uint32_t ODR;
	uint32_t BSRR;
	uint32_t LCKR;
	uint32_t AFRL;
	uint32_t AFRH;
} gpio_t;

#define LED_PIN 8
#define UART_TX_PIN 9 	//PA
#define UART_RX_PIN 10	//PA

#define REG_GPIOA ((volatile gpio_t *)0x40020000UL)
#define GPIO_MODER_OUTPUT (0x1U)
#define GPIO_MODER_AF (0x2U)
#define GPIO_OSPEEDR_HIGH (0x4U)
#define GPIO_AF_USART1_TX (0x7U)
#define GPIO_AF_USART1_RX (0x7U)

void led_init(void);
void led_toggle(void);


/********************************/
// USART
/********************************/
typedef struct {
	uint32_t SR;
	uint32_t DR;
	uint32_t BRR;
	uint32_t CR1;
	uint32_t CR2;
	uint32_t CR3;
	uint32_t GRPR;
} usart_t;

#define REG_USART1 ((volatile usart_t *)0x40011000UL)
#define USRAT_SR_TC (0x1U << 6)
#define USART_SR_RXNE (0x1U << 5)
#define USART_CR1_UE (0x1U << 13)
#define USART_CR1_M (0x1U <<12)
#define USART_CR1_TE (0x1U << 3)
#define USART_CR1_RE (0x1U << 2)
#define USART_CR3_DMAT (0x1U << 7)
#define USART_CR3_DMAR (0x1U << 6)
#define USART_CR2_STOP_1 (0x0U << 12)

void usart1_init(void);
void usart1_send(uint8_t *str);
void _usart1_send_char(uint8_t c);
uint8_t usart1_recv(void);
unsigned long _baud_rate(uint32_t b);



/********************************/
// SYSTICK
/********************************/
typedef struct
{
	uint32_t CSR;
	uint32_t LOAD;
	uint32_t VAL;
	uint32_t CALIB;
} systick_t;

#define REG_SYSTICK ((volatile systick_t *)0xE000E010UL)
#define TICK_MS (1000) //1sec
//#define CORE_CLK  (16000000UL)
#define LOAD_VAL (16000 * TICK_MS) //Max 24bit
//(CORE_CLK/1000*TICK_MS) //(TICK_MS/1000) / (1/f_ck) = TICK_MS*(f_ck/1000)

void systick_init(void);
void systick_handler(void);
