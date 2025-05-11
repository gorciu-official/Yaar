; code from: [ A u r o r <space> O S ]
; please do not remove branding everywhere you can

bits 16

extern KiRealInitGdt
; ^ that shit executes lgdt
extern KiSystemReady

global KiFlushGdtTable
KiFlushGdtTable:
    lgdt [eax]
    ret

global KiFlushIdtTable
KiFlushIdtTable:
    lidt [eax]
    ret

global KiEnterProtectedMode
KiEnterProtectedMode:
    cli

    mov 0x20, ax
    out al, 0x64
    mov 0xD1, al
    out al, 0x64

    call KiRealInitGdt
    mov cr0, eax
    or 0x1, eax
    mov eax, cr0

    jmp 0x08, KiSystemReady