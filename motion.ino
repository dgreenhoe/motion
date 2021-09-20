//=============================================================================
//  Motion Detection
//
//  \author Daniel J. Greenhoe
//
//  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
//  https://www.arduino.cc/en/Tutorial/BuiltInExamples/DigitalReadSerial
//  https://www.arduino.cc/en/Main/Products
//=============================================================================

const int sensorPIR = 3;
//-----------------------------------------------------------------------------
// \brief Setup
//-----------------------------------------------------------------------------
void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);  // digital pin LED_BUILTIN as an output
  pinMode(sensorPIR,  INPUT);   // digital pin sensor is an input
  Serial.begin(9600);
}

//-----------------------------------------------------------------------------
// \brief Main Loop
//-----------------------------------------------------------------------------
void loop() {
  char buf[128];
  int sensorState = digitalRead(sensorPIR);
  digitalWrite(LED_BUILTIN, HIGH);   // switch LED on
  //sprintf(buf, "sensorState=%d\n", sensorState);
  //Serial.write(buf);
  Serial.println(5*sensorState);  // use Serial.println for use with "Serial Plotter"
  if(sensorState==HIGH)
  {  
    delay(5);
    digitalWrite(LED_BUILTIN, LOW);    // switch LED off
    delay(5);
  }
}
