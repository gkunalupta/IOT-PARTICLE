const size_t SCAN_RESULT_MAX = 30;
// BlescanResult is the class in which the data of the scanned beacons is stored.
//scanResults is the object of that class which is created in the form of array , 
//so we have created the scanResults[30] object of BlescanResult class which 
//can store scanned(advertising) data of atmost 30 beacons
BleScanResult scanResults[SCAN_RESULT_MAX];
//BleScanResult scanResults;
SystemSleepConfiguration config;
//custum_data[] stores the manufacture specific data of the beacon 
    //get_data[] stores the advertising data as a complete block of the beacon
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

void setup() 

{

   pinMode(D5,OUTPUT);
   pinMode(D7,OUTPUT);
   Serial.begin(9600);
   Serial.println("Adafruit GPS library basic test!");
   BLE.setScanTimeout(100);
   scannedadvdata();
   config.mode(SystemSleepMode::STOP);
   config.duration(10s);

}

void loop()

{
    

  scannedadvdata();
  
  printbledataonterminal();
  isBeacon(scanResults);
    while(isBeacon(scanResults))
      {
          
      
      digitalWrite(D7,LOW);
      Particle.publish("found beacon");
      delay(1000);
      Serial.println("beacon found");
      printbledataonterminal();
      /* comment the next line if u dont want argon to go to sleep*/
      System.sleep(config);
      Serial.println(isBeacon(scanResults));
      scannedadvdata();
       }
    // Serial.println("out of while 1");
  
    while(!isBeacon(scanResults))
      {   
      
      //gps turned on
      digitalWrite(D5,LOW);
      digitalWrite(D7,HIGH);
      Particle.publish(" not found beacon");
      delay(1000);
      Serial.println("beacon not found");
      //printbledataonterminal();
      // Particle.publish("kunal");
      scannedadvdata();
       }
    // Serial.println("out of while 2");  
}
