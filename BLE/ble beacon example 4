/* ************************************************************ble beacon code *************************************************/

const size_t SCAN_RESULT_MAX = 30;
/*BlescanResult is the class in which the data of the scanned beacons is stored.
scanResults is the object of that class which is created in the form of array , 
so we have created the scanResults[30] object of BlescanResult class which 
can store scanned(advertising) data of atmost 30 beacons*/
BleScanResult scanResults[SCAN_RESULT_MAX];
//BleScanResult scanResults;
SystemSleepConfiguration config;
//variable to store number of ble devices found
int count;
char buffera[20];  
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
       char rs[5];
       // variable for storing the address of the beacon 
       char addr[30];
       //variable for storing the number of bytes in adress
       char nobadr[20];
       //variable for storing the uuid of the beacon from advertising data
       char uuid[30];
       //variable for storing the major of the beacon from the advertising data
       char ma[5];
       //variable for storing the minor of the beacon from the advertising data
       char mi[5];
       //variable for storing the power of the beacon from the advertising data
       char po[5];
       char blename[10];
       char blenamelen[5];
    };
  
dataread a[SCAN_RESULT_MAX];


void scannedadvdata()
{ 
    Particle.publish("scanning data");
    int rssi;
    int rssi_count;
    delay(1000);
    // Serial.println(BLE.scan(scanResults, SCAN_RESULT_MAX));
    count = BLE.scan(scanResults, SCAN_RESULT_MAX);
    itoa(count,buffera,10);
    Particle.publish("noofdevices",buffera);
    delay(1000);
    Serial.println(count);
      if(count)
        {  
           Serial.println(" ble device is found ");
           Particle.publish(" ble device is found ");
                        for(int i=0;i<count;i++)
                          {
                                // number of bytes in advertsing data is stored in len and advertising data is stored in custom_data
                                int len=scanResults[i].advertisingData.customData(a[i].custom_data,31);
                                itoa(len,a[i].nobadv,10);
                                int namelen = scanResults[i].advertisingData.deviceName(a[i].blename,sizeof(a[i].blename))
                                itoa(namelen,a[i].blenamelen,10);
                                Serial.print("device name length->");
                                Serial.println(a[i].blenamelen);
                                //printing uuid 
                                snprintf(a[i].uuid, sizeof(a[i].uuid), "%02X%02X%02X%02X-%02X%02X-%02X%02X-%02X%02X-%02X%02X%02X%02X%02X%02X",
                                a[i].custom_data[4], a[i].custom_data[5], a[i].custom_data[6], a[i].custom_data[7], a[i].custom_data[8], a[i].custom_data[9], 
                                a[i].custom_data[10], a[i].custom_data[11], a[i].custom_data[12],a[i].custom_data[13], a[i].custom_data[14], a[i].custom_data[15],
                                a[i].custom_data[16], a[i].custom_data[17], a[i].custom_data[18], a[i].custom_data[19]);
                                //no of bytes of address is stored in the addrlen and address is stored in addr
                                int addrlen = scanResults[i].address.toString(a[i].addr,sizeof(a[i].addr));
                                Serial.print("address->");
                                Serial.println(a[i].addr);
                                itoa(addrlen,a[i].nobadr,10);
                                //major
                                int major = a[i].custom_data[20] * 256 + a[i].custom_data[21];
                                itoa(major,a[i].ma,10);
                                Serial.print("major->");
                                Serial.println(a[0].ma);
                                //minor
                                int  minor = a[i].custom_data[22] * 256 + a[i].custom_data[23];
                                itoa(minor,a[i].mi,10);
                                Serial.print("minor->");
                                Serial.println(a[0].mi);
                                //power
                                int power = (int8_t)a[i].custom_data[24];
                                itoa(power,a[i].po,10);
                                //rssi
                                char rsvalue[5];
                                rssi += scanResults->rssi;
                                rssi_count++;
                                itoa(rssi/rssi_count,rsvalue,10);
                                Serial.print("rssi->");
                                Serial.println(rssi/rssi_count);
                                //Serial.println(rsvalue);
                                //rssi_count++;
                                // printbledataonterminal();
                                //isBeacon(scanResults);  
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
            
                                 Serial.print(a[i].custom_data[0],HEX);
                                 Serial.println(a[i].custom_data[1],HEX);
                                 Serial.println(a[i].custom_data[2],HEX);
                                 Serial.println(a[i].custom_data[3],HEX);
                                 return true;
                            }
                    }
               //Serial.println(custom_data,HEX);
                Serial.println("false");
                Serial.print(a[i].custom_data[0],HEX);
                Serial.println(a[i].custom_data[1],HEX);
                Serial.println(a[i].custom_data[2],HEX);
                Serial.println(a[i].custom_data[3],HEX);
                // return false;
            }
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

void setup() 

  {

    pinMode(D5,OUTPUT);
    pinMode(D7,OUTPUT);
    Serial.begin(9600);
    Serial.println("Adafruit GPS library basic test!");
    //BLE.scan(scanResults, SCAN_RESULT_MAX);
    config.mode(SystemSleepMode::STOP);
    config.duration(10s);
    BLE.setScanTimeout(100);
    scannedadvdata();
    // BLE.scan(scanResults, SCAN_RESULT_MAX);
    Serial.print("major->");
    Serial.println(a[0].ma);
    Serial.print("minor->");
    Serial.println(a[0].mi);
   }

void loop()

{
    

  scannedadvdata();
  
  printbledataonterminal();
  isBeacon(scanResults);
  
}
