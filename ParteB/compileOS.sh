echo Bootload
nasm bootload.asm
dd if=/dev/zero of=floppya.img bs=512 count=2880
dd if=bootload of=floppya.img bs=512 count=1 conv=notrunc

echo compilando kernel
bcc -ansi -c -o kernel.o kernel.c

echo ensamblando kernel.asm
as86 kernel.asm -o kernel_asm.o

echo ensamblando os_api.asm
as86 os_api.asm -o os_api_asm.o

echo ensamblando start.asm
as86 start.asm -o start_asm.o

echo Linkeando y creando el kernel
ld86 -o kernel -d start_asm.o kernel.o kernel_asm.o os_api_asm.o

echo Escribiendo el kernel en el sector 3
dd if=kernel of=floppya.img bs=512 conv=notrunc seek=3

dd if=message.txt of=floppya.img bs=512 count=1 seek=30 conv=notrunc

