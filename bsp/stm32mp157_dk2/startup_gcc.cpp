#include "bsp.hpp"


extern "C" {
  extern void __libc_init_array();
    
  /* The following are constructs created by the linker, indicating where the
    the "data"  and "bss" segments reside in memory */
  extern std::uint32_t __data_start__, __data_end__, __data_load__;
  extern std::uint32_t __bss_start__, __bss_end__;
  extern std::uint32_t __initial_sp__; 

    
    
  [[noreturn]] void DefaultHandler() {
    while(1) __NOP();
  }
    
    
    
  [[noreturn]] void ResetHandler() {
    __set_MSP(reinterpret_cast<std::uint32_t>(&__initial_sp__));

    //  Relocate the .data section 
    std::uint32_t*  dl = & __data_load__;
    std::uint32_t*  ds = & __data_start__;
    std::uint32_t*  de = & __data_end__;
    if (dl != ds) {
      while(ds < de) {
        *ds = *dl;
        dl++;
        ds++;
      }
    }


    //  Initiailize .bss to zero
    std::uint32_t*  bs = & __bss_start__;
    std::uint32_t*  be = & __bss_end__;
    while (bs < be) {
      *bs = 0;
      bs++;
    }       

    bsp::Init();
    
    //  Call static constructors
    __libc_init_array();
    
    main();

    while(1) __NOP();
  }
    
    
    
  
    
    
  __attribute__ ((section(".isr"), used)) 
  void (* const InterruptTable[])(void) =
  {
    /*  0 The initial stack pointer */
    reinterpret_cast< void(*)() >(&__initial_sp__),      
     
    /******  Cortex Interrupt   ************/ 
    ResetHandler,                 // 1 The reset handler
    DefaultHandler,               // 2 The NMI handler
    DefaultHandler,               // 3 The hard fault handler
    DefaultHandler,               // 4 Memory Management (MemManage) Fault
    DefaultHandler,               // 5 The bus fault handler
    DefaultHandler,               // 6 The usage fault handler
    nullptr,                      // 7 Reserved
    nullptr,                      // 8 Reserved
    nullptr,                      // 9 Reserved
    nullptr,                      // 10 Reserved
    DefaultHandler,               // 11 Supervisor Call (SVCall)
    DefaultHandler,               // 12 Debug monitor handler
    nullptr,                      // 13 Reserved
    DefaultHandler,               // 14 The PendSV handler
    bsp::Systick::Interrupt,      // 15 The SysTick handler

    /******  STM32  specific Interrupt  ************/
    DefaultHandler,                // 16 Window WatchDog 1
    DefaultHandler,                // 17 PVD and AVD through EXTI Line detection                        
    DefaultHandler,                // 18 Tamper and TimeStamps through the EXTI line
    DefaultHandler,                // 19 RTC Wakeup and Alarm through the EXTI line
    DefaultHandler,                // 20 Reserved
    DefaultHandler,                // 21 RCC                                             
    DefaultHandler,                // 22 EXTI Line0                                             
    DefaultHandler,                // 23 EXTI Line1                                             
    DefaultHandler,                // 24 EXTI Line2                                             
    DefaultHandler,                // 25 EXTI Line3                                             
    DefaultHandler,                // 26 EXTI Line4 
    DefaultHandler,                // 27 DMA1 Stream 0
    DefaultHandler,                // 28 DMA1 Stream 1                                   
    DefaultHandler,                // 29 DMA1 Stream 2                                   
    DefaultHandler,                // 30 DMA1 Stream 3                                   
    DefaultHandler,                // 31 DMA1 Stream 4                                   
    DefaultHandler,                // 32 DMA1 Stream 5
    DefaultHandler,                // 33 DMA1 Stream 6 
    DefaultHandler,                // 34 ADC1                             
    DefaultHandler,                // 35 FDCAN1 Interrupt line 0
    DefaultHandler,                // 36 FDCAN2 Interrupt line 0
    DefaultHandler,                // 37 FDCAN1 Interrupt line 1
    DefaultHandler,                // 38 FDCAN2 Interrupt line 1
    DefaultHandler,                // 39 External Line5 interrupts through AIEC
    DefaultHandler,                // 40 TIM1 Break interrupt
    DefaultHandler,                // 41 TIM1 Update Interrupt
    DefaultHandler,                // 42 TIM1 Trigger and Commutation Interrupt
    DefaultHandler,                // 43 TIM1 Capture Compare                                   
    DefaultHandler,                // 44 TIM2                                            
    DefaultHandler,                // 45 TIM3                                            
    DefaultHandler,                // 46 TIM4                                            
    DefaultHandler,                // 47 I2C1 Event                                             
    DefaultHandler,                // 48 I2C1 Error                                             
    DefaultHandler,                // 49 I2C2 Event                                             
    DefaultHandler,                // 50 I2C2 Error                                               
    DefaultHandler,                // 51 SPI1                                            
    DefaultHandler,                // 52 SPI2                                            
    DefaultHandler,                // 53 USART1                                          
    DefaultHandler,                // 54 USART2                                          
    DefaultHandler,                // 55 USART3                                          
    DefaultHandler,                // 56 External Line10 interrupts through AIEC
    DefaultHandler,                // 57 RTC TimeStamp through EXTI Line
    DefaultHandler,                // 58 External Line11 interrupts through AIEC
    DefaultHandler,                // 59 TIM8 Break Interrupt
    DefaultHandler,                // 60 TIM8 Update Interrupt
    DefaultHandler,                // 61 TIM8 Trigger and Commutation Interrupt
    DefaultHandler,                // 62 TIM8 Capture Compare Interrupt
    DefaultHandler,                // 63 DMA1 Stream7                                           
    DefaultHandler,                // 64 FMC                             
    DefaultHandler,                // 65 SDMMC1
    DefaultHandler,                // 66 TIM5                            
    DefaultHandler,                // 67 SPI3                            
    DefaultHandler,                // 68 UART4                           
    DefaultHandler,                // 69 UART5                           
    DefaultHandler,                // 70 TIM6
    DefaultHandler,                // 71 TIM7           
    DefaultHandler,                // 72 DMA2 Stream 0                   
    DefaultHandler,                // 73 DMA2 Stream 1                   
    DefaultHandler,                // 74 DMA2 Stream 2                   
    DefaultHandler,                // 75 DMA2 Stream 3                   
    DefaultHandler,                // 76 DMA2 Stream 4                   
    DefaultHandler,                // 77 Ethernet                        
    DefaultHandler,                // 78 Ethernet Wakeup through EXTI line              
    DefaultHandler,                // 79 FDCAN Calibration
    DefaultHandler,                // 80 EXTI Line6 interrupts through AIEC
    DefaultHandler,                // 81 EXTI Line7 interrupts through AIEC
    DefaultHandler,                // 82 EXTI Line8 interrupts through AIEC
    DefaultHandler,                // 83 EXTI Line9 interrupts through AIEC
    DefaultHandler,                // 84 DMA2 Stream 5                   
    DefaultHandler,                // 85 DMA2 Stream 6                   
    DefaultHandler,                // 86 DMA2 Stream 7                   
    DefaultHandler,                // 87 USART6                           
    DefaultHandler,                // 88 I2C3 event                             
    DefaultHandler,                // 89 I2C3 error                             
    DefaultHandler,                // 90 USB Host OHCI
    DefaultHandler,                // 91 USB Host EHCI
    DefaultHandler,                // 92 EXTI Line12 interrupts through AIEC
    DefaultHandler,                // 93 EXTI Line13 interrupts through AIEC
    DefaultHandler,                // 94 DCMI                            
    DefaultHandler,                // 95 Crypto1 global interrupt
    DefaultHandler,                // 96 Crypto Hash1 interrupt
    DefaultHandler,                // 97 FPU
    DefaultHandler,                // 98 UART7
    DefaultHandler,                // 99 UART8
    DefaultHandler,                // 100 SPI4
    DefaultHandler,                // 101 SPI5
    DefaultHandler,                // 102 SPI6
    DefaultHandler,                // 103 SAI1
    DefaultHandler,                // 104 LTDC
    DefaultHandler,                // 105 LTDC error
    DefaultHandler,                // 106 ADC2 
    DefaultHandler,                // 107 SAI2
    DefaultHandler,                // 108 QUADSPI
    DefaultHandler,                // 109 LPTIM1 global interrupt
    DefaultHandler,                // 110 HDMI_CEC
    DefaultHandler,                // 111 I2C4 Event                             
    DefaultHandler,                // 112 I2C4 Error 
    DefaultHandler,                // 113 SPDIF_RX
    DefaultHandler,                // 114 USB On The Go HS global interrupt
    DefaultHandler,                // 115 Reserved
    DefaultHandler,                // 116 Mailbox RX0 Free interrupt
    DefaultHandler,                // 117 Mailbox TX0 Free interrupt
    DefaultHandler,                // 118 DMAMUX1 Overrun interrupt
    DefaultHandler,                // 119 Mailbox RX1 Free interrupt
    DefaultHandler,                // 120 Mailbox TX1 Free interrupt
    DefaultHandler,                // 121 Crypto2 global interrupt
    DefaultHandler,                // 122 Crypto Hash2 interrupt
    DefaultHandler,                // 123 I2C5 Event Interrupt
    DefaultHandler,                // 124 I2C5 Error Interrupt
    DefaultHandler,                // 125 GPU Global Interrupt
    DefaultHandler,                // 126 DFSDM Filter0 Interrupt
    DefaultHandler,                // 127 DFSDM Filter1 Interrupt
    DefaultHandler,                // 128 DFSDM Filter2 Interrupt
    DefaultHandler,                // 129 DFSDM Filter3 Interrupt
    DefaultHandler,                // 130 SAI3 global Interrupt
    DefaultHandler,                // 131 DFSDM Filter4 Interrupt
    DefaultHandler,                // 132 TIM15 global Interrupt
    DefaultHandler,                // 133 TIM16 global Interrupt
    DefaultHandler,                // 134 TIM17 global Interrupt
    DefaultHandler,                // 135 TIM12 global Interrupt
    DefaultHandler,                // 136 MDIOS global Interrupt
    DefaultHandler,                // 137 EXTI Line14 interrupts through AIEC
    DefaultHandler,                // 138 MDMA global Interrupt
    DefaultHandler,                // 139 DSI global Interrupt
    DefaultHandler,                // 140 SDMMC2 global Interrupt
    DefaultHandler,                // 141 HSEM global Interrupt
    DefaultHandler,                // 142 DFSDM Filter5 Interrupt
    DefaultHandler,                // 143 EXTI Line15 interrupts through AIEC
    DefaultHandler,                // 144 Cortex-M4 CTI interrupt 1
    DefaultHandler,                // 145 Cortex-M4 CTI interrupt 2
    DefaultHandler,                // 146 TIM13 global interrupt
    DefaultHandler,                // 147 TIM14 global interrupt
    DefaultHandler,                // 148 DAC1 and DAC2 underrun error interrupts
    DefaultHandler,                // 149 RNG1 interrupt
    DefaultHandler,                // 150 RNG2 interrupt
    DefaultHandler,                // 151 I2C6 Event Interrupt
    DefaultHandler,                // 152 I2C6 Error Interrupt
    DefaultHandler,                // 153 SDMMC3 global Interrupt
    DefaultHandler,                // 154 LPTIM2 global interrupt
    DefaultHandler,                // 155 LPTIM3 global interrupt
    DefaultHandler,                // 156 LPTIM4 global interrupt
    DefaultHandler,                // 157 LPTIM5 global interrupt
    DefaultHandler,                // 158 ETH1_LPI interrupt 
    DefaultHandler,                // 159 Reserved
    DefaultHandler,                // 160 MPU Send Event through AIEC
    DefaultHandler,                // 161 RCC Wake up interrupt
    DefaultHandler,                // 162 SAI4 global interrupt
    DefaultHandler,                // 163 Temperature sensor interrupt
    DefaultHandler,                // 164 Reserved
    DefaultHandler,                // 165 Interrupt for all 6 wake-up pins    
  };
      
} //  extern "C"




