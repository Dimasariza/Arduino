#include <SoftwareSerial.h>

#include <LiquidCrystal.h>
#include <stdio.h>

#define PIN1 12
#define WARMWHITE 3
#define GREENPIN 4
#define REDPIN 5
#define BLUEPIN 6
#define COLDWHITE 7
#define SWITCH 13

int h = 9;
int m = 0;
float s = 0.1;
float ms = 0.1;
int maxS = 0;
int flag = 0;
int TIME = 0;
int state1 = 0;
int state2 = 0;
String K_conds;
String L_konds;
int button;
int count = 0;
bool switchOnOff = true;
int light_step = 0;

void setup()
{
  pinMode(PIN1, OUTPUT);
  pinMode(WARMWHITE, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(REDPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
  pinMode(COLDWHITE, OUTPUT);
  pinMode(SWITCH, INPUT);
  Serial.begin(9600);
}

void loop()
{
  // ====================== Time calculating =============== 
    s = s + 0.10;
    ms = ms + 0.10;
    maxS = maxS + 1;

    if (flag == 24) flag = 0;
    delay(100);

      //Serial.print(h);
      //Serial.print(";");
      //Serial.print(m);
      //Serial.print(";");
      //Serial.println(s);
      
    if (ms > 1.1) {
      ms = 0.1;
    }
    if (maxS == 600)
    {
      s = 0.1;
      m = m + 1;
      maxS = 0;
    }
    if (m == 60)
    {
      m = 0;
      h = h + 1;
      flag = flag + 1;
    }
    if (h == 24)
    {
      h = 0;
    }
    
    test_light();
    if (!switchOnOff){
      time(h, m);
    } else if (switchOnOff) {
      analogWrite(REDPIN, 0);
      analogWrite(GREENPIN, 0);
      analogWrite(BLUEPIN, 0);
      analogWrite(COLDWHITE, 0);
      analogWrite(WARMWHITE, 0);
    }
    button = digitalRead(SWITCH);
    Serial.println(button);
    switchButton(button);
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
  analogWrite(REDPIN, r);
  analogWrite(GREENPIN, g);
  analogWrite(BLUEPIN, b);
  analogWrite(COLDWHITE, cw);
  analogWrite(WARMWHITE, ww);
}

void switchButton(int conds)
{
    if(conds == 0 && switchOnOff) {
        count += 1;
      if(count == 20){
        light_step = 1;
        count = 0;
        switchOnOff = false;
        Serial.println("On");
      }
    };

    if(conds == 0 && !switchOnOff){
      count += 1;

      if (count == 15 && light_step == 1) {
          count = 0;
          light("K25", "L56"); 
          light_step = 2;
          Serial.println("change to step 1");
      }
      
      if (count == 15 && light_step == 2) {
          count = 0;
          light("K45", "L71"); 
          light_step = 1;
          Serial.println("change to step 2");
      }

      
      if(count == 20){
        light_step = 0;
        count = 0;
        switchOnOff = true;
        Serial.println("Off");
      }
    }
}








  //================== 3 right Digital Led test
void test_light()
{
  if (ms >= 0.1 && ms < 0.5){
    digitalWrite(PIN1, HIGH);
  }
  if (ms >= 0.5 && ms < 0.9){
    digitalWrite(PIN1, LOW);
  }
}
