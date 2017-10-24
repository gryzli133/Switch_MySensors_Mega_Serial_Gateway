// Enable debug prints to serial monitor
#define MY_DEBUG 

// Enable and select radio type attached
//#define MY_RADIO_NRF24
//#define MY_RADIO_RFM69

// Set LOW transmit power level as default, if you have an amplified NRF-module and
// power your radio separately with a good regulator you can turn up PA level. 
//#define MY_RF24_PA_LEVEL RF24_PA_LOW

// Enable serial gateway
#define MY_GATEWAY_SERIAL

// Define a lower baud rate for Arduino's running on 8 MHz (Arduino Pro Mini 3.3V & SenseBender)
#if F_CPU == 8000000L
#define MY_BAUD_RATE 38400
#endif

// Flash leds on rx/tx/err
// #define MY_LEDS_BLINKING_FEATURE
// Set blinking period
// #define MY_DEFAULT_LED_BLINK_PERIOD 300

// Inverses the behavior of leds
// #define MY_WITH_LEDS_BLINKING_INVERSE

// Enable inclusion mode
#define MY_INCLUSION_MODE_FEATURE
// Enable Inclusion mode button on gateway
#define MY_INCLUSION_BUTTON_FEATURE

// Inverses behavior of inclusion button (if using external pullup)
//#define MY_INCLUSION_BUTTON_EXTERNAL_PULLUP

// Set inclusion mode duration (in seconds)
#define MY_INCLUSION_MODE_DURATION 60 
// Digital pin used for inclusion mode button
//#define MY_INCLUSION_MODE_BUTTON_PIN  3 - uaktywnic gdyby cos nie gralo

// Uncomment to override default HW configurations
//#define MY_DEFAULT_ERR_LED_PIN 4  // Error led pin
//#define MY_DEFAULT_RX_LED_PIN  6  // Receive led pin
//#define MY_DEFAULT_TX_LED_PIN  5  // the PCB, on board LED

#include <SPI.h>
#include <MySensors.h>  
#include <Bounce2.h>
#include <Wire.h>

// Enable repeater functionality for this node
#define MY_REPEATER_FEATURE

//Piny przekaznikow Arduino
#define RELAY_1  32  
#define RELAY_2  33  
#define RELAY_3  34  
#define RELAY_4  35
#define RELAY_5  36  
#define RELAY_6  37  
#define RELAY_7  38  
#define RELAY_8  39
#define RELAY_9  40  
#define RELAY_10  41  
#define RELAY_11  42  
#define RELAY_12  43
#define RELAY_13  44  
#define RELAY_14  45  
#define RELAY_15  46  
#define RELAY_16  47
#define RELAY_17  48
#define RELAY_18  49  
#define RELAY_19  50  
#define RELAY_20  51  
#define RELAY_21  52
#define RELAY_22  53
#define NUMBER_OF_RELAYS 22 // Liczba sensora sterowana z arduino
/*
//piny przekanikow expander1
#define ex1RELAY_1  0  
#define ex1RELAY_2  1 
#define ex1RELAY_3  2  
#define ex1RELAY_4  3
#define ex1RELAY_5  4 
#define ex1RELAY_6  5 
#define ex1RELAY_7  6  
#define ex1RELAY_8  7
#define ex1NUMBER_OF_RELAYS 30 // numer ostatniego sensora sterowanego z expander1

//piny przekanikow expander2
#define ex2RELAY_1  0  
#define ex2RELAY_2  1 
#define ex2RELAY_3  2  
#define ex2RELAY_4  3
#define ex2RELAY_5  4 
#define ex2RELAY_6  5 
#define ex2RELAY_7  6  
#define ex2RELAY_8  7
#define ex2NUMBER_OF_RELAYS 38 // numer ostatniego sensora sterowanego z expander2
*/

#define RELAY_ON 1  // GPIO value to write to turn on attached relay
#define RELAY_OFF 0 // GPIO value to write to turn off attached relay

