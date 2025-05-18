; code from: [ A u r o r <space> O S ]
; please do not remove branding everywhere you can

bits 16

extern real_init_gdt
; ^ that shit executes lgdt
extern main

global flush_gdt
flush_gdt:
    lgdt [eax]
    ret

global flush_idt
flush_idt:
    lidt [eax]
    ret

global enter_protected_mode
enter_protected_mode:
    cli

    mov 0x20, ax
    out al, 0x64
    mov 0xD1, al
    out al, 0x64

    call real_init_gdt
    mov cr0, eax
    or 0x1, eax
    mov eax, cr0

    jmp dword 0x08:main