%macro print 2
mov rax,01
mov rdi,01
mov rsi,%1
mov rdx,%2
syscall
%endmacro

section .data
	msg1 db "Largest number is: "
	len1 equ $-msg1
	msg2 db "Largest Num"
	len2 equ $-msg2
	array dq 55h, 0x6a, 0x58, -7dh, 20h, 2h, -45h

section .bss
	count resb 2
	largest resq 4
	ncount resb 2
	temp resb 2

section .text
	global _start
_start:

	mov byte[count],07
	mov byte[largest],00

	mov rsi,array

	check:
		; using cmp
		mov rax, qword[rsi]
		cmp rax,[largest]
		jg greater
		
		jmp change_number
		greater:
		mov [largest],rax

	change_number:
		add rsi,08
		dec byte[count]
		jnz check

	;mov bl,[pcount]
	
	b1:
	print msg1,len1
	mov bh,[largest]
	call hex_to_ascii
	
	print 0h, 1

	mov rax,60
	mov rdi,00
	syscall

	;function
	hex_to_ascii:
		mov byte[count],02

		loop:
			rol bh,04
			mov al,bh
			AND al,0FH
			cmp al,09
			jbe l1
			add al,07h
		l1:
			add al,30h
			mov[temp],al
			print temp,02
			dec byte[count]
			jnz loop
	ret
