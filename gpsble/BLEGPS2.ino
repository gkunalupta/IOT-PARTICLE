// This #include statement was automatically added by the Particle IDE.
#include <Adafruit_GPS.h>



const size_t SCAN_RESULT_MAX = 30;
/*BlescanResult is the class in which the data of the scanned beacons is stored.
scanResults is the object of that class which is created in the form of array , 
so we have created the scanResults[30] object of BlescanResult class which 
can store scanned(advertising) data of atmost 30 beacons*/
BleScanResult scanResults[SCAN_RESULT_MAX];
//BleScanResult scanResults;
SystemSleepConfiguration config;
//variable to store number of ble devices found
#include <Adafruit_GPS.h>

// what's the name of the hardware serial port?
#define GPSSerial Serial1

// Connect to the GPS on the hardware port
Adafruit_GPS GPS(&GPSSerial);
     
/*Set GPSECHO to 'false' to turn off echoing the GPS data to the Serial console
 Set to 'true' if you want to debug and listen to the raw GPS sentences*/
#define GPSECHO true
/*
void debugPrint( message){
    bool debug = false;
    if(debug){
        Serial.println(message);
    }
}
*/
int count=0;
char buffera[20];  
int ival=0;
class Jsonread
{
    public:
    char data[500];
};

class dataread
   {
       public:
       //custum_data[] stores the manufacture specific data of the beacon 
       //get_data[] stores the advertising data as a complete block of the beacon
       uint8_t custom_data[BLE_MAX_ADV_DATA_LEN];   //BLE_MAX_ADV_DATA_LEN=31bytes
       uint8_t get_data[BLE_MAX_ADV_DATA_LEN];      //BLE_MAX_ADV_DATA_LEN=31bytes
       //variable for storing the number of bytes in custom_data
       char nobadv[20];
       //variables for storing and calculating the rssi value from the advertising data
       char rs[50];
       // variable for storing the address of the beacon 
       char addr[30];
       //variable for storing the number of bytes in adress
       char nobadr[20];
       //variable for storing the uuid of the beacon from advertising data
       char uuid[30];
       //variable for storing the major of the beacon from the advertising data
       char ma[50];
       //variable for storing the minor of the beacon from the advertising data
       char mi[50];
       //variable for storing the power of the beacon from the advertising data
       char po[5];
       char blename[10];
       char blenamelen[5];
       char Jsondata[500];
       char Jsonpvtdata[100];
    };
  
dataread a[SCAN_RESULT_MAX];


