/*  Hier komt de header  */

#ifndef QENCODER_H_
#define QENCODER_H_

class QEncoder {
  public:
    QEncoder(int interruptPin, int fasePin); 

    long QEncRead(void);
    void QEncWrite(long newValue);
    void QEncResolution(int resolutionChoise);

  private:
    long _QEncCount;   
    int _phasePin;
    int _interruptPin; 

    static void stateChange(void);

    //Single
    static void stateChangeSingleResolutionRising(void);
    
    //Double
    static void stateChangeDoubleResolutionRising(void);
    static void stateChangeDoubleResolutionFalling(void);

    //Quadruple
    static void stateChangeQuadrupleResolutionRisingInterrupt(void);
    static void stateChangeQuadrupleResolutionFallingInterrupt(void);
    static void stateChangeQuadrupleResolutionRisingPhase(void);
    static void stateChangeQuadrupleResolutionFallingPhase(void);
};
extern long QEnc;
#endif
