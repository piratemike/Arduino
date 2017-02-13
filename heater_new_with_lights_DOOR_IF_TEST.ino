#include <dht.h>

dht DHT;

#define DHT11_PIN 5
#define HEATER 13
#define WINDOW_SENSOR_PIN 8
#define MAX_TEMP 21 
#define MIN_TEMP 20
#define MAINLIGHT 11
#define MIRRORLIGHT 10
#define LAMPLEFT 2
#define LAMPRIGHT 3
#define DOOR_SENSOR_PIN 9

boolean heater_on = false;
boolean window_open = false;
boolean door_open = false;
unsigned long heater_on_ms = 0;
unsigned long last_temp_check = 0;
unsigned long last_door_check = 0;
unsigned long door_light_timer = 0;

String inputString = "";         // a string to hold incoming data
String heater_ctrl_on = "HTRON\n";
String heater_ctrl_off = "HTROFF\n";
boolean stringComplete = false;  // whether the string is complete

//MIRROR values
int mirrorState = HIGH;
long previous_mirror_ms = 0;
unsigned long current_mirror_ms = millis();
long mirror_on_time_ms = 5000;


void setup(){
  pinMode (WINDOW_SENSOR_PIN, INPUT_PULLUP);
  pinMode (DOOR_SENSOR_PIN, INPUT_PULLUP);
  pinMode (LAMPLEFT, OUTPUT);
  pinMode (LAMPRIGHT, OUTPUT);
  pinMode (HEATER, OUTPUT);
  pinMode (MAINLIGHT, OUTPUT);
  pinMode (MIRRORLIGHT, OUTPUT);
  
  digitalWrite(HEATER, HIGH);
  digitalWrite(MAINLIGHT, LOW);
  digitalWrite(LAMPLEFT, HIGH);
  digitalWrite(LAMPRIGHT, HIGH);
  digitalWrite(MIRRORLIGHT, HIGH);
  
  // turn heater off, so its state is known
  
  //window_open = digitalRead(WINDOW_SENSOR_PIN);
  Serial.begin(9600);
  int digitalRead = DHT.temperature;
  
}

void loop(){
 {  if (millis() - last_door_check > 1000){
        door_open = digitalRead(DOOR_SENSOR_PIN);
        if (door_open) digitalWrite(MIRRORLIGHT, LOW);
        else digitalWrite(MIRRORLIGHT, HIGH); last_door_check = millis();}} 
       
      
      //i inserted the code below after 'if (door open)'. Couldn't get it to work though
      
      //{if(current_mirror_ms - previous_mirror_ms > mirror_on_time_ms){
         //previous_mirror_ms = current_mirror_ms;
         //if (mirrorState == LOW) 
           //mirrorState = HIGH;
        // else mirrorState = LOW;
           //digitalWrite (MIRRORLIGHT, mirrorState);}} 
 
 
 
 
 
 
  
  // check the last time we ran the heater code
 { if (millis() - last_temp_check > 3000) {
    // it's been more than 10 seconds 
    int chk = DHT.read11(DHT11_PIN);
    Serial.print("TMP");
    Serial.println(DHT.temperature);
    
    if (DHT.temperature < MIN_TEMP && !heater_on){
      Serial.println("HTRON");
      digitalWrite(HEATER, LOW);
      heater_on = true;
      heater_on_ms = millis();
    // else if the temperature is too high and the heater is on
    } else if (DHT.temperature > MAX_TEMP && heater_on) {
      Serial.println("HTROFF");
      digitalWrite(HEATER, HIGH);
      heater_on = false;
    }
    
    last_temp_check = millis(); 
  } 
}
  if (stringComplete) {
    if (inputString == heater_ctrl_on) {
      Serial.println("HTRON");
      digitalWrite(HEATER, LOW);
      heater_on = true;
    } else if (inputString == heater_ctrl_off) {
      Serial.println("HTROFF");
      digitalWrite(HEATER, HIGH);
      heater_on = false;
    } else {
      Serial.println(inputString);
    }
    inputString = "";
    stringComplete = false;
  }
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
