#include "bsp.hpp"


mpp::tim::Timer< bsp::Systick > tim;

int main()
{
  tim.Start(250);
    
  while(1)
  {  
    if (tim.IsTimeOut())
    {
      tim.Reload();
      bsp::Leds::Toggle();
    }   
  }
  
  return 0;
}
