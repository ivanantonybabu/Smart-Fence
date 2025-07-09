#include <Wire.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED Display Setup
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define SDA_OLED      D2   // I2C SDA
#define SCL_OLED      D1   // I2C SCL
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// RFID RC522 Setup
#define SS_PIN    D4  
#define RST_PIN   D3  
MFRC522 rfid(SS_PIN, RST_PIN);

// Speaker Setup
#define SPEAKER_PIN D8  

// Track current class
bool classOngoing = false;
String activeTag = "";
String currentClass = "";

// Super Mario Notes & Durations
int melody[] = {660, 660, 0, 660, 0, 510, 660, 0, 770, 0, 380};
int duration[] = {100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100};

void setup() {
    Serial.begin(115200);
    
    // Initialize I2C
    Wire.begin(SDA_OLED, SCL_OLED);
    delay(100);  

    // Initialize OLED
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  
        Serial.println(F("SSD1306 OLED failed! Check wiring."));
        while (true);
    }

    Serial.println("OLED initialized successfully.");
    display.clearDisplay();
    display.display();
    
    // Initialize RFID
    SPI.begin();
    rfid.PCD_Init();
    Serial.println("RFID Ready...");

    // Initialize Speaker
    pinMode(SPEAKER_PIN, OUTPUT);
}

void loop() {
    if (!classOngoing) {
        showTapMessage();  // Blink "Tap Pls" message when idle
    }

    if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
        String tagUID = "";
        for (byte i = 0; i < rfid.uid.size; i++) {
            tagUID += String(rfid.uid.uidByte[i], HEX);
        }
        tagUID.toUpperCase();

        if (classOngoing) {
            // If the same tag is shown again, end the class
            if (tagUID == activeTag) {
                endClass();
            }
        } else {
            // Start a new class
            if (tagUID == "44F85141") {
                startClass("Python Class", tagUID);
            } else if (tagUID == "D0371858") {
                startClass("AIC Class", tagUID);
            } else {
                playPoliceAlarm();
            }
        }

        // Reset RFID module
        rfid.PICC_HaltA();
        rfid.PCD_StopCrypto1();
    }

    if (classOngoing) {
        blinkClassName(currentClass);  // Keep blinking class name
    }
}

void showTapMessage() {
    display.clearDisplay();
    display.setTextSize(2);
    for (int i = 0; i < 5; i++) {
        display.setTextColor(i % 2 == 0 ? SSD1306_WHITE : SSD1306_BLACK);
        display.setCursor(25, 20);
        display.println("Tap Pls");
        display.display();
        delay(500);
    }
}

void startClass(String className, String tagUID) {
    activeTag = tagUID;
    currentClass = className;
    classOngoing = true;
    
    playDoorBell();
}

void blinkClassName(String className) {
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(20, 20);
    display.println(className);
    display.display();
    delay(500);

    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_BLACK);
    display.setCursor(20, 20);
    display.println(className);
    display.display();
    delay(500);
}

void endClass() {
    classOngoing = false;
    activeTag = "";
    currentClass = "";
    display.clearDisplay();
    displayText("Class Over");
    delay(2000);
    
    playSuperMario();  // 🎵 Play the Super Mario theme when class ends
    
    // Reset RFID module properly
    rfid.PCD_Init();
}

void displayText(String text) {
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(10, 20);
    display.println(text);
    display.display();
}

void playDoorBell() {
    tone(SPEAKER_PIN, 1000, 500);
    delay(500);
    tone(SPEAKER_PIN, 1200, 500);
    delay(500);
    noTone(SPEAKER_PIN);
}

void playSuperMario() {
    for (int i = 0; i < sizeof(melody) / sizeof(melody[0]); i++) {
        if (melody[i] == 0) {
            delay(duration[i]);
        } else {
            tone(SPEAKER_PIN, melody[i], duration[i]);
            delay(duration[i] + 50);
        }
    }
    noTone(SPEAKER_PIN);
}

void playPoliceAlarm() {
    tone(SPEAKER_PIN, 200, 1000);
    delay(1000);
    noTone(SPEAKER_PIN);
}
