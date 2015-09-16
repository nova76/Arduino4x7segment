/*  4 digit 7 segment LED display common cathode
 *  display shows numbers and letters from the serial interface
 *  without the use of a library
 *  every digit can have a decimal point
 *  decimal point can be entered with . or ,
 *
 * Author: Silvia Rothen, rothen ecotronics, Bern, Switzerland
 * part of the code is from the library SevSeg by Dean Reading
 */
  
boolean DigitOn = LOW;
boolean DigitOff = HIGH;
boolean SegOn=HIGH;
boolean SegOff=LOW;
int DigitPins[] = {10, 11, 12, 13};
int SegmentPins[] = {2, 3, 4, 5, 6, 7, 8, 9};
 
//looks terrible, but I didn't find a way to copy Arrays or merge them from parts
//N is for numbers and NxP is a number with a decimal point behind
int BLANK[] = {LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW};
int N0[]    = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW, LOW};
int N0P[]   = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW, HIGH};
int N1[]    = {LOW, HIGH, HIGH, LOW, LOW, LOW, LOW, LOW};
int N1P[]   = {LOW, HIGH, HIGH, LOW, LOW, LOW, LOW, HIGH};
int N2[]    = {HIGH, HIGH, LOW, HIGH, HIGH, LOW, HIGH, LOW};
int N2P[]   = {HIGH, HIGH, LOW, HIGH, HIGH, LOW, HIGH, HIGH};
int N3[]    = {HIGH, HIGH, HIGH, HIGH, LOW, LOW, HIGH, LOW};
int N3P[]   = {HIGH, HIGH, HIGH, HIGH, LOW, LOW, HIGH, HIGH};
int N4[]    = {LOW, HIGH, HIGH, LOW, LOW, HIGH, HIGH, LOW};
int N4P[]   = {LOW, HIGH, HIGH, LOW, LOW, HIGH, HIGH, HIGH};
int N5[]    = {HIGH, LOW, HIGH, HIGH, LOW, HIGH, HIGH, LOW};
int N5P[]   = {HIGH, LOW, HIGH, HIGH, LOW, HIGH, HIGH, HIGH};
int N6[]    = {HIGH, LOW, HIGH, HIGH, HIGH, HIGH, HIGH, LOW};
int N6P[]   = {HIGH, LOW, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH};
int N7[]    = {HIGH, HIGH, HIGH, LOW, LOW, LOW, LOW, LOW};
int N7P[]   = {HIGH, HIGH, HIGH, LOW, LOW, LOW, LOW, HIGH};
int N8[]    = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW};
int N8P[]   = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH};
int N9[]    = {HIGH, HIGH, HIGH, HIGH, LOW, HIGH, HIGH, LOW};
int N9P[]   = {HIGH, HIGH, HIGH, HIGH, LOW, HIGH, HIGH, HIGH};
int MIN[]   = {LOW, LOW, LOW, LOW, LOW, LOW, HIGH, LOW};
//The letters K, M, N, T, V, W, Z are off limits with a 7 segment display
//Some letters like D, G, Q are hard to recognize, as D is like O and G like 6
int A[] = {HIGH, HIGH, HIGH, LOW, HIGH, HIGH, HIGH, LOW};
int B[] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW};
int C[] = {HIGH, LOW, LOW, HIGH, HIGH, HIGH, LOW, LOW};
int D[] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW, LOW};
int E[] = {HIGH, LOW, LOW, HIGH, HIGH, HIGH, HIGH, LOW};
int F[] = {HIGH, LOW, LOW, LOW, HIGH, HIGH, HIGH, LOW};
int G[] = {HIGH, LOW, HIGH, HIGH, HIGH, HIGH, HIGH, LOW};
int H[] = {LOW, HIGH, HIGH, LOW, HIGH, HIGH, HIGH, LOW};
int I[] = {LOW, HIGH, HIGH, LOW, LOW, LOW, LOW, LOW};
int J[] = {LOW, HIGH, HIGH, HIGH, HIGH, LOW, LOW, LOW};
int L[] = {LOW, LOW, LOW, HIGH, HIGH, HIGH, LOW, LOW};
int O[] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW, LOW};
int P[] = {HIGH, HIGH, LOW, LOW, HIGH, HIGH, HIGH, LOW};
int Q[] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW, HIGH};
int R[] = {HIGH, HIGH, HIGH, LOW, HIGH, HIGH, HIGH, LOW};
int S[] = {HIGH, LOW, HIGH, HIGH, LOW, HIGH, HIGH, LOW};
int U[] = {LOW, HIGH, HIGH, HIGH, HIGH, HIGH, LOW, LOW};
int Y[] = {LOW, HIGH, HIGH, HIGH, LOW, HIGH, HIGH, LOW};
 
//Array of pointers for the 4 digits
int* lights[4];
 
//char array coming from the serial interface
//4 numbers or chars, 4 optional decimal points, 1 end-of-line char
char incoming[9] = {}; 
 
void setup() {
  Serial.begin(9600);
 
  for (byte digit=0;digit<4;digit++) {
    pinMode(DigitPins[digit], OUTPUT);
  }
  for (byte seg=0;seg<8;seg++) {
    pinMode(SegmentPins[seg], OUTPUT);
  }
  //initialize display with 1.234
  lights[0] = N1P;
  lights[1] = N2;
  lights[2] = N3;
  lights[3] = N4;
}
 
void loop() {
 
  //This part of the code is from the library SevSeg by Dean Reading
  for (byte seg=0;seg<8;seg++) {
    //Turn the relevant segment on
    digitalWrite(SegmentPins[seg],SegOn);
 
    //For each digit, turn relevant digits on
    for (byte digit=0;digit<4;digit++){
      if (lights[digit][seg]==1) {
        digitalWrite(DigitPins[digit],DigitOn);
      }
      //delay(200); //Uncomment this to see it in slow motion
    }
    //Turn all digits off
    for (byte digit=0;digit<4;digit++){
      digitalWrite(DigitPins[digit],DigitOff);
    }
 
    //Turn the relevant segment off
    digitalWrite(SegmentPins[seg],SegOff);
  } //end of for
}
