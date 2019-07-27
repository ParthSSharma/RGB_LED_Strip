#include <FastLED.h>
#define ledpin 6
#define numled 144
#define input A7

unsigned int sum = 0;
int values[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
CRGB led[numled];

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<NEOPIXEL, ledpin>(led, numled);
  for(int i=0; i<numled; i++){
    led[i] = CRGB(255, 0, 0);
  }
  FastLED.show();
}

void loop() {
  int value = analogRead(input);
  int showled = map(value, 0, 1023, 0, 144);
  sum = sum - values[0];
  for(int k=0; k<9; k++){
    values[k] = values[k+1];
  }
  values[9] = showled;
  sum = sum + values[9];
  int avg = int (sum/10);
  for(int i=0; i<numled; i++){
    if(i<avg){
      if(avg<50){
        led[i] = CRGB(255, 0, 0);
      }
      if(avg>=50 && avg<100){
        led[i] = CRGB(0, 255, 0);
      }
      if(avg>=100){
        led[i] = CRGB(0, 0, 255);
      }
    }
    if(i>avg){
      led[i] = CRGB(0, 0, 0);
    }
  }
  FastLED.show();
  Serial.println(avg);
  delay(5);
}
