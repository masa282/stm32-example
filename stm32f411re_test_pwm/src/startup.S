/* Definition of Section */
        .syntax unified
        .thumb
        .section .isr_vector,"a",%progbits

    .align  2
    .global  __Vectors
__Vectors:
        .long   __main_stack_start    /* Main stack pointer (MSP) */
        .long   Reset_Handler         /* Reset Handler */
        .long   NMI_Handler           /* NMI Handler */
        .long   HardFault_Handler     /* Hard Fault Handler */
        .long   MemManage_Handler     /* MPU Fault Handler */
        .long   BusFault_Handler      /* Bus Fault Handler */
        .long   UsageFault_Handler    /* Usage Fault Handler */
        .long   0                     /* Reserved */
        .long   0                     /* Reserved */
        .long   0                     /* Reserved */
        .long   0                     /* Reserved */
        .long   Svc_Handler           /* SVCall Handler */
        .long   0                     /* Debug Monitor Handler */
        .long   0                     /* Reserved */
        .long   PendSV_Handler        /* PendSV Handler */
        .long   Systick_Handler       /* SysTick Handler */

        .long   Default_IRQHandler    /* 16: WWDG */
        .long   Default_IRQHandler    /* 17: PVD */
        .long   Default_IRQHandler    /* 18: TAMPER */
        .long   Default_IRQHandler    /* 19: RTC */
        .long   Default_IRQHandler    /* 20: FLASH */
        .long   Default_IRQHandler    /* 21: RCC */
        .long   Default_IRQHandler    /* 22: EXTI0 */
        .long   Default_IRQHandler    /* 23: EXTI1 */
        .long   Default_IRQHandler    /* 24: EXTI2 */
        .long   Default_IRQHandler    /* 25: EXTI3 */
        .long   Default_IRQHandler    /* 26: EXTI4 */
        .long   Default_IRQHandler    /* 27: DMA1Stream0 */
        .long   Default_IRQHandler    /* 28: DMA1Stream1 */
        .long   Default_IRQHandler    /* 29: DMA1Stream2 */
        .long   Default_IRQHandler    /* 30: DMA1Stream3 */
        .long   Default_IRQHandler    /* 31: DMA1Stream4 */
        .long   Default_IRQHandler    /* 32: DMA1Stream5 */
        .long   Default_IRQHandler    /* 33: DMA1Stream6 */
        .long   Default_IRQHandler    /* 34: ADC */
        .long   Default_IRQHandler    /* 35: CAN1_TX */
        .long   Default_IRQHandler    /* 36: CAN1_RX0 */
        .long   Default_IRQHandler    /* 37: CAN1_RX1 */
        .long   Default_IRQHandler    /* 38: CAN1_SCE */
        .long   Default_IRQHandler    /* 39: EXTI9_5 */
        .long   Default_IRQHandler    /* 40: TIM1_BRK_TIM9 */
        .long   Default_IRQHandler    /* 41: TIM1_UP_TIM10 */
        .long   Default_IRQHandler    /* 42: IRQ_TIM1_TRG_COM_TIM11 */
        .long   Default_IRQHandler    /* 43: TIM1_CC */
        .long   Default_IRQHandler    /* 44: TIM2 */
        .long   Default_IRQHandler    /* 45: TIM3 */
        .long   Default_IRQHandler    /* 46: TIM4 */
        .long   Default_IRQHandler    /* 47: I2C1_EV */
        .long   Default_IRQHandler    /* 48: I2C1_ER */
        .long   Default_IRQHandler    /* 49: I2C2_EV */
        .long   Default_IRQHandler    /* 50: I2C2_ER */
        .long   Default_IRQHandler    /* 51: SPI1 */
        .long   Default_IRQHandler    /* 52: SPI2 */
        .long   Default_IRQHandler    /* 53: USART1 */
        .long   Default_IRQHandler    /* 54: USART2 */
        .long   Default_IRQHandler    /* 55: USART3 */
        .long   Default_IRQHandler    /* 56: EXTI15_10 */
        .long   Default_IRQHandler    /* 57: RTCAlarm */
        .long   Default_IRQHandler    /* 58: OTG_FS_WKUP */
        .long   Default_IRQHandler    /* 59: TIM8_BRK_TIM12 */
        .long   Default_IRQHandler    /* 60: TIM8_UP_TIM13 */
        .long   Default_IRQHandler    /* 61: TIM8_TRG_COM_TIM14 */
        .long   Default_IRQHandler    /* 62: TIM8_CC */
        .long   Default_IRQHandler    /* 63: DMA1Stream7 */
        .long   Default_IRQHandler    /* 64: FSMC */
        .long   Default_IRQHandler    /* 65: SDIO */
        .long   Default_IRQHandler    /* 66: TIM5 */
        .long   Default_IRQHandler    /* 67: SPI3 */
        .long   Default_IRQHandler    /* 68: USART4 */
        .long   Default_IRQHandler    /* 69: USART5 */
        .long   Default_IRQHandler    /* 70: TIM6_DAC */
        .long   Default_IRQHandler    /* 71: TIM7 */
        .long   Default_IRQHandler    /* 72: DMA2Stream0 */
        .long   Default_IRQHandler    /* 73: DMA2Stream1 */
        .long   Default_IRQHandler    /* 74: DMA2Stream2 */
        .long   Default_IRQHandler    /* 75: DMA2Stream3 */
        .long   Default_IRQHandler    /* 76: DMA2Stream4 */
        .long   Default_IRQHandler    /* 77: ETH */
        .long   Default_IRQHandler    /* 78: ETH_WKUP */
        .long   Default_IRQHandler    /* 79: CAN2_TX */
        .long   Default_IRQHandler    /* 80: CAN2_RX0 */
        .long   Default_IRQHandler    /* 81: CAN2_RX1 */
        .long   Default_IRQHandler    /* 82: CAN2_SCE */
        .long   Default_IRQHandler    /* 83: OTG_FS */
        .long   Default_IRQHandler    /* 84: DMA2Stream5 */
        .long   Default_IRQHandler    /* 85: DMA2Stream6 */
        .long   Default_IRQHandler    /* 86: DMA2Stream7 */
        .long   Default_IRQHandler    /* 87: USART6 */
        .long   Default_IRQHandler    /* 88: I2C3_EV */
        .long   Default_IRQHandler    /* 89: I2C3_ER */
        .long   Default_IRQHandler    /* 90: OTG_HS_EP1_OUT */
        .long   Default_IRQHandler    /* 91: OTG_HS_EP1_IN */
        .long   Default_IRQHandler    /* 92: OTG_HS_WKUP */
        .long   Default_IRQHandler    /* 93: OTG_HS */
        .long   Default_IRQHandler    /* 94: DCMI */
        .long   Default_IRQHandler    /* 95: CRYP */
        .long   Default_IRQHandler    /* 96: HASH_RNG */
        .long   Default_IRQHandler    /* 97: FPU */

        .text
        .align  2

