 ;os_api.asm
; SisOp 21511028
    
   .global _syscall_printString
   .global _syscall_readSector
   .global _syscall_readString

;(char *str)
_syscall_printString:
    push bp
	mov bp,sp
	push ds;[bp+2]

    mov ax, #0x0
    mov bx, [bp+4]
    mov cx, #0x0
    mov dx, #0x0
    int #0x21

    pop ds
	pop bp
	ret

;(char *str)
_syscall_readString:
    push bp
	mov bp,sp
	push ds

    mov ax, #0x1
    mov bx, [bp+4]
    mov cx, #0x0
    mov dx, #0x0
    int #0x21

    pop ds
	pop bp
	ret
    
;(char *buff, int sector)
_syscall_readSector:
    push bp
	mov bp,sp
	push ds

    mov ax, #0x2
    mov bx, [bp+4]
    mov cx, [bp+6]
    mov dx, #0x0
    int #0x21

    pop ds
	pop bp
	ret


