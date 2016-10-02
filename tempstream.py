#! /usr/bin/env python

import time
from ISStreamer.Streamer import Streamer
 
import serial
import requests
import json
import ConfigParser

configParser = ConfigParser.RawConfigParser()
configFilePath = r'./tempstream.ini'
configParser.read(configFilePath)

accessKey = configParser.get('initialstate.com', 'accesskey')
bucketKey = configParser.get('initialstate.com', 'bucketkey')
print("The access key is %s" % accessKey)
print("The bucket key is %s" % bucketKey)

inputcount = 1
sensor_id = 0
output_yn = "Y"
max_light = 0
min_light = 256
new_value = 0
light_value = 'N'

streamer = Streamer(bucket_name="Stream Example", bucket_key=bucketKey, access_key=accessKey)
 
streamer.log("My Messages", "Waiting for temp")
#print("Started");
ser = serial.Serial('/dev/ttyUSB0', 9600)

#print("Testing the input")
while True:	
	streamer.log("My Messages", "Value Aquired")
	streamer.log("Input Count", inputcount)
	#print("Got a reading.  Input count %d" % inputcount)
	output_yn = 'Y'
	
	#print("Read value")
	sensor_output = ser.readline().strip()
	#print("Read value")
	
	#Discard the first reading from the serial input is it seems to be badly formed	
	#print("Test for the first reading")
	if inputcount > 0:
		#print("First reading to write")
		data = json.loads(sensor_output)
	
		for key, value in data.iteritems():
			if key=="Voltage":
				streamer.log("Voltage", value)
				
			if key=="Temperature":
				streamer.log("Temperature", value)

			#print("Value %s" % value)
			#print("Light Value %s" % light_value)

			if key=="Light":
				streamer.log("Light", value)
				streamer.log("LightMeter", value)
				new_value = int(value)
				light_value = 'Y'
				#print("Value %s" % value)
				#print("New Value %d" % new_value)
				#print("Light Value %s" % light_value)
				#print("Max Light %d" %  max_light)
				#print("Min Light %d" % min_light) 

			if light_value=="Y" and max_light < new_value:
				max_light = new_value
				streamer.log("Max Light", max_light)
				#print("2. max_light %s" % max_light)
				#print("2. New Value %s" % new_value)
				#print("2. Light Value %s" % light_value)
				#print("2. Max Light %s" % max_light)
				#print("2. Min Light %s" %  min_light) 

			if light_value=="Y" and min_light > new_value:
				#print("Min light")
				min_light = new_value
				streamer.log("Min Light", min_light)
				light_value = 'N'
				#print("min_light %s" % min_light)

		streamer.log("My Messages", "Value Posted")

	inputcount = inputcount + 1

streamer.log("My Messages", "Stream Done")
#print("Done")