void scannedadvdata()
{ 
    Particle.publish("scanning data");
    delay(1000);
    int rssi;
    int rssi_count;
    delay(1000);
    // Serial.println(BLE.scan(scanResults, SCAN_RESULT_MAX));
    count = BLE.scan(scanResults, SCAN_RESULT_MAX);   // --------> this statement scan for ble devices and store it in scanResults object and return number of devices found in timeperiod set by BLE.setScanTimeout(100);
    itoa(count,buffera,10);                           // the class of scanResult object has 4 members in the class-------->BleAddress address; BleAdvertisingData advertisingData; BleAdvertisingData scanResponse; int8_t rssi;
    Particle.publish("noofdevices",buffera);
    delay(1000);
    Serial.println(count);
      if(count)
        {  char hus[100];
           Serial.println(" ble device is found ");                                                         
           Particle.publish(" ble device is found ");
           delay(1000);
                        for(int i=0;i<count;i++)                                                       //-------->parsing the advertsing data to the class dataread
                          {                                                                             //-------->here count is the number of ble devices found and i is the ith ble device from 0 to count
                                int len=scanResults[i].advertisingData.customData(a[i].custom_data,31);  //-------->parsing the advertsing data
                                itoa(len,a[i].nobadv,10);
                                int namelen = scanResults[i].advertisingData.deviceName(a[i].blename,sizeof(a[i].blename));//------> parsing the device name and storing it in blename
                                itoa(namelen,a[i].blenamelen,10);                                                          //namelen is the length of the devicename
                                Serial.print("device name length->");
                                Serial.println(a[i].blenamelen);
                                //printing uuid 
                                snprintf(a[i].uuid, sizeof(a[i].uuid), "%02X%02X%02X%02X-%02X%02X-%02X%02X-%02X%02X-%02X%02X%02X%02X%02X%02X",
                                a[i].custom_data[4], a[i].custom_data[5], a[i].custom_data[6], a[i].custom_data[7], a[i].custom_data[8], a[i].custom_data[9], 
                                a[i].custom_data[10], a[i].custom_data[11], a[i].custom_data[12],a[i].custom_data[13], a[i].custom_data[14], a[i].custom_data[15],  //------->parsing the uuid from advertsing data
                                a[i].custom_data[16], a[i].custom_data[17], a[i].custom_data[18], a[i].custom_data[19]);
                                //no of bytes of address is stored in the addrlen and address is stored in addr
                                int addrlen = scanResults[i].address.toString(a[i].addr,sizeof(a[i].addr));     //------->parsing the address from the scanResults object
                                Serial.print("address->");
                                Serial.println(a[i].addr);
                                itoa(addrlen,a[i].nobadr,10);
                                //major
                                int major = a[i].custom_data[20] * 256 + a[i].custom_data[21];                  //-------> parsing the major 
                                snprintf(a[i].ma,sizeof(a[i].ma),"%i",major);
                                Serial.print("major->");
                                Serial.println(major);
                               // Particle.publish("major",a[i].ma);
                                //delay(1000);
                                //minor
                                int  minor = a[i].custom_data[22] * 256 + a[i].custom_data[23];                 //------->parsing the minor
                                snprintf(a[i].mi,sizeof(a[i].mi),"%i",minor);
                                Serial.print("minor->");
                                Serial.println(minor);
                                //Particle.publish("minor",a[i].mi);
                                //delay(1000);
                                //power
                                int power = (int8_t)a[i].custom_data[24];                                      //--------->parsing the power
                                itoa(power,a[i].po,10);
                                //rssi
                                char rsvalue[50];
                                rssi += scanResults[i].rssi;
                                rssi_count++;                                                                      
                                itoa((rssi/rssi_count),rsvalue,10);                                                //--------> parsing the rssi value
                                Serial.print("rssi->");
                                Serial.println(rssi/rssi_count);
                                //Particle.publish("rssi",rsvalue);
                               // delay(1000);  
                                
                                
                                
                                char BN[20];
                                memset( a[i].Jsondata,0, sizeof(a[i].Jsondata));
                                memset(BN,0,sizeof(BN));
                                JSONBufferWriter writer(a[i].Jsondata, sizeof(a[i].Jsondata) - 1);
                                snprintf( BN, sizeof(BN),  "beacon device  %d", i);
                                writer.beginObject();
                                writer.name(BN).beginObject();
                                writer.name("noofbytes").value(a[i].nobadv);
                                writer.name("UUID").value(a[i].uuid);
                                writer.name("device name").value(a[i].blename);
                                writer.name("address").value(a[i].addr);
                                writer.name("address length").value(a[i].nobadr);
                                writer.name("major-").value(a[i].ma);
                                writer.name("minor-").value(a[i].mi);
                                writer.name("Power").value(a[i].po);
                                writer.name("rssi").value(rssi/rssi_count);
                                
                                writer.endObject();
                                writer.endObject();
                                delay(1000);
                                //Particle.publish("Beacon Devices", a[i].Jsondata);
                                delay(1000);
                          }

        }
    else
       { 
    
            Serial.println(" no  ble device is found");
            Particle.publish(" no ble device is found");
            delay(1000);
                        for(int i=0;i<count;i++)
                            {
                                memset( a[i].nobadv,0, sizeof(a[i].nobadv));
                                memset(a[i].rs,0, sizeof(a[i].rs));
                                memset(a[i].addr ,0, sizeof(a[i].addr));
                                memset( a[i].nobadr,0, sizeof(a[i].nobadr));
                                memset(a[i].uuid ,0, sizeof(a[i].uuid));
                                memset( a[i].ma,0, sizeof(a[i].ma));
                                memset(a[i].mi ,0, sizeof(a[i].mi));
                                memset( a[i].po,0, sizeof(a[i].po));
                                memset( a[i].blename,0,sizeof(a[i].blename));
                                memset(a[i].custom_data,0,sizeof(a[i].custom_data));
                                
                                scanResults[i].advertisingData.clear();
                            }
                            
        }

}

 bool isBeacon(const BleScanResult *scanResults)
{
    Serial.println(" no ob devices ");
    Serial.println(count);
        for(int i=0;i<count;i++)
           { 
              Serial.println(scanResults[i].advertisingData.customData(a[i].custom_data, sizeof(a[i].custom_data)));
                 if (scanResults[i].advertisingData.customData(a[i].custom_data, sizeof(a[i].custom_data)) == 25)                  // actual =25     //trial =9
                    {
                            if (a[i].custom_data[0] == 0x4c && a[i].custom_data[1] == 0x00 && a[i].custom_data[2] == 0x02 && a[i].custom_data[3] == 0x15)             //actual 0-0x4c  , 1-0x00  , 2-0x10  , 3-0x5
                            {   

                                delay(1000);
                                ival=i;
                                 Serial.print(a[i].custom_data[0],HEX);
                                 Serial.println(a[i].custom_data[1],HEX);
                                 Serial.println(a[i].custom_data[2],HEX);
                                 Serial.println(a[i].custom_data[3],HEX);
                                 return true;
                            }
                    }
  
                delay(1000);
                ival=0;
                Serial.println("false");
                Serial.print(a[i].custom_data[0],HEX);
                Serial.println(a[i].custom_data[1],HEX);
                Serial.println(a[i].custom_data[2],HEX);
                Serial.println(a[i].custom_data[3],HEX);
               
            }
            return false;
}



