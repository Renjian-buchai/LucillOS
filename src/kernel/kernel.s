section .kernel 

copy_target: 
bits 32

global kernel 
kernel:
	mov esp,kernel_stack_top
	extern kmain
	call kmain
	cli
	hlt

section .bss
align 4
kernel_stack_bottom: equ $
	resb 16384 ; 16 KB
kernel_stack_top:

