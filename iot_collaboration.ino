const int sensorPin = A0;
const float baselineTemp = 19.0;

void setup () {
  Serial.begin(9600); //Open Pin A0 as a serial port 
  
  //Loop round pins number 2 through to 6 and set them as output pins
  for (int pinNumber = 2; pinNumber <6; pinNumber++){
    pinMode(pinNumber, OUTPUT);
    digitalWrite(pinNumber, LOW);
  }
}

void loop (){

  // Get the volgate measured at the analogue input
  int sensorVal = analogRead(A0);
  
  //Send the information to the PC so that it can be seen
  Serial.print("Sensor value: ");
  Serial.print(sensorVal);
  
  //Figure out the actual voltage on the analogue port
  float voltage = (sensorVal/1024.0) * 4.1;
  
  //Push these values to the PC
  Serial.print(" Voltage: ");
  Serial.print(voltage);
  
  //Send the temperature to the PC
  Serial.print(", degrees C: ");
  
  //Convert the voltage to temperature in celcius
  float temperature = (voltage - 0.5) * 100;
  Serial.println(temperature);
}
