/**
  ***********************************************************
  @author Evgenii Fedoseev
  @file   /bsp/stm32f407g_disco/bsp.hpp
  @brief  Compatible board stm32f407-discovery 
  ***********************************************************
**/

#pragma once

//___________________DEFINITION___________________//
#define STM32F4         (1)
#define STM32F407xx     (1)



//____________________INCLUDE_____________________//
#include <cstdint>
#include "stm32f407xx.h"
#include "mppio/io.hpp"
#include "mpptim/cortex.hpp"
#include "mpptim/soft.hpp"


int main();


namespace bsp
{
  // Systick and DWT
  struct ClockTree {
    constexpr static std::uint32_t kSysClkHz     = 16'000'000u;
    constexpr static std::uint32_t kSysTickClkHz = 16'000'000u;
  };

  using Systick = mpp::tim::Systick < ClockTree >;

    
  // Leds
  struct LedTrait final: mpp::io::LedTrait
  {
    constexpr static mpp::io::Inversion kInversion = mpp::io::Inversion::Off;
  };
    
  struct LedInvTrait final: mpp::io::LedTrait
  {
    constexpr static mpp::io::Inversion kInversion = mpp::io::Inversion::On;
  };

  using LedBlue   = mpp::io::Gpio < mpp::io::PD15, LedTrait >;
  using LedRed    = mpp::io::Gpio < mpp::io::PD14, LedInvTrait >;    
  using LedOrange = mpp::io::Gpio < mpp::io::PD13, LedInvTrait >;   
  using LedGreen  = mpp::io::Gpio < mpp::io::PD12, LedTrait >;  

  using Leds = mpp::io::IoGroup < LedBlue, LedRed, LedOrange, LedGreen >;
	
	
  // Specific function 
  void Init();
    
} // namespace board


