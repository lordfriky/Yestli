/*
  Yestli, 'Sangre Nueva'
  Como parte del proyecto 'Yolotli' (proyecto corazón)
  
  Responsables del proyecto:
  - Daniel Hernández Muñoz
  - David de León Gonzalez
  - Melissa Gómez Hernández
  - Yerik Martín García
  
  Publicado bajo la GNU General Public License 3.0
  Mas info en: https://github.com/Yestli/Yestli-Project/blob/master/LICENSE
*/

// Inclusión de librerías necesarias
#include <SoftwareSerial.h>          // Librería para el serial por software (Bluetooth)
#include <Wire.h>                    // Librería I2C
#include <MAX30100_PulseOximeter.h>  // Librería para el MAX30100
#include <LiquidCrystal.h>           // Librería para el LCD

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2; // Pines usados por la pantalla

LiquidCrystal lcd(rs, en, d4, d5, d6, d7); // Pantalla definida

PulseOximeter pox; // MAX30100 definido

SoftwareSerial BT(9, 10); //Bluetooth definido (RX, TX)

char BTserial = 'StandBy';
char globalState; //Puede ser útil para exponer datos en el LCD

int PulX = 0; // Cambia el tipo de variable si lo requieres, aquí almacena el valor correspondiente
int OxiX = 0; // x2
int TemX = 0; // x3

/*
  Es una putiza para concatenar, lo intentaré después
  No juzgues...
*/
char GP = 'GetPul'; // Variable de solicitud de envío de pulso
char GO = 'GetOxi'; // Lo de arriba x2 con oxígeno
char GT = 'GetTem'; // Lo de arriba x3 con temperatura

char SnP = 'SendingPul'; // Variable para confirmar la solicitud de envío de pulso
char SnO = 'SendingOxi'; // Lo de arriba x2 con oxígeno
char SnT = 'SendingTem'; // Lo de arriba x3 con temperatura

char OP = 'GetPulOk'; // Variable de confirmación de envío de pulso
char OO = 'GetOxiOk'; // Lo de arriba x2 con oxígeno
char OT = 'GetTemOk'; // Lo de arriba x3 con temperatura

void setup() {
  lcd.begin(16, 2); // LCD iniciado
  Serial.begin(115200); // Aún no estoy seguro para qué es este serial...
  BT.begin(9600); // Bluetooth iniciado
  
}

void loop() {
  if(BT.available()>0){        // Lee el Bluetooth y almacena en BTserial
    BTserial = BT.read();
  }
  while(BTserial=='StandBy'){
    /*
    Aquí pones lo que sea mientras Yestli no hace nada
    Se creativo ;)
    */
  }
  if(BTserial==GP){ // Si pide pulso mandar confirmación y luego mandar datos
    BT.println(SnP);
    SendData(PulX);
  }
  if(BTserial==GO){ // Lo de arriba x2 con oxígeno
    BT.println(SnO);
    SendData(OxiX);
  }
  if(BTserial==GT){ // Lo de arriva x3 con temperatura
    BT.println(SnT);
    SendData(TemX);
  }
}

void SendData(char data) {  // Constituye los pasos necesarios a partir de los relojes en la app
  delay(1000);
  BT.println(data);
  if(BTserial==OP){
    globalState = 'Pulso obtenido correctamente';  // Ya sabes para qué es útil esto...
  }
  else if(BTserial==OO){
    globalState = 'Oxígeno obtenido correctamente';
  }
  else if(BTserial==OT){
    globalState = 'Temperatura obtenida correctamente';
  }
  BTserial = 'StandBy';  // Termina regresando el serial a su estado original
}
