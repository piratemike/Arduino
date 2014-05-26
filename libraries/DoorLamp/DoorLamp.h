#ifndef DoorLamp_h
#define DoorLamp_h

#include "Arduino.h"

class DoorLamp
{
  public:
    DoorLamp(int pin);
	void turnOnPermenantly();
	void turnOnTimed(int timeout);
    void turnOff();
	void updateState();
	bool isOn();
  private:
    int _pin;
    int _timeout;
    unsigned long _timeTurnedOn; 
	void _setTimeOn();
	void _turnOn();
	
	enum light_state
	{
	  ON,
	  OFF,
	  TIMED_ON,
	  TIMED_OFF
	};

    light_state _lightState;

};

#endif // DoorLamp_h
