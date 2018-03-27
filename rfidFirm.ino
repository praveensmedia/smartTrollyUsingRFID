//code written for Arduino-UNO
#include <SPI.h>                     //to initialize spi communication
#include <MFRC522.h>                 //to initialize the rfid reader and writer
#include <LiquidCrystal.h>           //lib file for display
LiquidCrystal lcd(8, 9, 5, 6, 7, 10);//pins to connect display
#define RST_PIN         A3           // Configurable, see typical pin layout above
#define SS_PIN          A2           // Configurable, see typical pin layout above
#define BUZZ_PIN        2
#define BTN_PIN         A4
String keyy ;
char   ky; 
int total=0;
boolean lp;
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance

//*****************************************************************************************//
void setup() {
  Serial.begin(9600);                                           // Initialize serial communications with the PC
  SPI.begin();                                                  // Init SPI bus
  lcd.begin(16, 2);
  pinMode(BUZZ_PIN, OUTPUT);
  pinMode(BTN_PIN,   INPUT);
  digitalWrite(BUZZ_PIN,HIGH);
  mfrc522.PCD_Init();                                              // Init MFRC522 card
  lcd.print("  SMART TROLLY");
  lcd.setCursor(0,1);
  lcd.print("     SYSTEM");

}

//*****************************************************************************************//
void loop() {

  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;

  //some variables we need
  byte block;
  byte len;
  MFRC522::StatusCode status;

  //-------------------------------------------
  if(lp)
  { 
  lcd.clear();
  lcd.print("Place your item:");
  lcd.setCursor(0,1);
  lcd.print("Total:   Rs.");
  lcd.setCursor(12,1);
  lcd.print(total);
  lp=false;
  }
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  lcd.clear();
  lcd.print("  Item Detected");
  digitalWrite(BUZZ_PIN,LOW);
  delay(100);
  digitalWrite(BUZZ_PIN,HIGH);
  lp=true;
  lcd.setCursor(0,1);
  byte buffer1[18];

  block = 4;
  len = 18;

  //------------------------------------------- GET FIRST NAME
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 4, &key, &(mfrc522.uid)); //line 834 of MFRC522.cpp file
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Authentication failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  status = mfrc522.MIFARE_Read(block, buffer1, &len);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Reading failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

 
  for (uint8_t i = 0; i < 16; i++)
  {
    if (buffer1[i] != 32)
    {
    if (i==3) ky = char(buffer1[3]);
    }
  }
  if(ky=='1')
  {
    lcd.print("DOVE SOAP  Rs.45");
    if(digitalRead(BTN_PIN))total=total+45;
    else if(total<45)
    {
    total=0;
    lcd.setCursor(0,1);
    lcd.print("Wrong Item-ERROR");
    }
    else total=total-45;
  }
  if(ky=='2')
  {
    lcd.print("ATTA 5kg  Rs.350");
    if(digitalRead(BTN_PIN))total=total+350;
    else if(total<350)
    {
      total=0;
      lcd.setCursor(0,1);
      lcd.print("Wrong Item-ERROR");
    }
    else total=total-350;
  }
  if(ky=='3')
  {
    lcd.print("MAGGI 3pak Rs.50");
    if(digitalRead(BTN_PIN))total=total+50;
    else if(total<50)
    {
      total=0;
      lcd.setCursor(0,1);
      lcd.print("Wrong Item-ERROR");
    }
    else total=total-50;
  }

  delay(1000); //change value if you want to read cards faster
 
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}
//*****************************************************************************************//
