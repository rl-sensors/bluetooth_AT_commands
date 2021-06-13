#include <Arduino.h>

/* ******************************************************
 * Setup for Teensy 4.0
 *
 * HC05 RX to PIN8
 * HC05 TX to PIN 7
 * HC05 GDN to GDN
 * HD05 VCC to 3V (should work with 5V as well)
 *
 * you will need another wire connected to pin 34 of the HC05 (that's the last pin on the right - I just pushed a breadboard cable under the heatsink)
 * and connect it to PIN 20
 *
 * After uploading the code to Teensy, disconnect power to the HC05 (just pull out the lead)
 * and then connect the lead from PIN20 to PIN 34 on the HC05 (under the heatsink)
 * then connect the power to the HC05 again
 * the HC05 led should be blinking slowly (2s on, 2s off) - that means you're in the AT command mode
 *
 * !!!!!!!!!Very important when sending the AT commands you need to use CR + LF as new lines otherwise it won't work
 * I used CuteCom, selected /dev/ttyACM0, 9600 and changed the line endings to CR + LF
 * and sent the following commands:
 *  1) AT
 *  2) AT+VERSION?
 *  3) AT+UART=115200,1,0
 *
 *  Each of the commands should receive response OK (the version command should also return the version)
 *
 */

void setup()
{
  pinMode(20, OUTPUT);  // this pin will pull the HC-05 pin 34 (key pin) HIGH to switch module to AT mode
  digitalWrite(20, HIGH);
  Serial.begin(9600);
  Serial.println("Enter AT commands:");
  Serial2.begin(38400);  // HC-05 default speed in AT command more
}

void loop()
{

  // Keep reading from HC-05 and send to Arduino Serial Monitor
  if (Serial2.available()) {
    Serial.write(Serial2.read());
  }


  // Keep reading from Arduino Serial Monitor and send to HC-05
  if (Serial.available()) {
    Serial2.write(Serial.read());
  }

}