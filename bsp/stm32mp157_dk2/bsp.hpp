/**
  ***********************************************************
  @author Evgenii Fedoseev
  @file   /bsp/stm32mp157_dk2/bsp.hpp
  @brief  
  ***********************************************************
**/

#pragma once

//___________________DEFINITION___________________//
#define STM32MP1      (1)
#define STM32MP15xx   (1)


//____________________INCLUDE_____________________//
#include <cstdint>
#include "stm32mp157cxx_cm4.h"
#include "mppio/io.hpp"
#include "mpptim/cortex.hpp"
#include "mpptim/soft.hpp"



int main();


namespace bsp
{
  struct ClockTree {
    constexpr static std::uint32_t kSysClkHz     = 160'000'000u;
    constexpr static std::uint32_t kSysTickClkHz = 160'000'000u; 
  };

  using Systick = mpp::tim::Systick < ClockTree >;
  
  // Leds
  struct LedTrait final: mpp::io::LedTrait
  {
    constexpr static mpp::io::Inversion kInversion = mpp::io::Inversion::Off;
  };
    
  struct LedTraitInv final: mpp::io::LedTrait
  {
    constexpr static mpp::io::Inversion kInversion = mpp::io::Inversion::On;
  };
  
  using LedOrange  = mpp::io::Gpio < mpp::io::PH7,  LedTrait >;  
  using LedGreen   = mpp::io::Gpio < mpp::io::PA14, LedTraitInv >;  
  using LedRed     = mpp::io::Gpio < mpp::io::PA13, LedTrait >;
  using LedBlue    = mpp::io::Gpio < mpp::io::PD11, LedTrait >;
  using Leds       = mpp::io::IoSet < LedGreen, LedOrange, LedRed, LedBlue >;
  
    
  // Specific function 
  void Init();   

} // namespace board

 
