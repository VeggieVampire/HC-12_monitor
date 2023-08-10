
#include <SoftwareSerial.h> //HC12 needs this for RX and TX

SoftwareSerial HC12(4, 3); //RX, TX


int setATCommandPin = 5; //digital pin 5
String input; // Declare the 'input' variable at the beginning of the function
String deviceName = "myoldname"; // Default device name
String currentDeviceName;
String AtCommand;
String Status;

void setup() {
  Serial.begin(9600);
  pinMode(setATCommandPin, OUTPUT);
  digitalWrite(setATCommandPin, HIGH); // Set HC-12 into Standard mode by default


  Serial.println("Device Started"); // Print information for the user
  // Simulate input data for testing substring extraction
  //Serial.println("config " + deviceName + " AT");
  HC12.begin(9600);
  //HC12.println("config " + deviceName + " AT");
  
}

void loop() {
  if (digitalRead(setATCommandPin) == HIGH) { // (Standard mode)
    if ((Serial.available() > 0) || (HC12.available() > 0)) { // Read from HC-12 and send to serial monitor
    //if (Serial.available() > 0) { // Read from serial monitor
      //String input = Serial.readString(); // Get text from serial monitor
      input = HC12.readString(); // Get text from HC12 device
      Serial.println(input); // Print to Serial

      // Check if the received data contains the word "check"
      if (input.indexOf("check") >= 0 && input.indexOf(deviceName) >= 0) {
     // if (input.indexOf("check") >= 0) {
        digitalWrite(setATCommandPin, LOW);
        delay(100); // Wait for a short duration
        HC12.println("AT+RX"); // Send "AT+RX" command to the HC-12 Device
        delay(400); // Wait for a short duration
        String Status;
       // Serial.write(HC12.read()); // Read data from HC-12 and send it to the Serial monitor
        Status = HC12.readString(); // Store the data read from HC-12 in the 'Status' variable
        digitalWrite(setATCommandPin, HIGH);// Set HC-12 into Standerd mode
        delay(400); // Wait for a short duration
        HC12.println(deviceName + " Status: ");
        HC12.println(Status);
        Serial.println(deviceName + " Status: ");
        Serial.println(Status);
        

      }

      // Check if the received data contains the word "config" and the deviceName
      if (input.indexOf("config") >= 0 && input.indexOf(deviceName) >= 0) {
        // Set HC-12 into AT Command mode
        digitalWrite(setATCommandPin, LOW);
        Serial.println(deviceName + " Entered in HC-12 AT Command Mode:");

        // Extract the new name for the device from the received data
        int spaceAfterConfig = input.indexOf("config") + 7; // Length of "config "
        int spaceAfterName = input.indexOf(" ", spaceAfterConfig);

        if (spaceAfterName >= 0) { // Extract the strings individually
              // Extract the string currentDeviceName
              currentDeviceName = input.substring(spaceAfterConfig, spaceAfterName);
              Serial.print("currentDeviceName: ");
              Serial.println(currentDeviceName);
    
              // Extract AtCommand string
              AtCommand = input.substring(spaceAfterName + 1, input.indexOf(" ", spaceAfterName + 1));
    
    
              Serial.print("AtCommand: ");
              Serial.println(AtCommand);
              
              Serial.println(currentDeviceName + " " + AtCommand);
    
              HC12.println(AtCommand); // Send "AT" command to the HC-12 Device
              delay(400); // Wait for a short duration
              String Status;
             // Serial.write(HC12.read()); // Read data from HC-12 and send it to the Serial monitor
              Status = HC12.readString(); // Store the data read from HC-12 in the 'Status' variable
              digitalWrite(setATCommandPin, HIGH);// Set HC-12 into Standerd mode
              delay(400); // Wait for a short duration
              HC12.println(deviceName + " Status: ");
              HC12.println(Status);
              Serial.println(deviceName + " Status: ");
              Serial.println(Status);
          }
      }
      // Check if the received data contains "change" and deviceName
      if (input.indexOf("change") >= 0 && input.indexOf(deviceName) >= 0) {
            Serial.println("Received 'change' and " + deviceName + " in the data.");
 
    
       // Extract the new name for the device from the received data
          int changeIndex = input.indexOf("change");
          int spaceAfterChange = input.indexOf(" ", changeIndex);
          
              if (spaceAfterChange >= 0) {
                // Extract the strings individually
                String changeString = input.substring(changeIndex, spaceAfterChange);
                String currentDeviceName = input.substring(spaceAfterChange + 1, input.indexOf(" ", spaceAfterChange + 1));
                String newDeviceName = input.substring(input.lastIndexOf(" ") + 1);
          
                // Trim any leading or trailing whitespaces
                changeString.trim();
                currentDeviceName.trim();
                newDeviceName.trim();
          
                Serial.println("Change command: " + changeString);
                Serial.println("Current device name: " + currentDeviceName);
                Serial.println("New device name: " + newDeviceName);
                deviceName = newDeviceName;
                Serial.println("Should change to the new deviceName: " + newDeviceName);
                Serial.println("Device name changed to: " + deviceName);
                HC12.println("Device name changed to: " + deviceName);
              }
    
    
    
          }

      

      
    }
    //Print Data to HC-12 and serial
    Serial.println(deviceName + " Status: " );
    HC12.println(deviceName + " Status: " );
    delay(2000); // Wait for a short duration
    
  } else if (digitalRead(setATCommandPin) == LOW) { // AT Command mode is active
    // Serial.println(changeString + " " + currentDeviceName + " " + AtCommand);
  }
}
