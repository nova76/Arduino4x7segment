/*
 * firmata for 4x7segment Display
*/

#include <Firmata.h>

/*==============================================================================
 * SYSEX-BASED commands
 *============================================================================*/

void sysexCallback(byte command, byte argc, byte *argv)
{
  switch (command) {
    case CAPABILITY_QUERY:
      Firmata.write(START_SYSEX);
      Firmata.write(CAPABILITY_RESPONSE);
      for (byte pin = 0; pin < TOTAL_PINS; pin++) {
        if (IS_PIN_DIGITAL(pin)) {
          Firmata.write((byte)INPUT);
          Firmata.write(1);
          Firmata.write((byte)OUTPUT);
          Firmata.write(1);
        }
        if (IS_PIN_ANALOG(pin)) {
          Firmata.write(ANALOG);
          Firmata.write(10); // 10 = 10-bit resolution
        }
        if (IS_PIN_PWM(pin)) {
          Firmata.write(PWM);
          Firmata.write(8); // 8 = 8-bit resolution
        }
        if (IS_PIN_DIGITAL(pin)) {
          Firmata.write(SERVO);
          Firmata.write(14);
        }
        if (IS_PIN_I2C(pin)) {
          Firmata.write(I2C);
          Firmata.write(1);  // TODO: could assign a number to map to SCL or SDA
        }
        Firmata.write(127);
      }
      Firmata.write(END_SYSEX);
      break;
    case ANALOG_MAPPING_QUERY:
      Firmata.write(START_SYSEX);
      Firmata.write(ANALOG_MAPPING_RESPONSE);
      for (byte pin = 0; pin < TOTAL_PINS; pin++) {
        Firmata.write(IS_PIN_ANALOG(pin) ? PIN_TO_ANALOG(pin) : 127);
      }
      Firmata.write(END_SYSEX);
      break;
  }
}




bool DISPLAY_BOOL = false;


/*
 * https://github.com/BenTommyE/Arduino_getStringPartByNr
 */
String getStringPartByNr(String data, char separator, int index)
{
    // spliting a string and return the part nr index
    // split by separator
    
    int stringData = 0;        //variable to count data part nr 
    String dataPart = "";      //variable to hole the return text
    
    for(int i = 0; i<data.length(); i++) {    //Walk through the text one letter at a time
      
      if(data[i]==separator) {
        //Count the number of times separator character appears in the text
        stringData++;
        
      }else if(stringData==index) {
        //get the text when separator is the rignt one
        dataPart.concat(data[i]);
        
      }else if(stringData>index) {
        //return text and stop if the next separator appears - to save CPU-time
        return dataPart;
        break;
        
      }

    }
    //return text if this is the last part
    return dataPart;
}
/*
 * https://coderwall.com/p/zfmwsg/arduino-string-to-char
 */
char* string2char(String command){
    if(command.length()!=0){
        char *p = const_cast<char*>(command.c_str());
        return p;
    }
}


String DISPLAY_VALUE = "0000";

void stringCallback(char *myString)
{
  
  if (getStringPartByNr(myString, '|', 0)=="DISPLAY")
  {
    lcd_setup();
    if (getStringPartByNr(myString, '|', 1) == "OFF")
    {
      DISPLAY_BOOL = false;  
    }
    else if (getStringPartByNr(myString, '|', 1) == "ON")
    {
      DISPLAY_BOOL = true;  
      setLights(DISPLAY_VALUE);
    }
    else
    {
      DISPLAY_BOOL = true;
      DISPLAY_VALUE = getStringPartByNr(myString, '|', 1);   
      setLights(DISPLAY_VALUE);
    }
    Firmata.sendString(string2char(DISPLAY_VALUE));
  }
  
  Firmata.sendString(myString);
}

void setup()
{
  Firmata.setFirmwareVersion(FIRMATA_MAJOR_VERSION, FIRMATA_MINOR_VERSION);

  Firmata.attach(START_SYSEX, sysexCallback);
  Firmata.attach(STRING_DATA, stringCallback);

  Firmata.begin(57600);
  
}

/*==============================================================================
 * LOOP()
 *============================================================================*/

void loop()
{

  if (DISPLAY_BOOL == true)
  {
    lcd_loop();
  }

  /* STREAMREAD - processing incoming messagse as soon as possible, while still
   * checking digital inputs.  */
  while (Firmata.available())
    Firmata.processInput();
}
