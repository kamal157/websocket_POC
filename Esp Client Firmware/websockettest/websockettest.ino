/*

Download  WebSocketClient lib from https://github.com/brandenhall/Arduino-Websocket
*/


#include <ESP8266WiFi.h>
#include <WebSocketClient.h>
#define myPin D2

const char* ssid     = "SSID";
const char* password = "PASSWORD HERE";
char path[] = "/node";
char host[] = "<SERVER IP>:8080";
  
WebSocketClient webSocketClient;

// Use WiFiClient class to create TCP connections
WiFiClient client;

void setup() {
  Serial.begin(115200);
  
  delay(10);
  pinMode(myPin, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid,password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  delay(5000);
  

  // Connect to the websocket server
  if (client.connect("<SERVER IP>", 8080)) {
    Serial.println("Connected");
  } else {
    Serial.println("Connection failed.");
  }

  // Handshake with the server
  webSocketClient.path = path;
  webSocketClient.host = host;
  if (webSocketClient.handshake(client)) {
    delay(200);
     Serial.println("handshake success");
  } else {
    delay(200);
    Serial.println("handshake failed.");
  }

}


void loop() {
  String data;

  if (client.connected()) {
    
    webSocketClient.getData(data);
    if (data.length() > 0) {
      
      int ind1 = data.indexOf('=');  //finds location of first ,
      data = data.substring(ind1+1, data.length());   //captures first data String
      Serial.print("Received data: ");
     
      char charBuf[data.length()] ;
      data.toCharArray(charBuf,data.length()+1); 
      
      int bri = atoi(charBuf);
      bri%=1024;
      
      analogWrite(myPin,  bri); 
      Serial.println(bri);
    }
    
   
    //webSocketClient.sendData(data);
    
  } else {
    Serial.println("Client disconnected.");
     delay(1000);
  }

  
  // wait to fully let the client disconnect
 
  //Serial.println("is con"+client.connected());
  
}
