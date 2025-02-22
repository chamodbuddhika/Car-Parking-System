#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10    // RFID SS (SDA) Pin
#define RST_PIN 9    // RFID RST Pin

MFRC522 rfid(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;

// LCD Initialization (20x4)
LiquidCrystal_I2C lcd(0x27, 20, 4);

Servo myservo;

// IR Sensors for Slot Detection & Exit
#define ir_back 4
#define ir_enter 2  

#define ir_car1 5
#define ir_car2 6
#define ir_car3 7
#define ir_car4 8

int S1 = 0, S2 = 0, S3 = 0, S4 = 0;
int flag1 = 0, flag2 = 0;  
int slot = 4;  // Available slots

// Function Prototypes (Declare before use)
void Read_Sensor();
void openGate();
void closeGate();

void setup() {
    Serial.begin(9600);

    SPI.begin();     
    rfid.PCD_Init();  

    pinMode(ir_car1, INPUT);
    pinMode(ir_car2, INPUT);
    pinMode(ir_car3, INPUT);
    pinMode(ir_car4, INPUT);
    pinMode(ir_back, INPUT);
    pinMode(ir_enter, INPUT);

    myservo.attach(3);
    myservo.write(90);

    lcd.begin();
    lcd.backlight();
    lcd.setCursor(0, 1);
    lcd.print("  Car Parking ");
    lcd.setCursor(0, 2);
    lcd.print("     System   ");
    delay(2000);
    lcd.clear();   

    Read_Sensor();
    int total = S1 + S2 + S3 + S4;
    slot = slot - total;
}

void loop() {
    Read_Sensor();

    lcd.setCursor(0, 0);
    lcd.print(" Slots: "); 
    lcd.print(slot);
    lcd.print("    ");  

    lcd.setCursor(0, 1);
    lcd.print(S1 ? "S1:Fill " : "S1:Empty");
    lcd.setCursor(10, 1);
    lcd.print(S2 ? "S2:Fill " : "S2:Empty");

    lcd.setCursor(0, 2);
    lcd.print(S3 ? "S3:Fill " : "S3:Empty");
    lcd.setCursor(10, 2);
    lcd.print(S4 ? "S4:Fill " : "S4:Empty");

    // RFID Entry Access
    if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
        Serial.println("Card Detected!");
        
        if (slot > 0) {
            flag1 = 1;
            if (flag2 == 0) {
                openGate();
                slot--;  // Reduce available slots
            }
        } else {
            lcd.setCursor(0, 0);
            lcd.print(" Parking Full ");
            delay(1500);
        }

        rfid.PICC_HaltA();
        rfid.PCD_StopCrypto1();
    }

    // Exit Logic
    if (digitalRead(ir_back) == LOW && flag2 == 0) {
        flag2 = 1;
        if (flag1 == 0) {
            openGate();
            slot++; // Open gate for exit
        }
    }

    // Car Fully Entered, Close Gate
    if (digitalRead(ir_back) == LOW && flag2 == 0) {
        flag2 = 1;
        if (flag1 == 0) {
            closeGate();
            // Increase available slots
        }
    }

    // Reset Flags after Entry & Exit
    if (flag1 == 1 && flag2 == 1) {
        delay(1000);
        closeGate();
        flag1 = 0;
        flag2 = 0;
    }

    delay(1);
}

// Read Slot Sensors
void Read_Sensor() {
    S1 = digitalRead(ir_car1) == LOW ? 1 : 0;
    S2 = digitalRead(ir_car2) == LOW ? 1 : 0;
    S3 = digitalRead(ir_car3) == LOW ? 1 : 0;
    S4 = digitalRead(ir_car4) == LOW ? 1 : 0;
}

// Open the gate
void openGate() {
    myservo.write(180);
    lcd.setCursor(0, 0);
    lcd.print(" Gate Opening... ");
    delay(2000);
}

// Close the gate
void closeGate() {
    myservo.write(90);
    lcd.setCursor(0, 0);
    lcd.print(" Gate Closing... ");
    delay(2000);
}
