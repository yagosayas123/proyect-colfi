#include <stdlib.h>
const int ldrPin = A1;
const int ldrPin2 = A0;
const int sincro = A2;
int lectura1, lectura2;
int iguales = 0;

String binario;
String vacio = "00000000";
int lectura;
float estimacion=10;
int estimacionfinal=100;
float K[5]={0.35, 0.25, 0.20, 0.12, 0.08};
int acomodo=0;
char total;
int valDel = 2;
int umbral = 1;
int numBin1=0, numAct1=0, delays, tiempoact, diftiempo;
int numBin2=0, numAct2=0;
int numBinSincro=0, numActSincro=0, numAntSincro=0;
bool espera=false;
bool reset=false;
bool eravez=false;

int numAnt1=0;
int numAnt2=0;
unsigned long t2;
int inicio = 0;
int conteo = 0;
unsigned long t1[8];
unsigned long tf1[8];
unsigned long tf2[8];
unsigned long tiempo;
bool cambio=false;
bool cambio2=false;
int i;
int lecturas=5;
int a=1;
int b=1;
unsigned long t0=0;
void setup() {
  Serial.begin(115200);
  pinMode(ldrPin, INPUT);
  pinMode(ldrPin2, INPUT);
  pinMode(sincro, INPUT);
  Serial.println("--------------");
}

void loop() {
  numActSincro=analogRead(sincro);
  if (numActSincro>numAntSincro+umbral){numBinSincro=1;}
  if (numActSincro<numAntSincro-umbral){numBinSincro=0;}
  numAntSincro=numActSincro;
  if (espera==false && lecturas==5)
  {
    numAct2=0;
    numAct1=0;
    numAnt2=0;
    numAnt1=0;
    numBin1=0;
    numBin2=0;
  }

  while(lecturas==5 && numBinSincro==0)
  {
    numActSincro=analogRead(sincro);
    //numAct1=analogRead(ldrPin);
    //Serial.println(numAct1);
    if (numActSincro>numAntSincro+2){numBinSincro=1;}
    if (numActSincro<numAntSincro-2){numBinSincro=0;}
    numAntSincro=numActSincro;
    reset=true;
    espera=true;
  }
  numAct2 = analogRead(ldrPin2);
  numAct1 = analogRead(ldrPin);
  if (numAct1>numAnt1+umbral){numBin1=1;}
  if (numAct1<numAnt1-umbral){numBin1=0;}
  if (numAct2>numAnt2+umbral){numBin2=1;}
  if (numAct2<numAnt2-umbral){numBin2=0;}
  numAnt1=numAct1;
  numAnt2=numAct2;
  //Serial.println(eravez);
  if (lecturas==5 && reset==true)
  {
    numAct1=analogRead(ldrPin);
    Serial.println(numAct1);
    if (numBin1==1)
    {
      if(eravez==false)
      {
        binario+="0";
        conteo+=1;
        //Serial.print("Caracter:");
        Serial.println("0");
      }
      else
      {
      binario+="1";
      conteo+=1;
      //Serial.print("Caracter:");
      Serial.println("1");
      }
    }
    else
    {
      binario+="0";
      conteo+=1;
      //Serial.print("Caracter:");
      Serial.println("0");
    }

    if (numBin2==1)
    {
      binario+="1";
      conteo+=1;
      //Serial.print("Caracter:");
      Serial.println("1");
      eravez=true;
    }
    else
    {
      if(eravez==false)
      {
        binario+="1";
        conteo+=1;
        //Serial.print("Caracter:");
        Serial.println("1");
        eravez=true;
      }
      else
      {
      binario+="0";
      conteo+=1;
      //Serial.print("Caracter:");
      Serial.println("0");
      }
    }
    reset=false;
  }

  if (conteo==8)
    {
      if (binario==vacio)
      {
        asm volatile ("jmp 0");
      }
      char caracter = (char)strtol(binario.c_str(), NULL, 2);
      Serial.print(caracter); 
      conteo=0;
      binario="";
    }

    delay((estimacionfinal/100)*30);
}
