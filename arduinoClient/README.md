# arduinoClient

This arduino program will control the ESP8266 for connection through WiFi.

It will create a TCP connection to the server and send HTTP GET requests to receive the user specified status of our 2 light bulbs.

The server will send back the status in JSON format which the ESP8266 gives back to the arduino. The arduino will then accordingly control the relay to switch ON/OFF the lights.

