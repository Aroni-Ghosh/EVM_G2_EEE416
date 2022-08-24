

#ifdef __cplusplus
extern "C" {
#endif
uint8_t temprature_sens_read();
#ifdef __cplusplus
}
#endif
uint8_t temprature_sens_read();
#include <WiFi.h>
#include <ThingSpeak.h>
#include <HTTPClient.h>

unsigned long myChannelNumber = 1834845;
String apiKey = "F927ZLTQGES0AEEG";                  //  Enter your Write API key from ThingSpeak
const char* ssid =  " ";                                    // replace with your wifi ssid and wpa2 key
const char* pass =  " ";
const char* server = "api.thingspeak.com";

String serverName = "https://api.thingspeak.com/update?api_key=F927ZLTQGES0AEEG";
WiFiClient client;


void setup()
{
  Serial.begin(115200);
  delay(1000);
  // WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

}



void loop()
{

  int h = 0;
  float t = 0;

  h = hallRead();
  t = ((temprature_sens_read() - 32) / 1.8);            //changing temperature parameter to celsius
  if (client.connect(server, 80))                                //   "184.106.153.149" or api.thingspeak.com
  {

    String postStr = apiKey;
    postStr += "&field1=";
    postStr += String(h);
    postStr += "&field2=";
    postStr += String(t);
    postStr += "\r\n\r\n";
//
//    client.println("POST /update HTTP/1.1\n");
//    client.println("Host: api.thingspeak.com\n");
//    client.println("Connection: close\n");
//    client.println("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
//    client.println("Content-Type: application/x-www-form-urlencoded\n");
//    client.println("Content-Length: ");
//    client.println(postStr.length());
//    client.println("\n\n");
//    client.println(postStr);

    //    Serial.println("Hall: ");
    //    Serial.println(h);
    //    // client.println(h);
    //    Serial.println("Temperature:");
    //    Serial.println(t);
    //    Serial.println(" C");
    //    Serial.println("%. Send to Thingspeak.");

    HTTPClient http;
    
    String url = serverName + "&field1=" + t + "&field2=" + h ;
      
    http.begin(url.c_str());
   // http.begin(server);
//    String DataSent = "api_key=" + apiKey + "&field1=" + String(t) + "&field2=" + String(h);
//    int Response = http.POST(DataSent);
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    } else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }

    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.print(" degrees Celcius, Hall: ");
    Serial.print(h);
    Serial.println("%. Send to Thingspeak.");
    http.end();
  }
  client.stop();
  Serial.println("Waiting...");
  delay(10000);
}
