; Disassembly of file: simple1.o
; Sun Apr 21 20:31:04 2019
; Mode: 64 bits
; Syntax: YASM/NASM
; Instruction set: 8086, x64

default rel

global _main

_main:  ; Function begin
        push    rbp                                     ; 0000 _ 55
        mov     rbp, rsp                                ; 0001 _ 48: 89. E5
        xor     eax, eax                                ; 0004 _ 31. C0
        mov     dword [rbp-4H], 0                       ; 0006 _ C7. 45, FC, 00000000
        pop     rbp                                     ; 000D _ 5D
        ret                                             ; 000E _ C3
; _main End of function