void printbledataonconsule()
{ 
    for(int i=0;i<count;i++)
      {
          
          
          
          
          
          
          
          
          
           Particle.publish("printing data");
           delay(1000);
           //no of bytes in custumdata
           Particle.publish("noofbytes",a[i].nobadv);
           // to print
           delay(1000);
           Particle.publish("uuid",a[i].uuid);
           delay(1000);
           Particle.publish("device name", a[i].blename);
           delay(1000);
           Particle.publish("address",a[i].addr);
           delay(1000);

           Particle.publish("addrlen",a[i].nobadr);  
           delay(1000);
           Particle.publish("major",a[i].ma);
           delay(1000);
           Particle.publish("minor",a[i].mi);
           delay(1000);
           Particle.publish("power",a[i].po);
           delay(1000);
           Particle.publish("rssi",a[i].rs);
           delay(1000);
       }
}


void printbledataonterminal()
{ 
   for(int i=0;i<count;i++)
       {
           Serial.println("print data");
           // delay(1000);
           //no of bytes in custumdata
           Serial.print("noofbytes ->");
           Serial.println(a[i].nobadv);
           // to print
           // delay(1000);
           Serial.print("uuid ->");
           Serial.println(a[i].uuid);
           //delay(1000);
           Serial.print("device name->");
           Serial.println(a[i].blename);
           //delay(1000);
           Serial.print("address->");
           Serial.println(a[i].addr);
           //delay(1000);
           Serial.print("addrlen->");
           Serial.println(a[i].nobadr);
           //delay(1000);
           Serial.print("major->");
           Serial.println(a[i].ma);
           //delay(1000);
           Serial.print("minor->");
           Serial.println(a[i].mi);
           //delay(1000);
           Serial.print("power->");
           Serial.println(a[i].po);
           //delay(1000);
           Serial.print("rssi->");
           Serial.println(a[i].rs);
           delay(1000);
       }
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
    Serial.print("Date: ");
    Serial.print(GPS.day, DEC); Serial.print('/');
    Serial.print(GPS.month, DEC); Serial.print("/20");
    Serial.println(GPS.year, DEC);
    snprintf(date,sizeof(date),"%d:%d:%d",GPS.day,GPS.month,GPS.year);
    Serial.print("Fix: "); Serial.print((int)GPS.fix);
    itoa((int)GPS.fix,fix,10);
    Serial.print(" quality: "); Serial.println((int)GPS.fixquality);
    itoa((int)GPS.fixquality,fiq,10);
    Particle.process();
    Serial.print("Location: ");
    //Serial.print(GPS.latitude,4); Serial.print(GPS.lat);
    snprintf(lati,sizeof(lati),"%f%c",GPS.latitudeDegrees,GPS.lat);
    Particle.publish("latitude",lati);
    delay(1000);
    Serial.print(GPS.latitudeDegrees,4);
    //Serial.print(GPS.latitude_fixed);
    Serial.print(", ");
    //Serial.print(GPS.longitude,4); Serial.println(GPS.lon);
    snprintf(longi,sizeof(longi),"%f%c",GPS.longitudeDegrees,GPS.lon);
    //gcvt(GPS.longitudeDegrees,6,longi);
    Particle.publish("longitude",longi);
    delay(1000);
    Serial.println(GPS.longitudeDegrees,4);
    //Serial.println(GPS.longitude_fixed);
    Serial.print("Speed (knots): "); Serial.println(GPS.speed);
    Serial.print("Angle: "); Serial.println(GPS.angle);
    Serial.print("Altitude: "); Serial.println(GPS.altitude);
    Serial.print("Satellites: "); Serial.println((int)GPS.satellites);
    
//GPS JSON data    
                                char BN[20], GPS_DATA[200];
                                memset( GPS_DATA,0, sizeof(GPS_DATA));
                                memset(BN,0,sizeof(BN));
                                memset(GPS_DATA,0,200);
                                JSONBufferWriter writer(GPS_DATA, sizeof(GPS_DATA) - 1);
                                snprintf( BN, sizeof(BN),  "GPS DATA ");
                                writer.beginObject();
                                writer.name(BN).beginObject();
                                writer.name("Time").value(time);
                                writer.name("Date").value(date);
                                writer.name("Fix").value(fix);
                                writer.name("quality").value(fiq);
                                writer.name("Latitude").value(lati);
                                writer.name("Longitude").value(longi);
                                writer.name("speed").value(GPS.speed);
                                writer.name("Amgle").value(GPS.angle);
                                writer.name("Altitudes").value(GPS.altitude);
                                writer.name("Satellites : ").value(GPS.satellites);
                                writer.endObject();
                                writer.endObject();
                                delay(1000);
                                
                                Particle.publish("GPS",GPS_DATA);
    
    
    
    Particle.process();
    Serial.println("scanning gps again for new update on gps data ");
    Particle.publish("scanning gps again for new update on gps data");
    delay(1000);
    gpsscanfixnew();
    Serial.println("scanning for beacon");
    Particle.publish("scanning for beacon");
    scannedadvdata();
       if(isBeacon(scanResults))
           {
              Serial.println("beaconfound");
              Particle.publish("beaconfound");
              delay(1000);
              break;
           }
       else
          {
              Serial.println("beacon not found so sending location");
              Particle.publish("beacon not found so sending location");
              delay(1000);
          }  //end of scan beacon if
 } //end of while gps.fix()
    while(!GPS.fix)
    {
    Serial.println("waiting to fix");
    Particle.publish("Waiting to fix");
    delay(1000);
    gpsscanfixnew();   // if gps is fixed then it will come out of this loop and also come out from gps data loop
    Serial.println("scanning for beacon");
    Particle.publish("scanning for beacon");
    delay(1000);
    scannedadvdata();
       if(isBeacon(scanResults))
           {
              Serial.println("beaconfound");
              Particle.publish("beaconfound");
              delay(1000);
              break;
           }
       else
          {
              Serial.println("beacon not found so trying to fix with gps signals again ");
               Particle.publish("beacon not found so trying to fix with gps signals again");
               delay(1000);
           }
 }
}

