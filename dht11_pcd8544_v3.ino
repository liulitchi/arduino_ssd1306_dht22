#include <SPI.h>
#include <DHT.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

// Software SPI (slower updates, more flexible pin options):
// pin 7 - Serial clock out (SCLK)
// pin 6 - Serial data out (DIN)
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
Adafruit_PCD8544 display = Adafruit_PCD8544(13, 12, 5, 4, 3);


#define DHTPIN 2     // Digital pin connected to the DHT sensor
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)


DHT dht(DHTPIN, DHTTYPE);

// 字模来自：https://www.zhetao.com/fontarray.html
// 温
static const unsigned char PROGMEM temp_cn[] = {
    0b01110011, 0b11111100, 
    0b01111011, 0b11111100, 
    0b00111111, 0b00001100, 
    0b00001011, 0b00001100, 
    0b00000011, 0b11111100, 
    0b11110011, 0b00001100, 
    0b01111011, 0b11111100, 
    0b00010011, 0b11111100, 
    0b00000111, 0b11111110, 
    0b00011111, 0b11111110, 
    0b00011110, 0b11110110, 
    0b00111110, 0b11110110, 
    0b00110110, 0b11110110, 
    0b01110110, 0b11110110, 
    0b01101111, 0b11111111, 
    0b01101111, 0b11111111
};


// 湿
static const unsigned char PROGMEM humi_cn[] = {
    0b01110000, 0b00000000, 
    0b01111111, 0b11111110, 
    0b00111110, 0b00000110, 
    0b00011110, 0b00000110, 
    0b00000111, 0b11111110, 
    0b11110110, 0b00000110, 
    0b01111111, 0b11111110, 
    0b00010011, 0b11111100, 
    0b00010110, 0b11110110, 
    0b00011110, 0b11110110, 
    0b00111111, 0b11110110, 
    0b00110111, 0b11111110, 
    0b01110011, 0b11111100, 
    0b01110010, 0b11110100, 
    0b01101111, 0b11111111, 
    0b01101111, 0b11111111
};

// 度 
static const unsigned char PROGMEM degree_cn[] = {
    0b00000001, 0b11000000, 
    0b00111111, 0b11111111, 
    0b00111111, 0b11111111, 
    0b00110011, 0b00011000, 
    0b00110011, 0b00011000, 
    0b00111111, 0b11111110, 
    0b00110011, 0b00011000, 
    0b01110011, 0b00011000, 
    0b01110011, 0b11111000, 
    0b01110000, 0b00000100, 
    0b01111111, 0b11111100, 
    0b01100111, 0b00011100, 
    0b01100011, 0b11111000, 
    0b01100011, 0b11110000, 
    0b11111111, 0b11111111, 
    0b11011111, 0b00011111
};


void setup() {

    dht.begin();
    display.begin();
    display.setContrast(56); // 显示屏对比度,50~60之间最佳
    display.clearDisplay();

}


void loop() {
   
    delay(10000);
    display.clearDisplay();

    //float hu = dht.readHumidity();
    int8_t hu = dht.readHumidity();
    //float te = dht.readTemperature();
    int8_t te = dht.readTemperature();
    if (isnan(hu) || isnan(te)) {
      return;
    }

    // compure heat index in Celsius
    //float hi = dht.computeHeatIndex(te, hu);
    
    display.drawBitmap(5, 0, temp_cn, 16, 16, BLACK);
    display.display();

    display.drawBitmap(23, 0, degree_cn, 16, 16, BLACK);
    display.display();


    display.drawBitmap(46, 0, humi_cn, 16, 16, BLACK);
    display.display();    

    display.drawBitmap(64, 0, degree_cn, 16, 16, BLACK);
    display.display();

    //display.drawRect();
    //display.display();
    
    display.setTextSize(2);
    display.setTextColor(BLACK);


    display.setCursor(3, 33);
    display.println(te);
    display.display();
    
    display.setCursor(48, 33);
    display.println(hu);
    display.display();

    display.setCursor(72, 33);
    display.println("%");
    display.display();

}