#define BUTTON_PIN A0
#define BUTTON2_PIN A1
#define BUTTON3_PIN A2
#define BUTTON4_PIN A3
#define BUTTON5_PIN A4
#define BUTTON6_PIN A5
#define BUTTON7_PIN A6
#define BUTTON8_PIN A7
#define BUTTON9_PIN A8
#define BUTTON10_PIN A9
#define BUTTON11_PIN A10
#define BUTTON12_PIN A11
#define BUTTON13_PIN A12
#define BUTTON14_PIN A13
#define BUTTON15_PIN A14
#define BUTTON16_PIN A15
#define BUTTON17_PIN 2
#define BUTTON18_PIN 3
#define BUTTON19_PIN 4
#define BUTTON20_PIN 5
#define BUTTON21_PIN 6
#define BUTTON22_PIN 7
#define BUTTON23_PIN 8
#define BUTTON24_PIN 9
#define BUTTON25_PIN 10
#define BUTTON26_PIN 11
#define BUTTON27_PIN 12
#define BUTTON28_PIN 13
#define BUTTON29_PIN 14
#define BUTTON30_PIN 15
#define BUTTON31_PIN 16
#define BUTTON32_PIN 17
#define BUTTON33_PIN 18
#define BUTTON34_PIN 19
#define BUTTON35_PIN 20
#define BUTTON36_PIN 21
#define BUTTON37_PIN 22
#define BUTTON38_PIN 23
#define BUTTON39_PIN 24
#define BUTTON40_PIN 25
/*
PCF8574 expander1;
PCF8574 expander2;
*/
MyMessage msg(1, V_LIGHT);
MyMessage msg2(2, V_LIGHT);
MyMessage msg3(3, V_LIGHT);
MyMessage msg4(4, V_LIGHT);
MyMessage msg5(5, V_LIGHT);
MyMessage msg6(6, V_LIGHT);
MyMessage msg7(7, V_LIGHT);
MyMessage msg8(8, V_LIGHT);
MyMessage msg9(9, V_LIGHT);
MyMessage msg10(10, V_LIGHT);
MyMessage msg11(11, V_LIGHT);
MyMessage msg12(12, V_LIGHT);
MyMessage msg13(13, V_LIGHT);
MyMessage msg14(14, V_LIGHT);
MyMessage msg15(15, V_LIGHT);
MyMessage msg16(16, V_LIGHT);
MyMessage msg17(17, V_LIGHT);
MyMessage msg18(18, V_LIGHT);
MyMessage msg19(19, V_LIGHT);
MyMessage msg20(20, V_LIGHT);
MyMessage msg21(21, V_LIGHT);
MyMessage msg22(22, V_LIGHT);
MyMessage msg23(23, V_LIGHT);
MyMessage msg24(24, V_LIGHT);
MyMessage msg25(25, V_LIGHT);
MyMessage msg26(26, V_LIGHT);
MyMessage msg27(27, V_LIGHT);
MyMessage msg28(28, V_LIGHT);
MyMessage msg29(29, V_LIGHT);
MyMessage msg30(30, V_LIGHT);
MyMessage msg31(31, V_LIGHT);
MyMessage msg32(32, V_LIGHT);
MyMessage msg33(33, V_LIGHT);
MyMessage msg34(34, V_LIGHT);
MyMessage msg35(35, V_LIGHT);
MyMessage msg36(36, V_LIGHT);
MyMessage msg37(37, V_LIGHT);
MyMessage msg38(38, V_LIGHT);
MyMessage msg39(39, V_LIGHT);
MyMessage msg40(40, V_LIGHT);

Bounce debouncer = Bounce();
Bounce debouncer2 = Bounce();
Bounce debouncer3 = Bounce();
Bounce debouncer4 = Bounce();
Bounce debouncer5 = Bounce();
Bounce debouncer6 = Bounce();
Bounce debouncer7 = Bounce();
Bounce debouncer8 = Bounce();
Bounce debouncer9 = Bounce();
Bounce debouncer10 = Bounce();
Bounce debouncer11 = Bounce();
Bounce debouncer12 = Bounce();
Bounce debouncer13 = Bounce();
Bounce debouncer14 = Bounce();
Bounce debouncer15 = Bounce();
Bounce debouncer16 = Bounce();
Bounce debouncer17 = Bounce();
Bounce debouncer18 = Bounce();
Bounce debouncer19 = Bounce();
Bounce debouncer20 = Bounce();
Bounce debouncer21 = Bounce();
Bounce debouncer22 = Bounce();
Bounce debouncer23 = Bounce();
Bounce debouncer24 = Bounce();
Bounce debouncer25 = Bounce();
Bounce debouncer26 = Bounce();
Bounce debouncer27 = Bounce();
Bounce debouncer28 = Bounce();
Bounce debouncer29 = Bounce();
Bounce debouncer30 = Bounce();
Bounce debouncer31 = Bounce();
Bounce debouncer32 = Bounce();
Bounce debouncer33 = Bounce();
Bounce debouncer34 = Bounce();
Bounce debouncer35 = Bounce();
Bounce debouncer36 = Bounce();
Bounce debouncer37 = Bounce();
Bounce debouncer38 = Bounce();
Bounce debouncer39 = Bounce();
Bounce debouncer40 = Bounce();

