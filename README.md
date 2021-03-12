# QEncoder
With this library you can control a Encoder motor.

## Components
These are the components that I used
* Arduino
* Encoder motor
* H-Bridge

## Functions

| Function name | Description                    |
| ------------- | ------------------------------ |
| `QEncoder motor1(i, p)`      | Setup the motor, where 'i' is the interrupt pin and 'p' the phase pin. These are both `int` types      |
| `QEnc`   | Read the flanks of the motor. This returns a `long` type. |
| `motor1.QEncResolution(value)`   | Set the resolution of the output. It supports `Single`, `Double` and `Quadruple` resolution where `value` is a `int` type and can be set to `1`, `2` or `4`.|
| `motor1.QEncWrite(value)`   | Set the startposition of the motor. `value` is a `long` type. |


## Example
Down below you can view an example

```c++
//===== LIBRARIES =====
#include <TimerOne.h>
#include "QEncoder.h"

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
```

You can define the rotationdirection by changing the digitalWrite() to the H-Bridge
```c++
digitalWrite(M1_A1, value);
digitalWrite(M1_A2, value);
```

If the `value` is both `LOW` or `HIGH` the motor **STOPS**.
If one of the `value` is `LOW` and the other is `HIGH` the motor will rotate depending of how the motor is connected.
