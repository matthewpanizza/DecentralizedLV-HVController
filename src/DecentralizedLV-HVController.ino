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

#define CHARGE_ENABLE       D3
#define DISCHARGE_ENABLE    D4
#define BMS_FAULT           A0      //BMS Fault input pin

// Let Device OS manage the connection to the Particle Cloud
SYSTEM_MODE(MANUAL);

SYSTEM_THREAD(DISABLED);

CAN_Controller hvCanController;
CAN_Controller lvCanController;

DashController_CAN dashController(DASH_CONTROL_ADDR);

PowerController_CAN powerController(POWER_CONTROL_ADDR);

// setup() runs once, when the device is first turned on
void setup() {
    Serial.begin(115200);

    RGB.control(true);
    RGB.color(255,255,255);

    pinMode(CHARGE_ENABLE, OUTPUT);     //Set up the FETs at outputs.
    pinMode(DISCHARGE_ENABLE, OUTPUT);
    pinMode(BMS_FAULT, INPUT);

    lvCanController.begin(CAN_500KBPS, S4);
    lvCanController.addFilter(powerController.boardAddress);   //Allow incoming messages from Power Controller
    lvCanController.addFilter(dashController.boardAddress);   //Allow incoming messages from Power Controller

    hvCanController.begin(CAN_500KBPS, S3);
    hvCanController.addFilter(powerController.boardAddress);   //Allow incoming messages from Power Controller
    hvCanController.addFilter(dashController.boardAddress);   //Allow incoming messages from Power Controller
    
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {

    LV_CANMessage rxLVMessage;
    LV_CANMessage rxHVMessage;

    if(lvCanController.receive(rxLVMessage)){
        Serial.printlnf("Got LV CAN Message. ID: 0x%x", rxLVMessage.addr);
        powerController.receiveCANData(rxLVMessage);
    }

    if(hvCanController.receive(rxHVMessage)){
        Serial.printlnf("Got HV CAN Message. ID: 0x%x", rxHVMessage.addr);
        
    }

    digitalWrite(CHARGE_ENABLE, powerController.Acc);
    digitalWrite(DISCHARGE_ENABLE, powerController.Ign);
    
    delay(10);
}