void before() { 

  //Dla przekaznikow sterowanych z arduino
  for (int sensor=1, pin=RELAY_1; sensor<=NUMBER_OF_RELAYS;sensor++, pin++) {
    // Then set relay pins in output mode
    pinMode(pin, OUTPUT);   
    // Set relay to last known state (using eeprom storage) 
    digitalWrite(pin, loadState(sensor)?RELAY_ON:RELAY_OFF);
  }
/*
  //Dla przekaznikow sterowanych z expander1
 for (int sensor=23, pin=ex1RELAY_1; sensor<=ex1NUMBER_OF_RELAYS;sensor++, pin++) {
    // Then set relay pins in output mode
    expander1.pinMode(pin, OUTPUT);   
    // Set relay to last known state (using eeprom storage) 
    expander1.digitalWrite(pin, loadState(sensor)?RELAY_ON:RELAY_OFF);
  }

 //Dla przekaznikow sterowanych z expander2
 for (int sensor=31, pin=ex2RELAY_1; sensor<=ex2NUMBER_OF_RELAYS;sensor++, pin++) {
    // Then set relay pins in output mode
    expander2.pinMode(pin, OUTPUT);   
    // Set relay to last known state (using eeprom storage) 
    expander2.digitalWrite(pin, loadState(sensor)?RELAY_ON:RELAY_OFF);
  }*/
}

void setup() { 
  delay(10000);

  // expander1.begin(0x38);
  // expander2.begin(0x38);
  
  Serial1.begin(9600);
  
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);
  pinMode(BUTTON3_PIN, INPUT_PULLUP);
  pinMode(BUTTON4_PIN, INPUT_PULLUP);
  pinMode(BUTTON5_PIN, INPUT_PULLUP);
  pinMode(BUTTON6_PIN, INPUT_PULLUP);
  pinMode(BUTTON7_PIN, INPUT_PULLUP);
  pinMode(BUTTON8_PIN, INPUT_PULLUP);
  pinMode(BUTTON9_PIN, INPUT_PULLUP);
  pinMode(BUTTON10_PIN, INPUT_PULLUP);
  pinMode(BUTTON11_PIN, INPUT_PULLUP);
  pinMode(BUTTON12_PIN, INPUT_PULLUP);
  pinMode(BUTTON13_PIN, INPUT_PULLUP);
  pinMode(BUTTON14_PIN, INPUT_PULLUP);
  pinMode(BUTTON15_PIN, INPUT_PULLUP);
  pinMode(BUTTON16_PIN, INPUT_PULLUP);

  for (int pin=BUTTON17_PIN, licznik=1; licznik<=25; licznik++, pin++) {
    pinMode(pin, INPUT_PULLUP); 
  }

  setupDebouncer(debouncer, BUTTON_PIN);
  setupDebouncer(debouncer2, BUTTON2_PIN);
  setupDebouncer(debouncer3, BUTTON3_PIN);
  setupDebouncer(debouncer4, BUTTON4_PIN);
  setupDebouncer(debouncer5, BUTTON5_PIN);
  setupDebouncer(debouncer6, BUTTON6_PIN);
  setupDebouncer(debouncer7, BUTTON7_PIN);
  setupDebouncer(debouncer8, BUTTON8_PIN);
  setupDebouncer(debouncer9, BUTTON9_PIN);
  setupDebouncer(debouncer10, BUTTON10_PIN);
  setupDebouncer(debouncer11, BUTTON11_PIN);
  setupDebouncer(debouncer12, BUTTON12_PIN);
  setupDebouncer(debouncer13, BUTTON13_PIN);
  setupDebouncer(debouncer14, BUTTON14_PIN);
  setupDebouncer(debouncer15, BUTTON15_PIN);
  setupDebouncer(debouncer16, BUTTON16_PIN);
  setupDebouncer(debouncer17, BUTTON17_PIN);
  setupDebouncer(debouncer18, BUTTON18_PIN);
  setupDebouncer(debouncer19, BUTTON19_PIN);
  setupDebouncer(debouncer20, BUTTON20_PIN);
  setupDebouncer(debouncer21, BUTTON21_PIN);
  setupDebouncer(debouncer22, BUTTON22_PIN);
  setupDebouncer(debouncer23, BUTTON23_PIN);
  setupDebouncer(debouncer24, BUTTON24_PIN);
  setupDebouncer(debouncer25, BUTTON25_PIN);
  setupDebouncer(debouncer26, BUTTON26_PIN);
  setupDebouncer(debouncer27, BUTTON27_PIN);
  setupDebouncer(debouncer28, BUTTON28_PIN);
  setupDebouncer(debouncer29, BUTTON29_PIN);
  setupDebouncer(debouncer30, BUTTON30_PIN);
  setupDebouncer(debouncer31, BUTTON31_PIN);
  setupDebouncer(debouncer32, BUTTON32_PIN);
  setupDebouncer(debouncer33, BUTTON33_PIN);
  setupDebouncer(debouncer34, BUTTON34_PIN);
  setupDebouncer(debouncer35, BUTTON35_PIN);
  setupDebouncer(debouncer36, BUTTON36_PIN);
  setupDebouncer(debouncer37, BUTTON37_PIN);
  setupDebouncer(debouncer38, BUTTON38_PIN);
  setupDebouncer(debouncer39, BUTTON39_PIN);
  setupDebouncer(debouncer40, BUTTON40_PIN);

  //presentation();
}

