#include "bsp.hpp"


void bsp::Init()
{
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN | RCC_AHB1ENR_CRCEN;
  
  bsp::Systick::Init();
  bsp::Leds::Init();
	
  return;
}

