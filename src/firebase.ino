#include <Arduino.h>
#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

// Firebase configuration
#define FIREBASE_AUTH "AIzaSyC1qJDOtTrNJvjfCoJBZe4X1_BLeZ0Qxl8"
#define FIREBASE_DB_URL "https://esp32-96d7e-default-rtdb.europe-west1.firebasedatabase.app/"

// WiFi configuration

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
static int count = 0;
static int switchState = 0;
bool signupOK = false;
#define LED_PIN 18
#define SWITCH_PIN 5

void setup()
{
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(SWITCH_PIN, INPUT_PULLUP);
  digitalWrite(LED_PIN, LOW);

  // Connect to WiFi
  WiFi.begin("Wokwi-GUEST", "", 6);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }
  Serial.println("WiFi connected!");

  /* Assign the API key and RTDB URL */
  config.api_key = FIREBASE_AUTH;
  config.database_url = FIREBASE_DB_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", ""))
  {
    Serial.println("Firebase sign-up successful!");
    signupOK = true;
  }
  else
  {
    Serial.printf("Firebase sign-up failed: %s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for token generation task */
  config.token_status_callback = tokenStatusCallback;

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop()
{
  if (Firebase.ready() && signupOK && millis() - sendDataPrevMillis > 1000 || sendDataPrevMillis == 01 )
  {
    if (Firebase.RTDB.getInt(&fbdo, "test/int", &count))
    {
      Serial.print("Read count from Firebase: ");
      Serial.println(count);
    }
    if (Firebase.RTDB.setInt(&fbdo, "test/switch", digitalRead(SWITCH_PIN)))
    {
      Serial.print("Wrote switch state to Firebase: ");
      Serial.println(digitalRead(SWITCH_PIN));
    }

    if (count == 0)
    {
      digitalWrite(LED_PIN, LOW);
      Serial.println("LED turned off (LOW)");
    }
    else
    {
      digitalWrite(LED_PIN, HIGH);
      Serial.println("LED turned on (HIGH)");
    }

    sendDataPrevMillis = millis();
  }
}
 