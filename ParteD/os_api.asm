 ;os_api.asm
; SisOp 21511028
    
   .global _syscall_printString
   .global _syscall_readSector
   .global _syscall_readString
   .global _syscall_readFile
   .global _syscall_executeProgram
   .global _syscall_terminate
   .global _syscall_clearScreen
   .global _syscall_writeSector
   .global _syscall_deleteFile
   .global _syscall_writeFile

;clearScreen();
_syscall_clearScreen:
    push bp
	mov bp,sp
	push ds;[bp+2]

    mov ax, #0xa
    mov bx, #0x0
    mov cx, #0x0
    mov dx, #0x0
    int #0x21

    pop ds
	pop bp
	ret

;terminate()
_syscall_terminate:
    push bp
	mov bp,sp
	push ds;[bp+2]

    mov ax, #0x5
    mov bx, #0x0
    mov cx, #0x0
    mov dx, #0x0
    int #0x21

    pop ds
	pop bp
	ret

;(char * name, int segment)
_syscall_executeProgram:
    push bp
	mov bp,sp
	push ds;[bp+2]

    mov ax, #0x4
    mov bx, [bp+4]
    mov cx, [bp+6]
    mov dx, #0x0
    int #0x21

    pop ds
	pop bp
	ret

;(char * filename, char* buffer)
_syscall_readFile:
    push bp
	mov bp,sp
	push ds;[bp+2]

    mov ax, #0x3
    mov bx, [bp+4];filename
    mov cx, [bp+6];buffer
    mov dx, #0x0
    int #0x21

    pop ds
	pop bp
	ret

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

;(char *buff, int sector)
_syscall_writeSector:
    push bp
	mov bp,sp
	push ds;bp+2

    mov ax, #0x6
    mov bx, [bp+4]
    mov cx, [bp+6]
    mov dx, #0x0
    int #0x21

    pop ds
    pop bp
    ret

;(char * filename)
_syscall_deleteFile:
    push bp
    mov bp,sp
    push ds;bp+2

    mov ax, #0x7
    mov bx, [bp+4]
    mov cx, #0x0
    mov dx, #0x0
    int #0x21

    pop ds
    pop bp
    ret

;(char * filename, char * buffer, int numberofSector)
_syscall_writeFile:
    push bp
    mov bp,sp
    push ds;bp+2

    mov ax, #0x8
    mov bx,[bp+4]
    mov cx,[bp+6]
    mov dx,[bp+8]
    int #0x21

    pop ds
    pop bp
    ret

