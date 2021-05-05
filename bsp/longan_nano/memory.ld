OUTPUT_ARCH("riscv")

ENTRY(Reset)

MEMORY
{
  FLASH (rxai!w) : ORIGIN = 0x00000000, LENGTH = 64K
  RAM   (wxa!ri) : ORIGIN = 0x20000000, LENGTH = 20K
}


SECTIONS
{
  .text :
  {
    __text_start__ = .;
    KEEP(*(.init))
    *(.text*)
    *(.rodata*)
    *(.srodata*)
    . = ALIGN(4);
    __text_end__ = .;
  } > FLASH


  .data : 
  {
    __data_start__ = .;
    *(.data*)
    *(.sdata*)
    __global_pointer$ = . + 2K;
    . = ALIGN(4);
    __data_end__ = .;
    _edata = .;
  } > RAM AT>FLASH 
	
	
  .bss :
  {
    __bss_start__ = .;
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    __bss_end__ = .;
    _end = .; 
  } > RAM
	
	
} /* SECTIONS */


PROVIDE(__heap_start__ = __bss_end__);
PROVIDE(__stack_end__  = ORIGIN(RAM) + LENGTH(RAM));
PROVIDE(__data_load__  = LOADADDR(.data));


