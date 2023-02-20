
#include "esphome.h"
#include <TFT_ILI9163C.h>
#define __CS 15
#define __DC 0

TFT_ILI9163C tft = TFT_ILI9163C(__CS, __DC);
class ILI9163CTestComponent : public PollingComponent {
  float angle=0;
  int is_init=0;
public:
  ILI9163CTestComponent() : PollingComponent(1000) {}

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
    tft.setTextSize(2);
    tft.setCursor(25, 48);
    tft.print("miratest");
    tft.writeFramebuffer();

    ESP_LOGD("custom", "Display Initialized!");
    is_init=1;

  }

  void update() override {
    tft.fillScreen(BLACK);  //make screen black
    tft.setTextSize(1);
    tft.setCursor(15, 48);
    tft.print("gpn17badge");
    char out[10];

    id(homeassistant_time).now().strftime(out, sizeof(out), "%H:%M:%S");
    tft.setCursor(15, 90);
    tft.print(out);
    tft.writeFramebuffer();
  }
};
