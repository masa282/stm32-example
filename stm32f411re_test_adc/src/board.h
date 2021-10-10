#include "stdint.h"

/********************************/
// RCC
/********************************/
typedef struct{
	uint32_t CR;			//0x00
	uint32_t PLLCFGR;		//0x04
	uint32_t CFGR;			//0x08
	uint32_t CIR;			//0x0c
	uint32_t AHB1RSTR;		//0x10
	uint32_t AHB2RSTR;		//0x14
	uint32_t rev[2];
	uint32_t APB1RSTR;		//0x20
	uint32_t APB2RSTR;		//0x24
	uint32_t rev2[2];
	uint32_t AHB1ENR;		//0x30
	uint32_t AHB2ENR;		//0x34
	uint32_t rev3[2];
	uint32_t APB1ENR;		//0x40
	uint32_t APB2ENR;		//0x44
	uint32_t rev4[2];
	uint32_t AHB1LPENR;		//0x50
	uint32_t AHB2LPENR;		//0x54
	uint32_t rev5[2];
	uint32_t APB1LPENR;		//0x60
	uint32_t APB2LPENR;		//0x64
	uint32_t rev6[2];
	uint32_t BDCR;			//0x70
	uint32_t CSR;			//0x74
	uint32_t rev7[2];
	uint32_t SSCGR;			//0x80
	uint32_t PLLI2SCFGR;	//0x84
	uint32_t rev8;
	uint32_t DCKCFGR;		//0x8c
} rcc_t;

#define REG_RCC ((volatile rcc_t *)0x40023800UL)
#define	RCC_AHB1ENR_GPIOAEN 	(0x1U) 	//for USART
#define RCC_AHB1ENR_GPIOCEN 	(0x4U)	//for ADC
#define RCC_APB2ENR_USART1EN 	(0x1U << 4)
#define RCC_APB2ENR_ADC1EN 		(0x1U << 8)


/********************************/
// ADC
/********************************/
typedef struct{
	uint32_t SR;
	uint32_t CR1;
	uint32_t CR2;
	uint32_t SMPR1;
	uint32_t SMPR2;
	uint32_t JOFR1;
	uint32_t JOFR2;
	uint32_t JOFR3;
	uint32_t JOFR4;
	uint32_t HTR;
	uint32_t LTR;
	uint32_t SQR1;
	uint32_t SQR2;
	uint32_t SQR3;
	uint32_t JSQR;
	uint32_t JDR1;
	uint32_t JDR2;
	uint32_t JDR3;
	uint32_t JDR4;
	uint32_t DR;
} adc_t;

typedef struct {
	uint32_t CCR;
} adc_common_t;

#define ADC_PIN 5	//PC
#define addr_adc1 	((uint32_t)0x40012000)
#define REG_ADC1 	((volatile adc_t *)addr_adc1)
#define REG_ADC 	((volatile adc_common_t *)(addr_adc1 + 0x300 + 0x04))

#define ADC_SR_EOC 			(0x1U << 1)
#define ADC_CR1_RES12 		(0x0U << 24) 		//12 bit,  15 ADCCLK cycles
#define ADC_CR2_ADON 		(0x1U)				//ADC ON
#define ADC_CR2_CONT 		(0x1U << 1)			//Continuous conversion mode
#define ADC_CR2_SWSTART		(0x1U << 30) 		//Starts conversion, ADON must be set 1
#define ADC_CCR_ADCPRE0 	(0x0U << 16) 		//PCLK2 divided by 2

void adc1_init(void);
void adc1_start(void);
void adc1_stop(void);
uint16_t adc1_getval(void);


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

#define REG_GPIOA ((volatile gpio_t *)0x40020000UL)
#define REG_GPIOC ((volatile gpio_t *)0x40020800UL)
#define GPIO_MODER_AF 		(0x2U)
#define GPIO_MODER_ANALOG 	(0x3U)
#define GPIO_OSPEEDR_HIGH 	(0x4U)
#define GPIO_AF_USART1_TX 	(0x7U)
#define GPIO_AF_USART1_RX 	(0x7U)


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

#define REG_SYSTICK 	((volatile systick_t *)0xE000E010UL)
#define TICK_MS 		(1000) //1sec
#define LOAD_VAL 		(16000 * TICK_MS) //Max 24bit

void systick_init(void);
void systick_handler(void);


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

#define UART_TX_PIN 9 	//PA
#define UART_RX_PIN 10	//PA

#define REG_USART1 ((volatile usart_t *)0x40011000UL)
#define USRAT_SR_TC 		(0x1U << 6)
#define USART_SR_RXNE 		(0x1U << 5)
#define USART_CR1_UE 		(0x1U << 13)
#define USART_CR1_M 		(0x1U << 12)
#define USART_CR1_TE 		(0x1U << 3)
#define USART_CR1_RE 		(0x1U << 2)
#define USART_CR3_DMAT 		(0x1U << 7)
#define USART_CR3_DMAR 		(0x1U << 6)
#define USART_CR2_STOP_1 	(0x0U << 12)

void usart1_init(void);
void usart1_send_val(uint8_t c);
