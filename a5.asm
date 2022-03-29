%macro print 2
mov rax,01
mov rdi,01
mov rsi,%1
mov rdx,%2
syscall
%endmacro

section .data
	msg1 db "Number of Positive numbers:"
	len1 equ $-msg1
	msg2 db ", Number of negative numbers:"
	len2 equ $-msg2
	array dq 0xffffffffffffff32,0xdffffffffffffff3,0xffffffffffffff2a,0x123a,0x23,0x46,0x32

section .bss
	count resb 2
	pcount resb 2
	ncount resb 2
	temp resb 2

section .text
	global _start
_start:

	mov byte[count],07
	mov byte[pcount],00
	mov byte[ncount],00

	mov rsi,array

	check:
		
		; using js flag
		;mov rax, 00
		;add rax, [rsi]
		;js neg
		
		; using bit test
		;mov rax, qword[rsi]
		;BT rax, 63
		;jc neg
		
		; using cmp
		mov rax, qword[rsi]
		cmp rax, 00
		jl neg
		
		inc byte[pcount]
		jmp change_number
		neg:
		inc byte[ncount]

	change_number:
		add rsi,08
		dec byte[count]
		jnz check

	mov bl,[pcount]
	mov dl,[ncount]
	b1:

	print msg1,len1
	mov bh,[pcount]
	call hex_to_ascii

	print 0h, 1

	print msg2,len2
	mov bh,[ncount]
	call hex_to_ascii

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
