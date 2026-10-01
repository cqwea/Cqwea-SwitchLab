/*
 * Cqwea SwitchLab
 * Firmware placeholder
 *
 * Hardware:
 * - Seeed Studio XIAO ESP32-S3
 * - 20-key mechanical switch matrix
 * - 128x64 SSD1306 I2C OLED
 *
 * This is a development placeholder.
 * Calculator functionality and final key mapping will be implemented later.
 */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ---------- OLED ----------

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_SDA D9
#define OLED_SCL D10
#define OLED_ADDR 0x3C

Adafruit_SSD1306 display(
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    &Wire,
    -1
);

// ---------- Matrix ----------

// 5 rows × 4 columns = 20 switches

const uint8_t ROWS = 5;
const uint8_t COLS = 4;

const uint8_t rowPins[ROWS] = {
    D0, D1, D2, D3, D4
};

const uint8_t colPins[COLS] = {
    D5, D6, D7, D8
};

void setup() {
    Serial.begin(115200);

    // Matrix setup
    for (uint8_t r = 0; r < ROWS; r++) {
        pinMode(rowPins[r], OUTPUT);
        digitalWrite(rowPins[r], HIGH);
    }

    for (uint8_t c = 0; c < COLS; c++) {
        pinMode(colPins[c], INPUT_PULLUP);
    }

    // OLED setup
    Wire.begin(OLED_SDA, OLED_SCL);

    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
        Serial.println("OLED initialization failed!");
        while (true) {
            delay(1000);
        }
    }

    display.clearDisplay();

    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(2);
    display.setCursor(8, 10);
    display.println("SwitchLab");

    display.setTextSize(1);
    display.setCursor(8, 36);
    display.println("Firmware placeholder");

    display.setCursor(8, 50);
    display.println("Cqwea Engineering");

    display.display();

    Serial.println("Cqwea SwitchLab starting...");
}

void loop() {
    scanMatrix();

    delay(10);
}

void scanMatrix() {
    for (uint8_t r = 0; r < ROWS; r++) {

        // Activate one row
        digitalWrite(rowPins[r], LOW);

        for (uint8_t c = 0; c < COLS; c++) {

            if (digitalRead(colPins[c]) == LOW) {
                Serial.print("Key detected: R");
                Serial.print(r);
                Serial.print(" C");
                Serial.println(c);
            }
        }

        // Deactivate row
        digitalWrite(rowPins[r], HIGH);
    }
}