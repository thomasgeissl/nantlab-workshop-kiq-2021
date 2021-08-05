#include "./IO.h"
IO io;

void startAnimation() {
  io.clear();
  for (auto i = 0; i < LED_COUNT; i++) {
    io.setColorAtIndex(i, 255, 0, 0);
    delay(100);
    io.show();
  }
  io.clear();
  io.show();
}

void demoAnimation() {
  io.clear();
  for (auto i = 0; i < LED_COUNT; i++) {
    int red = 64;
    int blue = 0;
    int distance = io.getDistance();
    if(distance < 100){
      blue = 127;
    }
    if(distance < 50){
      blue = 255;
    }
    
    io.setColorAtIndex(i, red, 0, blue);
    delay(20);
    io.show();
  }
  io.clear();
  io.show();
}


void setup() {
  io.begin();
  startAnimation();
}

void loop() {
  io.print();
  //    Serial.println(io.micLevel);
  //    Serial.println(io.distance);

  //  if (io.distance > 15 && io.distance < 100) {
  //    demoAnimation();
  //  }
  demoAnimation();
}
