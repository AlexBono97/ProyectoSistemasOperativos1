
void main(){
    int i=0;
    int j=0;
    int k=0;
    int contSect=0;
    int range=512;
    int nSector=1;
    char buffer[74];
    char dirbuff[512];
    char archibuff[13312];
    char filename[7];
    char filename2[7];

    for(i=0;i<13312;i++){
            archibuff[i]='\0';
    }
    for(i=0;i<15;i++){
            buffer[i]='\0';
    }
    for(i=0;i<7;i++){
            filename[i]='\0';
    }
    for(i=0;i<7;i++){
            filename2[i]='\0';
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
           
    }else if(buffer[0]=='d' && buffer[1]=='e' && buffer[2]=='l' && buffer[3]=='e' && buffer[4]=='t' && buffer[5]=='e'){
            filename[0]=buffer[7];
            filename[1]=buffer[8];
            filename[2]=buffer[9];
            filename[3]=buffer[10];
            filename[4]=buffer[11];
            filename[5]=buffer[12];
            filename[6]='\0';
            syscall_deleteFile(filename);
            syscall_terminate();
    }else if(buffer[0]=='c' && buffer[1]=='o' && buffer[2]=='p' && buffer[3]=='y'){
            i=5;
            while(buffer[i]!=' ' && i<11){
                    filename[j]=buffer[i];
                    j=j+1;
                    i=i+1;
            }
            filename[j]='\0';
            i=i+1;//salta el espacio
            j=0;
            while(buffer[i]!='\0'){
                    filename2[j]=buffer[i];
                    j=j+1;
                    i=i+1;
            }
            filename2[j]='\0';
        
            //reading file1
            syscall_readFile(filename,archibuff);
            //calculating number of sectors
            //HASTA AQUI FUNCIONA BIEN
            //ARREGLAR PARA LEER NUMERO DE SECTORES DESDE EL MAP
            //Y ASI PODER COPIAR EL SHELL
            
            i=0;
            while(archibuff[i]!='\0'){
                 if(i>range-1){
                         range=range+512;
                         nSector=nSector+1;
                         syscall_printString("B");
                 }
                i=i+512;
            }
            //writing file
            syscall_writeFile(filename2,archibuff,nSector);
            syscall_terminate();
    }else if(buffer[0]=='d' && buffer[1]=='i' && buffer[2]=='r'){
            syscall_printString("Lista de Archivos en Disco");
            syscall_printString("\r\n");
            //loading directory for reading
            syscall_readSector(dirbuff,2); 
            //recorriendo e imprimiendo nombres
            for(i=0;i<=480;i=i+32){
                    if(dirbuff[i]!=0){
                        //empezamos a imprimir
                        for(j=0;j<6;j++){
                                filename[j]=dirbuff[i+j];
                        }
                        for(j=6;j<32;j++){
                                if(dirbuff[i+j]!='\0'){
                                        contSect=contSect+1;
                                }else{
                                        break;
                                }
                        }
                        syscall_printString(filename);
                        syscall_printString("..........");
                        //ARREGLA PARA IMPRIMIR EL SIZE
                        //syscall_printChar("\0"+contSect);
                        syscall_printString("\r\n");

                    }
                
            }            
            syscall_terminate();
    }else if(buffer[0]=='c' && buffer[1]=='r' && buffer[2]=='e' && buffer[3]=='a' && buffer[4]=='t' && buffer[5]=='e'){
        filename[0]=buffer[7];
        filename[1]=buffer[8];
        filename[2]=buffer[9];
        filename[3]=buffer[10];
        filename[4]=buffer[11];
        filename[5]=buffer[12];
        filename[6]='\0';
        //HASTA AQUI SE QUE LLEGO!!!
        //ciclo de lectura
        while(i!=0){
                //syscall_printString("A");
                syscall_readString(buffer);
                syscall_printString("\r\n");
                if(buffer[0]=='\0'){
                //syscall_printString("D");
                        //se hallo linea vacia, se procede a escribir
                        while(archibuff[i]!='\0'){
                        if(i>range){
                                range=range+512;
                                nSector=nSector+1;
                                }
                        i=i+1;
                        }
                syscall_writeFile(filename,archibuff,nSector);
                i=0;
                }else{
                        //syscall_printString("C");
                       //copiar del buffer (hasta encontrar \0)
                       //en el archibuff
                       j=0;
                       while(buffer[j]!='\0'){
                               archibuff[k]=buffer[j];
                        
                               k=k+1;
                               j=j+1;
                       }
                       //archibuff[k]="\r\n";
                       //archibuff[k+2]="\n"; 
                }
        }
        //syscall_printString("B");
        syscall_terminate();
        
        

    }else{
           syscall_printString("Invalid Command");
           syscall_printString("\r\n");
           syscall_terminate();
           
    }
        
        
}