void setup() 

{
   pinMode(D4,INPUT);
   pinMode(D5,OUTPUT);
   pinMode(D7,OUTPUT);
   Serial.begin(9600);
 //  Serial1.begin(9600);
   //Serial.println("Adafruit GPS library basic test!");
   //Serial.println("Adafruit GPS library basic test!");
   //BLE.scan(scanResults, SCAN_RESULT_MAX);
   config.mode(SystemSleepMode::STOP);
   config.duration(10s);
   gpsinit();
   //gpsscanfixnew();
   BLE.setScanTimeout(100);
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
    delay(1000);
    Serial.println("beacon found");
    //printbledataonterminal();
    //printbledataonconsule();
    //argon goes to sleep
    Particle.publish("adv data of found ibeacon", a[ival].Jsondata);
    System.sleep(config);
    //delay(2000);
    
    Particle.publish("waked up and scanning ");
    delay(1000);
    Serial.println("waked up and scanning ");
    scannedadvdata();
    // Particle.publish("scanning complete");
    }
     //Serial.println("out of while 1");
    gpsscanfixnew();
    while(!isBeacon(scanResults))
    {   
    //Serial.println(uuid);
    //gps turned on
    digitalWrite(D5,LOW);
    digitalWrite(D7,HIGH);
    Particle.publish(" not found beacon");
    delay(1000);
    Serial.println("beacon not found");
    gpsdata();
    // Particle.publish("kunal");
    //Serial.println(isBeacon(scanResults));
   // scannedadvdata();
    }
    //  Serial.println("out of while 2");  
}
