#include <LCD4884.h>

int zaehler = 0;
char string[10];
int wert1 = 50;
char stringwert1[10];
char stringwert2[10];
char stringwert3[10];
char stringwert4[10];
int i;
int runde;
int hexwert1;
int hexwert2;
char ergebnis[10];
int ergebnis_char;

void punkt(int zaehler, int hexwert1, int hexwert2){
    lcd.LCD_set_XY(zaehler,0);
    lcd.LCD_write_byte(hexwert1, 1);
    lcd.LCD_set_XY(zaehler,1);
    lcd.LCD_write_byte(hexwert2, 1);
  };
  

unsigned char grad_bmp[]=
{
    0b0000011101010101,
    0b0000010101010101,
    0b0000011101010101,
    0b0011111001010101,
    0b0100000101010101,
    0b0100000101010101,
    0b0011011001010101,
    0b0000000001010101,
    0b0000000001010101,
};
 
void setup()
{
  Serial.begin(9600);
  lcd.LCD_init();
  lcd.LCD_clear();
}

long getIntFromString (char *stringWithInt, byte num)
// input: pointer to a char array
// returns an integer number from the string (positive numbers only!)
// num=1, returns 1st number from the string
// num=2, returns 2nd number from the string, and so on
{
  char *tail;
  while (num>0)
  {
    num--;
    // skip non-digits
    while ((!isdigit (*stringWithInt))&&(*stringWithInt!=0)) stringWithInt++;
    tail=stringWithInt;
    // find digits
    while ((isdigit(*tail))&&(*tail!=0)) tail++;
    if (num>0) stringWithInt=tail; // new search string is the string after that number
  }  
  return(strtol(stringWithInt, &tail, 0));
}  


