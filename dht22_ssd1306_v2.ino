#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin) -1 or 4
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
#define DHTTYPE DHT22 // DHT 22  (AM2302), AM2321
#define DHTPIN 2 // Digital pin connected to the DHT sensor

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, & Wire, OLED_RESET);

DHT dht(DHTPIN, DHTTYPE);

// degree 10*16
/*static const unsigned char degree[] PROGMEM = {
  0x0f,0xc0,0x0f,0xc0,0x0c,0xc0,0x0c,0xc0,0x0f,0xc0,0x0f,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};*/

void setup() {

    dht.begin();
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

    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    float h = dht.readHumidity();
    // Read temperature as Celsius
    float t = dht.readTemperature();

    // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(t)) {
        //display.println(F("Failed to read from DHT sensor!"));
        return;
    }

    // Compute heat index in Celsius 
    float hi = dht.computeHeatIndex(t, h);

    display.setTextColor(WHITE);
    display.setTextSize(2);

    display.setCursor(0, 0);
    display.print("Temp:");

    display.setCursor(64, 0);
    display.print(t, 1); // 小数点后一位

    display.setCursor(0, 28);
    display.print("Humi:");

    display.setCursor(64, 28);
    display.print(h, 1);  // 小数点后一位

    display.setCursor(0, 48);
    display.print("HtIn:");

    display.setCursor(64, 48);
    display.print(hi);  

    // % , 
    display.setCursor(116,28);  // Start at top-left corner
    display.print("%");
    

    display.drawRect(122, 0, 4, 4, WHITE); // Put degree symbol ( ° )

    display.display();

}
