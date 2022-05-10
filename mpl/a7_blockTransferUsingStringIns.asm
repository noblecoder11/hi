%macro write 2
mov rax, 01
mov rdi, 01
mov rsi, %1
mov rdx, %2
syscall
%endmacro

section .data
    sbmsg db "Source block: "
    sblen db $ - sbmsg
    
    dbmsg db 0xa, "Destination block: "
    dblen db $ - dbmsg
    
    sourceBlock: dq 11h, 22h, 33h, 44h, 55h
    
    
section .bss
    destBlock resq 5
    temp resq 1
    count resb 1
    result resb 4
    
section .text
    global _start

_start:
    
    write sbmsg, sblen 
    mov rsi, sourceBlock
    call display_block
    
    write dbmsg, dblen
    mov rsi, destBlock
    call display_block
    
    mov cl, 5
    mov rsi, sourceBlock
    mov rdi, destBlock
    cld
    movsq
    
    mov rsi, sourceBlock
    call display_block
    
    write dbmsg, dblen
    mov rsi, destBlock
    call display_block
    
    jmp exit
    
exit:  
    mov rax, 60
    mov rdi, 0
    syscall
    
    
display_block:
    ; mov cl, 5
    
    ; change_number:
    ;     mov rbx, rsi
    ;     call hex_to_ascii
    ;     mov rbx, [rsi]
    ;     call hex_to_ascii
    ;     add rsi, 08
    ;     ; inc rsi
    ;     dec cl
    ;     jnz change_number
    mov rbp,5
    next:mov al,[rsi]
         push rsi
         call disp
         pop rsi
         inc rsi
         dec rbp
         jnz next
ret

hex_to_ascii:
        mov bl,al ;store number in bl
        mov rdi, result ;point rdi to result variable
        mov cx,02 ;load count of rotation in cl
up1:
        rol bl,04 ;rotate number left by four bits
        mov al,bl ;move lower byte in dl
        and al,0fh ; get only LSB
        cmp al,09h ;compare with 39h
        jg add_37 ;if grater than 39h skip add 37
        add al,30h
        jmp skip1 ;else add 30
add_37: add al,37h
skip1:  mov [rdi],al ;store ascii code in result variable
        inc rdi ;point to next byte
        dec cx ;decrement the count of digits to display
        jnz up1 ;if not zero jump to repeat
        
        write result , 4
        
    ret
