// Test code for Ultimate GPS Using Hardware Serial
// (e.g. GPS for Leonardo, Flora or FeatherWing)
//
// This code shows how to test a passthru between USB and hardware serial
//
// Tested and works great with the Adafruit GPS FeatherWing
// ------> https://www.adafruit.com/products/3133
// or Flora GPS
// ------> https://www.adafruit.com/products/1059
// but also works with the shield, breakout
// ------> https://www.adafruit.com/products/1272
// ------> https://www.adafruit.com/products/746
// 
// Pick one up today at the Adafruit electronics shop
// and help support open source hardware & software! -ada

 #include <Adafruit_GPS.h>
  /* 
  what's the name of the hardware serial port? Serial1( Hardware Serial) is the port for 
  communicating with GPS receiver and defining GPSSerial for Serial1 keyword
  argon     GPS receiver
  Rx  ----->   Tx
  Tx  ----->   Rx
  */
  #define GPSSerial Serial1
  Adafruit_GPS GPS(&GPSSerial);

void setup()
{
  // wait for hardware serial to appear
  while (!Serial);

  // make this baud rate fast enough to we aren't waiting on it
  Serial.begin(115200);
  pinMode(D4,INPUT);
  // 9600 baud is the default rate for the Ultimate GPS
  GPSSerial.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
 
  /* uncomment this line to turn on only the "minimum recommended" data
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);
  For parsing data, we don't suggest using anything but either RMC only or RMC+GGA since
  the parser doesn't care about other sentences at this time
  Set the update rate*/
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); // 1 Hz update rate
  // For the parsing code to work nicely and have time to sort thru the data, and
  // print it out we don't suggest using anything higher than 1 Hz
     
}

     
void loop() 
{  
  char fixvalue[5];
  if (Serial.available())
    {
       char c = Serial.read();
       GPSSerial.write(c);
    }
  // Serial.println("fix pin --");
  //Serial.println(digitalRead(D4));
  int x = digitalRead(D4);
  itoa(x,fixvalue,10);
  Particle.publish("fix pin --",fixvalue);
  delay(1000);
  while(GPSSerial.available()>0)
    {
       char c = GPSSerial.read();
       Serial.write(c);
       delay(10);
    }
}

