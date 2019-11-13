
void main(){
    int i=0;
    char buffer[15];
    char archibuff[13312];
    char filename[7];

    for(i=0;i<13312;i++){
            archibuff[i]='\0';
    }
    for(i=0;i<15;i++){
            buffer[i]='\0';
    }
    for(i=0;i<7;i++){
            filename[i]='\0';
    }
    
    syscall_printString("SHELL>");
    syscall_readString(buffer);
    syscall_printString("\r\n");

    if(buffer[0]=='c' && buffer[1]=='l' && buffer[2]=='e' && buffer[3]=='a' && buffer[4]=='r'){
    
       syscall_clearScreen();
       syscall_terminate();
    }else if(buffer[0]=='t' && buffer[1]=='y' && buffer[2]=='p' && buffer[3]=='e'){
            
            //syscall_printString("Type is a yes");
            
            filename[0]=buffer[5];
            filename[1]=buffer[6];
            filename[2]=buffer[7];
            filename[3]=buffer[8];
            filename[4]=buffer[9];
            filename[5]=buffer[10];
            filename[6]='\0';
            syscall_readFile(filename,archibuff);
            syscall_printString(archibuff);
            syscall_printString("\r\n");
            syscall_terminate();
        
    }else if(buffer[0]=='e' && buffer[1]=='x' && buffer[2]=='e' && buffer[3]=='c' && buffer[4]=='u' && buffer[5]=='t' && buffer[6]=='e'){
           filename[0]=buffer[8];
            filename[1]=buffer[9];
            filename[2]=buffer[10];
            filename[3]=buffer[11];
            filename[4]=buffer[12];
            filename[5]=buffer[13];
            filename[6]='\0';
            syscall_executeProgram(filename,0x4000);
           
    }else{
           syscall_printString("Invalid Command");
           syscall_printString("\r\n");
           syscall_terminate();
           
    }
        
        
}

