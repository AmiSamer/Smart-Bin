#include <Servo.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

Servo myservo;
Servo myservo1;
Servo myservo2;
Servo myservo3;

const byte interruptPin = 2;

int trigPin = 12;
int echoPin = 8;
int trigPin1 = 7;
int echoPin1 = 4;
int Buzzer = 13;

long duration;
int Human_distance_cm;
int Bin_Garbaze_distance_cm;

int Bin_Garbaze_Set_distance = 10;            ////set garbaze distane
int Open_Bin_distance = 20;                   ////set bin open ditsnce

int Bin_Open_Angel = 180;                     ////set bin open angel
int Bin_Close_Angel = 90;                     ////set bin close angel

int Metal_Chamber_Open_Angel = 90;            ////set metal chamber open angel
int Metal_Chamber_Close_Angel = 180;          ////set metal chamber close angel

int Organic_Chamber_Open_Angel = 0;           ////set organic chamber open angel
int Organic_Chamber_Close_Angel = 180;        ////set organic chamber close angel

int Tissu_Open_Angel = 0;                     ////set tissu dispenser open angel
int Tissu_Close_Angel = 100;                  ////set tissu dispenser close angel


void setup() {
  Serial.begin(9600);
  pinMode(Buzzer, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  pinMode(echoPin, INPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(trigPin1, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), metal, RISING);
  myservo.attach(11);
  myservo1.attach(10);
  myservo2.attach(9);
  myservo3.attach(6);
  digitalWrite(Buzzer, LOW);
  lcd.begin();
  lcd.backlight();
}

void loop() {
  duration = 0;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(10);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  Human_distance_cm = (duration / 58);
  Serial.print("Human_distance_cm:");
  Serial.println(Human_distance_cm);

  if (Human_distance_cm < Open_Bin_distance) {
    myservo.write(Bin_Open_Angel);
    delay(5000);
    myservo2.write(Organic_Chamber_Open_Angel);
    myservo3.write(Tissu_Open_Angel);
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("THANK YOU");
  }
  else {
    myservo.write(Bin_Close_Angel);
    myservo2.write(Organic_Chamber_Close_Angel);
    myservo3.write(Tissu_Close_Angel);
    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.print("WELCOME");
    lcd.setCursor(5, 1);
    lcd.print("USE ME");
  }
  duration = 0;
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(10);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);

  duration = pulseIn(echoPin1, HIGH);
  Bin_Garbaze_distance_cm = (duration / 58);
  Serial.print("Bin_Garbaze_distance_cm:");
  Serial.println(Bin_Garbaze_distance_cm);

  if (Bin_Garbaze_distance_cm < Bin_Garbaze_Set_distance) {
    digitalWrite(Buzzer, HIGH);
  }
  else {
    digitalWrite(Buzzer, LOW);
  }
  delay(2000);
  myservo1.write(Metal_Chamber_Close_Angel);
}

void metal() {
  Serial.println("Metal_Found");
  myservo1.write(Metal_Chamber_Open_Angel);
  delay(1000);
}
