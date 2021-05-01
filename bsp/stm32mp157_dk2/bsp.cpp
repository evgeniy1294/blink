#include "bsp.hpp"



   
              
void bsp::Init()
{
  RCC->MC_AHB4ENSETR = RCC->MC_AHB4ENSETR | RCC_MC_AHB4ENSETR_GPIOAEN | RCC_MC_AHB4ENSETR_GPIOHEN | RCC_MC_AHB4ENSETR_GPIODEN;
  
  Systick::Init();
  Leds::Init();
  
  return;
}




