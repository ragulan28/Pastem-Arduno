#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "pastem-3f318.firebaseio.com"
#define FIREBASE_AUTH "y1hp8pwUIdJMPC2McFGqcfGmLwy8UFarY3WsWSz7"
#define WIFI_SSID "Ragulg"
#define WIFI_PASSWORD "RAGUL@942412649v"

bool opened;
bool lastVal;
void setup() {
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D6, OUTPUT);

  digitalWrite(D1, HIGH);
  Serial.begin(115200);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  digitalWrite(D1, LOW);
}


void loop() {

  opened = Firebase.getBool("Cabinet/CabinetId/lockers/lockerId/IsOpen");
  if (lastVal != opened) {
    lastVal = opened;
    if (opened) {
      digitalWrite(D2, HIGH);
      digitalWrite(D6, HIGH);

    } else {
      digitalWrite(D2, LOW);
      digitalWrite(D6 , LOW);
    }
    Serial.println(opened);
  }
}
