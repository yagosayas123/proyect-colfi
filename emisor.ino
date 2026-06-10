#include <stdio.h>
#include <ctype.h>
#include <string.h>
int led1 = 6;
int led2 = 3;
int sincro = 7;
char testeo[] ="";
bool pasa= false;
String texto="";
int conteo=0;
String palabra="";
float espera=2500;
char c[9];
int bit = 0;
int a=true;
void setup() 
{
  Serial.println("");
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(sincro, OUTPUT);
  Serial.begin(115200);
  Serial.setTimeout(100);
  Serial.println("INGRESE PALABRA");
  while(Serial.available()==0)
  {
  }
  palabra = Serial.readStringUntil('\n');
  //int cant=palabra.length();
  //char buffer[cant];
  //itoa(palabra, buffer, 10);
}


void loop() 
{
  if(bit == 0)
  {
    char letra = palabra[conteo];

    for(int i = 0; i < 8; i++)
    {
      c[i] = bitRead(letra, 7 - i) + '0';
    }

    c[8] = '\0';
    if(a){
      delay(2000);
      a=false;
    }
  }
  //palabra = Serial.readStringUntil('\n');
  if(Serial.available())
  {
    palabra = Serial.readStringUntil('\n');
  }
  /*while(pasa==false)
  {
    char c = testeo[conteo];
    if(c=='0')
    {
      digitalWrite(led1, LOW);
    }
    else
    {
      digitalWrite(led1, HIGH);
    }
    Serial.print(c);
    delay(espera);
    conteo+=1;
    if(conteo==5)
    {
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      Serial.println("");
      conteo=0;
      pasa=true;
    }
  }*/
  Serial.println(c[bit]);
  if(c[bit]=='0')
  {
    digitalWrite(led1, LOW);
  }
  else
  {
    digitalWrite(led1, HIGH);
  } 
  bit++;
  Serial.println(c[bit]);
  if(c[bit]=='0')
  {
    digitalWrite(led2, LOW);
  }
  else
  {
    digitalWrite(led2, HIGH);
  }
  bit++;
  delay((espera/100)*25);
  digitalWrite(sincro, HIGH);
  delay((espera/100)*50);
  digitalWrite(sincro, LOW);
  delay((espera/100)*25); 
  if(bit == 8)
  {
    bit = 0;
    conteo++;
  }

  if(conteo >= palabra.length() || palabra== "para gil")
  {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    asm volatile ("jmp 0");
  }
}
