echo bcc -ansi
bcc -ansi -c -o test.o test.c

echo os-api
as86 -o os_api.o os_api.asm

echo linking
ld86 -o syscall-test -d test.o os_api.o

echo copying
echo dd if=syscall-test of=floppya.img bs=512 count=1 seek=11 conv=notrunc