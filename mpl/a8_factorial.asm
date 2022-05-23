section .data
num db 4
result db 0,0,0,0
section .text
global _start
_start: mov ax,1
	mov bh,0
	mov bl,[num]
      call fact
      mov esi,result    ; convert to ascii and display
      mov cl,4          
up:   rol ax,4          
      mov dx,ax           
      and ax,0fh         
      cmp al,09
      jbe skip
      add al,07
skip: add al,30h
      mov [esi],al      
      inc esi            
      mov ax,dx         
      dec cl            
      jnz up
      mov rax,1
      mov rdi,1
      mov rsi,result
      mov rdx,4
      syscall

      mov rax,60
      mov rdi,0
      syscall

; procedure - recursive   iteration 1      2         3       4
fact: cmp bx,1 
      jne next                             
      ret
next: mul bx            ; ax*bx            ax =5     20       60       120
      dec bx            ;                  bx = 4    3         2       1
      call fact
ret
