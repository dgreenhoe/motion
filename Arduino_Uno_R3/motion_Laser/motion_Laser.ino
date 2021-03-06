//=============================================================================
// Motion Detection using PIR
//
// \author Daniel J. Greenhoe
//
// https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
// https://www.arduino.cc/en/Tutorial/BuiltInExamples/DigitalReadSerial
// https://www.arduino.cc/en/Main/Products
// https://youtu.be/mZCJNOf69JI
// Hardware Needs:
//   (1) Arduino Uno R3 board
//   (2) HC-SR501 PIR Motion Sensor module
// References
//   (1) HC-SR501
//       https://www.amazon.com/dp/B07KZW86YR 
//       https://learn.adafruit.com/pir-passive-infrared-proximity-motion-sensor
//       https://diyi0t.com/hc-sr501-pir-motion-sensor-arduino-esp8266-esp32/
//       https://www.epitran.it/ebayDrive/datasheet/44.pdf
//       https://www.mpja.com/download/31227sc.pdf
//       https://youtu.be/M4q85neFwjE  Andreas Spiess "#325 6 PIR Sensors tested..."
//        _____________________
//       |                    o|<--jumper top two for single detect
//       |  BOTTOM VIEW       o|
//       |                    o|<--jumper bottom two for repeated detect
//       |         __________5V (regulated down to 3.3V through Holtek 7133-1 LDO)
//       |        |  ________Digital Out (3.3V==>motion detected, 0V==>no detect)
//       |        | |  ______GND
//       |        | | |        |
//       |        o o o        |
//       |_____________________|
//    (2) Holtek HT7133-1 3.3V 30mA LDO  
//        https://www.holtek.com/documents/10179/116711/HT71xx-1v250.pdf
// 
//=============================================================================

const int digitalPin = 3;
const int laserEnbl  = 4;
const int analogPin  = A3;
//-----------------------------------------------------------------------------
// \brief Setup
//-----------------------------------------------------------------------------
void setup()
{
  pinMode(LED_BUILTIN, OUTPUT); // configure digital pin LED_BUILTIN as an output
  pinMode(digitalPin,  INPUT);   // configure digital pin sensor as an input
  pinMode(laserEnbl,  OUTPUT);   // configure digital pin as output
//  digitalWrite(LED_BUILTIN, LOW);    // switch LED off
  Serial.begin(9600);
  digitalWrite( laserEnbl, HIGH );
  Serial.write("Laser ON!!!\n");
}

//-----------------------------------------------------------------------------
// \brief Main Loop
//-----------------------------------------------------------------------------
void loop() {
  char buf[128];
  char buf2[128];
//int sensorState = digitalRead(digitalPin);
  int sensorState = analogRead(analogPin);
  float outVal = 5.0 * (float)sensorState / 1024.0;
  dtostrf(outVal,8,3,buf2);
  sprintf(buf, "sensorState=%d  %s\n", sensorState, buf2);
  //Serial.write(buf);
  //Serial.println(5*sensorState);  // use Serial.println for use with "Serial Plotter"
  Serial.println(outVal);  // use Serial.println for use with "Serial Plotter"
  if(sensorState>500)
  {  
    digitalWrite(LED_BUILTIN, HIGH);   // switch LED on
    delay(5);
    digitalWrite(LED_BUILTIN, LOW);    // switch LED off
  }
}
