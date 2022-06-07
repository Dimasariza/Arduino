#include <DS3231.h>
#define PIN1 12
DS3231 rtc(SDA,SCL);

const int relay=A3;
bool on=LOW;
bool off=HIGH;
String hari;
String waktu;
String tanggal;

void setup() {
  rtc.begin();
  Serial.begin(9600);
  pinMode(relay,OUTPUT);
  pinMode(PIN1, OUTPUT);
  digitalWrite(relay,off);
  //rtc.setDOW(WEDNESDAY);
  //rtc.setTime(18,51,0);
  //rtc.setDate(1,6,2022);
}

void loop() {
  delay(100);
  digitalWrite(PIN1, HIGH);
  delay(100);
  digitalWrite(PIN1, LOW);


  //hari=rtc.getDOWStr();
  waktu=rtc.getTimeStr();
  //tanggal=rtc.getDateStr();
  Serial.println(waktu);

  //delay(1000);
}
