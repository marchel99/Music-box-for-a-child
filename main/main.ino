#include <LiquidCrystal.h>
#include <Adafruit_NeoPixel.h>
#include <DFMiniMp3.h>
#include <SoftwareSerial.h>

#define PIN_LED 6
#define NUM_LEDS 10
#define PIN_RX 2
#define PIN_TX 3

const int PinCLK = 4;
const int PinDT = 5;
const int PinSW = 7;
int counter = 1;
int clkState;
int lastClkState = HIGH;

SoftwareSerial mySerial(PIN_RX, PIN_TX);
DFMiniMp3<SoftwareSerial> mp3(mySerial);

LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_LEDS, PIN_LED, NEO_GRB + NEO_KHZ800);

void setup() {
  lcd.begin(16, 2);
  display.setCursor(0,0);
  display.println("Pozytywka");
  display.setCursor(0,1);
  display.println("Jasia");
  pinMode(PinCLK, INPUT);
  pinMode(PinDT, INPUT);
  pinMode(PinSW, INPUT_PULLUP);
  pixels.begin();
  mySerial.begin(9600);
  mp3.begin();
}

void loop() {
  lcd.setCursor(0, 1);
  lcd.print("Gram ");
  switch(counter) {
    case 1:
      lcd.print("Wilcza zamiec");
      mp3.playMp3FolderTrack(1);
      break;
    case 2:
      lcd.print("Pieski dwa");
      mp3.playMp3FolderTrack(2);
      break;
    case 3:
      lcd.print("Spij juz");
      mp3.playMp3FolderTrack(3);
      break;
    case 4:
      lcd.print("Kaczuszki");
      mp3.playMp3FolderTrack(4);
      break;
    case 5:
      lcd.print("Ach, Spij");
      mp3.playMp3FolderTrack(5);
      break;
    default:
      lcd.print("Wilcza zamiec");
      mp3.playMp3FolderTrack(1);
      counter = 1;
      break;
  }

  for(int i=0;i<NUM_LEDS;i++) {
    pixels.setPixelColor(i, pixels.Color(random(0, 255), random(0, 255), random(0, 255)));
  }
  pixels.show();

  if(digitalRead(PinSW) == LOW){
    lcd.clear();
    lcd.print("Kliknij przycisk");
    delay(500);
    while(digitalRead(PinSW) == LOW){
      //do nothing
    }
    lcd.clear();
    counter++;
  }

  clkState = digitalRead(PinCLK);
  if(clkState != lastClkState){
    if(digitalRead(PinDT) != clkState){
      counter++;
    }
    else{
      counter--;
    }
  }
  lastClkState = clkState;

  delay(1000);
}
