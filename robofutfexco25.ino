//PmwA, A1, A2, B1, B2, PmwB
//13, 12, 14, 27, 26, 25
//16, 17, 5, 18, 19, 21
#include "BluetoothSerial.h"
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
BluetoothSerial SerialBT;
char comando='S';
//char fija='S';
int pmw[4]={13, 25, 16, 21};
int ports[4][2]={{12, 14}, {27, 26}, {17, 5}, {18,19}};
int vel=180;
int velg=230;
bool first=true;
void setup() {
  for(int i=0;i<=3;i++){pinMode(pmw[i], OUTPUT);pinMode(ports[i][0], OUTPUT);pinMode(ports[i][1], OUTPUT);}
  Serial.begin(115200);
  SerialBT.begin("ESP32__Alvaro123");
  Serial.println("The device started, now you can connected");
}
void loop() {
  if(SerialBT.available()){
      char lec=char(SerialBT.read());
      if(lec=='R' || lec=='L' || lec=='F' || lec=='S' || lec=='B' /*|| lec=='W' || lec=='w'*/){
          comando=lec;  
      }
      //if(first && comando=='W'){first=false;fija=comando;}
      //if(comando=='S'){first=true;fija='S';}
      switch(comando){
        case'R':motoresh(velg, -velg);
                Serial.println("derecha");
                break;
        case'L':motoresh(-velg, velg);
                Serial.println("izquierda");
                break;
        case'F':motoresh(vel, vel);
                Serial.println("adelante");
                break;
        case'B':motoresh(-vel, -vel);
                Serial.println("atras");
                break;
        default:motoresh(0,0);
                Serial.println("Parar");
               
      }
  }
}
void motoresh(int veli, int veld){
  if(veli>0){
    digitalWrite(ports[0][0], HIGH);
    digitalWrite(ports[0][1], LOW);
    digitalWrite(ports[2][0], HIGH);
    digitalWrite(ports[2][1], LOW);
  }
  else if(veli<0){
    digitalWrite(ports[0][1], HIGH);
    digitalWrite(ports[0][0], LOW);
    digitalWrite(ports[2][1], HIGH);
    digitalWrite(ports[2][0], LOW);
    veli=veli*(-1);
  }
  if(veld>0){
    digitalWrite(ports[1][0], HIGH);
    digitalWrite(ports[1][1], LOW);
    digitalWrite(ports[3][0], HIGH);
    digitalWrite(ports[3][1], LOW);
  }
  else if(veld<0){
    digitalWrite(ports[1][1], HIGH);
    digitalWrite(ports[1][0], LOW);
    digitalWrite(ports[3][1], HIGH);
    digitalWrite(ports[3][0], LOW);
    veld=veld*(-1);
  }
  analogWrite(pmw[0], veli);
  analogWrite(pmw[1], veld);
  analogWrite(pmw[2], veli);
  analogWrite(pmw[3], veld);
  delay(20); 
}
