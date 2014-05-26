#include "DoorLamp.h"

DoorLamp::DoorLamp(int pin)
{
  _pin = pin; 
  _lightState = OFF;
  pinMode(pin, OUTPUT);
}

void DoorLamp::turnOnPermenantly()
{
  if( _lightState != ON ) {
    Serial.println("Turned light on permenantly");
    _lightState = ON;
	_turnOn();
  }
}

void DoorLamp::isOn()
{
  if ( _lightState == ON )
  {
    return true;
  }
  else if ( _lightState == TIMED_ON )
  {
    return true;
  }
  else
  {
    return false;
  }
}

void DoorLamp::_turnOn()
{
  digitalWrite(_pin, HIGH); 
}

void DoorLamp::turnOnTimed(int timeout)
{
  if( _lightState != ON ) {
    Serial.println("Turned light on temporarily");
    _timeout = timeout;
    _turnOn();
    _setTimeOn();
    _lightState = TIMED_ON;
  }
}

void DoorLamp::_setTimeOn()
{
  _timeTurnedOn = millis();
}

void DoorLamp::turnOff()
{
  if ( (_lightState == ON ) || (_lightState == TIMED_ON)) {
    digitalWrite(_pin, LOW);
	_lightState = OFF;
  }
}

void DoorLamp::updateState()
{
  if( _lightState == TIMED_ON )
  {
    Serial.print("millis = ");
	Serial.println(millis());
	Serial.print("_timeTurnedOn = ");
	Serial.println(_timeTurnedOn);
    if( (millis() - _timeTurnedOn) > _timeout )
    {
      turnOff();
      Serial.println("Turned light off");
    }  
  }
}
