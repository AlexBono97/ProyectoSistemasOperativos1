bcc -ansi -c -o kernel.o kernel.c
as86 kernel.asm -o kernel_asm.o
ld86 -o kernel -d kernel.o kernel_asm.o 
dd if=kernel of=floppya.img bs=512 conv=notrunc seek=3 

