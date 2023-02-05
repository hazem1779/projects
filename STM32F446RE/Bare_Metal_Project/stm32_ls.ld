ENTRY(Reset_Handler)

MEMORY
{
    FLASH(rx) : ORIGIN =0x08000000,LENGTH =1024K
    SRAM(rwx) : ORIGIN =0x20000000,LENGTH =128K
}

SECTIONS
{
    /*.text section*/
    .text :
    {
        /*merge all .isr_vector of all input files*/
        *(.isr_vector)
        
        /*merge all .text       of all input files*/
        *(.text)
        *(.text.*)
        *(.init)
        *(.fini)

        /*merge all .rodata     of all input files*/
        *(.rodata)
        *(.rodata.*)
        . = ALIGN(4);

        _etext = .; /*store the updated location counter into a symbol end_of_text*/

    }> FLASH
    
    
    /*.data section*/
    _la_data = LOADADDR(.data);
    .data :
    {
        _sdata = .; /*Assign a value to a symbol*/

        /*merge all .data sections of all input files*/
        *(.data)
        *(.data.*)
        . = ALIGN(4);
        _edata = .; /*store the updated location counter*/
        
    }> SRAM AT> FLASH


    /*.bss section*/
    .bss :
    {
        _sbss = .;
        __bss_start__ = _sbss;
        /*merge all .bss sections of all input files*/
        *(.bss)
        *(.bss.*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;  
        __bss_end__ = _ebss; 
        . = ALIGN(4);
        end = .;
        __end__ = .;
    }> SRAM
}
