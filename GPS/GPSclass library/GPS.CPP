#include <Adafruit_GPS.h>

// what's the name of the hardware serial port?
#define GPSSerial Serial1

// Connect to the GPS on the hardware port
Adafruit_GPS GPS(&GPSSerial);
     
// Set GPSECHO to 'false' to turn off echoing the GPS data to the Serial console
// Set to 'true' if you want to debug and listen to the raw GPS sentences
#define GPSECHO true

void GPS::gpsinit()
{
         
  // 9600 NMEA is the default baud rate for Adafruit MTK GPS's- some use 4800
  GPS.begin(9600);
  // uncomment this line to turn on RMC (recommended minimum) and GGA (fix data) including altitude
 // GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_ALLDATA);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
 
  // uncomment this line to turn on only the "minimum recommended" data
  //GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);
  // For parsing data, we don't suggest using anything but either RMC only or RMC+GGA since
  // the parser doesn't care about other sentences at this time
  // Set the update rate
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); // 1 Hz update rate
  // For the parsing code to work nicely and have time to sort thru the data, and
  // print it out we don't suggest using anything higher than 1 Hz
     
  // Request updates on antenna status, comment out to keep quiet
  GPS.sendCommand(PGCMD_NOANTENNA);
  // Ask for firmware version
 // GPSSerial.println(PMTK_Q_RELEASE);
}
void GPS::gpsscanfix()
{
    
     // read data from the GPS in the 'main loop'
   //  Serial.println("");
  // Serial.println("scanning");
   //delay(100);
      char c = GPS.read();
  // if you want to debug, this is a good time to do it!
  if (GPSECHO)
    if (c) Serial.println(c);
 //   Serial.println("receiving new nmea");
  // if a sentence is received, we can check the checksum, parse it...
  if (GPS.newNMEAreceived()) {
     delay(1000);
      Serial.println("New NMEA");
    // a tricky thing here is if we print the NMEA sentence, or data
    // we end up not listening and catching other sentences!
    // so be very wary if using OUTPUT_ALLDATA and trytng to print out data
    Serial.println(GPS.lastNMEA()); // this also sets the newNMEAreceived() flag to false
    
    //delay(1000);
    if (!GPS.parse(GPS.lastNMEA())) // this also sets the newNMEAreceived() flag to false
      return; // we can fail to parse a sentence in which case we should just wait for another
  }
  Serial.println(GPS.lastNMEA());
}


void GPS::gpsscanfixnew()
{ 
    //when no NMEA command is received 
    while(!GPS.newNMEAreceived())
  
   {
       
       //return  the each incoming character from gps receiver and buffer that in the string that is returned by GPS.lastNMEA() function
        char c = GPS.read();
  // if you want to debug, this is a good time to do it!
  //if (GPSECHO)
  //  if (c) Serial.println(c);
    Serial.println("receiving new nmea");
    }

    // when nem NMEA command is reeceived 
    while(GPS.newNMEAreceived())
    {      // GPS.parse() checks whether NEW NMEA command received can be parsed or not 
         if (GPS.parse(GPS.lastNMEA())) 
       {
     // Serial.println("New NMEA");
      delay(100);

   // Serial.println(GPS.lastNMEA()); // this also sets the newNMEAreceived() flag to false
      
    //delay(1000);
    if (!GPS.parse(GPS.lastNMEA())) // this also sets the newNMEAreceived() flag to false
      return; // we can fail to p
        
    }
   // Serial.println(GPS.lastNMEA());
}
}
void GPS::gpsdata()
{
   // Serial.println(GPS.lastNMEA());
     char time[10],date[10],lati[20],longi[20],fix[3],fiq[5];
    // Serial.println("gps data");
    Serial.println("gps data");
    // Serial.println(GPS.fix);
     //delay(1000);
     while(GPS.fix)
{     
    Serial.println("fixed");
    Particle.process();
    delay(1000);
    
    /*
    //For printing time on terminal screen 
    Serial.print("\nTime: ");
    Serial.print(GPS.hour, DEC); Serial.print(':');
    Serial.print(GPS.minute, DEC); Serial.print(':');
    Serial.print(GPS.seconds, DEC); Serial.print('.');
    Serial.println(GPS.milliseconds);
    */
    
    /* As GPS.hour , GPS.minute and GPS.seconds are uint8_t type(d) so these are catenated into a string time for publishing it into consule*/
    snprintf(time,sizeof(time),"%d:%d:%d",GPS.hour,GPS.minute,GPS.seconds);
    Particle.publish("time",time);
    /*
    //For printing date on terminal screen
    Serial.print("Date: ");
    Serial.print(GPS.day, DEC); Serial.print('/');
    Serial.print(GPS.month, DEC); Serial.print("/20");
    Serial.println(GPS.year, DEC);
    */
    /*As GPS.year , GPS.day and GPS.month are uint8_t type(d) so these are catenated into a string time for publishing it into consule*/
    snprintf(date,sizeof(date),"%d:%d:%d",GPS.day,GPS.month,GPS.year);
    Particle.publish("date",date);
    /*Print Fix on Terminal screen*/
    Serial.print("Fix: "); Serial.print((int)GPS.fix);
    /* converting int GPS.fix to string for publishing it into consule*/
    itoa((int)GPS.fix,fix,10);
    Particle.publish("fix",fix);
    /*Print Fix quality on terminal screen*/
    Serial.print(" quality: "); Serial.println((int)GPS.fixquality);
    /* converting int GPS.fixquality to string for publishing it into consule*/
    itoa((int)GPS.fixquality,fiq,10);
    Particle.publish("fix quality ",fiq);
    Particle.process();
    //if (GPS.fix)
    Serial.println("gupta");
        Particle.publish("kunal");
      Serial.print("Location: ");
     // Serial.print(GPS.latitude,4); Serial.print(GPS.lat);
    snprintf(lati,sizeof(lati),"%f%c",GPS.latitudeDegrees,GPS.lat);
    // gcvt(GPS.latitudeDegrees,6,lati);
   // sprintf(GPS.latitudeDegrees,)
     Particle.publish("latitude",lati);
      Serial.print(GPS.latitudeDegrees,4);
      //Serial.print(GPS.latitude_fixed);
      Serial.print(", ");
     // Serial.print(GPS.longitude,4); Serial.println(GPS.lon);
    snprintf(longi,sizeof(longi),"%f%c",GPS.longitudeDegrees,GPS.lon);
   // gcvt(GPS.longitudeDegrees,6,longi);
     Particle.publish("longitude",longi);
      Serial.println(GPS.longitudeDegrees,4);
    // Serial.println(GPS.longitude_fixed);
      Serial.print("Speed (knots): "); Serial.println(GPS.speed);
      Serial.print("Angle: "); Serial.println(GPS.angle);
      Serial.print("Altitude: "); Serial.println(GPS.altitude);
      Serial.print("Satellites: "); Serial.println((int)GPS.satellites);
      Particle.process();
      
      Serial.println("end");
      
      //check again whether New NMEA command is received or not , so that GPS.fix can be updated 
      gpsscanfixnew();
    

}//end of while gps.fix()
while(!GPS.fix)
{
    Serial.println("waiting to fix");
     //check again whether New NMEA command is received or not , so that GPS.fix can be updated 
    gpsscanfixnew();
}
}
