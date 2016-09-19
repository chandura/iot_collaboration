#! /usr/bin/env python

import time
from ISStreamer.Streamer import Streamer
 
import serial
import requests
import json

inputcount = 0
sensor_id = 0
output_yn = "Y"

streamer = Streamer(bucket_name="Stream Example", bucket_key="MFS123", access_key="[place acess key here]")
 
streamer.log("My Messages", "Waiting for temp")
#print("Started");
ser = serial.Serial('/dev/ttyUSB0', 9600)

while True:	
	streamer.log("My Messages", "Value Aquired")
	streamer.log("Input Count", inputcount)
	#print("Got a reading.  Input count %d" % inputcount)
	output_yn = 'Y'
		
	sensor_output = ser.readline().strip()	
	
	#Discard the first reading from the serial input is it seems to be badly formed	
	if inputcount > 0:
		#print("First reading to write")
		data = json.loads(sensor_output)
	
		for key, value in data.iteritems():
			if key=="Voltage":
                                streamer.log("Voltage", value)
				
			if key=="Temperature":
                                streamer.log("Temperature", value)
				streamer.log("My Messages", "Value Posted")

	inputcount = inputcount + 1

streamer.log("My Messages", "Stream Done")
