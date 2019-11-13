


void printString( char * c){
    int i = 0;
    while(c[i]!='\0'){
        printChar(c[i]);
        i++;
    }
}

void readString(char * c){
    int escribir=0; 
    while(escribir<=78){
        char ch = readChar();

        if(ch==0xd){
            c[escribir]='\0';
            break;
        }else if(ch==0x8){
            if(escribir>0){
                c[escribir-1]=' ';
                escribir--;
                printChar(ch);
                
            }
        }else{
           c[escribir]=ch;
           escribir++; 
           printChar(ch);
        }
        

    }
           
}

void handleInterrupt21 (int AX, int BX, int CX, int DX){
    if(AX==0){
        printString(BX);
    }else if(AX==1){
        readString(BX);
    }else if(AX==2){
        readSector(BX,CX);
    }else{
        printString("Error on InterruptCall");
    }   
}

main(){
    //printString("asdasdasfasafdsfdsfsdfsd\0");
    
    //test 2
    //char line[80];
    //printString("Enter a line: \0");
    //readString(line);

    //test 3
    //char buffer[512];
    //readSector(buffer,30);
    //printString(buffer);
    
    //test 4-5 
    //char line[80];
    //makeInterrupt21();
    //printString("Escriba algo: ");
    //syscall_readString(line);
    //syscall_printString(line);
    
    //testfinal
    makeInterrupt21();
    loadProgram();
}


