#include "io430.h"
#include "displayLCD.h"
#include "teclado_debounce.h"

//Aluna: Rebekah Pinheiro ELT3B

char dado = 1, status;

char palavra[11]="23:59:55";
char data[11]="31/12/23";

char isActiveKeyboard = 0;
char tecla = 0;
char conferetecla = 0;
char cursorColumn = 4;

char month = 12;
char dayUNI= 1;
char dayDEZ= 3;
char monthUNI = 2;
char monthDEZ = 1;
char yearUNI = 3;
char yearDEZ = 2;
char ultimoDiaDoMes = 0;

char segundoUNI = 5;
char segundoDEZ = 5;
char minutoUNI = 9;
char minutoDEZ = 5;
char horaUNI = 3;
char horaDEZ = 2;

void AtualizarValor(char cursorLine, char cursorColumn, char tecla)
{
  tecla-=48;
  if (cursorLine == 1) {
    if (cursorColumn == 5) {
      horaDEZ = tecla;
    } else if (cursorColumn == 6) {
      horaUNI = tecla;
    } else if (cursorColumn == 8) {
      minutoDEZ = tecla;
    } else if (cursorColumn == 9) {
      minutoUNI = tecla;
    } else if (cursorColumn == 11) {
      segundoDEZ = tecla;
    } else if (cursorColumn == 12) {
      segundoUNI = tecla;
    }
  } else if (cursorLine == 2) {
    if (cursorColumn == 5) {
      dayDEZ = tecla;
    } else if (cursorColumn == 6) {
      dayUNI = tecla;
    } else if (cursorColumn == 8) {
      monthDEZ = tecla;
    } else if (cursorColumn == 9) {
      monthUNI = tecla;
    } else if (cursorColumn == 11) {
      yearDEZ = tecla;
    } else if (cursorColumn == 12) {
      yearUNI = tecla;
    }
  }
  
  LCD_PosicaoCursor(cursorLine, cursorColumn);
  LCD_EscreveCaractere(tecla+=48);
}

void Teclado ()
{
  conferetecla = Teclado_Status();
  tecla = Teclado_Leitura();
  char cursorLine = 1;
  if (tecla == '#') {
    while (conferetecla) {
      tecla = Teclado_Leitura();
      if (tecla && tecla != '#') {
        cursorColumn++;
        if (cursorColumn == 7 || cursorColumn == 10) {
          cursorColumn++;
        }

        AtualizarValor(cursorLine, cursorColumn, tecla);
      }
      else if (tecla == '#' && cursorLine == 2) {
        conferetecla = 0;
        break;
      } else if (tecla == '#') {
        cursorLine++;
      }

      if (cursorColumn == 12) {
        cursorColumn = 4;
      }
    }
    cursorLine = 1;
    cursorColumn = 4;
  } else {
    conferetecla = 0;
  }
  
}

void Segundos (void)
{
  if (segundoUNI < 10 ){
    LCD_PosicaoCursor(1,12);
    LCD_EscreveCaractere(segundoUNI+48);
  }
  else {
    segundoUNI = 0;
    segundoDEZ++;
    LCD_PosicaoCursor(1,12);
    LCD_EscreveCaractere(segundoUNI+48);
    LCD_PosicaoCursor(1,11);
    LCD_EscreveCaractere(segundoDEZ+48);
  }
}

void Minutos (void)
{
  minutoUNI++;
  if (minutoUNI < 10){
    LCD_PosicaoCursor(1,9);
    LCD_EscreveCaractere(minutoUNI + 48);
  }
  else{
    minutoUNI = 0;
    minutoDEZ++;
    LCD_PosicaoCursor(1,9);
    LCD_EscreveCaractere(minutoUNI + 48);
    LCD_PosicaoCursor(1,8);
    LCD_EscreveCaractere(minutoDEZ + 48);
  }
}

void Horas (void)
{
  horaUNI++;
  if (horaUNI < 10 ){
    LCD_PosicaoCursor(1,6);
    LCD_EscreveCaractere(horaUNI+48);
  }
  else {
    horaUNI = 0;
    horaDEZ++;
    LCD_PosicaoCursor(1,6);
    LCD_EscreveCaractere(horaUNI+48);
    LCD_PosicaoCursor(1,5);
    LCD_EscreveCaractere(horaDEZ+48);
  }
}

