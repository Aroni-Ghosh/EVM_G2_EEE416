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
#define RXp2 16
#define TXp2 17
#include <stdio.h>
#include <ctype.h>
int first=1;
unsigned long myChannelNumber = 1843139;
String apiKey = "F2T7H0GSKT0OVAXG";                  //  Enter your Write API key from ThingSpeak
const char* ssid =  " ";                                    // replace with your wifi ssid and wpa2 key
const char* pass =  " ";
const char* server = "api.thingspeak.com";

String serverName = "https://api.thingspeak.com/update?api_key=F2T7H0GSKT0OVAXG";
WiFiClient client;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXp2, TXp2);


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


void loop() {

  //Serial.println(Serial2.readString());
  String str = Serial2.readString();
  char *p;
  str.toCharArray(p, str.length()+1);
  
        int number_of_candidate = 3;
        int int_arr[number_of_candidate];
        int i = 0;
        while (*p) {
            if (isdigit(*p)) {
                int_arr[i] = strtol(p, &p, 10);;
                i++;
            } else {
                p++;
            }
        }
        
        for (i=0; i<number_of_candidate; i++){
            printf("%d\n", int_arr[i]);
        }  



  if (client.connect(server, 80))                                //   "184.106.153.149" or api.thingspeak.com
  {

    //    String postStr = apiKey;
    //    postStr += "&field1=";
    //    postStr += String(int_arr[0]);
    //    postStr += "&field2=";
    //    postStr += String(int_arr[1]);
    //    postStr += "&field3=";
    //    postStr += String(int_arr[2]);
    //    postStr += "\r\n\r\n";

    HTTPClient http;

    String url = serverName + "&field1=" + int_arr[0] + "&field2=" + int_arr[1] + "&field3=" + int_arr[2] ;
    //Serial.println(url);

    http.begin(url.c_str());
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    } else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }

    Serial.print("Can1: ");
    Serial.print(int_arr[0]);
    Serial.print(" Can2: ");
    Serial.print(int_arr[1]);
    Serial.print(" Can3: ");
    Serial.print(int_arr[2]);
    Serial.println("\t Send to Thingspeak.");
    http.end();
  }
  client.stop();
  Serial.println("Waiting...");
  delay(10000);


}
