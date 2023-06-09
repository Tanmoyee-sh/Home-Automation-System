#define REMOTEXY_MODE__HARDSERIAL

#define REMOTEXY_SERIAL Serial

#define REMOTEXY_SERIAL_SPEED 9600

#define IR_RECEIVE_PIN 10

#define LDRPin A0

 

 

 

#include <RemoteXY.h>

#include <IRremote.h>

#include <LiquidCrystal.h>

#include <EduIntro.h>

 

DHT11 dht11(A5);

 

 

int LIGHT = 10;

int motion = 6;

int motionLed = 7;

int Led1 = 5;

int Led2 = 4;

int Led3 = 3;

int Led4 = 2;

int sound = 34;

int redLed = 35;

int smoke = A7;

int buzzer = 36;

int sensorThres = 400;

int C;

 

const int rs = 12, en = 11, d4 = 30, d5 = 31, d6 = 32, d7 = 33;

 

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

 

#pragma pack(push, 1)

#pragma pack(pop)

 

uint8_t RemoteXY_CONF[] =   // 44 bytes

  {255,0,0,33,0,37,0,16,31,1,130,1,2,19,57,73,17,67,4,5,

  39,25,5,2,26,11,67,4,5,53,52,5,2,26,11,67,4,5,67,52,

  5,2,26,11 };

struct {

 

    // output variables

  char text_1[11];  // string UTF8 end zero

  char text_2[11];  // string UTF8 end zero

  char text_3[11]; // string UTF8 end zero

 

    // other variable

  uint8_t connect_flag; // =1 if wire connected, else =0

 

} RemoteXY;

 

void setup()

{

  RemoteXY_Init ();

 

  Serial.begin(9600);

  Serial.println("Enabling IRin");

  Serial.println("Enabled IRin");

 

  pinMode(LDRPin, INPUT);

 

  pinMode(motion, INPUT);

  pinMode(motionLed, OUTPUT);

 

  pinMode(Led1, OUTPUT);

  pinMode(Led2, OUTPUT);

  pinMode(Led3, OUTPUT);

  pinMode(Led4, OUTPUT);

 

  pinMode(sound,INPUT);

 

  pinMode(smoke, INPUT);

  pinMode(redLed, OUTPUT);

  pinMode(buzzer, OUTPUT);

 

  IrReceiver.begin(IR_RECEIVE_PIN);

 

  lcd.begin(16, 2);

}

 

void loop()

{

  RemoteXY_Handler ();

 

  dht11.update();

  C = dht11.readCelsius();

 

  dtostrf(C, 0, 1, RemoteXY.text_1);

 

  int LDRValue = analogRead(LDRPin);

  if (LDRValue < LIGHT )

  {

    motion_detector_led();

    room_leds();

  }

  else

  {

  digitalWrite(motionLed, LOW);

  digitalWrite(Led1, LOW);

  digitalWrite(Led2, LOW);

  digitalWrite(Led3, LOW);

  digitalWrite(Led4, LOW);  

  }

 

  sound_detector();

  fire_detector();

}

 

void motion_detector_led(){

    long sensor = digitalRead(motion);

 

  if(sensor == HIGH){

     digitalWrite (motionLed, HIGH);

     delay(500);

   }

   else

   {

      digitalWrite (motionLed, LOW);

   }

}

 

void room_leds(){

 

    if (IrReceiver.decode()) {

    int command = IrReceiver.decodedIRData.command;

    Serial.println(command);

 

     // Receive the next value

    switch (command) {

      case 12:

        digitalWrite(Led1, !digitalRead(Led1));

        break;

     

      case 24:

        digitalWrite(Led2, !digitalRead(Led2));

        break;

     

      case 94:

        digitalWrite(Led3, !digitalRead(Led3));

        break;

     

      case 8:

        digitalWrite(Led4, !digitalRead(Led4));

    }

    IrReceiver.resume();

  }

}

 

void sound_detector(){

  int SensorData=digitalRead(sound);

  if(SensorData==1){

    lcd.setCursor(0, 1);

    lcd.print("SOUND! ");

    sprintf (RemoteXY.text_2, "SOUND!");

    }

}

 

void fire_detector(){

  int analogSensor = analogRead(smoke);

  if (analogSensor > sensorThres)

  {

    digitalWrite(redLed, HIGH);

    tone(buzzer, 1000, 200);

    lcd.setCursor(0, 1);

    lcd.print("SMOKE!");

    sprintf (RemoteXY.text_3, "SMOKE!");

  }

  else

  {

    digitalWrite(redLed, LOW);

    noTone(buzzer);

    }

}

 
