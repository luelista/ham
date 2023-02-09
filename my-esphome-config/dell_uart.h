#include "esphome.h"

// Dell P4317Q

class DellUartComponent : public Component, public UARTDevice {
 public:
  DellUartComponent(UARTComponent *parent) : UARTDevice(parent) {}

  void setup() override {
    // nothing to do here
  }
  void loop() override {
    // TODO implement protocol parser for Dell P4317Q to receive ACKs and retrieve states

  }
};