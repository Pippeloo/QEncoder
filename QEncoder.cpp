//===== LIBRARIES =====
#include "QEncoder.h"
#include <Arduino.h>

//===== VARIABLES =====
long QEnc;

QEncoder *classEncoder;

QEncoder::QEncoder(int interruptPin, int phasePin) {
  //Define class point
  classEncoder = this;
  
  //Define pins
  _phasePin = phasePin;
  _interruptPin = digitalPinToInterrupt(interruptPin);

  //Default interrupt;
  attachInterrupt(_interruptPin, stateChangeSingleResolutionRising, RISING);
}

//===== Resolution =====
void QEncoder::QEncResolution(int resolutionChoice) {
  
  if(resolutionChoice == 0){
    
  }else if(resolutionChoice == 1){
    
    attachInterrupt(classEncoder->_interruptPin, stateChangeSingleResolutionRising, RISING);
    
  }else if(resolutionChoice == 2){

    attachInterrupt(classEncoder->_interruptPin, stateChangeDoubleResolutionRising, RISING);
    
  }else if(resolutionChoice == 3){

    attachInterrupt(classEncoder->_interruptPin, stateChangeQuadrupleResolutionRisingInterrupt, RISING);
    attachInterrupt(classEncoder->_phasePin, stateChangeQuadrupleResolutionRisingPhase, RISING);
    
  }else{

    attachInterrupt(classEncoder->_interruptPin, stateChangeSingleResolutionRising, RISING);
    
  }
}

void QEncoder::QEncWrite(long newValue) {
  _QEncCount = newValue;
}

//===== Single Resolution =====
static void QEncoder::stateChangeSingleResolutionRising(void) {
  if (digitalRead(classEncoder->_phasePin)) {
    classEncoder->_QEncCount += 1;
  } else {  
    classEncoder->_QEncCount -= 1;
  }
  QEnc = classEncoder->_QEncCount;
}

//===== Double Resolution =====
static void QEncoder::stateChangeDoubleResolutionRising(void) {
  if (digitalRead(classEncoder->_phasePin)) {
    classEncoder->_QEncCount += 1;
  } else {  
    classEncoder->_QEncCount -= 1;
  }
  QEnc = classEncoder->_QEncCount;
  attachInterrupt(classEncoder->_interruptPin, stateChangeDoubleResolutionFalling, FALLING);
}

static void QEncoder::stateChangeDoubleResolutionFalling(void) {
  if (digitalRead(classEncoder->_phasePin)) {
    classEncoder->_QEncCount -= 1;
  } else {  
    classEncoder->_QEncCount += 1;
  }
  QEnc = classEncoder->_QEncCount;
  attachInterrupt(classEncoder->_interruptPin, stateChangeDoubleResolutionRising, RISING);
}

//===== QUADRUPLE =====
// === Interrupt ===
static void QEncoder::stateChangeQuadrupleResolutionRisingInterrupt(void) {
  if (digitalRead(classEncoder->_phasePin)) {
    classEncoder->_QEncCount += 1;
  } else {  
    classEncoder->_QEncCount -= 1;
  }
  QEnc = classEncoder->_QEncCount;
  attachInterrupt(classEncoder->_interruptPin, stateChangeQuadrupleResolutionFallingInterrupt, FALLING);
}

static void QEncoder::stateChangeQuadrupleResolutionFallingInterrupt(void) {
  if (digitalRead(classEncoder->_phasePin)) {
    classEncoder->_QEncCount -= 1;
  } else {  
    classEncoder->_QEncCount += 1;
  }
  QEnc = classEncoder->_QEncCount;
  attachInterrupt(classEncoder->_interruptPin, stateChangeQuadrupleResolutionRisingInterrupt, RISING);
}

// === Phase ===
static void QEncoder::stateChangeQuadrupleResolutionRisingPhase(void) {
  if (digitalRead(classEncoder->_phasePin)) {
    classEncoder->_QEncCount -= 1;
  } else {  
    classEncoder->_QEncCount += 1;
  }
  QEnc = classEncoder->_QEncCount;
  attachInterrupt(classEncoder->_phasePin, stateChangeQuadrupleResolutionFallingPhase, FALLING);
}

static void QEncoder::stateChangeQuadrupleResolutionFallingPhase(void) {
  if (digitalRead(classEncoder->_phasePin)) {
    classEncoder->_QEncCount -= 1;
  } else {  
    classEncoder->_QEncCount += 1;
  }
  QEnc = classEncoder->_QEncCount;
  attachInterrupt(classEncoder->_phasePin, stateChangeQuadrupleResolutionRisingPhase, RISING);
}
