global irq1_handler
extern ps2_handler_main

section .text
irq1_handler:
    cli  
    pushad  
    call ps2_handler_main
    popad 
    sti  
    iretd 