void MudarDia() 
{
   switch(month) {
    case 1://janeiro
    case 3://março
    case 5://maio
    case 7://julho
    case 8://agosto
    case 10://outubro
    case 12://dezembro
      ultimoDiaDoMes = 1;
      break;
    case 2://fevereiro
    case 4://abril
    case 6://junho
    case 9:// setembro
    case 11://novembro
      ultimoDiaDoMes = 0;
    default:
      ultimoDiaDoMes = 0;
  }
  
  dayUNI++;
  if (dayUNI > 9) {
    dayUNI = 0;
    dayDEZ++;
    LCD_PosicaoCursor(2,5);
    LCD_EscreveCaractere(dayDEZ+48);
  }
  LCD_PosicaoCursor(2,6);
  LCD_EscreveCaractere(dayUNI+48);
  
  
  if (dayDEZ > 2 && dayUNI > ultimoDiaDoMes) {
    dayUNI = 1;
    LCD_PosicaoCursor(2,6);
    LCD_EscreveCaractere(dayUNI+48);
    dayDEZ = 0;
    LCD_PosicaoCursor(2,5);
    LCD_EscreveCaractere(dayDEZ+48);
    
    month++;
    monthUNI++;
    if (monthUNI > 9) {
      monthUNI = 0;
      monthDEZ++;
      LCD_PosicaoCursor(2,8);
      LCD_EscreveCaractere(monthDEZ+48);
    }
    LCD_PosicaoCursor(2,9);
    LCD_EscreveCaractere(monthUNI+48);

    if(monthDEZ >= 1 && monthUNI > 2){
      monthUNI = 1;
      LCD_PosicaoCursor(2,9);
      LCD_EscreveCaractere(monthUNI+48);
      monthDEZ = 0;
      LCD_PosicaoCursor(2,8);
      LCD_EscreveCaractere(monthDEZ+48);
      
      yearUNI++;
      if(yearUNI > 9){
        yearUNI = 0;
        yearDEZ++;
        LCD_PosicaoCursor(2,11);
        LCD_EscreveCaractere(yearDEZ+48);
      }
      LCD_PosicaoCursor(2,12);
      LCD_EscreveCaractere(yearUNI+48);

      if(yearDEZ > 9) {
        yearDEZ = 0;
        LCD_PosicaoCursor(2,11);
        LCD_EscreveCaractere(yearDEZ+48);
      }
    }
  }
}

void relogio ( void )
{
 //P1IFG_bit.P0 = 1;
  while(1)
  {
    
    Teclado();
    if(segundoDEZ != 6){
      Segundos();
    }  
    else {
      segundoDEZ = 0;
      LCD_PosicaoCursor(1,11);
      LCD_EscreveCaractere(segundoDEZ+48);
      segundoUNI = 0; 
      Minutos();
    }
    
    if (minutoDEZ == 6){
      minutoDEZ = 0;
      minutoUNI = 0;
      LCD_PosicaoCursor(1,8);
      LCD_EscreveCaractere(minutoDEZ+48);
      Horas();
    }
    if (horaDEZ == 2 && horaUNI == 4){
      horaDEZ = 0;
      horaUNI = 0;
      minutoDEZ = 0;
      minutoUNI = 0;
      segundoDEZ = 0;
      segundoUNI = 0;
      LCD_PosicaoCursor(1,6);
      LCD_EscreveCaractere(horaUNI+48);
      LCD_PosicaoCursor(1,5); 
      LCD_EscreveCaractere(horaDEZ+48);
      MudarDia();
    }
  }
}

int main( void )
{ 
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  LCD_Init();
  Teclado_Init();
  LCD_DesligaCursor();
  LCD_PosicaoCursor(1,5);
  LCD_EscreveFrase("23:59:55");
  LCD_PosicaoCursor(2,5);
  LCD_EscreveFrase("31/12/23");
  
  P1IES &=0XFE;  //Define interrupção P1.0 pela borda de subida
  P1IE |= 0X01;  //Habilita interrupçaõ da porta P1.0 
  __enable_interrupt(); // ativa as interrupções globais 
 
  
    LCD_PosicaoCursor(1,5);
    relogio();
}
 
#pragma vector=PORT1_VECTOR
__interrupt void exti ()
{
   if(conferetecla ==0)
  segundoUNI++;
  P1IFG_bit.P0 = 0;
  
}

