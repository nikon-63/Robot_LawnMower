#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>


const char* ssid = "TEB_Lawn";  
const char* password = "12345678"; 

ESP8266WebServer server(80);

int IN1 = 0;
int IN2 = 2;
int IN3 = 16;
int IN4 = 5;


bool Leftstatus = LOW;
bool Rightstatus = LOW;
bool Brakestatus = LOW;
bool BrakeButton = LOW;
bool cen = LOW;


const int analogInPin = A0;
int sensorValue = 0;


void setup() {
  Serial.begin(115200);

  //Setting up the Actuators
  pinMode(IN1, OUTPUT); //D3
  pinMode(IN2, OUTPUT); //D4
  pinMode(IN3, OUTPUT); //D0
  pinMode(IN4, OUTPUT); //D1
  pinMode(14, INPUT); //D5 R
  pinMode(12, INPUT); //D6 M
  pinMode(13, INPUT); //D7 L
  pinMode(15, INPUT); //D8 B
  pinMode(4, INPUT); //D2 Brakebutton
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
    
  //Wifi Set-up
  WiFi.softAP(ssid, password);
  IPAddress apip = WiFi.softAPIP();
  delay(100);

  //Sever Comands
  server.on("/", handle_OnConnect);
  server.on("/Lefton", handle_Lefton);
  server.on("/Leftoff", handle_Leftoff);
  server.on("/Righton", handle_Righton);
  server.on("/Rightoff", handle_Rightoff);
  server.on("/Brakeon", handle_Brakeon);
  server.on("/Brakeoff", handle_Brakeoff); 
  server.on("/cen", handle_cen); //Added
  server.on("/cenoff", handle_cenoff); //Added
  server.onNotFound(handle_NotFound);
  server.begin();
  Serial.println("HTTP server started");
}


void loop() {
  server.handleClient();

  //Button Controle on the board
  byte valR = digitalRead(14); //R
  if( valR == HIGH){
    Serial.println("Right");
    handle_Righton();
  }
  byte valM = digitalRead(12); //M
  if( valM == HIGH){
    Serial.println("Mid");
    handle_Rightoff();
  }
  byte valL = digitalRead(13); //L
  if( valL == HIGH){
    Serial.println("Left");
    handle_Lefton();
  }
  byte valB = digitalRead(15); //B
  if( valB == HIGH){
    Serial.println("Brake");
    if( Brakestatus == HIGH){
      handle_Brakeoff();
      delay(500);
    }else{
      handle_Brakeon();
      delay(500);
    }
  }
  //Button on the brake to stop at right place
  byte valBB = digitalRead(4); //BB
  if( valBB == HIGH){
    Serial.println("Button turch");
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    delay(500);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }


  //Pot
  sensorValue = analogRead(analogInPin);
  sensorValue = map(sensorValue, 0, 1023, 0, 180);
  Serial.println(sensorValue);
  delay(200);
}

// When a user connects 
void handle_OnConnect() {
  Leftstatus = LOW;
  Rightstatus = LOW;
  Brakestatus = LOW;
  cen = LOW;
  Serial.println("GPIO7 Status: OFF | GPIO6 Status: OFF");
  server.send(200, "text/html", SendHTML(Leftstatus,Rightstatus,Brakestatus,cen)); 
}

//Turn the wheels left
void handle_Lefton() {
  Leftstatus = HIGH;
  Serial.println("Left ON");
  server.send(200, "text/html", SendHTML(Leftstatus,Rightstatus,Brakestatus,cen)); 
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  delay(100);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}

//Stop turning the wheels
void handle_Leftoff() {
  Leftstatus = LOW;
  Serial.println("Left OFF");
  server.send(200, "text/html", SendHTML(Leftstatus,Rightstatus,Brakestatus,cen)); 
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}

//Turn the wheels right
void handle_Righton() {
  Rightstatus = HIGH;
  Serial.println("Right ON");
  server.send(200, "text/html", SendHTML(Leftstatus,Rightstatus,Brakestatus,cen));
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  delay(100);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
}

