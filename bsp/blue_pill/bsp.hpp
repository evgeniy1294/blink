/**
  ***********************************************************
  @author Evgenii Fedoseev
  @file   /bsp/blue_pill/bsp.hpp
  @brief  Compatible board: blue pill
  ***********************************************************
**/

#pragma once


//___________________DEFINITION___________________//
#define STM32F1       (1)
#define STM32F103xB   (1)



//____________________INCLUDE_____________________//
#include <cstdint>
#include "stm32f103xb.h"
#include "mppio/io.hpp"
#include "mpptim/cortex.hpp"
#include "mpptim/soft.hpp"

int main();


namespace bsp
{
  // Systick and DWT
  struct ClockTree {
    constexpr static std::uint32_t kSysClkHz     = 8'000'000u;
    constexpr static std::uint32_t kSysTickClkHz = 8'000'000u; 
  };

  using Systick = mpp::tim::Systick < ClockTree >;
  
  // Leds
  struct LedTrait final: mpp::io::LedTrait
  {
    constexpr static mpp::io::Inversion kInversion = mpp::io::Inversion::Off;
  };
    

  using LedGreen  = mpp::io::Gpio < mpp::io::IO< mpp::io::Port::C, 13 >,  LedTrait >;  
  using Leds = mpp::io::IoGroup < LedGreen >;
  
  
  // Specific function 
  void Init();
  
    
} // namespace board
