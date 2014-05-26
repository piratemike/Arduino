//TMP36 Pin Variables
int sensorPin1 = 0;
int sensorPin2 = 1;
                        //the analog pin the TMP36's Vout (sense) pin is connected to
                        //the resolution is 10 mV / degree centigrade with a
                        //500 mV offset to allow for negative temperatures
 
/*
 * setup() - this function runs once when you turn your Arduino on
 * We initialize the serial connection with the computer
 */
void setup()
{
  Serial.begin(9600);  //Start the serial connection with the computer
                       //to view the result open the serial monitor 
}
 
void loop()                     // run over and over again
{
 //getting the voltage reading from the temperature sensor
 int reading1 = analogRead(sensorPin1);
 int reading2 = analogRead(sensorPin2); 
 
 // converting that reading to voltage, for 3.3v arduino use 3.3
 float voltage1 = reading1 * 5.0;
 voltage1 /= 1024.0; 
 float voltage2 = reading2 * 5.0;
 voltage2 /= 1024.0; 
 
 // print out the voltage
 Serial.print(voltage1); Serial.println(" volts");
 Serial.print(voltage2); Serial.println(" volts");
 
 // now print out the temperature
 float temperatureC1 = (voltage1 - 0.5) * 100 ;
 float temperatureC2 = (voltage2 - 0.5) * 100 ;  
 float temp = (temperatureC1 + temperatureC2)/2;
                                               //converting from 10 mv per degree wit 500 mV offset
                                               //to degrees ((voltage - 500mV) times 100)
 Serial.print(temperatureC1); Serial.println(" degrees C");
 Serial.print(temperatureC2); Serial.println(" degrees C");
 Serial.print(temp); Serial.println(" degrees C");

 
 // now convert to Fahrenheit
 float temperatureF = (temperatureC1 * 9.0 / 5.0) + 32.0;
 
 
 delay(4000);                                     //waiting a second
}