/* Reset Handler */
        .global Reset_Handler
        .thumb_func
        .type   Reset_Handler, %function
Reset_Handler:

        b       l1
        .ltorg
        .thumb
l1:

        /* Copy the data sections. */
        ldr     r0,  =_sidata
        ldr     r1,  =_sdata
        ldr     r2,  =_edata
        cmp     r0,  r1
        beq     2f
1:
        cmp     r1,  r2
        itt     ne
        ldrne   r3, [r0], #4
        strne   r3, [r1], #4
        bne     1b
2:
        /* Zero fill the bss segment. */
        mov     r0,  #0
        ldr     r1,  =_sbss
        ldr     r2,  =_ebss
3:
        cmp     r1,  r2
        bge     4f
        str     r0,  [r1],  #4
        b       3b
4:

        /* Call the application's entry point.*/
        ldr     r2, =main
        bx      r2


/* Exception Handler Definition */

        .global NMI_Handler
        .thumb_func
        .type   NMI_Handler, %function
NMI_Handler:
        b       NMI_Handler

        .global HardFault_Handler
        .thumb_func
        .type   HardFault_Handler, %function
HardFault_Handler:
        b       HardFault_Handler

        .global MemManage_Handler
        .thumb_func
        .type   MemManage_Handler, %function
MemManage_Handler:
        b       MemManage_Handler

        .global BusFault_Handler
        .thumb_func
        .type   BusFault_Handler, %function
BusFault_Handler:
        b       BusFault_Handler

        .global UsageFault_Handler
        .thumb_func
        .type   UsageFault_Handler, %function
UsageFault_Handler:
        b       UsageFault_Handler

        .global DebugMon_Handler
        .thumb_func
        .type   DebugMon_Handler, %function
DebugMon_Handler:
        b       DebugMon_Handler

        .global Svc_Handler
        .thumb_func
        .type 	Svc_Handler, %function
Svc_Handler:
		b		Svc_Handler

        .global PendSV_Handler
        .thumb_func
        .type   PendSV_Handler, %function
PendSV_Handler:
        b       PendSV_Handler

        .global Systick_Handler
        .thumb_func
        .type	Systick_Handler, %function
Systick_Handler:
		b		Systick_Handler

        .global Default_IRQHandler
        .thumb_func
        .type   Default_IRQHandler, %function
Default_IRQHandler:
        b       Default_IRQHandler

    .end
