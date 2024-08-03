#include "oled.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include "pinout.h"

int SCREEN_WIDTH = 128;  // OLED display width, in pixels
int SCREEN_HEIGHT = 64;  // OLED display height, in pixels
int OLED_RESET = -1;  // No reset pin (use -1 if shared with ESP32)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void oledSetup() {
    Wire.begin(OLED_SDA_PIN, OLED_SCL_PIN);
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        for (;;); // Infinite loop
    }
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("OLED initialized!");
    display.display();
}

void oledDisplay(String message) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println(message);
    display.display();
}

void oledAppendDisplay(String message) {
    display.println(message);
    display.display();
}