//Set up the pins to be used and their purpose
const int sensorPin = A0;

//setup the offset for use when calculating the temperature 
//set to 0.5 for the TMP36 or 0 for the LM35 sensor
const int sensorOffset = 0.5; 

//Declaration of global variables
//Declare the variables that will be used to measure the tempreature 
int sensorVal;
float inputVoltage;
float voltage;
float temperature;

//Set a base temprature for the measurement
const float baselineTemp = 19.0;

//Declare a variable to be used to meausre the amount of time that has passed
long previousMillis;

void setup () {
  Serial.begin(9600); //Open Pin A0 as a serial port 
  
  //Loop round pins number 2 through to 6 and set them as output pins
  for (int pinNumber = 2; pinNumber <6; pinNumber++){
    pinMode(pinNumber, OUTPUT);
    digitalWrite(pinNumber, LOW);
  }

  //Set previousMillis to the number of milliseconds since the Arduino started
  previousMillis = millis();
}

void loop (){
  // Get the volgate measured at the analogue input
  sensorVal = analogRead(A0);
  
  //Set the input voltage to the actual input voltage on the arduino
  inputVoltage = readVcc()/1000;

  //Figure out the actual voltage on the analogue port
  voltage = (sensorVal/1024.0) * inputVoltage;
    
  //Convert the voltage to temperature in celcius
  temperature = (voltage - sensorOffset) * 100;

  //Check to see if a 10 minutes has passed
  if (millis() > (previousMillis + (1000.00 * 60.00 * 10))) {
       //If 10 mins has passed write of the temp and reset the timer
       writeTemp();
       previousMillis = millis();
  }
}

//code below is from SecretVoltmeter
//https://code.google.com/archive/p/tinkerit/wikis/SecretVoltmeter.wiki
long readVcc() { 
  long result; 
  // Read 1.1V reference against AVcc 
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1); 
  delay(2); 
  // Wait for Vref to settle 
  ADCSRA |= _BV(ADSC); 
  // Convert 
  while (bit_is_set(ADCSRA,ADSC)); 
  result = ADCL; 
  result |= ADCH<<8; 
  result = 1126400L / result; 
  // Back-calculate AVcc in mV 
  return result; 
 }



