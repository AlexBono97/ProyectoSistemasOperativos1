;kernel.asm
;Michael Black, 2007

;kernel.asm contains assembly functions that you can use in your kernel

	.global _loadProgram
	.global _putInMemory
	.global _interrupt
	.global _makeInterrupt21
	.extern _handleInterrupt21
	.global _printChar
	.global _readChar
	.global _readSector

; Load a program from sector 11 into segment 0x20000
_loadProgram:
 	mov ax, #0x2000
 	mov ds, ax
 	mov ss, ax
 	mov es, ax

	;lets have the stack start at 0x2000:fff0
	mov ax, #0xfff0
 	mov sp, ax
 	mov bp, ax

	; Read the program from the floppy
	mov cl, #12 ;cl holds sector number
 	mov dh, #0 ;dh holds head number - 0
 	mov ch, #0 ;ch holds track number - 0
 	mov ah, #2 ;absolute disk read
 	mov al, #1 ;read 1 sector
 	mov dl, #0 ;read from floppy disk A
 	mov bx, #0 ;read into offset 0 (in the segment)
 	int #0x13 ;call BIOS disk read function

	; Switch to program
 	jmp #0x2000:#0

;void readSector(char * buffer, int sector) buffer->[bp+4],sector->[bp+6]
_readSector:
	push bp
	mov bp,sp
	push ds ;[bp-2]

	;calculando track
	mov ax, [bp+6];sector location
	mov bx, #0x24
	mov dx, #0x0
	div bx
	mov ch,al
	

	;calculando relative sector
	mov ax, [bp+6]
	mov bx, #0x12
	mov dx, #0x0
	div bx
	add dx, #0x1
	mov cl, dl
	

	;calculando head
	mov ax, [bp+6]
	mov bx, #0x12
	mov dx, #0x0
	div bx ;cociente quedo en ax
	mov bx, #0x2
	mov dx, #0x0
	div bx
	mov dh,dl ;residuo que queda en dx
	

	
	;pasando el resto de parametros
	mov ah, #0x2
	mov al, #0x1
	mov bx, [bp+4]
	mov dl, #0x0
	int #0x13

	pop ds
	pop bp
	ret

;char readChar()
_readChar:
	push bp
	mov bp,sp
	push ds
	mov ah,#0x0
	int #0x16
	pop ds
	pop bp
	ret

;void printChar(char ch)
_printChar:
	push bp
	mov bp,sp
	push ds
	mov al,[bp+4] 
	mov ah,#0x0e
	int #0x10
	pop ds
	pop bp
	ret
	

;void putInMemory (int segment, int address, char character)
_putInMemory:
	push bp
	mov bp,sp
	push ds
	mov ax,[bp+4]
	mov si,[bp+6]
	mov cl,[bp+8]
	mov ds,ax
	mov [si],cl
	pop ds
	pop bp
	ret

;int interrupt (int number, int AX, int BX, int CX, int DX)
_interrupt:
	push bp
	mov bp,sp
	mov ax,[bp+4]	;get the interrupt number in AL
	push ds		;use self-modifying code to call the right interrupt
	mov bx,cs
	mov ds,bx
	mov si,#intr
	mov [si+1],al	;change the 00 below to the contents of AL
	pop ds
	mov ax,[bp+6]	;get the other parameters AX, BX, CX, and DX
	mov bx,[bp+8]
	mov cx,[bp+10]
	mov dx,[bp+12]

intr:	int #0x00	;call the interrupt (00 will be changed above)

	mov ah,#0	;we only want AL returned
	pop bp
	ret

;void makeInterrupt21()
;this sets up the interrupt 0x21 vector
;when an interrupt 0x21 is called in the future, 
;_interrupt21ServiceRoutine will run

_makeInterrupt21:
	;get the address of the service routine
	mov dx,#_interrupt21ServiceRoutine
	push ds
	mov ax, #0	;interrupts are in lowest memory
	mov ds,ax
	mov si,#0x84	;interrupt 0x21 vector (21 * 4 = 84)
	mov ax,cs	;have interrupt go to the current segment
	mov [si+2],ax
	mov [si],dx	;set up our vector
	pop ds
	ret

;this is called when interrupt 21 happens
;sit will call your function:
;void handleInterrupt21 (int AX, int BX, int CX, int DX)
_interrupt21ServiceRoutine:
	push dx
	push cx
	push bx
	push ax
	call _handleInterrupt21
	pop ax
	pop bx
	pop cx
	pop dx

	iret


	






