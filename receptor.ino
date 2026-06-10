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
int estimacionfinal=50;
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

  if(numActSincro < 50)
  {
      reset = true;
  }

  numAct2 = analogRead(ldrPin2);
  numAct1 = analogRead(ldrPin);
  if (numAct1>50){numBin1=1;}
  else{numBin1=0;}
  if (numAct2>140){numBin2=1;}
  else{numBin2=0;}
  numAnt1=numAct1;
  numAnt2=numAct2;
  //Serial.println(eravez);
  if (numActSincro>50 && reset)
  {
    //Serial.print("SYNC=");
    //Serial.println(numActSincro);
    //Serial.print("PAR=");
    //Serial.print(numBin1);
    //Serial.println(numBin2);

    //Serial.print("A1=");
    //Serial.print(numAct1);
    //Serial.print(" A0=");
    //Serial.priwntln(numAct2); 
    
    binario += numBin1;
    binario += numBin2;
    conteo+=2;

    //Serial.print("BIN DESPUES=");
    //Serial.println(binario);
    reset=false;
    //Serial.println(conteo);
  }

  if (conteo==8)
    {
      if (binario==vacio)
      {
        asm volatile ("jmp 0");
      }
      //Serial.print("BIN=");
      //Serial.println(binario);

      char caracter = (char)strtol(binario.c_str(), NULL, 2);

      //Serial.print("CHAR=");
      Serial.print(caracter);
      conteo=0;
      binario="";
    }

}
