
import processing.serial.*; // soros port eléréséhez
import cc.arduino.*; // firmata eléréséhez

Arduino arduino; // Arduino, mint objektum

int LOW = 0;
int HIGH = 1;

int ledPin = 2;
int DigitOn = 0;
int DigitOff = 1;
int SegOn=HIGH;
int SegOff=LOW;
int DigitPins[] = {10, 11, 12, 13};
int SegmentPins[] = {2, 3, 4, 5, 6, 7, 8, 9};

//Array of pointers for the 4 digits

//char array coming from the serial interface
//4 numbers or chars, 4 optional decimal points, 1 end-of-line char

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

//initialize display with 1.234
int[][] lights = { N0, N0, N0, N0 };  

void setup()
{
  println(Arduino.list()); // Arduinonak tűnő eszközök listája
  arduino = new Arduino(this, Arduino.list()[0], 57600); 
  // megnyitjuk a portot
  background(0);
  
  for (byte digit=0;digit<4;digit++) {
    arduino.pinMode(DigitPins[digit], Arduino.OUTPUT);
  }
  for (byte seg=0;seg<8;seg++) {
    arduino.pinMode(SegmentPins[seg], Arduino.OUTPUT);
  }
}

void loop()
{
  //This part of the code is from the library SevSeg by Dean Reading
  for (byte seg=0;seg<8;seg++) {
    //Turn the relevant segment on
    arduino.digitalWrite(SegmentPins[seg],SegOn);
 
    //For each digit, turn relevant digits on
    for (byte digit=0;digit<4;digit++){
      if (lights[digit][seg]==HIGH) {
        arduino.digitalWrite(DigitPins[digit],DigitOn);
      }
      //delay(200); //Uncomment this to see it in slow motion
    }
    //Turn all digits off
    for (byte digit=0;digit<4;digit++){
      arduino.digitalWrite(DigitPins[digit],DigitOff);
    }
 
    //Turn the relevant segment off
    arduino.digitalWrite(SegmentPins[seg],SegOff);
  } //end of for  
}

int i,i2 = 0;
int time1 = millis();

void draw()
{
  int time2 = millis();
  if (time2-time1>1000) { 
      time1=time2;
      i ++ ; 
      i2 = i;
      println(i);
      for (int j = 0; j < 4; j = j+1) {
        lights[3-j] = getArray(i2%10);
        i2 = int(i2/10);
      }      
  }
  loop();  
}

int[] getArray(int i)
{
  int[] result;
        switch(i) {
        case 0: 
          result = N0;
          break;
        case 1: 
          result = N1;
          break;
        case 2: 
          result = N2;
          break;
        case 3: 
          result = N3;
          break;
        case 4: 
          result = N4;
          break;
        case 5: 
          result = N5;
          break;
        case 6: 
          result = N6;
          break;
        case 7: 
          result = N7;
          break;
        case 8: 
          result = N8;
          break;
        case 9: 
          result = N9;
          break;
        default:
          result = BLANK;
      }
      return result;  

}



 
 