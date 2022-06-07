#include <DS3231.h>
#define POTENSIO A3
#define COLDWHITE 5
#define BLUEPIN 6
#define REDPIN 9
#define GREENPIN 10
#define WARMWHITE 11
#define PIN1 7
#define BUTTON 13

DS3231 rtc(SDA,SCL);

String hari;
String waktu;
String tanggal;
int rasio;
int mode;
String jam;
String menit;
int h;
int m;
int count = 0;
int led_mode = 0;
float index_rasio = 0.1;
bool start = false;
bool switch_to_mode = false;

void setup() {
  rtc.begin();
  Serial.begin(9600);
  pinMode(BUTTON, INPUT);
  pinMode(POTENSIO, INPUT);
  pinMode(PIN1, OUTPUT);
  //rtc.setDOW(TUESDAY);
  //rtc.setTime(5,44,0);
  //rtc.setDate(7,6,2022);
}

void loop() {
  hari=rtc.getDOWStr();
  waktu=rtc.getTimeStr();
  tanggal=rtc.getDateStr();
  rasio = analogRead(POTENSIO);
  mode = digitalRead(BUTTON);

  jam = waktu.substring(0,2);
  h = jam.toInt();
  menit = waktu.substring(3,5);
  m = menit.toInt();
  
  //Serial.print(h);
  //Serial.println(m);
   
  if(start && led_mode == 0){
    time(h,m);
  }
  
  if(!start){
    analogWrite(REDPIN,    LOW);
    analogWrite(GREENPIN,  LOW);
    analogWrite(BLUEPIN,   LOW);
    analogWrite(COLDWHITE, LOW);
    analogWrite(WARMWHITE, LOW);
  }
  
  on_off_button(mode);
  potensio_rasio(rasio);
}

void on_off_button(int on_off){
  Serial.print("on_off: ");
  Serial.print(on_off);
  Serial.print(" count: ");
  Serial.print(count);
  Serial.print(" led_mode: ");
  Serial.print(led_mode);
  Serial.print(" mode: ");
  Serial.print(switch_to_mode);
  Serial.print(" jam: ");
  Serial.print(jam);
  Serial.print(" menit: ");
  Serial.print(menit);
  Serial.print(" rasio: ");
  Serial.println(index_rasio * 255);
  delay(500);
  if(on_off == 0){
    count++;
    // Turn on the lamp
    if(count >= 6 && !start){
      start = true;
      switch_to_mode = true;
      led_mode = 0;
      count = 0;
      digitalWrite(PIN1, start);
    }
    // Turn off the lamp
    if(count >= 6 && start){
      start = false;
      switch_to_mode = false;
      led_mode = 0;
      count = 0;
      digitalWrite(PIN1, start);
    }
  }
  
  // reset number of count
  if(on_off == 1){
    if(count < 6 && !start){
      count = 0;
    }
    if(count < 2){
      count = 0;
    }
    if(switch_to_mode){
      if(led_mode == 0 && count >= 2){
        Serial.println("switch mode");
        light("K25", "L56"); 
        led_mode = 1;  
        count = 0;

        //test
        digitalWrite(PIN1 , LOW);
        delay(500);
        digitalWrite(PIN1, HIGH);
        delay(500);
      }
      if(led_mode == 1 && count >= 2){
        Serial.println("switch mode");
        light("K45", "L72"); 
        led_mode = 2;
        count = 0;

        //test
        digitalWrite(PIN1 , LOW);
        delay(500);
        digitalWrite(PIN1, HIGH);
        delay(500);
      }
      if(led_mode == 2 && count >= 2){
        Serial.println("switch mode");
        led_mode = 0;
        count = 0;

        //test
        digitalWrite(PIN1 , LOW);
        delay(500);
        digitalWrite(PIN1, HIGH);
        delay(500);
        digitalWrite(PIN1 , LOW);
        delay(500);
        digitalWrite(PIN1, HIGH);
        delay(500);
      }
    }
  }
}


