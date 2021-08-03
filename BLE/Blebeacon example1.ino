
const size_t SCAN_RESULT_MAX = 30;
BleScanResult scanResults[SCAN_RESULT_MAX];
//BleScanResult scanResults;
void setup() 

{
   // BLE.on();
   // BLE.begin();
}

void loop()
{
    delay(1000);
    uint8_t custom_data[BLE_MAX_ADV_DATA_LEN];   //BLE_MAX_ADV_DATA_LEN=31bytes
    int rssi;
    int rssi_count;
    char addr[20];
     char buffera[20];  //
     char nobadv[20];  //
     char nobadr[20];  //
     char uuid[30];
     char ma[5];
     char mi[5];
     char po[5];
     char rs[5];
    // char major[30];
     //char addr[30];
   /// int a=10;
    BLE.setScanTimeout(50);
    int count = BLE.scan(scanResults, SCAN_RESULT_MAX);
    itoa(count,buffera,10);
    //Particle.publish("noofdevices",buffera);
  // delay(3000);
  
  // number of bytes in advertsing data is stored in len and advertising data is stored in custom_data
    int len=scanResults->advertisingData.customData(custom_data, sizeof(custom_data));
    itoa(len,nobadv,10);
    Particle.publish("noofbytes",nobadv);
   delay(1000);
   //printing uuid 
    snprintf(uuid, sizeof(uuid), "%02X%02X%02X%02X-%02X%02X-%02X%02X-%02X%02X-%02X%02X%02X%02X%02X%02X",custom_data[4], custom_data[5], custom_data[6], custom_data[7], custom_data[8], custom_data[9], custom_data[10], custom_data[11], custom_data[12],custom_data[13], custom_data[14], custom_data[15], custom_data[16], custom_data[17], custom_data[18], custom_data[19]);
    Particle.publish("uuid",uuid);
   // delay(1000);
    //no of bytes of address is stored in the addrlen and address is stored in addr
    int addrlen = scanResults->address.toString(addr,sizeof(addr));
    Particle.publish("address",addr);
   delay(1000);
    itoa(addrlen,nobadr,10);
    Particle.publish("addrlen",nobadr);         
    delay(1000);
    //major
    int major = custom_data[20] * 256 + custom_data[21];
    itoa(major,ma,10);
    Particle.publish("major",ma);
    delay(1000);
    //minor
   int  minor = custom_data[22] * 256 + custom_data[23];
   itoa(minor,mi,10);
   Particle.publish("minor",mi);
   delay(1000);
   //power
  int power = (int8_t)custom_data[24];
  itoa(power,po,10);
  Particle.publish("power",po);
  delay(1000);
       //rssi
       
       rssi += scanResults->rssi;
        rssi_count++;
        itoa(rssi/rssi_count,rs,10);
        Particle.publish("rssi",rs);
       delay(1000);
        //rssi_count++;
    }
