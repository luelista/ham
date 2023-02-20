
#include "esphome.h"
#include <TFT_ILI9163C.h>
#define __CS 15
#define __DC 0

TFT_ILI9163C tft = TFT_ILI9163C(__CS, __DC);
class ILI9163CTestComponent : public Component {
  float angle=0;
  bool is_init=false;
public:
  void setup() override {
  }


  // Translate a hue "angle" -120 to 120 degrees (ie -2PI/3 to 2PI/3) to
  // a 6-bit R channel value
  //
  // This is very slow on a microcontroller, not a great example!
  inline int angle_to_channel(float a) {
    if (a < -PI) a += 2 * PI;
    if (a < -2 * PI / 3  || a > 2 * PI / 3) return 0;
    float f_channel = cos(a * 3 / 4); // remap 120-degree 0-1.0 to 90 ??
    return ceil(f_channel * 255);//63
  }

  void initialize() {
    
    tft.begin(); //initialize the tft. This also sets up SPI to 80MHz Mode 0
    tft.setRotation(2); //turn screen
    tft.scroll(32); //move down by 32 pixels (needed)
    tft.fillScreen(BLACK);  //make screen black

    ESP_LOGD("custom", "Display Initialized!");
    is_init=true;

  }

  void loop() override {
    if (!is_init) return;

    uint16_t clr = (((angle_to_channel(angle - 4 * PI / 3) >> 1) & 0xF8) << 8) | (((angle_to_channel(angle - 2 * PI / 3)) & 0xFC) << 3) | ((angle_to_channel(angle) >> 1) >> 3);
    tft.fillScreen(clr);

    angle += 0.01;
    if (angle > PI)
        angle -= 2 * PI;
  }
};