void loop(){

 
  for (zaehler; zaehler < 81; zaehler++) //da immer 2 punkte gesetzt werden, doppelt so viele wie messerwte pro zeile
  {
  char commandbuffer[40];
  char c;
  int i=0;

  // runde löschen
    for (runde; runde > 0; runde--)
      {
      delay(100);
      string[0] = runde;
      string[1] = '\0';
      lcd.LCD_set_XY(runde,3);
      lcd.LCD_write_byte(0x00, 1);
      }
//    memset(commandbuffer,0,sizeof(commandbuffer)); // Speicher loeschen

  serial:
  if (Serial.available())
  {
    delay(75); // warten, bis die Zeile eingetroffen ist
﻿  
    // Puffer mit Nullbytes fuellen und dadurch loeschen
//    memset(commandbuffer,0,sizeof(commandbuffer)); // Speicher loeschen
    while (Serial.available())
    {
      c=Serial.read(); // Zeichen einlesen
      // Zeichen nur verarbeiten, wenn kein Steuerzeichen und Platz im Puffer
      if (c>=32 && i<sizeof(commandbuffer)-1)
      {
        commandbuffer[i] = c;
        i++;
      }  
      if (c<32) break; // Abbrechen bei Zeilenende-Zeichen
    }
    if (strcmp(commandbuffer,"\0")>0) // keine Leerzeile
    {
      for (i=1;i<5;i++) // Versuche 4 Zahlen aus der Zeile auszulesen
      {
//        Serial.print(getIntFromString(commandbuffer, i));
//        int wert = (getIntFromString(commandbuffer, i));
//        lcd.LCD_write_string(0,3, "wert da",MENU_NORMAL);
//        delay(1000);
//        lcd.LCD_write_string(0,3, "              ",MENU_NORMAL);
//                ergebnis_char = getIntFromString(commandbuffer, i);
//                ergebnis[0] = ergebnis_char;
//                ergebnis[1] = '\0';
//      lcd.LCD_write_string(0,2,ergebnis,MENU_NORMAL);

//        Serial.print("   ");
//        Serial.print(wert);
//        Serial.print(getIntFromString(commandbuffer, 1));
      }
//      Serial.println();
    }
  }
   else {
    runde++;
    string[0] = runde;
    string[1] = '\0';
    lcd.LCD_set_XY(runde,3);
    lcd.LCD_write_byte(0x01, 1);
    delay (60000);
   goto serial;
   }
   
   int wert1 = (getIntFromString(commandbuffer, 1));
   int wert2 = (getIntFromString(commandbuffer, 2));
   int wert3 = (getIntFromString(commandbuffer, 3));
   int wert4 = (getIntFromString(commandbuffer, 4));

  itoa(wert1, stringwert1, 10);
  itoa(wert2, stringwert2, 10);
  itoa(wert3, stringwert3, 10);
  itoa(wert4, stringwert4, 10);
  lcd.LCD_write_string(0,4,"% i",MENU_NORMAL);
  lcd.LCD_write_string(25,4, stringwert1 , MENU_NORMAL);
  lcd.LCD_draw_bmp_pixel(0,5, grad_bmp, 8,8);
  lcd.LCD_write_string(12,5,"i",MENU_NORMAL);
  lcd.LCD_write_string(25,5,stringwert3, MENU_NORMAL);
  lcd.LCD_write_string(50,4,"a",MENU_NORMAL);
  lcd.LCD_write_string(64,4,stringwert2, MENU_NORMAL);
  lcd.LCD_write_string(50,5,"a",MENU_NORMAL);
  lcd.LCD_write_string(64,5,stringwert4, MENU_NORMAL);
  int wert = wert1;
  if (wert < 19){
    hexwert1=0xFF;
    hexwert2=0xFF;
    string[0] = zaehler;
    string[1] = '\0';
    punkt(zaehler, hexwert1,hexwert2);
    goto end;
  }
  if (wert < 29){
    hexwert1=0xFE;
    hexwert2=0xFF;
    string[0] = zaehler;
    string[1] = '\0';
    punkt(zaehler,hexwert1,hexwert2);
    goto end;
  }
  if (wert < 39){
    hexwert1=0xFC;
    hexwert2=0xFF;
    string[0] = zaehler;
    string[1] = '\0';
    punkt(zaehler, hexwert1,hexwert2);
    goto end;
  }
  if (wert < 44){
    hexwert1=0xF8;
    hexwert2=0xFF;
    string[0] = zaehler;
    string[1] = '\0';
    punkt(zaehler, hexwert1,hexwert2);
    goto end;
  }
  if (wert < 49){
    hexwert1=0xF0;
    hexwert2=0xFF;
    string[0] = zaehler;
    string[1] = '\0';
    punkt(zaehler, hexwert1,hexwert2);
    goto end;
  }
  if (wert < 54){
    hexwert1=0xE0;
    hexwert2=0xFF;
    string[0] = zaehler;
    string[1] = '\0';
    punkt(zaehler, hexwert1,hexwert2);
    goto end;
  }
  if (wert < 59){
    hexwert1=0xC0;
    hexwert2=0xFF;
    string[0] = zaehler;
    string[1] = '\0';
    punkt(zaehler, hexwert1,hexwert2);
    goto end;
  }
  if (wert < 64){
    hexwert1=0x80;
    hexwert2=0xFF;
    string[0] = zaehler;
    string[1] = '\0';
    punkt(zaehler, hexwert1,hexwert2);
    goto end;
  }
  if (wert < 69){
    hexwert1=0x00;
    hexwert2=0xFF;
    string[0] = zaehler;
    string[1] = '\0';
    punkt(zaehler, hexwert1,hexwert2);
    goto end;
  }
  if (wert < 73){
    hexwert1=0x00;
    hexwert2=0xFE;
    string[0] = zaehler;
    string[1] = '\0';
    punkt(zaehler, hexwert1,hexwert2);
    goto end;
  }
  if (wert < 75){
    hexwert1=0x00;
    hexwert2=0xFC;
    string[0] = zaehler;
    string[1] = '\0';
    punkt(zaehler, hexwert1,hexwert2);
    goto end;
  }
  if (wert < 77){
    hexwert1=0x00;
    hexwert2=0xF8;
    string[0] = zaehler;
    string[1] = '\0';
    punkt(zaehler, hexwert1,hexwert2);
    goto end;
  }
  if (wert < 79){
    hexwert1=0x00;
    hexwert2=0xF0;
    string[0] = zaehler;
    string[1] = '\0';
    punkt(zaehler, hexwert1,hexwert2);
    goto end;
  }
  if (wert < 84){
    hexwert1=0x00;
    hexwert2=0xE0;
    string[0] = zaehler;
    string[1] = '\0';
    punkt(zaehler, hexwert1,hexwert2);
    goto end;
  }
  if (wert < 89){
    hexwert1=0x00;
    hexwert2=0xC0;
    string[0] = zaehler;
    string[1] = '\0';
    punkt(zaehler, hexwert1,hexwert2);
    goto end;
  }
  if (wert < 99){
    hexwert1=0x00;
    hexwert2=0x80;
    string[0] = zaehler;
    string[1] = '\0';
    punkt(zaehler, hexwert1,hexwert2);
    goto end;
  }
  end:
  
  delay(1000);
  }
  lcd.LCD_clear();
  lcd.LCD_write_string(0,0,"reboot",MENU_NORMAL);
  delay (1000);
  lcd.LCD_clear();
  zaehler=0;
        
}