void presentation()  
{   
  // Send the sketch version information to the gateway and Controller
  sendSketchInfo("Relay", "1.2");

  for (int sensor=1, pin=RELAY_1; sensor<=NUMBER_OF_RELAYS;sensor++, pin++) {
    // Register all sensors to gw (they will be created as child devices)
    present(sensor, S_LIGHT);
  }
/*  for (int sensor=23, pin=ex1RELAY_1; sensor<=ex1NUMBER_OF_RELAYS;sensor++, pin++) {
    // Register all sensors to gw (they will be created as child devices)
    present(sensor, S_LIGHT);
  }
   for (int sensor=31, pin=ex2RELAY_1; sensor<=ex2NUMBER_OF_RELAYS;sensor++, pin++) {
    // Register all sensors to gw (they will be created as child devices)
    present(sensor, S_LIGHT);
  }*/
 
}

void loop() { 
  // Send locally attached sensor data here 
  checkSwitch(debouncer, msg, RELAY_1, 1);
  checkSwitch(debouncer2, msg2, RELAY_2, 2);
  checkSwitch(debouncer3, msg3, RELAY_3, 3);
  checkSwitch(debouncer4, msg4, RELAY_4, 4);
  checkSwitch(debouncer5, msg5, RELAY_5, 5);
  checkSwitch(debouncer6, msg6, RELAY_6, 6);
  checkSwitch(debouncer7, msg7, RELAY_7, 7);
  checkSwitch(debouncer8, msg8, RELAY_8, 8);
  checkSwitch(debouncer9, msg9, RELAY_9, 9);
  checkSwitch(debouncer10, msg10, RELAY_10, 10);
  checkSwitch(debouncer11, msg11, RELAY_11, 11);
  checkSwitch(debouncer12, msg12, RELAY_12, 12);
  checkSwitch(debouncer13, msg13, RELAY_13, 13);
  checkSwitch(debouncer14, msg14, RELAY_14, 14);
  checkSwitch(debouncer15, msg15, RELAY_15, 15);
  checkSwitch(debouncer16, msg16, RELAY_16, 16);
  checkSwitch(debouncer17, msg17, RELAY_17, 17);
  checkSwitch(debouncer18, msg18, RELAY_18, 18);
  checkSwitch(debouncer19, msg19, RELAY_19, 19);
  checkSwitch(debouncer20, msg20, RELAY_20, 20);
  checkSwitch(debouncer21, msg21, RELAY_21, 21);
  checkSwitch(debouncer22, msg22, RELAY_22, 22);
/*  
  checkSwitch(debouncer23, msg23, ex1RELAY_1, 23, &expander1);
  checkSwitch(debouncer24, msg24, ex1RELAY_2, 24, &expander1);
  checkSwitch(debouncer25, msg25, ex1RELAY_3, 25, &expander1);
  checkSwitch(debouncer26, msg26, ex1RELAY_4, 26, &expander1);
  checkSwitch(debouncer27, msg27, ex1RELAY_5, 27, &expander1);
  checkSwitch(debouncer28, msg28, ex1RELAY_6, 28, &expander1);
  checkSwitch(debouncer29, msg29, ex1RELAY_7, 29, &expander1);
  checkSwitch(debouncer30, msg30, ex1RELAY_8, 30, &expander1);
  checkSwitch(debouncer31, msg31, ex2RELAY_1, 31, &expander2);
  checkSwitch(debouncer32, msg32, ex2RELAY_2, 32, &expander2);
  checkSwitch(debouncer33, msg33, ex2RELAY_3, 33, &expander2);
  checkSwitch(debouncer34, msg34, ex2RELAY_4, 34, &expander2);
  checkSwitch(debouncer35, msg35, ex2RELAY_5, 35, &expander2);
  checkSwitch(debouncer36, msg36, ex2RELAY_6, 36, &expander2);
  checkSwitch(debouncer37, msg37, ex2RELAY_7, 37, &expander2);
  checkSwitch(debouncer38, msg38, ex2RELAY_8, 38, &expander2);
*/
}
/*
void checkSwitch(Bounce& debouncer, MyMessage& myMessage, byte relayPin, byte stateId) {
  checkSwitch(debouncer, myMessage, relayPin, stateId, NULL);
}
*/
void checkSwitch(Bounce& debouncer, MyMessage& myMessage, byte relayPin, byte stateId) {
  if (debouncer.update()) {
    // Get the update value.
    int value = debouncer.read();
    // Send in the new value.
    if (value == LOW){
       saveState(stateId, !loadState(stateId));

         digitalWrite(relayPin, loadState(stateId) ? RELAY_ON : RELAY_OFF);

       send(myMessage.set(loadState(stateId)));
    }
  }
}
/*
void checkSwitch(Bounce& debouncer, MyMessage& myMessage, byte relayPin, byte stateId, PCF8574* expander) {
  if (debouncer.update()) {
    // Get the update value.
    int value = debouncer.read();
    // Send in the new value.
    if (value == LOW){
       saveState(stateId, !loadState(stateId));
       if (expander == NULL) {
         digitalWrite(relayPin, loadState(stateId) ? RELAY_ON : RELAY_OFF);
       } else {
        expander->digitalWrite(relayPin, loadState(stateId) ? RELAY_ON : RELAY_OFF);
       }
       send(myMessage.set(loadState(stateId)));
    }
  }
}
*/

void setupDebouncer(Bounce& debouncer, byte buttonPin) {
  debouncer.attach(buttonPin);
  debouncer.interval(5);
}

void receive(const MyMessage &message) {
  // We only expect one type of message from controller. But we better check anyway.
  if (message.type==V_LIGHT) {
     // Change relay state
     if (message.sensor < 23) {
        digitalWrite(message.sensor-1+RELAY_1, message.getBool()?RELAY_ON:RELAY_OFF);
     } /*else if (message.sensor < 31) {
        expander1.digitalWrite(message.sensor-23, message.getBool()?RELAY_ON:RELAY_OFF);
     } else {
        expander2.digitalWrite(message.sensor-31, message.getBool()?RELAY_ON:RELAY_OFF);
     }*/
     // Store state in eeprom
     saveState(message.sensor, message.getBool());
     // Write some debug info
     Serial.print("Incoming change for sensor:");
     Serial.print(message.sensor);
     Serial.print(", New status: ");
     Serial.println(message.getBool());
   } 
}
