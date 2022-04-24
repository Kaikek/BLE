#include "BluetoothSerial.h"
#include "Wire.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

BluetoothSerial SerialBT;
DHT dht(DHTPIN, DHTTYPE);

float t;
String truetemp;
int timer = 0;
String payload;
String Data = "";

void setup() {
  Serial.begin(115200);
  SerialBT.begin("TTGOOOOO"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  { 
    Serial.println(F("SSD1306 allocation failed"));
  }
}

void loop() 
{
  int i = 0;
  while (SerialBT.available()) 
  {
    i++;
    char character = SerialBT.read();
    Data.concat(character);
    if(i == 4)
    {
      display.clearDisplay();
      display.setTextSize(0);
      display.setTextColor(WHITE);
      display.setCursor(32, 18);
      display.print(Data);
      Serial.println(Data);
      display.display();
      Data = "";
      i = 0;
    }
  }
}
