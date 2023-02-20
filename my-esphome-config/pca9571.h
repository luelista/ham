#include "esphome.h"

#define I2C_PCA 0x25
#define ANALOG_JOYSTK 0
#define ANALOG_BATLVL 1
#define ANALOG_LDRSNS 2
#define ANALOG_IN1 5

class PCA9571Component : public Component {
 public:
  uint16_t data = 0;
  void setup() override {
    // Initialize the device here. Usually Wire.begin() will be called in here,
    // though that call is unnecessary if you have an 'i2c:' entry in your config

    //...clear the I2C extender to switch off vobrator and LCD backlight
    set_ir_enable(true);
    update();
    ESP_LOGD("custom", "GPIO Mux Initialized!");
  }
  void update() {
    Wire.beginTransmission(I2C_PCA);
    Wire.write(data); 
    Wire.endTransmission();

  }
  void loop() override {
    // Example: write the value 0x42 to register 0x78 of device with address 0x21
    
  }
  void set_vibrate(bool on) {
    set_bit(3, on);
  }
  void set_lcd_backlight(bool on) {
    set_bit(5, on);
  }
  void set_ir_enable(bool on) {
    set_bit(6, on);
  }
  void select_analog(int selection) {
    data &= 0b111111000;
    data |= selection&0b111;
  }
  void set_bit(int bit, bool on) {
    if (on) {
        data |= (1 << bit);
    } else {
        data &= ~(1 << bit);
    }
    update();
  }
};