void potensio_rasio(int rasio){
  if (rasio >= 0 && rasio < 60){
    index_rasio = 0.06;
  }
  if (rasio >= 60 && rasio < 120){
    index_rasio = 0.12;
  }
  if (rasio >=120 && rasio < 180){
    index_rasio = 0.18;
  }
  if (rasio >=180 && rasio < 240){
    index_rasio = 0.24;
  }
  if (rasio >=240 && rasio < 300){
    index_rasio = 0.3;
  }
  if (rasio >=300 && rasio < 360){
    index_rasio = 0.36;
  }
  if (rasio >=360 && rasio < 420){
    index_rasio = 0.42;
  }
  if (rasio >=420 && rasio < 480){
    index_rasio = 0.48;
  }
  if (rasio >=480 && rasio < 540){
    index_rasio = 0.54;
  }
  if (rasio >=540 && rasio < 600){
    index_rasio = 0.6;
  }
  if (rasio >=600 && rasio < 660){
    index_rasio = 0.66;
  }
  if (rasio >=660 && rasio < 720){
    index_rasio = 0.72;
  }
  if (rasio >=720 && rasio < 780){
    index_rasio = 0.78;
  }
  if (rasio >=780 && rasio < 840){
    index_rasio = 0.84;
  }
  if (rasio >=840 && rasio < 900){
    index_rasio = 0.90;
  }
  if (rasio >=900 && rasio < 960){
    index_rasio = 0.96;
  }
  if (rasio >=960){
    index_rasio = 1.0;
  }
}

void time(int h, int m)
{
  if(h==9 && m < 30){              
    light("K45", "L72");          //1
  }
  if(h==9 && m >= 30 && m < 59){  
    light("K40", "L67");          //2
  }
  if(h==10 && m < 30){            
    light("K35", "L64");          //3
  }
  if(h==10 && m >= 30 && m < 59){ 
    light("K30", "L63");          //4
  }
  if(h==11 && m < 30){
    light("K28", "L57");          //5
  }
  if(h==11 && m >= 30 && m <59){  
    light("K25", "L56");          //6
  }
  if(h==12 && m < 30){           
    light("K25", "L55");          //7
  }
  if(h==12 && m >= 30 && m < 59){ 
    light("K25", "L55");          //8
  }
  if(h==13 && m < 30){            
    light("K45", "L71");          //9
  }
  if(h==12 && m >= 30 && m < 59){ 
    light("K40", "L72");          //10
  }
  if(h==14 && m < 30){            
    light("K35", "L70");          //11
  }
  if(h==14 && m >= 30 && m < 59){ 
    light("K30", "L66");          //12
  }
  if(h==15 && m < 30){            
    light("K25", "L61");          //13
  }
  if(h==15 && m >= 30 && m < 59){ 
    light("K25", "L56");          //14
  }
  if(h==16 && m < 30){            
    light("K25", "L55");          //15
  }
  if(h==16 && m >= 30 && m < 45){ 
    light("K25", "L60");          //16
  }
  if(h==16 && m >= 45 || h == 17){
    light("K25", "L65");          //17
  }
}

void light(String index_K, String index_L )
{
    // Index Kelvin
  int r=0,g=0,b=0,cw=0,ww=0 ;
    if ( index_K == "K25" ) {
      r = 255;
      g = 161;
      b = 72; 
    }
    if ( index_K == "K28" ) {
      r = 255;
      g = 173;
      b = 94; 
    }
    if ( index_K == "K30" ) {
      r = 255;
      g = 180;
      b = 107; 
    }
    if ( index_K == "K35" ) {
      r = 255;
      g = 196;
      b = 137; 
    }
    if ( index_K == "K40" ) {
      r = 255;
      g = 209;
      b = 163; 
    }
    if ( index_K == "K45" ) {
      r = 255;
      g = 255;
      b = 255; 
    }
  
  //Index Lux
    if ( index_L == "L55" ) {
      cw = 131;
      ww = 124; 
    }
    if ( index_L == "L56" ) {
      cw = 128;
      ww = 127; 
    }
    if ( index_L == "L57" ) {
      cw = 117;
      ww = 138; 
    }
    if ( index_L == "L60" ) {
      cw = 119;
      ww = 136; 
    }
    if ( index_L == "L61" ) {
      cw = 117;
      ww = 138; 
    }
    if ( index_L == "L63" ) {
      cw = 97;
      ww = 158; 
    }
    if ( index_L == "L64" ) {
      cw = 81;
      ww = 174; 
    }
    if ( index_L == "L65" ) {
      cw = 108;
      ww = 147; 
    }
    if ( index_L == "L66" ) {
      cw = 89;
      ww = 116; 
    }
    if ( index_L == "L67" ) {
      cw = 61;
      ww = 194; 
    }
    if ( index_L == "L70" ) {
      cw = 64;
      ww = 191; 
    }
    if ( index_L == "L71" ) {
      cw = 49;
      ww = 206; 
    }
    if ( index_L == "L72" ) {
      cw = 46;
      ww = 209; 
    }
  analogWrite(REDPIN,     r * index_rasio);
  analogWrite(GREENPIN,   g * index_rasio);
  analogWrite(BLUEPIN,    b * index_rasio);
  analogWrite(COLDWHITE,  cw * index_rasio);
  analogWrite(WARMWHITE,  ww * index_rasio);
}
