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


void setup() {
  io.begin();
  startAnimation();
}

void loop() {
  io.update();
//  io.print();
    Serial.println(io.micLevel);
  //    Serial.println(io.distance);

  //  if (io.distance > 15 && io.distance < 100) {
  //    demoAnimation();
  //  }
  //demoAnimation();
}
