echo bcc -ansi
bcc -ansi -c -o shell.o shell.c

echo os-api
as86 -o os_api.o os_api.asm

echo linking
ld86 -o shelll -d shell.o os_api.o
