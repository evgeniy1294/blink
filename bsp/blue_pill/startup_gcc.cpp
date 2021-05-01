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
    
    
    
  
    
    
  __attribute__ ((section(".isr_flash"), used)) 
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
    DefaultHandler,               // 15 The SysTick handler

    /******  STM32  specific Interrupt  ************/
    DefaultHandler,               // 16 Window WatchDog Interrupt                            
    DefaultHandler,               // 17 PVD through EXTI Line detection Interrupt            
    DefaultHandler,               // 18 Tamper Interrupt                                     
    DefaultHandler,               // 19 RTC global Interrupt                                 
    DefaultHandler,               // 20 FLASH global Interrupt                               
    DefaultHandler,               // 21 RCC global Interrupt                                 
    DefaultHandler,               // 22 EXTI Line0 Interrupt                                 
    DefaultHandler,               // 23 EXTI Line1 Interrupt                                 
    DefaultHandler,               // 24 EXTI Line2 Interrupt                                 
    DefaultHandler,               // 25 EXTI Line3 Interrupt                                 
    DefaultHandler,               // 26 EXTI Line4 Interrupt                                 
    DefaultHandler,               // 27 DMA1 Channel 1 global Interrupt                      
    DefaultHandler,               // 28 DMA1 Channel 2 global Interrupt                      
    DefaultHandler,               // 29 DMA1 Channel 3 global Interrupt                      
    DefaultHandler,               // 30 DMA1 Channel 4 global Interrupt                      
    DefaultHandler,               // 31 DMA1 Channel 5 global Interrupt                      
    DefaultHandler,               // 32 DMA1 Channel 6 global Interrupt                      
    DefaultHandler,               // 33 DMA1 Channel 7 global Interrupt                      
    DefaultHandler,               // 34 ADC1 and ADC2 global Interrupt                       
    DefaultHandler,               // 35 USB Device High Priority or CAN1 TX Interrupts       
    DefaultHandler,               // 36 USB Device Low Priority or CAN1 RX0 Interrupts       
    DefaultHandler,               // 37 CAN1 RX1 Interrupt                                   
    DefaultHandler,               // 38 CAN1 SCE Interrupt                                   
    DefaultHandler,               // 39 External Line[9:5] Interrupts                        
    DefaultHandler,               // 40 TIM1 Break Interrupt                                 
    DefaultHandler,               // 41 TIM1 Update Interrupt                                
    DefaultHandler,               // 42 TIM1 Trigger and Commutation Interrupt               
    DefaultHandler,               // 43 TIM1 Capture Compare Interrupt                       
    DefaultHandler,               // 44 TIM2 global Interrupt                                
    DefaultHandler,               // 45 TIM3 global Interrupt                                
    DefaultHandler,               // 46 TIM4 global Interrupt                                
    DefaultHandler,               // 47 I2C1 Event Interrupt                                 
    DefaultHandler,               // 48 I2C1 Error Interrupt                                 
    DefaultHandler,               // 49 I2C2 Event Interrupt                                 
    DefaultHandler,               // 50 I2C2 Error Interrupt                                 
    DefaultHandler,               // 51 SPI1 global Interrupt                                
    DefaultHandler,               // 52 SPI2 global Interrupt                                
    DefaultHandler,               // 53 USART1 global Interrupt                              
    DefaultHandler,               // 54 USART2 global Interrupt                              
    DefaultHandler,               // 55 USART3 global Interrupt                              
    DefaultHandler,               // 56 External Line[15:10] Interrupts                      
    DefaultHandler,               // 57 RTC Alarm through EXTI Line Interrupt                
    DefaultHandler                // 58 USB Device WakeUp from suspend through EXTI Line Interrupt      
  };
      
} //  extern "C"




