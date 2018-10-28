
#include "SoftwareSerial.h"

String ssid ="WIFI_NAME";
String password="WIFI_PASSWORD";

SoftwareSerial esp(3, 2);// RX, TX

String server = "hostaddress"; //Your Host 
String uri = "/GET_LIGHT_STATUS"; // Your URI

int RED_BULB=5; 
int YELLOW_BULB=6;

void setup() {
  pinMode(RED_BULB, OUTPUT);
  pinMode(YELLOW_BULB, OUTPUT);
  
  digitalWrite(RED_BULB, HIGH);
  digitalWrite(YELLOW_BULB, HIGH);
  
  esp.begin(9600);  
  Serial.begin(9600);
  connectWifi();
  httpget();
  delay(1000);

}

void connectWifi() {
    String cmd = "AT+CWJAP=\"" +ssid+"\",\"" + password + "\"";
    esp.println(cmd);
    delay(4000);
    if(esp.find("OK")) {
        Serial.println("Connected!");
    }
    else {
        Serial.println("Cannot connect to wifi ! Connecting again..."); 
    }
    connectWifi();
}
    



/////////////////////////////GET METHOD///////////////////////////////
void httpget() {
    esp.println("AT+CIPSTART=\"TCP\",\"" + server + "\",80");//start a TCP connection.
    if( esp.find("OK")) {
        Serial.println("TCP connection ready");
    } delay(1000);
    String getRequest =
        "GET " + uri + " HTTP/1.0\r\n" +
        "Host: " + server + "\r\n" +
        "Accept: *" + "/" + "*\r\n" +
        "Content-Type: application/json\r\n" +
       "\r\n";
    String sendCmd = "AT+CIPSEND=";
    esp.print(sendCmd);
    esp.println(getRequest.length() );
    delay(500);

    if(esp.find(">")) { 
        Serial.println("Sending.."); 
        esp.print(getRequest);
        if( esp.find("SEND OK")) { 
            Serial.println("Packet sent");
            while (esp.available()) {
                String response = esp.readString();
                int RED_BULB_ON = response.indexOf("RED_BULB>TRUE")>0?1:0;
                int YELLOW_BULB_ON = response.indexOf("YELLOW_BULB>TRUE")>0?1:0;
                if(RED_BULB_ON==1)
                {
                    digitalWrite(RED_BULB, LOW);
                }
                else
                {
                    digitalWrite(RED_BULB, HIGH);
                }
                if(YELLOW_BULB_ON==1)
                {
                    digitalWrite(YELLOW_BULB, LOW);
                }
                else
                {
                    digitalWrite(YELLOW_BULB, HIGH);
                }
            }
            esp.println("AT+CIPCLOSE");
        }
    }
}

void loop() {
  httpget();
}

