#include <examples/ArduinoBlink/Top/Components.hpp>
#include <Fw/Types/Generic/GenericLogAssert.hpp>
#include <Os/Log.hpp>
#ifdef ARDUINO
    #include <Os/Arduino/StreamLog.hpp>
    #include <Arduino.h>
#else
    #include <examples/ArduinoGpsTracker/SerialDriver/SerialDriver.hpp>
#endif

// Global handlers for this Topology
Fw::LogAssertHook assert;

#define STARTUP_DELAY_MS 2000

/**
 * Main function.
 */
int main(int argc, char* argv[]) {
	assert.registerHook();
#ifdef ARDUINO
    // Start Serial for logging, and give logger time to connect
    Serial.begin(9600);
    delay(STARTUP_DELAY_MS);
    // Setup log handler
    Os::setArduinoStreamLogHandler(&Serial);
#else
    // Set serial port
    FW_ASSERT(argc <= 2);
    if (argc == 2) {
        Arduino::SERIAL_PORT = reinterpret_cast<char**>(&argv[1]);
    }
#endif
    Fw::Logger::logMsg("[SETUP] Constructing system\n", 0, 0, 0, 0, 0, 0);
    constructApp();
#ifndef ARDUINO
    while (1) {}
#endif
    return 0;
}