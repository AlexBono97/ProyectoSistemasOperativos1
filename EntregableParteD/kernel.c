

void clearScreen();
void executeProgram(char * name, int segment);
void terminate();
void readFile(char * filename, char * buffer);
void printString(char * c);
void readString(char * c);
void handleInterrupt21(int AX, int BX, int CX, int DX);
int strcmp(char * word1, char * word2);
void strcpy(char * ori, char * dest, int base);
void strcpyinvertido(char * ori, char * dest, int base);
void deleteFile(char * filename);
void writeFile(char * filename, char * buffer, int numberofSectors);

void main(){
    
    //Load and Execute a Program
    makeInterrupt21();
    syscall_clearScreen();
    //syscall_terminate();
    syscall_executeProgram("shelll", 0x2000);
    //syscall_printString("Fallo");
    //while(1);

    //Testing the Shell
    //clearScreen();
}

void clearScreen(){
    int t = 0x8000;
    while(t<0x8FA0){
    putInMemory(0xb000,t,' ');
    t=t+1;
    putInMemory(0xb000,t,0x7);
    t=t+1;
    }
    pointerReset();
}


void executeProgram(char * name, int segment){
    int ext=0;
    char buffer[13312];
    syscall_readFile(name,buffer);

    if(segment > 0x1000 && segment < 0xA000){

        while(ext <=13311){
            putInMemory(segment,ext,buffer[ext]);
            ext++;
        }
        launchProgram(segment);
    }else{
        syscall_printString("Error en el segmento usado");
    }
}

void terminate(){
    char name[6];
    name[0]='s';
    name[1]='h';
    name[2]='e';
    name[3]='l';
    name[4]='l';
    name[5]='l';
    executeProgram(name,0x2000);
}

int strcmp(char * word1, char * word2){
    int i=0;
    while(i<6){
        if(word1[i] != word2[i]){
            return 0;
        }
        i++;
    }
    return 1;
}

void strcpy(char * ori, char * dest, int base){
    int i=0;
    while(i<512){
        dest[base*512+i]=ori[i];
        i++;
    }
}

void strcpyinvertido(char * ori, char * dest, int base){
    int i=0;
    while(i<512){
        dest[i]=ori[base*512+i];
        i++;
    }
}

void readFile(char * filename, char * buffer){    
    int i = 0;
    int pos=0;//guardara el control de en que parte del directorio estamos
    int temp=0;
    char name[6];
    char dirbuff[512];
    char tmpbuff[13312];//13312

    //limpieza de arreglos
    for(i=0;i<13312;i++){
        tmpbuff[i]='\0';
    }
    for(i=0;i<512;i++){
        dirbuff[i]='\0';
    }
    for(i=0;i<6;i++){
        name[i]='\0';
    }

    //fin de declaracion de variables
    readSector(dirbuff,2);//cargamos el directorio
    
    for(pos=0;pos<=480;pos=pos+32){
        for(i=0; i<6; i++){
            name[i]=dirbuff[pos+i];
        }
        //chequeando si son iguales
        if(strcmp(name,filename)){
            
            for (temp=6; temp < 32; temp++) {
                if(dirbuff[pos + temp]!=0){
                    readSector(tmpbuff, dirbuff[pos+temp]);
		            strcpy(tmpbuff, buffer, temp-6);
                }else{
                    return;
                }          
	        }
        }
        //no son iguales, avanzamos en el directorio
       
    }
    //no hallamos el archivo
     syscall_printString("Archivo no encontrado");

    /*while(filename[i]!='\0'){
        if(filename[i]==dirbuff[temp]){
            i++;
            temp++;
        }
        else if(pos>=511)
        {
            break;
        }else{
            pos=pos+32;
            i=0;
            temp=pos;
        }
    }*/
    //una vez aqui, comprobamos si hallamos el filename
    //contados --> 6, temp-->6(necesario para leer los sectores), i-->7 (no lo ocupamos mas)
    
}

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
                printChar(0x8);
                c[escribir-1]='\0';
                printChar(' ');
                printChar(0x8);
                escribir--;
            }
        }else{
           c[escribir]=ch;
           escribir++; 
           printChar(ch);
        }
        

    }
           
}

