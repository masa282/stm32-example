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
#define RCC_APB1ENR_TIM2EN	(0x1U)
#define RCC_APB1ENR_TIM3EN	(0x2U)
#define RCC_AHB1ENR_GPIOAEN (0x1U)
#define RCC_AHB1ENR_GPIOCEN (0x4U)


/********************************/
// TIMER
/********************************/
typedef struct{
	uint32_t CR1;	//0x00
	uint32_t CR2;	//0x04
	uint32_t SMCR;	//0x08
	uint32_t DIER;	//0x0C
	uint32_t SR;	//0x10
	uint32_t EGR;	//0x14
	uint32_t CCMR1;	//0x18
	uint32_t CCMR2;	//0x1C
	uint32_t CCER;	//0x20
	uint32_t CNT;	//0x24
	uint32_t PSC;	//0x28
	uint32_t ARR;	//0x2C
	uint32_t rev;
	uint32_t CCR1;	//0x34
	uint32_t CCR2;	//0x38
	uint32_t CCR3;	//0x3C
	uint32_t CCR4;	//0x40
	uint32_t rev2;
	uint32_t DCR;	//0x48
	uint32_t DMAR;	//0x4C
	uint32_t OR;	//0x50
} tim_t;

#define REG_TIM2 ((volatile tim_t *)0x40000000UL)
#define REG_TIM3 ((volatile tim_t *)0x40000400UL)

#define TIM_CR1_CEN 			(0x1U)			//Counter ENable
#define TIM_CR1_APRE			(0x1U << 7)		//Auto-Reload Pre-load Enable
#define TIM_SR_UIE 				(0x1U)			//Update Interrupt Flag
#define TIM_EGR_UG				(0x1U)
#define TIM_CCMR2_CC3S_OC		(0x0U)
#define TIM_CCMR2_OC3PE			(0x1U << 3)  	//Pre-load register on TIMx_CCR3 enabled
#define TIM_CCMR2_OC3M_PWM1		(0x6U << 4)  	//Output Capture, PWM1(in up-counting)
#define TIM_CCER_CC3E 			(0x1U << 8)  	//signal is output on the corresponding output pin
#define TIM_CCER_CC3P			(0x1U << 9)		//Output polarity 0:=Active High, 1:= Active Low

void pwm_init(void);
void tim2_init(void);
void delay_ms(uint16_t ms);
void delay_us(uint16_t us);


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

#define LED_PIN 	9
#define PWM_PIN 	8 //PC8-CH3
#define REG_GPIOA ((volatile gpio_t *)0x40020000UL)
#define REG_GPIOC ((volatile gpio_t *)0x40020800UL)

#define GPIO_MODER_OUTPUT	(0x1U)
#define GPIO_MODER_AF		(0x2U)
#define GPIO_OSPEEDR_HIGH	(0x3U)
#define GPIO_AF_TIM3_CH3	(0x2U) //AF02

void led_init(void);
void led_toggle(void);
