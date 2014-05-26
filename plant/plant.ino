/*  Soil Moisture measurement v0.1 20091017
 Simple circuit
 Not calibrated at this moment
 
 Started by Mike Rice, October 14, 2009
 Modified by M.A. de Pablo, October 17, 2009
 
 Circuit:
 To connect two nails and a 10 KOhms resistor as shown:
 
        digital 2---*
                  |
                  \
                  /
                  \ R1
                  /
                  |
                  |
        analog 0----*
                  |
                  |
                  *----> nail 1
                 
                  *----> nail 2
                  |
                  |
                  |
        digital 3---*
 */
 /* Code indicates moisture levels using three led's, green, yellow, red attached to pins 8,9,10 and then to ground.
 REPLACE this code with a signal to a relay to use only one pin.
 A testing needs to be follwed by an action with an interuptable delay to allow water to permeate the soil.
 Also include a 24 hour cycle which ensure overwatering does not occur if that is needed - RESEARCH THIS.
 Re-work code to include 'matser-timer' code to allow other actions to take place while countdowns happen.
 */

#define moisture_input 0
#define divider_top 2
#define divider_bottom 3

int moisture; // analogical value obtained from the experiment

int SoilMoisture(){
  int reading;
  // set driver pins to outputs
  pinMode(divider_top,OUTPUT);
  pinMode(divider_bottom,OUTPUT);

  // drive a current through the divider in one direction
  digitalWrite(divider_top,LOW);
  digitalWrite(divider_bottom,HIGH);

  // wait a moment for capacitance effects to settle
  delay(100);

  // take a reading
  reading=analogRead(moisture_input);

  // reverse the current
  digitalWrite(divider_top,HIGH);
  digitalWrite(divider_bottom,LOW);

  // give as much time in 'reverse' as in 'forward'
  delay(100);

  // stop the current
  digitalWrite(divider_bottom,LOW);

  return reading;
}

void setup () {
  Serial.begin(9600);
  int green = 10;
  int yellow = 9;
  int red = 8;
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);}

void loop (void) {
  moisture=SoilMoisture(); // assign the result of SoilMoisture() to the global variable 'moisture'
  Serial.print("Soil moisture: ");
  Serial.print(moisture); // print the analogical measurement of the experiment
  // later i will improve here a calculation for derive Soil Moisture in %
  Serial.println();
  if (moisture <= 10) {digitalWrite(8,LOW); digitalWrite(9,LOW);digitalWrite(10,LOW);} //Accounts for sensor out of the soil
  if (moisture > 11 && moisture <= 100) {digitalWrite(8,HIGH); digitalWrite(9,LOW);digitalWrite(10,LOW);} //Dry
  if (moisture > 100 && moisture <= 500) {digitalWrite(8,LOW);digitalWrite(9,HIGH);digitalWrite(10,LOW);} // Medium
  if (moisture > 500) {digitalWrite(8,LOW);digitalWrite(9,LOW);digitalWrite(10,HIGH);} //Wet
   delay(100);
}



