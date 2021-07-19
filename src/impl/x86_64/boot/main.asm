global start
section .text
;set the mode to 32-bit as instructions are still in 32 bit mode
bits 32
start:
    ; folling code print 'OK'
    mov dword [0xb8000], 0x2f4b2f4f ; number for 'OK'
    ; halts the program
    hlt