void deleteFile(char * filename){
    //declaracion variables
    char dirbuff[512];
    char mapbuff[512];
    char name[6];
    int pos=0;
    int i=0;
    int temp=0;
    //Load Directory and Map 
    readSector(dirbuff,2);
    readSector(mapbuff,1);

    //Search through directory for Filename
    for(pos=0;pos<=480;pos=pos+32){
        for(i=0; i<6; i++){
            name[i]=dirbuff[pos+i];
        }
        //chequeando si son iguales
        if(strcmp(name,filename)){

            //setear a 0x00 el primer byte del filename
            dirbuff[pos]=0x0;

            //para cada sector, escribir el byte
            //del mapa correspondiente a 0x00
            for (temp=6; temp < 32; temp++) {
                if(dirbuff[pos + temp]!=0){
                    i=dirbuff[pos+temp];
                    mapbuff[i]=0x0;
                }else{
                    break;
                }          
	        }
        }
        //no son iguales, avanzamos en el directorio
       
    }
    writeSector(mapbuff,1);
    writeSector(dirbuff,2);

}

void writeFile(char * filename, char * buffer, int numberofSectors){
    //declaracion variables
    char dirbuff[512];
    char mapbuff[512];
    char name[6];
    char databufftemp[512];
    
    int pos=0;//posicion en dir
    int posm=0;//posicion en map
    int posb=0;//posicion en buffer de archivo
    int i=0;//temporal
    int temp=0;//otro temporal
    //Load Directory and Map 
    readSector(dirbuff,2);
    readSector(mapbuff,1);

    //finding a free directory entry
    for(pos=0;pos<=480;pos=pos+32){
        if(dirbuff[pos]==0){
            //escribimos el nombre en esa entrada
            //nombre debe de llevar \0 al final del mismo
            for(i=0;i<6;i++){
                if(filename[i]=='\0'){
                    dirbuff[pos+i]=0x0;
                }else{
                    dirbuff[pos+i]=filename[i];
                }     
            }

            //HASTA AQUI SE QUE FUNCIONA BIEN
            break;
        }else if(pos>=480){
            syscall_printString("No hay directorios disponibles");
            return;
        }
    }

    //Ciclo por cada sector
    temp=numberofSectors;
    i=6;
    for(posm=0;posm<512;posm++){

        if(mapbuff[posm]==0 && temp>0 && i<32){
                mapbuff[posm]=0xFF;
                dirbuff[pos+i]=posm;

                //writing 512 bytes from buffer to sector
                strcpyinvertido(buffer,databufftemp,posb);
                writeSector(databufftemp,posm);

                //controles
                posb=posb+1;
                i=i+1;
                temp=temp-1;
        }else if(temp<=0){
            //fill remaining bytes in directory with 0
                while(i<32){
                    dirbuff[pos+i]=0x0;
                    i=i+1;
                }
            
            //writing back everything
            writeSector(mapbuff,1);
            writeSector(dirbuff,2);
            return;
        }
    }

    syscall_printString("No se hallaron mas sectores libres");
    return;

}

void handleInterrupt21 (int AX, int BX, int CX, int DX){
    if(AX==0){
        printString(BX);
    }else if(AX==1){
        readString(BX);
    }else if(AX==2){
        readSector(BX,CX);
    }else if(AX==3){
        readFile(BX,CX);
    }else if(AX==4){
        executeProgram(BX,CX);
    }else if(AX==5){
        terminate();
    } else if(AX==6){
        writeSector(BX,CX);
    }else if(AX==7){
        deleteFile(BX);
    }else if(AX==8){
        writeFile(BX,CX,DX);
    }else if(AX==0xa){
        clearScreen();
    }else{
        printString("Error on InterruptCall");
    }   
}




