#include "bsp.hpp"


void bsp::Init()
{
  Eclic::Init<MachineTimerInterrupt>();

  // Настраиваем машинный таймер. Таймер будет переполнятся раз в 1 мс.     
  bsp::Systick::Init();

  //Разрешить прерывание таймера - прерывание номер 7
  MachineTimerInterrupt::Enable();

  // Разрешаем глобальное машинное прерывание 
  mpp::core::MSTATUS::Set( MSTATUS_MIE );

  RCU_APB2EN = RCU_APB2EN | RCU_APB2EN_PAEN | RCU_APB2EN_PCEN;
  
  bsp::Leds::Init();
  bsp::Leds::Reset();

  return;
}

