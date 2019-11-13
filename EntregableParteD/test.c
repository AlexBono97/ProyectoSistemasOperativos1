
void main(){
    char nombre[6];
    nombre[0]='h';
    nombre[1]='o';
    nombre[2]='l';
    nombre[3]='a';
    nombre[4]='\0';
    syscall_printString("Si ves esto, significa que si funciona el execute");
    syscall_printString("\r\n");
    syscall_printString("Escribiendo un archivo");
    syscall_writeFile(nombre,"Hola que hay. Espero que puedas ver este mensaje",1);
    syscall_terminate();
    //while(1);
}