
#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
PN532_I2C pn532i2c(Wire);
PN532 nfc(pn532i2c);

void setup(void) {
  Serial.begin(2400);
  Serial.println("Hello!");

  nfc.begin();
  nfc.SAMConfig();
}


bool validateTag(uint8_t uid[], uint8_t uidLength, uint8_t data[]) {
  uint8_t success;
  if (uidLength == 4)
  {
    uint8_t keya[6] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF }; // REPLACE WITH YOUR ENCRYPTION KEY
    if (nfc.mifareclassic_AuthenticateBlock(uid, uidLength, 4, 0, keya))
    {
      if (nfc.mifareclassic_ReadDataBlock(4, data))
      {
        return true;
      }
    }
  }
  return false;
}

void loop(void) {
  uint8_t success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };
  uint8_t uidLength;
  uint8_t data[16];

  if (nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength)) {
    if (validateTag(uid, uidLength, data))  {
      Serial.print("VALID-");
      for (int i = 0; i < 15; i++) {
        Serial.print(data[i], HEX);
      }
      Serial.println(data[15], HEX);

    } else {
      Serial.println("INVALID");
    }
  } else {
    Serial.println("NONE");
  }
  delay(250);
}
