/** Escrito por Richard Mark Haes-ELlis **/

/*  DESCRIPCION:

Este juego esta programado para que
el ordenador sea capaz de "pensar"
por si solo, es decir, el ordenador
sabe que los barcos son rectos de modo
que ataca en lineas rectas si toca un barco
y ademas tiene algunas etrategias implementadas
El 50% de las veces el ordenador es el que gana
el partido.

EL codigo esta para que podais utilizarlo como
querais, cambiar cosas, mejorarlo lo que sea,
es libre.

Si teneis alguna duda o lo que sea podeis contactar
conmigo por aqui >> Richard_9661@hotmail.com
*/

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <stdio.h>
// #include <conio.h>
#define N 12

//VARIABLES ALEATORIAS
using namespace std;
//variables aleatorias
int random_row;            //    fila aleatoria
int random_column;         //    columna aleatoria
int random_dir;            //    direccion aleatorria
//variables coordenadas
int row1,column1;
int row2,column2;
//vector contador
int boat_hit_count_PC[4]={0,0,0,0};   //  contador de toques acertados para cada barco del ordenador
int boat_hit_count_PLY[4]={0,0,0,0};  //  contador de toques acertados para cada barco del jugador
//variables booleanas
bool hundido = false;     // booleano de estado del barco
bool alreadyhit=false;    // booleano de atacado repetitivo

//estructura de barcos
struct tipo_barco{
  char nombre[50];         // nombre del barco
  int numero; 			  // numero de barcos de este tipo
  int longitud;            // longuitud del barco
};

