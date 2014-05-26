#include <Button.h>
#include <DoorLamp.h>

#define OPEN 0
#define CLOSED 1
#define ON 0
#define OFF 1

int reedSwitch = 3;
int led = 12;
unsigned long timeout = 15000;
DoorLamp lamp1(led);
Button button = Button(11, PULLUP);

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // make the pushbutton's pin an input:
  pinMode(reedSwitch, INPUT);
  
}


void loop() {
  int doorState = digitalRead(reedSwitch);
  int buttonState = digitalRead(11);
  if ( doorState == OPEN )
  {
    lamp1.turnOnTimed(timeout);
  }
  if ( (lamp1.isOn() == false) && button.uniquePress() )
  {
    lamp1.turnOnPermenantly(); 
  }
  if( (lamp1.isOn() == true) && ( button.uniquePress() )) {
    lamp1.turnOff();
  } 
  lamp1.updateState();
}


