#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
int ledPin=4;
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance

unsigned long disableTime = 0;      // Stores the time until the card is disabled
unsigned long disableTime2 = 0;      // Stores the time until the card is disabled

unsigned long disableDuration = 20000;  // Time duration (in milliseconds) to disable the card

// Define the IDs of the cards to allow/deny access
byte allowedCardID[] = {0x49, 0x3E, 0xEA, 0x6E};  // Example allowed card ID
byte allowedCardID2[] = {0xF0, 0xE2, 0x25, 0x19};  // Example allowed card ID

byte deniedCardID[] = {0xEE, 0xFF, 0x11, 0x22};   // Example denied card ID

void setup() {
  Serial.begin(9600);   // Initialize serial communication
  SPI.begin();          // Initialize SPI bus
  mfrc522.PCD_Init();   // Initialize MFRC522


  pinMode(ledPin,OUTPUT);

  // Print a message to indicate the setup is complete
  Serial.println("RFID Reader initialized. Bring an RFID card closer to the reader.");
}
void loop() {
  // Check if a card is present
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    // Read the card's UID
    byte cardID[4];
    for (byte i = 0; i < 4; i++) {
      cardID[i] = mfrc522.uid.uidByte[i];
    }

    // Compare the card's UID with the allowedCardID
    if (memcmp(cardID, allowedCardID, sizeof(cardID)) == 0) {
      // Check if the card should be disabled or not
      if (millis() > disableTime) {
        // Access granted
        Serial.println("Access granted!");
        disableTime = millis() + disableDuration;  // Disable the card for a certain time
        digitalWrite(ledPin,HIGH);
        delay(2000);
        digitalWrite(ledPin,LOW);
      } else {
        // Card disabled
        Serial.println("Card disabled. Please wait.");
      }
    } 
    if (memcmp(cardID, allowedCardID2, sizeof(cardID)) == 0) {
      // Check if the card should be disabled or not
      if (millis() > disableTime2) {
        // Access granted
        Serial.println("Access granted!");
        disableTime2 = millis() + disableDuration;  // Disable the card for a certain time
        
        digitalWrite(ledPin,HIGH);
        delay(2000);
        digitalWrite(ledPin,LOW);
      } else {
        // Card disabled
        Serial.println("Card disabled. Please wait.");
      }
    } 
   

    // Halt PICC and stop encryption process
    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
  }
}
