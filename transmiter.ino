

#include <OneWire.h>


#include <ESP8266WiFi.h>

#include <WiFiUdp.h>



const char* ssid     = "Greenhouse";
const char* password = "greenhouse";



// UDP variables
unsigned int localPort = 8266;
WiFiUDP UDP;
boolean udpConnected = false;
unsigned int ServerPort = 6000;
IPAddress IP_REMOTE(192, 168, 4, 1);
IPAddress ipClient(192, 168, 4, 10);
IPAddress Subnet(255, 255, 255, 0);



OneWire ds1(14);
OneWire ds2(12);
OneWire ds3(13);

void setup() {
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  //Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  WiFi.mode(WIFI_STA); // para que solo sea STA y no genere la IP 192.168.4.1
  WiFi.config(ipClient, IP_REMOTE, Subnet);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  // connect to UDP – returns true if successful or false if not


Serial.println("");
Serial.println("Connecting to UDP");

if(UDP.begin(localPort) == 1){
Serial.println("Connection successful");

}
else{
Serial.println("Connection failed");
}

yield();  

}

void loop() {
  
char valueTemp[7];


byte data1[2];
ds1.reset(); 
ds1.write(0xCC);
ds1.write(0x44);
delay(750);
ds1.reset();
ds1.write(0xCC);
ds1.write(0xBE);
data1[0] = ds1.read(); 
data1[1] = ds1.read();
int Temp1 = (data1[1]<< 8)+data1[0];
//valueTemp[0] = Temp1>>4;
String str1;
str1=String(Temp1>>4);
Serial.println(Temp1>>4);


byte data2[2];
ds2.reset(); 
ds2.write(0xCC);
ds2.write(0x44);
delay(750);
ds2.reset();
ds2.write(0xCC);
ds2.write(0xBE);
data2[0] = ds2.read(); 
data2[1] = ds2.read();
int Temp2 = (data2[1]<< 8)+data2[0];
//valueTemp[1] = Temp2>>4;
String str2;
str2=String(Temp2>>4);
Serial.println(Temp2>>4);


byte data3[2];
ds3.reset(); 
ds3.write(0xCC);
ds3.write(0x44);
delay(750);
ds3.reset();
ds3.write(0xCC);
ds3.write(0xBE);
data3[0] = ds3.read(); 
data3[1] = ds3.read();
int Temp3 = (data3[1]<< 8)+data3[0];
//int temp3 = Temp3>>4;
String str3;
str3=String(Temp3>>4);
Serial.println(Temp3>>4);
Serial.println(str3);


yield();


String stringOne =  String( str1 + str2 + str3 );

Serial.println(stringOne);

stringOne.toCharArray(valueTemp,7); 




// send UDP to server

UDP.beginPacket(IP_REMOTE, ServerPort);
UDP.write(valueTemp);
UDP.endPacket();

Serial.println("Temp sended"); 



}
