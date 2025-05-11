; code from: [ A u r o r <space> O S ]
; please do not remove branding everywhere you can

bits 32

global KiFlushGdtTable
KiFlushGdtTable:
    lgdt [eax]
    ret

global KiFlushIdtTable
KiFlushIdtTable:
    lidt [eax]
    ret