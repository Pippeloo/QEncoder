//===== LIBRARIES =====
#include <TimerOne.h>
#include <QEncoder.h>

//===== H-BRIDGE PINS =====
#define M1_ENABLE 7
#define M1_A1    4
#define M1_A2    5

//===== MOTOR OUTPUT PINS =====
#define M1_INTERRUPT 3
#define M1_PHASE A1

//===== SETUP MOTOR =====
QEncoder motor1(M1_INTERRUPT, M1_PHASE);

//===== SETUP =====
void setup() {

  //Initialize the serial monitor
  Serial.begin(9600);
  
  //Define the H-bridge pins as outputs
  pinMode(M1_ENABLE,  OUTPUT);
  pinMode(M1_A1,     OUTPUT);
  pinMode(M1_A2,     OUTPUT);

  //Set the start position of the motor
  motor1.QEncWrite(0);
  motor1.QEncResolution(1);

  //Activate the motor
  digitalWrite(M1_ENABLE, HIGH);
  digitalWrite(M1_A1,    LOW);
  digitalWrite(M1_A2,    LOW);
  
}

//===== LOOP =====
void loop() {
  //Output the resolution of the motor
  Serial.println(QEnc);
  
}
