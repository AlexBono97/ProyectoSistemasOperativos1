
char * siso = "SISTEMAS OPERATIVOS I 0";
char * uni = "UNIVERSIDAD TECNOLOGICA CENTROAMERICANA (UNITEC) 0";
char * datos = "21511028 - ALEXANDER BONO \0";
char * titulo = "MI PRIMER SISTEMA OPERATIVO \0";
/*idiomas*/
char * esp = " Hola Mundo !! \0";
char * eng = " Hello world!! \0";
char * deu = " Hallo mensen!! \0";
char * fr = " Salut monde!! \0";
char * pr = " Ola mundo !! \0";
char * cat = " Hola Mon !! \0";
char * cro = " Pozdrav svijetu! \0";
char * dan = " Hej verden! \0";
char * esper = " Saluton Mondo! \0";
char * finl = " Moi maailma!! \0";
char * hol = " Hallo wereld!! \0";
char * nor = " Hei verden!! \0";
char * tur = " Merhaba dunya!! \0";
char * sue = " Hej varlden!! \0";
char * cze = " Dobry den svet!! \0";
char * pol = " witaj swiecie!! \0";
char * ita = " Ciao mondo!! \0";
char * isl = " Hallo heimur!! \0";
char * lat = " salve mundi!! \0";
char * vas = " Kaixo mundua!! \0"; 
main(){
    int t = 0x8000;
    int i = 0;
    int temp = 0;
    while(t<0x8036){
    putInMemory(0xb000,t,' ');
    t=t+1;
    putInMemory(0xb000,t,0x7);
    t=t+1;
    }
    
    /*SISTEMAS*/
    t = 0x8036;
    i = 0;
    while(siso[i]!='0'){
    putInMemory(0xb000,t,siso[i]);
    t=t+1;
    putInMemory(0xb000,t,0x7);
    t=t+1;
    i=i+1;
    }
    /*mas espacio*/
    t = 0x8066;
    while(t<0x80C0){
    putInMemory(0xb000,t,' ');
    t=t+1;
    putInMemory(0xb000,t,0x7);
    t=t+1;
    }

    /*UNIVERSIDAD TECNOLOGICA CENTROAMERICANA (UNITEC)*/
    t = 0x80C0;
    i = 0;
    while(uni[i]!='0'){
    putInMemory(0xb000,t,uni[i]);
    t=t+1;
    putInMemory(0xb000,t,0x7);
    t=t+1;
    i=i+1;
    }
    /*ESPACIADO*/
    t = 0x8120;
    while(t<0x8170){
    putInMemory(0xb000,t,' ');
    t=t+1;
    putInMemory(0xb000,t,0x7);
    t=t+1;
    }

    /*Datos*/
    t = 0x8170;
    i = 0;
    while(datos[i]!='\0'){
    putInMemory(0xb000,t,datos[i]);
    t=t+1;
    putInMemory(0xb000,t,0x7);
    t=t+1;
    i=i+1;
    }
    /*ESPACIOS*/
    t = 0x81A2;
    while(t<0x820E){
    putInMemory(0xb000,t,' ');
    t=t+1;
    putInMemory(0xb000,t,0x7);
    t=t+1;
    }

    /*titulo*/
    t = 0x820E;
    i = 0;
    while(titulo[i]!='\0'){
    putInMemory(0xb000,t,titulo[i]);
    t=t+1;
    putInMemory(0xb000,t,0x7);
    t=t+1;
    i=i+1;
    }

    /*---DIVISION--- */
    t = 0x8280;
    while(t<0x8320){
    putInMemory(0xb000,t,'-');
    t=t+1;
    putInMemory(0xb000,t,0xB);
    t=t+1;
    }
    
   /*HELLO WORLD EN DISTINTOS IDIOMAS*/
   /*Espanol*/
    t=0x8320;
    i=0;
    temp=0;/*160 para cambiar linea*/
    while(t<0x83C0){
        putInMemory(0xb000,t,'*');
        t=t+1;
        putInMemory(0xb000,t,0x9);
        t=t+1;
        while(t>=0x835B & esp[i]!='\0'){
            putInMemory(0xb000,t,esp[i]);
            t=t+1;
            putInMemory(0xb000,t,0xA);
            t=t+1;
            i=i+1;
        }
    }
    /*English*/
    t=0x83C0;
    i=0;
    while(t<0x8460){
        putInMemory(0xb000,t,'*');
        t=t+1;
        putInMemory(0xb000,t,0x7);
        t=t+1;
        while(t>=0x83FB & eng[i]!='\0'){
            putInMemory(0xb000,t,eng[i]);
            t=t+1;
            putInMemory(0xb000,t,0x8);
            t=t+1;
            i=i+1;
        }
    }
     /*Deutsch*/
    t=0x8460;
    i=0;
    while(t<0x8500){
        putInMemory(0xb000,t,'*');
        t=t+1;
        putInMemory(0xb000,t,0x5);
        t=t+1;
        while(t>=0x849B & deu[i]!='\0'){
            putInMemory(0xb000,t,deu[i]);
            t=t+1;
            putInMemory(0xb000,t,0x6);
            t=t+1;
            i=i+1;
        }
    }
     /*French*/
    t=0x8500;
    i=0;
    while(t<0x85A0){
        putInMemory(0xb000,t,'*');
        t=t+1;
        putInMemory(0xb000,t,0x3);
        t=t+1;
        while(t>=0x853B & fr[i]!='\0'){
            putInMemory(0xb000,t,fr[i]);
            t=t+1;
            putInMemory(0xb000,t,0x4);
            t=t+1;
            i=i+1;
        }
    }
     /*Portuguese*/
    t=0x85A0;
    i=0;
    while(t<0x8640){
        putInMemory(0xb000,t,'*');
        t=t+1;
        putInMemory(0xb000,t,0x1);
        t=t+1;
        while(t>=0x85DB & pr[i]!='\0'){
            putInMemory(0xb000,t,pr[i]);
            t=t+1;
            putInMemory(0xb000,t,0x2);
            t=t+1;
            i=i+1;
        }
    }
    /*Catalan*/
    t=0x8640;
    i=0;
    while(t<0x86E0){
        putInMemory(0xb000,t,'*');
        t=t+1;
        putInMemory(0xb000,t,0xE);
        t=t+1;
        while(t>=0x867B & cat[i]!='\0'){
            putInMemory(0xb000,t,cat[i]);
            t=t+1;
            putInMemory(0xb000,t,0xF);
            t=t+1;
            i=i+1;
        }
    }
    /*Croatian*/
    t=0x86E0;
    i=0;
    while(t<0x8780){
        putInMemory(0xb000,t,'*');
        t=t+1;
        putInMemory(0xb000,t,0xC);
        t=t+1;
        while(t>=0x871B & cro[i]!='\0'){
            putInMemory(0xb000,t,cro[i]);
            t=t+1;
            putInMemory(0xb000,t,0xD);
            t=t+1;
            i=i+1;
        }
    }
    /*Danish*/
    t=0x8780;
    i=0;
    while(t<0x8820){
        putInMemory(0xb000,t,'*');
        t=t+1;
        putInMemory(0xb000,t,0xA);
        t=t+1;
        while(t>=0x87BB & dan[i]!='\0'){
            putInMemory(0xb000,t,dan[i]);
            t=t+1;
            putInMemory(0xb000,t,0xB);
            t=t+1;
            i=i+1;
        }
    }
    /*Esperanto*/
    t=0x8820;
    i=0;
    while(t<0x88C0){
        putInMemory(0xb000,t,'*');
        t=t+1;
        putInMemory(0xb000,t,0x8);
        t=t+1;
        while(t>=0x885B & esper[i]!='\0'){
            putInMemory(0xb000,t,esper[i]);
            t=t+1;
            putInMemory(0xb000,t,0x9);
            t=t+1;
            i=i+1;
        }
    }
    /*Finnish*/
    t=0x88C0;
    i=0;
    while(t<0x8960){
        putInMemory(0xb000,t,'*');
        t=t+1;
        putInMemory(0xb000,t,0x6);
        t=t+1;
        while(t>=0x88FB & finl[i]!='\0'){
            putInMemory(0xb000,t,finl[i]);
            t=t+1;
            putInMemory(0xb000,t,0x7);
            t=t+1;
            i=i+1;
        }
    }
    /*Holandes*/
    t=0x8960;
    i=0;
    while(t<0x8A00){
        putInMemory(0xb000,t,'*');
        t=t+1;
        putInMemory(0xb000,t,0x4);
        t=t+1;
        while(t>=0x899B & hol[i]!='\0'){
            putInMemory(0xb000,t,hol[i]);
            t=t+1;
            putInMemory(0xb000,t,0x5);
            t=t+1;
            i=i+1;
        }
    }
    /*Norwegian*/
    t=0x8A00;
    i=0;
    while(t<0x8AA0){
        putInMemory(0xb000,t,'*');
        t=t+1;
        putInMemory(0xb000,t,0x2);
        t=t+1;
        while(t>=0x8A3B & nor[i]!='\0'){
            putInMemory(0xb000,t,nor[i]);
            t=t+1;
            putInMemory(0xb000,t,0x3);
            t=t+1;
            i=i+1;
        }
    }
    /*Turkish*/
    t=0x8AA0;
    i=0;
    while(t<0x8B40){
        putInMemory(0xb000,t,'*');
        t=t+1;
        putInMemory(0xb000,t,0xF);
        t=t+1;
        while(t>=0x8ADB & tur[i]!='\0'){
            putInMemory(0xb000,t,tur[i]);
            t=t+1;
            putInMemory(0xb000,t,0x1);
            t=t+1;
            i=i+1;
        }
    }
    /*Sueco*/
    t=0x8B40;
    i=0;
    while(t<0x8BE0){
        putInMemory(0xb000,t,'*');
        t=t+1;
        putInMemory(0xb000,t,0xD);
        t=t+1;
        while(t>=0x8B7B & sue[i]!='\0'){
            putInMemory(0xb000,t,sue[i]);
            t=t+1;
            putInMemory(0xb000,t,0xE);
            t=t+1;
            i=i+1;
        }
    }
    /*Czech*/
    t=0x8BE0;
    i=0;
    while(t<0x8C80){
        putInMemory(0xb000,t,'*');
        t=t+1;
        putInMemory(0xb000,t,0xB);
        t=t+1;
        while(t>=0x8C1B & cze[i]!='\0'){
            putInMemory(0xb000,t,cze[i]);
            t=t+1;
            putInMemory(0xb000,t,0xC);
            t=t+1;
            i=i+1;
        }
    }
    /*Polish*/
    t=0x8C80;
    i=0;
    while(t<0x8D20){
        putInMemory(0xb000,t,'*');
        t=t+1;
        putInMemory(0xb000,t,0x9);
        t=t+1;
        while(t>=0x8CBB & pol[i]!='\0'){
            putInMemory(0xb000,t,pol[i]);
            t=t+1;
            putInMemory(0xb000,t,0xA);
            t=t+1;
            i=i+1;
        }
    }
    /*Italian*/
    t=0x8D20;
    i=0;
    while(t<0x8DC0){
        putInMemory(0xb000,t,'*');
        t=t+1;
        putInMemory(0xb000,t,0x7);
        t=t+1;
        while(t>=0x8D5B & ita[i]!='\0'){
            putInMemory(0xb000,t,ita[i]);
            t=t+1;
            putInMemory(0xb000,t,0x8);
            t=t+1;
            i=i+1;
        }
    }
    /*Iceland*/
    t=0x8DC0;
    i=0;
    while(t<0x8E60){
        putInMemory(0xb000,t,'*');
        t=t+1;
        putInMemory(0xb000,t,0x5);
        t=t+1;
        while(t>=0x8DFB & isl[i]!='\0'){
            putInMemory(0xb000,t,isl[i]);
            t=t+1;
            putInMemory(0xb000,t,0x6);
            t=t+1;
            i=i+1;
        }
    }
    /*Latin*/
    t=0x8E60;
    i=0;
    while(t<0x8F00){
        putInMemory(0xb000,t,'*');
        t=t+1;
        putInMemory(0xb000,t,0x3);
        t=t+1;
        while(t>=0x8E9B & lat[i]!='\0'){
            putInMemory(0xb000,t,lat[i]);
            t=t+1;
            putInMemory(0xb000,t,0x4);
            t=t+1;
            i=i+1;
        }
    }
    /*Vasco*/
    t=0x8F00;
    i=0;
    while(t<0x8FA0){
        putInMemory(0xb000,t,'*');
        t=t+1;
        putInMemory(0xb000,t,0x1);
        t=t+1;
        while(t>=0x8F3B & vas[i]!='\0'){
            putInMemory(0xb000,t,vas[i]);
            t=t+1;
            putInMemory(0xb000,t,0x2);
            t=t+1;
            i=i+1;
        }
    }
    



    /*putInMemory(0xb000,0x83C0,'A');
    putInMemory(0xb000,0x83C1,0x7);*/

}
