const size_t SCAN_RESULT_MAX = 30;
/*BlescanResult is the class in which the data of the scanned beacons is stored.
scanResults is the object of that class which is created in the form of array , 
so we have created the scanResults[30] object of BlescanResult class which 
can store scanned(advertising) data of atmost 30 beacons*/
BleScanResult scanResults[SCAN_RESULT_MAX];
//BleScanResult scanResults;
SystemSleepConfiguration config;
#include <Adafruit_GPS.h>

// what's the name of the hardware serial port?
#define GPSSerial Serial1

// Connect to the GPS on the hardware port
Adafruit_GPS GPS(&GPSSerial);
     
/*Set GPSECHO to 'false' to turn off echoing the GPS data to the Serial console
 Set to 'true' if you want to debug and listen to the raw GPS sentences*/
#define GPSECHO true
uint32_t timer = millis();
/*custum_data[] stores the manufacture specific data of the beacon 
    get_data[] stores the advertising data as a complete block of the beacon*/
    uint8_t custom_data[BLE_MAX_ADV_DATA_LEN];   //BLE_MAX_ADV_DATA_LEN=31bytes
    uint8_t get_data[BLE_MAX_ADV_DATA_LEN];      //BLE_MAX_ADV_DATA_LEN=31bytes
    //variable for storing the number of bytes in custom_data
    char nobadv[20];
    //variables for storing and calculating the rssi value from the advertising data
    int rssi;
    int rssi_count;
    char rs[5];
    // variable for storing the address of the beacon 
    char addr[20];
    //variable for storing the number of bytes in adress
    char nobadr[20];
    //variable to store number of ble devices found
    char buffera[20];  
   //variable for storing the uuid of the beacon from advertising data
     char uuid[30];
     //variable for storing the major of the beacon from the advertising data
     char ma[5];
     //variable for storing the minor of the beacon from the advertising data
     char mi[5];
     //variable for storing the power of the beacon from the advertising data
     char po[5];
     
     
     /* 
     This function do the scanning for beacon devices and parse the advertising data , adress and rssi value*/
void scannedadvdata()
{
   Particle.publish("scanning data");
   delay(1000);
    /* Serial.println(BLE.scan(scanResults, SCAN_RESULT_MAX));
    this statement do the scanning , if in scanning it detects ble beacon then
    all the  scanned data can be accesed by scanResults object.
    and this function does not return untill it scans for any beacon device*/
   int count = BLE.scan(scanResults, SCAN_RESULT_MAX);
   itoa(count,buffera,10);
   Particle.publish("noofdevices",buffera);
   delay(1000);
   Serial.println(count);
   if(count)
    {  
    Serial.println("a ble device is found ");
    Particle.publish("a ble device is found ");
    // number of bytes in advertsing data is stored in len and advertising data is stored in custom_data
    int len=scanResults->advertisingData.customData(custom_data, sizeof(custom_data));
    itoa(len,nobadv,10);
    //printing uuid 
    snprintf(uuid, sizeof(uuid), "%02X%02X%02X%02X-%02X%02X-%02X%02X-%02X%02X-%02X%02X%02X%02X%02X%02X",
    custom_data[4], custom_data[5], custom_data[6], custom_data[7], custom_data[8], custom_data[9], 
    custom_data[10], custom_data[11], custom_data[12],custom_data[13], custom_data[14], custom_data[15],
    custom_data[16], custom_data[17], custom_data[18], custom_data[19]);
    //no of bytes of address is stored in the addrlen and address is stored in addr
    int addrlen = scanResults->address.toString(addr,sizeof(addr));
    Serial.print("address->");
    Serial.println(addr);
    itoa(addrlen,nobadr,10);
    //major
    int major = custom_data[20] * 256 + custom_data[21];
    itoa(major,ma,10);
    //minor
    int  minor = custom_data[22] * 256 + custom_data[23];
    itoa(minor,mi,10);
    //power
    int power = (int8_t)custom_data[24];
    itoa(power,po,10);
    //rssi
    rssi += scanResults->rssi;
    rssi_count++;
    itoa(rssi/rssi_count,rs,10);
    //rssi_count++;
}
else
{ 
    
    Serial.println(" no  ble device is found");
    Particle.publish(" no ble device is found");
    delay(1000);
    memset( nobadv,0, sizeof(nobadv));
    memset( rs,0, sizeof(rs));
    memset(addr ,0, sizeof(addr));
    memset( nobadr,0, sizeof(nobadr));
    memset( buffera,0, sizeof(buffera));
    memset(uuid ,0, sizeof(uuid));
    memset( ma,0, sizeof(ma));
    memset(mi ,0, sizeof(mi));
    memset( po,0, sizeof(po));
    memset(custom_data,0,sizeof(custom_data));
    scanResults->advertisingData.clear();

}
}

    bool isBeacon(const BleScanResult *scanResults)
{
  
    //Serial.println(scanResults->advertisingData.customData(custom_data, sizeof(custom_data)));
    if (scanResults->advertisingData.customData(custom_data, sizeof(custom_data)) == 25)                  // actual =25     //trial =9
    {
    if (custom_data[0] == 0x4c && custom_data[1] == 0x00 && custom_data[2] == 0x02 && custom_data[3] == 0x15)             //actual 0-0x4c  , 1-0x00  , 2-0x10  , 3-0x5
       {   /*
            
    Serial.print(custom_data[0],HEX);
    Serial.println(custom_data[1],HEX);
    Serial.println(custom_data[2],HEX);
    Serial.println(custom_data[3],HEX);
    */
    return true;
        }
    }
  /*
    //Serial.println(custom_data,HEX);
    Serial.println("false");
    Serial.print(custom_data[0],HEX);
    Serial.println(custom_data[1],HEX);
    Serial.println(custom_data[2],HEX);
    Serial.println(custom_data[3],HEX);
 */
    return false;
    }