//Stop turning the wheels
void handle_Rightoff() {
  Rightstatus = LOW;
  Serial.println("Right OFF");
  server.send(200, "text/html", SendHTML(Leftstatus,Rightstatus,Brakestatus,cen)); 
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}

//Turn the brakes on
void handle_Brakeon() {
  Brakestatus = HIGH;
  Serial.println("Brake ON");
  server.send(200, "text/html", SendHTML(Leftstatus,Rightstatus,Brakestatus,cen)); 
  bool BrakeButton = HIGH;
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  delay(100);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(300);
}

//Turn the brakes off
void handle_Brakeoff() {
  Brakestatus = LOW;
  Serial.println("Brake OFF");
  server.send(200, "text/html", SendHTML(Leftstatus,Rightstatus,Brakestatus,cen)); 
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  delay(100);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}


//Gose to mid 67 - 80
void handle_cen() {
  cen = HIGH;
  Serial.println("MID");
  server.send(200, "text/html", SendHTML(Leftstatus,Rightstatus,Brakestatus,cen)); 
  sensorValue = analogRead(analogInPin); 
  sensorValue = map(sensorValue, 0, 1023, 0, 180);
  if (sensorValue > 80);{
    sensorValue = analogRead(analogInPin); 
    sensorValue = map(sensorValue, 0, 1023, 0, 180);
    while (sensorValue > 80) {
      sensorValue = analogRead(analogInPin); 
      sensorValue = map(sensorValue, 0, 1023, 0, 180);
      Serial.println("Turn left");
      Serial.println(sensorValue);
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      delay(200);
    }
  }

  if (sensorValue < 67);{
    sensorValue = analogRead(analogInPin); 
    sensorValue = map(sensorValue, 0, 1023, 0, 180);
    while (sensorValue < 67) {
      sensorValue = analogRead(analogInPin); 
      sensorValue = map(sensorValue, 0, 1023, 0, 180);
      Serial.println("Turn right");
      Serial.println(sensorValue);
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      delay(200);
    }
  }
  if ((sensorValue >=67) && (sensorValue<=80));{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    Serial.println("hope brake");
    cen = LOW;
    }
}

void handle_cenoff() {
  cen = LOW;
  Serial.println("MID");
  server.send(200, "text/html", SendHTML(Leftstatus,Rightstatus,Brakestatus,cen)); 
  
}


void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}


//HTML Code
String SendHTML(uint8_t led1stat,uint8_t led2stat, uint8_t cen, uint8_t brakestat){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>TEB LawnMower</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr +=".button {display: block;width: 80px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-on {background-color: #1abc9c;}\n";
  ptr +=".button-on:active {background-color: #16a085;}\n";
  ptr +=".button-off {background-color: #34495e;}\n";
  ptr +=".button-off:active {background-color: #2c3e50;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>TEB LawnMower</h1>\n";
  ptr +="<h3>(AP) Mode</h3>\n";
  ptr +="<h4>"+String(sensorValue)+"</h4>\n";
  
   if(led1stat)
  {ptr +="<p>LED1 Status: ON</p><a class=\"button button-off\" href=\"/Leftoff\">OFF</a>\n";}
  else
  {ptr +="<p>LED1 Status: OFF</p><a class=\"button button-on\" href=\"/Lefton\">ON</a>\n";}

  if(led2stat)
  {ptr +="<p>LED2 Status: ON</p><a class=\"button button-off\" href=\"/Rightoff\">OFF</a>\n";}
  else
  {ptr +="<p>LED2 Status: OFF</p><a class=\"button button-on\" href=\"/Righton\">ON</a>\n";}

  if(brakestat)
  {ptr +="<p>LED3 Status: ON</p><a class=\"button button-off\" href=\"/Brakeoff\">OFF</a>\n";}
  else
  {ptr +="<p>LED2 Status: OFF</p><a class=\"button button-on\" href=\"/Brakeon\">ON</a>\n";}

  if(cen)
  {ptr +="<p>LED3 Status: ON</p><a class=\"button button-off\" href=\"/cenoff\">OFF</a>\n";}
  else
  {ptr +="<p>LED2 Status: OFF</p><a class=\"button button-on\" href=\"/cen\">ON</a>\n";}
  
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}