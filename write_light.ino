void writeLight (){
  
  //Write the calculated light value out to the serial port for transmission
  //Written out in JSON format
  Serial.print("{\"Sensor_ID\":6,\"Sensor_Value\":");
  Serial.print(lightsensorVal);
  
  Serial.print(",\"Light\":\"");
  Serial.print(lightValue);
 
  Serial.println("\"}");
}