void printbledataonconsule()
{ 
    Particle.publish("printing data");
    delay(1000);
    //no of bytes in custumdata
    Particle.publish("noofbytes",nobadv);
    // to print
    delay(1000);
    Particle.publish("uuid",uuid);
    delay(1000);
    Particle.publish("address",addr);
    delay(1000);
    Particle.publish("addrlen",nobadr);  
    delay(1000);
    Particle.publish("major",ma);
    delay(1000);
    Particle.publish("minor",mi);
    delay(1000);
    Particle.publish("power",po);
    delay(1000);
    Particle.publish("rssi",rs);
    delay(1000);
 
}
void printbledataonterminal()
{ 
   
   Serial.println("print data");
   // delay(1000);
   //no of bytes in custumdata
   Serial.print("noofbytes ->");
   Serial.println(nobadv);
   // delay(1000);
   Serial.print("uuid ->");
   Serial.println(uuid);
   //delay(1000);
   Serial.print("address->");
   Serial.println(addr);
   //delay(1000);
   Serial.print("addrlen->");
   Serial.println(nobadr);
   //delay(1000);
   Serial.print("major->");
   Serial.println(ma);
   //delay(1000);
   Serial.print("minor->");
   Serial.println(mi);
   //delay(1000);
   Serial.print("power->");
   Serial.println(po);
   //delay(1000);
   Serial.print("rssi->");
   Serial.println(rs);
   delay(1000);
 
}



void gpsinit()
{
        
    /* 9600 NMEA is the default baud rate for Adafruit MTK GPS's- some use 4800*/
    GPS.begin(9600);
    /* For parsing data, we don't suggest using anything but either RMC only or RMC+GGA since
    the parser doesn't care about other sentences at this time
    uncomment this line to turn on RMC (recommended minimum) and GGA (fix data) including altitude
    GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_ALLDATA);*/
    GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
    /*uncomment this line to turn on only the "minimum recommended" data
    GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);*/
    /* For the parsing code to work nicely and have time to sort thru the data, and
    print it out we don't suggest using anything higher than 1 Hz*/
    GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); 
    // Request updates on antenna status, comment out to keep quiet
    GPS.sendCommand(PGCMD_NOANTENNA);
    // Ask for firmware version
    // GPSSerial.println(PMTK_Q_RELEASE);
}


