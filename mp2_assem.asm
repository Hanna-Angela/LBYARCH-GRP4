%include "io64.inc"
section .data
intpix times 15 dw 0
fltpix times 15 dq 0
var1 dq 1.0
var2 dq 255.0

section .text
global main
main:
    ;write your code here
    xor rax, rax
    
    GET_DEC 1, r8
    GET_DEC 1, r9
    mov r10, r9
    
    imul r10, r8
    xor rax, rax
	

L1:
    xor r11w, r11w
    GET_DEC 2, r11w
    mov word [intpix + rax*2], r11w
    ;PRINT_DEC 2, [intpix + rax*2]
    ;NEWLINE
    inc rax
    cmp rax, r10
    jl L1

    lea rsi, [intpix]
    xor rdx, rdx
convert:
    xor eax, eax
    
    mov ax, [rsi]
    cvtsi2ss xmm0, eax
    vmovsd xmm1, [var1]
    vmovsd xmm2, [var2]
    vdivsd xmm3, xmm1, xmm2
    cvtss2sd xmm4, xmm0
    vmulpd xmm5, xmm4, xmm3
    ;cvtsd2ss xmm6, xmm5
    vmovsd [fltpix+rdx*8], xmm5
    
    ADD rsi, 2
    inc rdx
    cmp rdx, r10
    jl convert
    
    ret
    