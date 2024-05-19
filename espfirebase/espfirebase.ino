#include <WiFi.h>
#include <ESP32Firebase.h>

#define network "realme 6i"
#define pass "12345678"
#define url_ref "https://iotproject-2cabc-default-rtdb.asia-southeast1.firebasedatabase.app/"

Firebase firebase(url_ref);

int trig=5;
int echo=18;
int dis,x;





void connectWiFi(){
  WiFi.begin(network,pass);
  Serial.print("connecting to WiFi");

  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(100);

    if(WiFi.status() != WL_CONNECTED){
      Serial.print("failed");
      
    }
    else
    {
      Serial.print("connected");
      Serial.println(WiFi.localIP());
    }
  }
}


void setup() {
  Serial.begin(9600);
  connectWiFi();
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);


 

}

void loop() {
  /*digitalWrite(trig,HIGH);
   delayMicroseconds(2);
  digitalWrite(trig,LOW);
  delayMicroseconds(10);
  digitalWrite(trig,HIGH);
  x=pulseIn(echo,HIGH);
  dis=x*0.34/2;
  Serial.println(dis);*/

  x=analogRead(echo);
  Serial.println(x);

  


  firebase.setFloat("Example/distancecm", x);
  delay(100);
 
 
 

}