void gpsscanfix()
{
    // read data from the GPS in the 'main loop'
    //  Serial.println("");
    // Serial.println("scanning");
    //delay(100);
    char c = GPS.read();
    // if you want to debug, this is a good time to do it!
    if (GPSECHO)
    if (c) Serial.println(c);
    //Serial.println("receiving new nmea");
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


void gpsscanfixnew()
{
    while(!GPS.newNMEAreceived())
  
   {
    // Serial.println("receiving new nmea");
    char c = GPS.read();
    // if you want to debug, this is a good time to do it!
    //if (GPSECHO)
    // if (c) Serial.println(c);
    // Serial.print(".");
   }
    //Serial.println("exit while 1");
    // Serial.println(" received new nmea");
    while(GPS.newNMEAreceived())
    {  
    //Serial.println(" New Nmea received ");
    if (GPS.parse(GPS.lastNMEA())) 
    {
    //  Serial.println("New NMEA after succesfull parsing ");
    delay(100);
    /* a tricky thing here is if we print the NMEA sentence, or data
    we end up not listening and catching other sentences!
    so be very wary if using OUTPUT_ALLDATA and trytng to print out data
    Serial.println(GPS.lastNMEA()); // this also sets the newNMEAreceived() flag to false
    delay(1000);*/
    if (!GPS.parse(GPS.lastNMEA())) // this also sets the newNMEAreceived() flag to false
    return; // we can fail to parse
    }
   // Serial.println(GPS.lastNMEA());
}
}
void gpsdata()
{
   // Serial.println(GPS.lastNMEA());
     char time[10],date[10],lati[20],longi[20],fix[3],fiq[5];
     // if millis() or timer wraps around, we'll just reset it
    // Serial.println("gps data");
    Serial.println("gps data");
    // Serial.println(GPS.fix);
     //delay(1000);
     while(GPS.fix)
 {     
    Serial.println("fixed");
    Particle.process();
    delay(1000);
    Serial.print("\nTime: ");
    Serial.print(GPS.hour, DEC); Serial.print(':');
    Serial.print(GPS.minute, DEC); Serial.print(':');
    Serial.print(GPS.seconds, DEC); Serial.print('.');
    Serial.println(GPS.milliseconds);
    snprintf(time,sizeof(time),"%d:%d:%d",GPS.hour,GPS.minute,GPS.seconds);
    //Particle.publish("time",time);
    Serial.print("Date: ");
    Serial.print(GPS.day, DEC); Serial.print('/');
    Serial.print(GPS.month, DEC); Serial.print("/20");
    Serial.println(GPS.year, DEC);
    snprintf(date,sizeof(date),"%d:%d:%d",GPS.day,GPS.month,GPS.year);
    //Particle.publish("date",date);
    Serial.print("Fix: "); Serial.print((int)GPS.fix);
    itoa((int)GPS.fix,fix,10);
    //Particle.publish("fix",fix);
    Serial.print(" quality: "); Serial.println((int)GPS.fixquality);
    itoa((int)GPS.fixquality,fiq,10);
    //Particle.publish("fix quality ",fiq);
    Particle.process();
    //if (GPS.fix)
    //Serial.println("gupta");
    //Particle.publish("kunal");
    Serial.print("Location: ");
    //Serial.print(GPS.latitude,4); Serial.print(GPS.lat);
    snprintf(lati,sizeof(lati),"%f%c",GPS.latitudeDegrees,GPS.lat);
    //gcvt(GPS.latitudeDegrees,6,lati);
    //sprintf(GPS.latitudeDegrees,)
    Particle.publish("latitude",lati);
    Serial.print(GPS.latitudeDegrees,4);
    //Serial.print(GPS.latitude_fixed);
    Serial.print(", ");
    //Serial.print(GPS.longitude,4); Serial.println(GPS.lon);
    snprintf(longi,sizeof(longi),"%f%c",GPS.longitudeDegrees,GPS.lon);
    //gcvt(GPS.longitudeDegrees,6,longi);
    Particle.publish("longitude",longi);
    Serial.println(GPS.longitudeDegrees,4);
    //Serial.println(GPS.longitude_fixed);
    Serial.print("Speed (knots): "); Serial.println(GPS.speed);
    Serial.print("Angle: "); Serial.println(GPS.angle);
    Serial.print("Altitude: "); Serial.println(GPS.altitude);
    Serial.print("Satellites: "); Serial.println((int)GPS.satellites);
    Particle.process();
    Serial.println("scanning gps again for new update on gps data ");
    gpsscanfixnew();
    Serial.println("scanning for beacon");
    scannedadvdata();
       if(isBeacon(scanResults))
           {
              Serial.println("beaconfound");
              Particle.publish("beaconfound");
              break;
           }
       else
          {
              Serial.println("beacon not found so sending location");
              Particle.publish("beacon not found so sending location");
          }  //end of scan beacon if
 } //end of while gps.fix()
    while(!GPS.fix)
 {
    Serial.println("waiting to fix");
    Particle.publish("Waiting to fix");
    gpsscanfixnew();   // if gps is fixed then it will come out of this loop and also come out from gps data loop
    Serial.println("scanning for beacon");
    scannedadvdata();
       if(isBeacon(scanResults))
           {
              Serial.println("beaconfound");
              break;
           }
       else
          {
              Serial.println("beacon not found so trying to fix with gps signals again ");
               Particle.publish("beacon not found so trying to fix with gps signals again");
           }
 }
}

void setup() 

{
   pinMode(D4,INPUT);
   pinMode(D5,OUTPUT);
   pinMode(D7,OUTPUT);
   Serial.begin(9600);
   Serial.println("Adafruit GPS library basic test!");
   //BLE.scan(scanResults, SCAN_RESULT_MAX);
   config.mode(SystemSleepMode::STOP);
   config.duration(10s);
   gpsinit();
   gpsscanfixnew();
   BLE.setScanTimeout(50);
   scannedadvdata();

}

void loop()

{

   while(isBeacon(scanResults))
   {
    
    //gps turned off
    //digitalWrite(D5,HIGH);
    digitalWrite(D7,LOW);
    Particle.publish("found beacon");
    Serial.println("beacon found");
    printbledataonterminal();
    //argon goes to sleep
    System.sleep(config);
    //delay(2000);
    Particle.publish("waked up and scanning ");
    Serial.println("waked up and scanning ");
    scannedadvdata();
    // Particle.publish("scanning complete");
    }
    // Serial.println("out of while 1");
    while(!isBeacon(scanResults))
    {   
    //Serial.println(uuid);
    //gps turned on
    digitalWrite(D5,LOW);
    digitalWrite(D7,HIGH);
    Particle.publish(" not found beacon");
    Serial.println("beacon not found");
    gpsdata();
    // Particle.publish("kunal");
    //Serial.println(isBeacon(scanResults));
   // scannedadvdata();
    }
    //  Serial.println("out of while 2");  
    
}

 
