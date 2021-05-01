ENTRY(ResetHandler)

MEMORY
{
  FLASH  (rx) : ORIGIN = 0x08000000, LENGTH = 64k
  RAM    (xrw): ORIGIN = 0x20000000, LENGTH = 20k
}


__initial_sp__   = ORIGIN(RAM) + LENGTH(RAM); 
__firmware_end__ = ORIGIN(FLASH) + SIZEOF(.isr_flash) + SIZEOF(.text) + SIZEOF(.rodata) + 16; /* arm + init_array + fini_array = 16 bytes */
__data_load__    = LOADADDR(.data);


__MinHeapSize  = 0x200;  /* required amount of heap  */
__MinStackSize = 0x400;  /* required amount of stack */


/* Define output sections */
SECTIONS
{
  .isr_flash :
  {
    . = ALIGN(4);
    KEEP(*(.isr_flash))
    . = ALIGN(4);
  } >FLASH



  .text :
  {
    . = ALIGN(4);
    *(.text)     
    *(.text*)   
    *(.glue_7)      
    *(.glue_7t)   
    *(.eh_frame)

    KEEP (*(.init))
    KEEP (*(.fini))

    . = ALIGN(4);
    _etext = .;  
	
  } >FLASH




  .rodata :
  {
    . = ALIGN(4);	
    *(.rodata)         
    *(.rodata*)        
    . = ALIGN(4);
  } >FLASH




  .preinit_array :
  {
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array*))
    PROVIDE_HIDDEN (__preinit_array_end = .);
  } >FLASH
  
  
  
  
  
  .init_array :
  {
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array*))
    PROVIDE_HIDDEN (__init_array_end = .);
  } >FLASH
  
  
  
  
  
  .fini_array :
  {
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array*))
    PROVIDE_HIDDEN (__fini_array_end = .);
  } >FLASH

  
  

  

  /* Initialized data sections goes into RAM, load LMA copy after code */
  .data : 
  {
    . = ALIGN(4);	
    __data_start__ = .; 
    *(.data)      
    *(.data*)          
	
    . = ALIGN(4);
    __data_end__ = .;  
  } >RAM AT> FLASH

  

  

  
  .bss :
  {
    . = ALIGN(4);
    __bss_start__ = .;         
    *(.bss)
    *(.bss*)
    *(COMMON)
	
    . = ALIGN(4);	
    __bss_end__ = .;         
  } >RAM




  
  
  ._user_heap_stack :
  {
    . = ALIGN(8);
    PROVIDE ( end = . );
    PROVIDE ( _end = . );
    . = . + __MinHeapSize;
    . = . + __MinStackSize;
    . = ALIGN(8);
  } >RAM


}


