#include <WiFi.h>
#include <FirebaseESP32.h>
#define network "raspbbery"
#define pass "123456789"

#define DATABASE_URL "iotproject-2cabc-default-rtdb.asia-southeast1.firebasedatabase.app/"
#define API_KEY "AIzaSyA2gOYUlsagR4xFxxXTYS642oRkUK-6hU8"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;


int firestatus =0;
int pin=13;

void connectwifi(){
  WiFi.begin(network,pass);
  Serial.print("connecting to wifi");

  while(WiFi.status() != WL_CONNECTED ){
    Serial.print(".");
    delay(100);
  }

    if(WiFi.status() != WL_CONNECTED){
      Serial.print("failed");
      delay(100);
    }
    else{
      Serial.print("connected");
      Serial.println(WiFi.localIP());

    }
  }
void setupfirebase(){
  config.api_key=API_KEY;
  config.database_url=DATABASE_URL;
  Firebase.reconnectWiFi(true);
  Firebase.begin(&config,&auth);
  if(Firebase.ready()){
    Serial.println("fire base is ready");

  }
  else{
    Serial.println("failed");
  }


}




void setup() {
  Serial.begin(9600);
  connectwifi();
  setupfirebase();
  pinMode(pin,OUTPUT);
}
void loop(){
  if (Firebase.ready()) {
    if (Firebase.getInt(fbdo, "/led status")) {  // Correct path format
      if (fbdo.dataType() == "int") {
        firestatus = fbdo.intData();
        if (firestatus == 1) {
          digitalWrite(pin, HIGH);
        } else {
          digitalWrite(pin, LOW);
        }
        Serial.println(firestatus);
      }
    } else {
      Serial.println("Failed to get data from Firebase");
      Serial.println("REASON: " + fbdo.errorReason());
    }
  }
  delay(1000);  // Add a delay to avoid excessive requests
}
