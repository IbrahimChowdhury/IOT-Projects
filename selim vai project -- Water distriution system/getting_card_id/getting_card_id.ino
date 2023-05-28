#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
 
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();

}
void loop() {
  // Check if a card is present
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    // Read the card's UID
    byte cardID[4];
    for (byte i = 0; i < 4; i++) {
      cardID[i] = mfrc522.uid.uidByte[i];
    }

    // Print the byte values of the card ID
    Serial.print("Card ID: {");
    for (byte i = 0; i < 4; i++) {
      Serial.print("0x");
      if (cardID[i] < 0x10) {
        Serial.print("0");
      }
      Serial.print(cardID[i], HEX);
      if (i < 3) {
        Serial.print(", ");
      }
    }
    Serial.println("}");

    // Halt PICC and stop encryption process
    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
  }
}
