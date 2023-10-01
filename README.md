# Firebase with ESP32
===================

This is a simple example of how to use Firebase with virtual ESP32.
Using the Firebase ESP32 library, we can use the Firebase Realtime Database to store and sync data with ESP32.

## Running the example
make sure you have the following installed:
- [PlatformIO IDE](https://platformio.org/platformio-ide)
- [Wokwi Extension](https://marketplace.visualstudio.com/items?itemName=wokwi.wokwi-vscode)

1. Create a Firebase project in the [Firebase Console](https://console.firebase.google.com/).
2. Create a Realtime Database in the [Firebase Console](https://console.firebase.google.com/).
3. Set the rules of the Realtime Database to allow read and write permissions.
4. change the `WIFI_SSID` and `WIFI_PASSWORD` in the `firebase.ino` file.
note: use these credentials only for virtual esp32 
`"Wokwi-GUEST"` , `""`
5. change the `FIREBASE_HOST` and `FIREBASE_AUTH` in the `firebase.ino` file.
6. adjust config file `wokwi.toml` to your needs.
7. run `platformio:buid` in the platformio IDE.
8. run `Wokwi: Select Config file` and select `wokwi.toml` file.
9. run `Wokwi: Start Simulator`.