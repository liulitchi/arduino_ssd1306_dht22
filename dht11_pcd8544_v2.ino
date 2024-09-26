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
    display.drawBitmap(10, 0, temp_cn, 32, 32, BLACK);
    
  
    display.setTextSize(2);
    display.setTextColor(BLACK);


    display.setCursor(0, 0);
    display.println("Te Humi");
    display.display();

    display.setCursor(4, 17);
    display.println(te);
    display.display();

    display.setCursor(48, 17);
    display.println(hu);
    display.display();

    
    display.setCursor(16, 33);
    display.println("C");
    display.display();

    display.setCursor(48, 33);
    display.println("%");
    display.display();
    
}
