#pragma once
//
//    FILE: PCF8574.H
//  AUTHOR: Rob Tillaart
//    DATE: 02-febr-2013
// VERSION: 0.2.5
// PURPOSE: Arduino library for PCF8574 - I2C IO expander
//     URL: https://github.com/RobTillaart/PCF8574
//          http://forum.arduino.cc/index.php?topic=184800
//
// HISTORY:
// see PCF8574.cpp file
//

#include "Arduino.h"
#include "Wire.h"

#define PCF8574_LIB_VERSION "0.2.5"

#define PCF8574_OK          		0x00
#define PCF8574_INTERFACE_NOT_AVAILABLE 0x80
#define PCF8574_PIN_ERROR   		0x81
#define PCF8574_I2C_ERROR   		0x82


enum{
	PCF8574_INTERFACE_WIRE  = (uint8_t)0,
#ifdef WIRE_IMPLEMENT_WIRE1
	PCF8574_INTERFACE_WIRE1 = (uint8_t)1,
#endif
#ifdef WIRE_IMPLEMENT_WIRE2
	PCF8574_INTERFACE_WIRE2 = (uint8_t)2,
#endif
#ifdef WIRE_IMPLEMENT_WIRE3
	PCF8574_INTERFACE_WIRE3 = (uint8_t)3,
#endif
#ifdef WIRE_IMPLEMENT_WIRE4
	PCF8574_INTERFACE_WIRE4 = (uint8_t)4,
#endif
#ifdef WIRE_IMPLEMENT_WIRE5
	PCF8574_INTERFACE_WIRE5 = (uint8_t)5,
#endif
	
	/* ============================ */
	PCF8574_INTERFACE_NO_OF_INTERFACES,
};

class PCF8574
{
public:
  explicit PCF8574(uint8_t interfaceIndex, const uint8_t deviceAddress);

#if defined (ESP8266) || defined(ESP32)
  void   begin(uint8_t sda, uint8_t scl, uint8_t val = 0xFF);
#endif
  void    begin(uint8_t val = 0xFF);

  uint8_t read8();
  uint8_t read(uint8_t pin);
  uint8_t value() const { return _dataIn; };

  void    write8(const uint8_t value);
  void    write(const uint8_t pin, const uint8_t value);
  uint8_t valueOut() const { return _dataOut; }

  //added 0.1.07/08 Septillion
  inline uint8_t readButton8()  { return PCF8574::readButton8(_buttonMask); }
  uint8_t        readButton8(const uint8_t mask);
  uint8_t        readButton(const uint8_t pin);
  inline void    setButtonMask(uint8_t mask) { _buttonMask = mask; };

  // rotate, shift, toggle, reverse expect all lines are output
  void    toggle(const uint8_t pin);
  void    toggleMask(const uint8_t mask = 0xFF);    // default 0xFF ==> invertAll()
  void    shiftRight(const uint8_t n = 1);
  void    shiftLeft(const uint8_t n = 1);
  void    rotateRight(const uint8_t n = 1);
  void    rotateLeft(const uint8_t n = 1);
  void    reverse();

  int lastError();

private:
  uint8_t _interfaceIndex;
  uint8_t _address;
  uint8_t _dataIn;
  uint8_t _dataOut;
  uint8_t _buttonMask;
  int     _error;
};

// -- END OF FILE --
