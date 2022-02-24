//library for bluetooth
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

//Beacon List for check
const int NUMBER_OF_ELEMENTS = 2; //need to chance how many mac 
const int MAX_SIZE = 18;
char beacons [NUMBER_OF_ELEMENTS] [MAX_SIZE] = {
  { "xx:xx:xx:xx:xx:xx" }, //Beacon #1 headphone
  { "xx:xx:xx:xx:xx:xx" }, //Beacon #2 HUAWEI WATCH GT 2
};

//variables
 int scanTime = 3; //In seconds
 
//necessary
 BLEScan* pBLEScan;

//Checking to see if the Bluetooth Device is one of ours
bool mac_Check(const char test_mac[]) {
  for (int i = 0; i < NUMBER_OF_ELEMENTS; i++) {
    if (strcmp(test_mac, beacons[i]) == 0) {
      return true; //Match!
    }
  }
  return false; //No match.
}

bool ble_scanner (){
  bool key_found = false;
  Serial.print("Scanning for ");
  Serial.print(scanTime);
  Serial.println(" seconds.");

  BLEDevice::init("THE KEY SCANNER");
  pBLEScan = BLEDevice::getScan(); //create new scan
  //pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);  // less or equal setInterval value
  BLEScanResults foundDevices = pBLEScan->start(scanTime, false);

  int deviceCount = foundDevices.getCount();

  for (uint32_t i = 0; i < deviceCount; i++){
    BLEAdvertisedDevice device = foundDevices.getDevice(i);

    if (mac_Check(device.getAddress().toString().c_str())){

     Serial.print("Address ");
     Serial.print(device.getAddress().toString().c_str());
     Serial.print(" Name ");
     Serial.print(device.getName().c_str());
     Serial.print(" RSSI ");
     Serial.print(device.getRSSI());
     Serial.println(" matches our list of addresses, passed!");
    key_found = true;
    
    }else{

     Serial.print("Address ");
     Serial.print(device.getAddress().toString().c_str());
     Serial.print(" Name ");
     Serial.print(device.getName().c_str());
     Serial.print(" RSSI ");
     Serial.print(device.getRSSI());
     Serial.println(" did not match");

    }
  }
  if(key_found){
    Serial.println("Key found");
  }else{
    Serial.println("Key did not found");
  }
  return key_found;
  Serial.println("scan completed");
  pBLEScan->clearResults();   // delete results fromBLEScan buffer to release memory
  Serial.println("delete results fromBLEScan buffer to release memory");
}

void setup() {
  Serial.begin(115200);
}

void loop() {
  ble_scanner();
}

