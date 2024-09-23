#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin) -1 or 4
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

#define ONE_WIRE_BUS 4 // Data wire is conntec to the Arduino digital pin 4

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, & Wire, OLED_RESET);


void setup() {

    sensors.begin(); // Start up the library
    // put your setup code here, to run once:
    display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);

    //Serial.begin(9600);
    // Show initial display buffer contents on the screen --
    // the library initializes this with an Adafruit splash screen.
    display.display();
    delay(2000); // Pause for 2 seconds
    // Clear the buffer
    display.clearDisplay();

    // Draw a single pixel in white
    //display.drawPixel(10, 10, SSD1306_WHITE);
}


void loop() {
    // Wait a few seconds between measurements.
    delay(10000);
    display.clearDisplay();

    sensors.requestTemperatures();


    display.setTextColor(WHITE);
    display.setTextSize(2);

    display.setCursor(0, 0);
    display.print("   Temp");

    display.drawRect(91, 32, 3, 3, WHITE); // Put degree symbol ( ° )

    display.setCursor(96, 32);
    display.print("C");

    display.setCursor(16, 32);
    display.print(sensors.getTempCByIndex(0));


    display.display();

}
