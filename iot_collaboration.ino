//Set up the pins to be used and their purpose
const int sensorPin = A0;

//Declaration of global variables
//Declare the variables that will be used to measure the tempreature 
int sensorVal;
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

  //Figure out the actual voltage on the analogue port
  voltage = (sensorVal/1024.0) * 4.1;
    
  //Convert the voltage to temperature in celcius
  temperature = (voltage - 0.5) * 100;

  //Check to see if a 10 minutes has passed
  if (millis() > (previousMillis + (1000.00 * 60.00 * 10))) {
       //If 10 mins has passed write of the temp and reset the timer
       writeTemp();
       previousMillis = millis();
  }
}
