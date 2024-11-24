section .data
var1 dq 1.0    
var2 dq 255.0 

section .text
bits 64
default rel
global imgCvtGrayInttoFloat

; R8 = width
; R9 = height

; RCX = intPixels
; RDX = floatPixels

imgCvtGrayInttoFloat:
    ;write your code here
    xor rax, rax
    
    mov r10, r9
    
    imul r10, r8 
    xor rax, rax	

    movsd xmm1, [var1]      
    movsd xmm2, [var2]        
    divsd xmm1, xmm2  
    cvtsd2ss xmm4, xmm1

convert:
    cvtsi2ss xmm0, [rcx] 
    vmulss xmm5, xmm0, xmm4  
    movss [rdx], xmm5

    add rdx, 4         
    add rcx, 4

    inc rax

    xorps xmm0, xmm0
    xorps xmm5, xmm5

    cmp rax, r10
    jl convert
    
    ret
    