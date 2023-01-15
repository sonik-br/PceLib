/*******************************************************************************
 * NEC PC Engine controller input library.
 * https://github.com/sonik-br/PceLib
 * 
 * The library depends on greiman's DigitalIO library.
 * https://github.com/greiman/DigitalIO
 * 
 * I recommend the usage of SukkoPera's fork of DigitalIO as it supports a few more platforms.
 * https://github.com/SukkoPera/DigitalIO
 * 
 * 
 * This sketch is ready to use on a Leonardo but may work on any
 * arduino with the correct number of pins and proper setup.
*/

//Enable or disable multitap support
//#define PCE_ENABLE_MULTITAP

#include <PceLib.h>

//PCE pins - Port 1
#define PCE1_SEL 5
#define PCE1_CLR 4
#define PCE1_D0  9 //U 1 3
#define PCE1_D1  8 //R 2 4
#define PCE1_D2  7 //D S 5
#define PCE1_D3  6 //L R 6


PcePort<PCE1_SEL, PCE1_CLR, PCE1_D0, PCE1_D1, PCE1_D2, PCE1_D3> pce1;

#define ENABLE_SERIAL_DEBUG


#ifdef ENABLE_SERIAL_DEBUG
#define dstart(spd) do {Serial.begin (spd); while (!Serial) {}} while (0);
#define debug(...) Serial.print (__VA_ARGS__)
#define debugln(...) Serial.println (__VA_ARGS__)
#else
#define dstart(...)
#define debug(...)
#define debugln(...)
#endif


#define DIGITALSTATE(D) \
if(sc.digitalJustPressed(D)) { \
  debugln(F("Digital pressed: " #D)); \
} else if(sc.digitalJustReleased(D)) {\
  debugln(F("Digital released: " #D)); \
}

#define DEVICE(A, B) \
if(A == B) {\
  debug(#B); \
}

void printDeviceType (const PceDeviceType_Enum d){
  DEVICE(d, PCE_DEVICE_NONE)
  DEVICE(d, PCE_DEVICE_NOTSUPPORTED)
  DEVICE(d, PCE_DEVICE_PAD2)
  DEVICE(d, PCE_DEVICE_PAD6)
}

void printButtons(const PceController& sc) {
  DIGITALSTATE(PCE_PAD_UP)
  DIGITALSTATE(PCE_PAD_DOWN)
  DIGITALSTATE(PCE_PAD_LEFT)
  DIGITALSTATE(PCE_PAD_RIGHT)
  DIGITALSTATE(PCE_1)
  DIGITALSTATE(PCE_2)
  DIGITALSTATE(PCE_SELECT)
  DIGITALSTATE(PCE_RUN)
  DIGITALSTATE(PCE_3)
  DIGITALSTATE(PCE_4)
  DIGITALSTATE(PCE_5)
  DIGITALSTATE(PCE_6)
}

void setup() {
  dstart (115200);
  
  //Init the library.
  pce1.begin();

  //pce1.detectMultitap();
  //delay(1000);
  
  debugln (F("Powered on!"));
}

void loop() {
  static unsigned long idleTimer = 0;
  static uint8_t lastControllerCount = 0;
  static uint8_t lastMultitapPorts = 0;
  static PceDeviceType_Enum dtype[TAP_PCE_PORTS] = { PCE_DEVICE_NONE, PCE_DEVICE_NONE, PCE_DEVICE_NONE, PCE_DEVICE_NONE, PCE_DEVICE_NONE };
  
  //uint8_t hatData;

  const unsigned long start = micros();
  
  //Call update to read the controller(s)
  pce1.update();
  
  //Time spent to read controller(s) in microseconds
  const unsigned long delta = micros() - start;

  //debugln(delta);

  const uint8_t multitapPorts = pce1.getMultitapPorts();

  //A multitap was connected or disconnected?
  if (lastMultitapPorts > multitapPorts) {
    debugln(F("Multitap disconnected"));
  } else if (lastMultitapPorts < multitapPorts) {
    debug(F("Multitap connected. Ports: "));
    debugln(pce1.getMultitapPorts());
  }
  
  const uint8_t joyCount = pce1.getControllerCount();
  //debugln(joyCount);
  if (lastControllerCount != joyCount) {
    debug(F("Connected devices: "));
    debugln(joyCount);
  }
  
  bool isIdle = true;
  for (uint8_t i = 0; i < joyCount; i++) {
    const PceController& sc = pce1.getPceController(i);
    if (sc.stateChanged()) {
      isIdle = false;
      
      //hatData = sc.hat();
      //dtype = sc.deviceType();

      //Controller just connected. Also can happen when changing mode the 6btn pad
      if (sc.deviceJustChanged()) {
        debug(F("Device changed from "));
        printDeviceType(dtype[i]);
        debug(F(" to "));
        dtype[i] = sc.deviceType();
        printDeviceType(dtype[i]);
        debugln();
      }

      //bool isPressed = sc.digitalPressed(PCE_RUN);
      
      printButtons(sc);
      
    }
    
  }

  //Controller has been disconnected?
  if (lastControllerCount > joyCount) {
    for (uint8_t i = joyCount; i < lastControllerCount; i++) {
      const PceController& sc = pce1.getPceController(i);
      if (sc.stateChanged() && sc.deviceJustChanged()) {
        debugln(F("Device disconnected"));
        dtype[i] = PCE_DEVICE_NONE;
      }
    }
  }
  
  lastControllerCount = joyCount;
  lastMultitapPorts = multitapPorts;

  if(isIdle) {
    if (millis() - idleTimer >= 3000) {
      idleTimer = millis();
      debug(F("Idle. Read time: "));
      debugln(delta);
    }
  } else {
    idleTimer = millis();
    debug(F("Read time: "));
    debugln(delta);
  }

  delayMicroseconds(500);
  //delay(100);
}
