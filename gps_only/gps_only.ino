#include <TinyGPS++.h>
#include <SoftwareSerial.h>

static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;
 String gps_loc = "";
 String gps_date = "";
 String gps_time = "";
 String gps_data = "";
 int TIME_CORRECTION = 6;
// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

void setup(){
  Serial.begin(9600);
  ss.begin(GPSBaud);
}

void loop(){
  // This sketch displays information every time a new sentence is correctly encoded.
  while (ss.available() > 0){
    gps.encode(ss.read());
    if (gps.location.isUpdated()){
      gps_loc = String(gps.location.lat(), 6)+"_"+String(gps.location.lng(), 6);
      gps_date = String(gps.date.year())+"/"+String(gps.date.month())+"/"+String(gps.date.day());
      gps_time = String(gps.time.hour()-TIME_CORRECTION)+":"+String(gps.time.minute())+":"+String(gps.time.second());
      gps_data = gps_date+"_"+gps_time+"_"+gps_loc;
      Serial.println(gps_data);
      delay(3000);
    }
  }
}
