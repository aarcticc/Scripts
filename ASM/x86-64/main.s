section .data
	string1 db "Hello World!", 10,0

section .text
	global _start

	_start
	; calculate lenght of string "Hello World!"
	mov		rdi, dword string1
	mov		rcx, dword -1
	xor		al,al
	cld
	repnz scasb

	; place length of string in RDX
	mov		rdx, dword -2
	sub		rdx, rcx

	; place the string using write() system call
	mov		rsi, dword string1
	push	0x1
	pop		rax
	mov		rdi, rax
	syscall

	; exit from the application here
	xor		rdi, rdi
	push	0x3c
	pop		rax
	syscall