//PROTOTIPOS
void random_coordenates(void);
void reinicia_variables(int &SUMCOLUMN,int&SUMROW,int &I,bool &firstHit,bool &secondHit,bool &nextHit);
void imprime_tablero(char tablero_1[][N],char tablero_2[][N]);
void place_boat(tipo_barco barco,int row,int column,int dir,char tablero[][N]);
bool check_position(int row,int column,int dir,int lenght,char tablero[][N]);
bool coloca_barco(tipo_barco barco,char tablero[][N],int row,int column,int dir);
void coloca_barco_aleatorio(tipo_barco barco,char tablero[][N]);
bool tocado_o_hundido(int &boat,int a,int row,int column,char tablero_atacado[][N],char ataques[][N],int &boat_count);
bool attack(bool &valid,char tablero_atacado[][N],char ataques[][N],int row,int column,int *boatCount,int &boat_count);
bool random_attack(char tablero_atacado[][N],char ataques[][N],int &boat_count);
void imprime_tableroo(char tablero_1[][N]);
//FUNCION PRINCIPAL
int main()
{
  //tablero del ordenador
  char tablero_PC[N][N]={
  {201,205,205,205,205,205,205,205,205,205,205,187},
  {186,176,176,176,176,176,176,176,176,176,176,186},
  {186,176,176,176,176,176,176,176,176,176,176,186},
  {186,176,176,176,176,176,176,176,176,176,176,186},
  {186,176,176,176,176,176,176,176,176,176,176,186},
  {186,176,176,176,176,176,176,176,176,176,176,186},
  {186,176,176,176,176,176,176,176,176,176,176,186},
  {186,176,176,176,176,176,176,176,176,176,176,186},
  {186,176,176,176,176,176,176,176,176,176,176,186},
  {186,176,176,176,176,176,176,176,176,176,176,186},
  {186,176,176,176,176,176,176,176,176,176,176,186},
  {200,205,205,205,205,205,205,205,205,205,205,188}};
  //tablero del jugador
  char tablero_JUG[N][N]={
    {201,205,205,205,205,205,205,205,205,205,205,187},
  {186,176,176,176,176,176,176,176,176,176,176,186},
  {186,176,176,176,176,176,176,176,176,176,176,186},
  {186,176,176,176,176,176,176,176,176,176,176,186},
  {186,176,176,176,176,176,176,176,176,176,176,186},
  {186,176,176,176,176,176,176,176,176,176,176,186},
  {186,176,176,176,176,176,176,176,176,176,176,186},
  {186,176,176,176,176,176,176,176,176,176,176,186},
  {186,176,176,176,176,176,176,176,176,176,176,186},
  {186,176,176,176,176,176,176,176,176,176,176,186},
  {186,176,176,176,176,176,176,176,176,176,176,186},
  {200,205,205,205,205,205,205,205,205,205,205,188}};
  //tabla de ataques anteriores del ordenador
  char ataques_PC[N][N]={
  {201,205,205,205,205,205,205,205,205,205,205,187},
  {186,176,176,176,176,176,176,176,176,176,176,186},
  {186,176,176,176,176,176,176,176,176,176,176,186},
  {186,176,176,176,176,176,176,176,176,176,176,186},
  {186,176,176,176,176,176,176,176,176,176,176,186},
  {186,176,176,176,176,176,176,176,176,176,176,186},
  {186,176,176,176,176,176,176,176,176,176,176,186},
  {186,176,176,176,176,176,176,176,176,176,176,186},
  {186,176,176,176,176,176,176,176,176,176,176,186},
  {186,176,176,176,176,176,176,176,176,176,176,186},
  {186,176,176,176,176,176,176,176,176,176,176,186},
  {200,205,205,205,205,205,205,205,205,205,205,188}};
  //tabla de ataques anteriores del juagador
  char ataques_JUG[N][N]={
  {201,205,205,205,205,205,205,205,205,205,205,187},
  {186,176,176,176,176,176,176,176,176,176,176,186},
  {186,176,176,176,176,176,176,176,176,176,176,186},
  {186,176,176,176,176,176,176,176,176,176,176,186},
  {186,176,176,176,176,176,176,176,176,176,176,186},
  {186,176,176,176,176,176,176,176,176,176,176,186},
  {186,176,176,176,176,176,176,176,176,176,176,186},
  {186,176,176,176,176,176,176,176,176,176,176,186},
  {186,176,176,176,176,176,176,176,176,176,176,186},
  {186,176,176,176,176,176,176,176,176,176,176,186},
  {186,176,176,176,176,176,176,176,176,176,176,186},
  {200,205,205,205,205,205,205,205,205,205,205,188}};
  //crea los barcos
  struct tipo_barco barco[4]={{"Portaaviones",1,6},{"Destructor" ,1,5},{"Buque",2,3},{"Lancha",3,2}};
  int i,j,I=0,row,column,turno,SUMCOLUMN=1,SUMROW=1;
  bool valid=false,acepted=false;
  bool firstHit=false,secondHit=false,nextHit=false,golpeado=false;
  //variables para determinar quien a ganado
  bool PCWIN=false,PLYWIN=false;
  //cuenta los barcos hundidos
  int boat_count_PC=0;
  int boat_count_PLY=0;
  //variable para la interfaz (no es importante)
  int resp;
  //semilla para crear variables aleatorias
  srand(time(NULL));
  //interfaz
  printf("\n\n\n                        HUNDIR LA FLOTA\n\n");
  printf("        LOS TABLEROS SON DE 10x10, COORDENADAS MENORES DE 1, O MAYORES DE 10\n        NO SON VALIDOS, !QUE EMPIECE EL JUEGO!\n");




  //inicializa tablero del pc
  for(i=0;i<4;i++)//cuatro tipos barcos
  {
    for(j=0;j<(2*i)+(1-(2*j));j++)//algoritmo que cuenta 1,1,2,3 veces en cada iteracion del bucle i
    {
      coloca_barco_aleatorio(barco[i],tablero_PC);//coloca el barco aleatoriamente
    }
  }//alfinal se acaban colocando 7 barcos

  //inicializa tablero del jugador
  do
  {
    printf("\n\n        ¿Quieres introducir los barcos manualmente o aleatoriamente?\n        1 = aleatorio\n        0 = manual\n\n        ");
    scanf("%i",&resp);//segun lo que respondes se coloca aleatoriamente o manualmente
    if(resp==1)//crea el tablero aleatoriamente
    {
      for(i=0;i<4;i++)//mismo procedimiento que el anterior con los barcos del ordenador (linea 122)
      {
        for(j=0;j<(2*i)+(1-(2*j));j++)//lo mismo que antes (linea 122)
        {
          coloca_barco_aleatorio(barco[i],tablero_JUG);
        }
      }
      acepted=true; //para salir de bucle do-while
    }
    else if(resp==0)//crea el tablero manualmente
    {
      for(i=0;i<4;i++)//cuatro tipo de barcos
      {
        for(j=0;j<(2*i)+(1-(2*j));j++)
        {
          do
          {
            imprime_tablero(tablero_JUG,ataques_JUG);//imprime los tableros del jugador
            printf("\n        %s de dimension %i\n",barco[i].nombre,barco[i].longitud);
            printf("\n        Columna:");
            scanf("%i",&random_column);//reutilizo las variables random que no las estoy utilizando en este momento
            printf("\n        Fila:");
            scanf("%i",&random_row);//reutilizo las variables random que no las estoy utilizando en este momento
            printf("\n        Direccion:\n        1 = vertical\n        0 = horizontal\n");
            scanf("%i",&random_dir);//reutilizo las variables random que no las estoy utilizando en este momento
            valid = coloca_barco(barco[i],tablero_JUG,random_row,random_column,random_dir);//procede a colocar y si
            if(valid==false)                                                               //no cumple con los requisitos
            {                                                                              //devuelve un false y true
              printf("\n        Error, coordenadas incorrectas\n");                      //al contrario
            }
            else
            {
              system("CLS");  //limpia la pantalla
            }
          }while(valid==false);  //se seguira ejecuntando hasta que la posicion del barco sea valida
          //que este dentro del tablero, que no se solape con otros barcos.. etc.
        }
      }
      acepted=true;//una vez colocado todo correctamente se le asigna true para salir del bucle
    }
  }while(acepted==false);

  acepted=false;//lo vuelvo a dejar como esta

  //bucle de turnos
  for(turno=2;turno<2000 && PCWIN==false && PLYWIN ==false;turno++){//cre un contador de 2000 turnos
    if(turno%2==0)//si turno es par
    {
      system("CLS");
      printf("\n\n        TU TURNO\n\n");
      printf("\n\n        Tablero:              Ataques anteriores:\n\n");
      imprime_tablero(tablero_JUG,ataques_JUG);// imprime tableros
      //================================================================================================================
      do
      {
        printf("\n        Columna:"); //imprime
        scanf("%i",&random_column);   // guarda el varo en la variable random_column (es la misma par las variables aleatorias, la reutiliamos)
        printf("\n        Fila:");    // lo mismo aqui
        scanf("%i",&random_row);
        attack(valid,tablero_PC,ataques_JUG,random_row,random_column,boat_hit_count_PLY,boat_count_PLY); // llama a la fucion attack con las coordenadas
        // introducidas
        if(valid==false)    //si las coordenadas son validas. Notar que valid es una variable global que se ve modificada en la funcion attack.
        {
          printf("\n        Error:");
          imprime_tablero(tablero_JUG,ataques_JUG); //imprime loos tableros indicados  en los paramatros.
        }
        if(alreadyhit==true) //si ya se ha atacado ahi
        {
          printf("\n        Ya has atacado aqui."); //imprime el mensaje indicado
        }
        if(hundido==true)    //si resulta ser hunndido
        {
          hundido=false;
        }
        printf("\n        ");
        system("pause");
        system("CLS");

      }while(valid==false || alreadyhit==true); //mientras que el ataque no sea valido o ya se haya atacado ahi se vuelve a preguntar por las ccoordenadas.
      //================================================================================================================
    }
    else  //si turno no es par, osea impar ==== turno del PC
    {
      printf("\n\n        TURNO DEL PC\n\n");
      if(firstHit==true)//si el ataqque del anterior turno fue exito
      {
        if(secondHit==true)//si el segundo ataque consecutivo fue exito
        {
          if(row1==row2)// si el barco esta orientado horizontalmentee
          {
            if(column1<column2)// con cual atac� primmero
            {
              do 				//  a partir de aqui ya no lo voy a explicar hasta el siguente comentario
              {  				//  por que es uns pedazo de lio que flipas (y no hay mucho que aprender aqui)
                switch(I)   //	solo hay un laberinto de switches do-whiles e ifs.... no mola...
                {			//	de igual forma esta parte es la que se encarga de que el ordenador
                  case 0: //	"piense" por si solo de modo que sabe donde atacar con etrategias y tal..
                  nextHit=attack(valid,tablero_JUG,ataques_PC,row1,column2+SUMCOLUMN,boat_hit_count_PC,boat_count_PC);
                  break;

                  case 1:
                  nextHit=attack(valid,tablero_JUG,ataques_PC,row1,column1-SUMCOLUMN,boat_hit_count_PC,boat_count_PC);
                  break;
                }
                if(nextHit==true && hundido==false)
                {
                  SUMCOLUMN++;
                }
                if(nextHit==false)
                {
                  I++;
                  SUMCOLUMN=1;
                }
                if(hundido==true)
                {
                  reinicia_variables(SUMCOLUMN,SUMROW,I,firstHit,secondHit,nextHit);
                }
              }while(valid==false);
            }
            else
            {
              do
              {
                switch(I)
                {
                  case 0:
                  nextHit=attack(valid,tablero_JUG,ataques_PC,row1,column1+SUMCOLUMN,boat_hit_count_PC,boat_count_PC);
                  break;

                  case 1:
                  nextHit=attack(valid,tablero_JUG,ataques_PC,row1,column2-SUMCOLUMN,boat_hit_count_PC,boat_count_PC);
                  break;
                }
                if(nextHit==true && hundido==false)
                {
                  SUMCOLUMN++;
                }
                if(nextHit==false)
                {
                  I++;
                  SUMCOLUMN=1;
                }
                if(hundido==true)
                {
                  reinicia_variables(SUMCOLUMN,SUMROW,I,firstHit,secondHit,nextHit);
                }
              }while(valid==false);
            }
          }
          else if(column1==column2)
          {
            if(row1<row2)
            {
              do
              {
                switch(I)
                {
                  case 0:
                  nextHit=attack(valid,tablero_JUG,ataques_PC,row2+SUMROW,column1,boat_hit_count_PC,boat_count_PC);
                  break;

                  case 1:
                  nextHit=attack(valid,tablero_JUG,ataques_PC,row1-SUMROW,column1,boat_hit_count_PC,boat_count_PC);
                  break;
                }
                if(nextHit==true && hundido==false)
                {
                  SUMROW++;
                }
                if(nextHit==false)
                {
                  I++;
                  SUMROW=1;
                }
                if(hundido==true)
                {
                  reinicia_variables(SUMCOLUMN,SUMROW,I,firstHit,secondHit,nextHit);
                }
              }while(valid==false);
            }
            else
            {
              do
              {
                switch(I)
                {
                  case 0:
                  nextHit=attack(valid,tablero_JUG,ataques_PC,row1+SUMROW,column1,boat_hit_count_PC,boat_count_PC);
                  break;

                  case 1:
                  nextHit=attack(valid,tablero_JUG,ataques_PC,row2-SUMROW,column1,boat_hit_count_PC,boat_count_PC);
                  break;
                }
                if(nextHit==true && hundido==false)
                {
                  SUMROW++;
                }
                if(nextHit==false)
                {
                  I++;
                  SUMROW=1;
                }
                if(hundido==true)
                {
                  reinicia_variables(SUMCOLUMN,SUMROW,I,firstHit,secondHit,nextHit);
                }
              }while(valid==false);
            }
          }

        }
        else
        {
          do
          {
            switch(I)
            {
              case 0: secondHit=attack(valid,tablero_JUG,ataques_PC,row1,column1+1,boat_hit_count_PC,boat_count_PC);
              if(secondHit==true)
              {
                row2=row1;
                column2=column1+1;
              }
              break;
              case 1: secondHit=attack(valid,tablero_JUG,ataques_PC,row1-1,column1,boat_hit_count_PC,boat_count_PC);
              if(secondHit==true)
              {
                row2=row1-1;
                column2=column1;
              }
              break;
              case 2: secondHit=attack(valid,tablero_JUG,ataques_PC,row1,column1-1,boat_hit_count_PC,boat_count_PC);
              if(secondHit==true)
              {
                row2=row1;
                column2=column1-1;
              }
              break;
              case 3: secondHit=attack(valid,tablero_JUG,ataques_PC,row1+1,column1,boat_hit_count_PC,boat_count_PC);
              if(secondHit==true)
              {
                row2=row1+1;
                column2=column1;
              }
              break;
            }
            if(secondHit==false)
            {
              I++;
            }
            else
            {
              I=0;
            }
            if(hundido==true)
            {
              reinicia_variables(SUMCOLUMN,SUMROW,I,firstHit,secondHit,nextHit);
            }
          }while(valid==false);
        }
      }
      else
      {	do //genera coordenadas aleatorias hasta que se verifique si esta dentro de la matriz y si el ataque es valido( no repetido etc)
        {
          firstHit=random_attack(tablero_JUG,ataques_PC,boat_count_PC);
        }while(alreadyhit==true);
      }
      imprime_tableroo(tablero_JUG);
      printf("\n        ");
      system("pause");
    }
    if(boat_count_PC==7) //si el contador de barcos hundidos del pc es 7 esque ha destruido todos y ha ganado
    {
      system("CLS");
      PCWIN=true;
      printf("\n\n\n\n\n\n\n        HAS PERDIDO\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    }
    else if(boat_count_PLY==7) // si el contador de barcos hundidos del jugador es 7 esque ha destruido todos y ha ganado
    {
      system("CLS");
      PLYWIN=true;
      printf("\n\n\n\n\n\n\n        HAS GANADO\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    }
  }
}

//genera coordenadas aleatorias con direccion
void random_coordenates(void)
{
  random_row=1+rand()%(10);
  random_column=1+rand()%(10);
  random_dir=rand()%(2);
}

void imprime_tableroo(char tablero_1[][N])
{
  printf("\n");
  int i,j;
  for(i=0;i<N;i++) // se imprime los tableros a la vez 1 bucle para la fila de los dos y 2 bucles para las columnas de ambos
  {
    printf("        ");// espacio entre la ventana y el primer tablero
    for(j=0;j<N;j++)
    {
      printf("%c",tablero_1[i][j]);
    }
    printf("\n");
  }
}

//reestablece varias aleatorias a su predeterminado
void reinicia_variables(int &SUMCOLUMN,int&SUMROW,int &I,bool &firstHit,bool &secondHit,bool &nextHit)
{
  SUMCOLUMN=1;
  SUMROW=1;
  I=0;
  row1=0;
  row2=0;
  column1=0;
  column2=0;
  hundido=false;
  firstHit=false;
  secondHit=false;
  nextHit=false;
}

//imprime dos tableros uno al lado de otro  (ejecuta el codigo para verlo)
void imprime_tablero(char tablero_1[][N],char tablero_2[][N])
{
  printf("\n");
  int i,j;
  for(i=0;i<N;i++) // se imprime los tableros a la vez 1 bucle para la fila de los dos y 2 bucles para las columnas de ambos
  {
    printf("        ");// espacio entre la ventana y el primer tablero
    for(j=0;j<N;j++)
    {
      printf("%c",tablero_1[i][j]);
    }
    printf("          ");// espacio entre tableros
    for(j=0;j<N;j++)
    {
      printf("%c",tablero_2[i][j]);
    }
    printf("\n");
  }
}

//coloca un barco segun los parametros de entrada
void place_boat(tipo_barco barco,int row,int column,int dir,char tablero[][N])
{
  int fila,columna;

  if(dir==0)//horizontal
  {
    for(columna=column;columna<column+barco.longitud;columna++)//coloca el valor del barco la longuitud del barco
    {
      tablero[row][columna]=barco.longitud+48; //40 en ascii es 0, le sumamos la longitud y nos da el valor del barco (6,5,3 o 2)
    }
  }else if(dir==1)//vertical
  {
    for(fila=row;fila<row+barco.longitud;fila++) //igual
    {
      tablero[fila][column]=barco.longitud+48; //igual
    }
  }
}

//comprueba que la posicion es valida en un tablero
bool check_position(int row,int column,int dir,int lenght,char tablero[][N])
{
  int fila,columna,k;
  bool result = true;

  if(dir==0)//direccion horizontal
  {
    for(k=0;k<lenght && result == true;k++)// la longuitud led barco
    {
      for(fila=-1;fila<=1 && result == true;fila++)// contador de [-1,0,+1] horizontalmente
      {
        for(columna=-1;columna<=1 && result == true;columna++)// contador de [-1,0,+1] verticalmente
        {
          //si los alrededores son iguales a cualquier valor de otro barco (6,5,3 o 1)
          if(tablero[row+(fila)][column+(columna)]==54 || tablero[row+(fila)][column+(columna)]==53 || tablero[row+(fila)][column+(columna)]==51 || tablero[row+(fila)][column+(columna)]==50)
          {
            result = false; //posicion no valida
          }
        }
      }
      column++;
    }

  }
  else if(dir==1)//direccion vertical
  {
    for(k=0;k<lenght && result == true;k++)// la longuitud led barco
    {
      for(fila=-1;fila<2 && result == true;fila++)// contador de [-1,0,+1] horizontalmente
      {
        for(columna=-1;columna<2 && result == true;columna++)// contador de [-1,0,+1] verticalmente
        {
          //si los alrededores son iguales a cualquier valor de otro barco (6,5,3 o 1)
          if(tablero[row+(fila)][column+(columna)]==54 || tablero[row+(fila)][column+(columna)]==53 || tablero[row+(fila)][column+(columna)]==51 || tablero[row+(fila)][column+(columna)]==50)
          {
            result = false; //posicion no valida
          }
        }
      }
      row++;
    }

  }

  return result;
}

//intenta colocar un barco con las coordenaddas dadas
bool coloca_barco(tipo_barco barco,char tablero[][N],int row,int column,int dir)
{
  bool ok=false;

  if(row<11 && row>0 && column<11 && column>0 && dir<2 && dir>=0)//si las coordenadas estan dentro de la matriz
  {
    if(tablero[row][column]!=54 && tablero[row][column]!=53 && tablero[row][column]!= 51 && tablero[row][column]!=50) //si la posicion
    {                                                                                                   //es diferente de todos los
      if(dir==0)                                                                                      //valores de los barcos (6,5,3 o 1)
      {
        if((barco.longitud-1)+column <=10)  //con el tama�o del barco, cabe en el tablero?
        {
          if(check_position(row,column,dir,barco.longitud,tablero)) //es todo agua en el entorno del barco?
          {
            place_boat(barco,row,column,dir,tablero);// si pasa todas las condiciones se coloca el barco
            ok=true; //se asigna true a la variable ok que sera devuelta
          }
        }
      }
      else
      {
        if((barco.longitud-1)+row <= 10)  //con el tama�o del barco, cabe en el tablero?
        {
          if(check_position(row,column,dir,barco.longitud,tablero)) //es todo agua en el entorno del barco?
          {
            place_boat(barco,row,column,dir,tablero);// si pasa todas las condiciones se coloca el barco
            ok=true; //se asigna true a la variable ok que sera devuelta
          }
        }
      }

    }
  }
  return ok;
}

//coloca un barco de forma aleatoria
void coloca_barco_aleatorio(tipo_barco barco,char tablero[][N])
{
  bool valid=false;
  do // bucle que genera coordenadas aleatorias hasta que alugna sea validas para colocar el barco con sus requisitos
  {  // si cabe en el tablero si esta dentro del tablero si se solapa o no etc..
    random_coordenates();
    valid = coloca_barco(barco,tablero,random_row,random_column,random_dir);
  }while(valid==false); // una vez se coloque el barco se sale de bucle
}

//comprueba si el ataque solo toca o hunde el barco
bool tocado_o_hundido(int &boat,int a,int row,int column,char tablero_atacado[][N],char ataques[][N],int &boat_count)
{
  bool prevHit =  false;
  boat++; // aumenta el contador del barco correspondiente,sea boatcount[0] o 1 o 3.. mirar la variable que se pasa en la linea
  if(boat==a) // a es el tama�o del barco, si resulta que el contador llega a este valor esque se ha hundido
  {
    boat=0; //se vuelve a piner a 0 el contador para contar los otros barcos del mismo tipo
    printf("\n        -> Barco hundido!\n");
    tablero_atacado[row][column]='X'; //se coloca una X en la posicion tocada
    ataques[row][column]='X';         //en los dos tableros, el se ataques y el de el jugador que  sea
    hundido = true;
    prevHit = true; //esto es para los ataques automaticos del ordenador ( no es importante para entender )
    boat_count++; //contador de barcos hundidos, una vez este valor alcance los barcos totales, te habra ganado.
  }
  else
  {
    printf("\n        ->  Tocado!\n");
    tablero_atacado[row][column]='X'; //se coloca una X en la posicion tocada
    ataques[row][column]='X';         //en los dos tableros, el se ataques y el de el jugador que  sea
    prevHit = true; //esto es para los ataques automaticos del ordenador ( no es importante para entender )
  }
  return prevHit;
}
//ataca al tablero
bool attack(bool &valid,char tablero_atacado[][N],char ataques[][N],int row,int column,int *boatCount,int &boat_count)
{
  alreadyhit=false; //variable de ataque repetitivo
  bool prevHit=false;

  if(row>10 || row<1 || column>10 || column<1)//si esta fuera del tablero ya no es valido
  {
    valid=false;
  }
  else// si coincide con algun valor de barco (6,5,3 o 2  en ascii) entonces ataca en dicha coordenada y devuelve true
  {
    if(tablero_atacado[row][column]==54)
    {
      prevHit=tocado_o_hundido(boatCount[0],6,row,column,tablero_atacado,ataques,boat_count);
      valid = true;
    }
    else if(tablero_atacado[row][column]==53)
    {
      prevHit=tocado_o_hundido(boatCount[1],5,row,column,tablero_atacado,ataques,boat_count);
      valid = true;
    }
    else if(tablero_atacado[row][column]== 51)
    {
      prevHit=tocado_o_hundido(boatCount[2],3,row,column,tablero_atacado,ataques,boat_count);
      valid = true;
    }
    else if(tablero_atacado[row][column]==50)
    {
      prevHit=tocado_o_hundido(boatCount[3],2,row,column,tablero_atacado,ataques,boat_count);
      valid = true;
    }
    else if(tablero_atacado[row][column]==88 || tablero_atacado[row][column]==178) // si alguna coordenada reepetitiva
    {
      alreadyhit=true; //variable repetitiva a true
      valid=false;
    }
    else// si toca agua
    {
      printf("\n        -> Agua!\n");
      tablero_atacado[row][column]=178;
      ataques[row][column]=178;
      prevHit=false;
      valid = true;
    }

  }

  return prevHit;
}
//genera unas coordenadas aleatorias para atacar
bool random_attack(char tablero_atacado[][N],char ataques[][N],int &boat_count)
{
  bool valid=true,prevHit=false;
  do //bucle para generar coordenadas que sean validas( que esteen contenidas dentro del tablero, que no sea repetida.. etc)
  {
    random_coordenates();//genera coordenadas aleatorias
    row1=random_row;
    column1=random_column;
    prevHit = attack(valid,tablero_atacado,ataques,row1,column1,boat_hit_count_PC,boat_count);
  }while(valid==false);
  return prevHit;
}
