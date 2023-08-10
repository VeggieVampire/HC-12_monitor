#include <SoftwareSerial.h>

SoftwareSerial HC12(4, 3);

const int setATCommandPin = 5;
String deviceName = "myoldname";
String currentDeviceName;
String AtCommand;

void setup() {
  Serial.begin(9600);
  pinMode(setATCommandPin, OUTPUT);
  digitalWrite(setATCommandPin, HIGH);
  HC12.begin(9600);
}

void loop() {
  if (digitalRead(setATCommandPin) == HIGH) {
    if (HC12.available()) {
      String input = HC12.readString();
      Serial.println(input);

      if (input.indexOf("check") >= 0 && input.indexOf(deviceName) >= 0) {
        executeATCommand("AT+RX");
      }

      if (input.indexOf("config") >= 0 && input.indexOf(deviceName) >= 0) {
        int spaceAfterConfig = input.indexOf("config") + 7;
        int spaceAfterName = input.indexOf(" ", spaceAfterConfig);
        if (spaceAfterName >= 0) {
          currentDeviceName = input.substring(spaceAfterConfig, spaceAfterName);
          AtCommand = input.substring(spaceAfterName + 1, input.indexOf(" ", spaceAfterName + 1));
          executeATCommand(AtCommand);
        }
      }

      if (input.indexOf("change") >= 0 && input.indexOf(deviceName) >= 0) {
        int changeIndex = input.indexOf("change");
        int spaceAfterChange = input.indexOf(" ", changeIndex);
        if (spaceAfterChange >= 0) {
          String newDeviceName = input.substring(input.lastIndexOf(" ") + 1);
          newDeviceName.trim();
          deviceName = newDeviceName;
          HC12.println("Device name changed to: " + deviceName);
        }
      }
    }

    Serial.println(deviceName + " Status: ");
    HC12.println(deviceName + " Status: ");
    delay(2000);
  }
}

void executeATCommand(const String &command) {
  digitalWrite(setATCommandPin, LOW);
  delay(100);
  HC12.println(command);
  delay(400);
  String status = HC12.readString();
  digitalWrite(setATCommandPin, HIGH);
  delay(400);
  HC12.println(deviceName + " Status: ");
  HC12.println(status);
  Serial.println(deviceName + " Status: ");
  Serial.println(status);
}
