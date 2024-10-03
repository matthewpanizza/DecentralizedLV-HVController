/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#line 1 "c:/Users/mligh/OneDrive/Particle/DecentralizedLV-HVController/src/DecentralizedLV-HVController.ino"
/* 
 * Project myProject
 * Author: Your Name
 * Date: 
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

// Include Particle Device OS APIs
#include "Particle.h"
#include "DecentralizedLV-Boards/DecentralizedLV-Boards.h"

// Let Device OS manage the connection to the Particle Cloud
void setup();
void loop();
#line 14 "c:/Users/mligh/OneDrive/Particle/DecentralizedLV-HVController/src/DecentralizedLV-HVController.ino"
SYSTEM_MODE(MANUAL);

CAN_Controller canController;

DashController_CAN dashController(DASH_CONTROL_ADDR);

PowerController_CAN powerController(POWER_CONTROL_ADDR);

// setup() runs once, when the device is first turned on
void setup() {
    Serial.begin(115200);

    canController.begin(CAN_500KBPS, S3);
    canController.addFilter(powerController.boardAddress);   //Allow incoming messages from Power Controller
    canController.addFilter(dashController.boardAddress);   //Allow incoming messages from Power Controller
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.

  // Example: Publish event to cloud every 10 seconds. Uncomment the next 3 lines to try it!
  // Log.info("Sending Hello World to the cloud!");
  // Particle.publish("Hello world!");
  // delay( 10 * 1000 ); // milliseconds and blocking - see docs for more info!
}
