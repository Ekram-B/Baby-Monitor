/**************************************************************
 * Blynk is a platform with iOS and Android apps to control
 * Arduino, Raspberry Pi and the likes over the Internet.
 * You can easily build graphic interfaces for all your
 * projects by simply dragging and dropping widgets.
 *
 *   Downloads, docs, tutorials: http://www.blynk.cc
 *   Sketch generator:           http://examples.blynk.cc
 *   Blynk community:            http://community.blynk.cc
 *   Social networks:            http://www.fb.com/blynkapp
 *                               http://twitter.com/blynk_app
 *
 * Blynk library is licensed under MIT license
 * This example code is in public domain.
 *
 **************************************************************
 * This example runs directly on NodeMCU.
 *
 * Note: This requires ESP8266 support package:
 *   https://github.com/esp8266/Arduino
 *
 * Please be sure to select the right NodeMCU module
 * in the Tools -> Board menu!
 *
 * For advanced settings please follow ESP examples :
 *  - ESP8266_Standalone_Manual_IP.ino
 *  - ESP8266_Standalone_SmartConfig.ino
 *  - ESP8266_Standalone_SSL.ino
 *
 * Change WiFi ssid, pass, and Blynk auth token to run :)
 *
 **************************************************************/

/* Header files */
#define BLYNK_PRINT Serial    
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>

/* Directives */
#define MY_BAUD_RATE 9600
#define MY_ESP8266_SSID "SM-G900W8_2790"
#define MY_ESP8266_PASSWORD "aqgo7577"
#define VIRTUAL_ANALOG_PIN 0

/* Pin outs for board - already defined
*static const uint8_t LED_BUILTIN = 2;
*static const uint8_t BUILTIN_LED = 2;
*static const uint8_t D0   = 16;
*static const uint8_t D1   = 5;
*static const uint8_t D2   = 4;
*static const uint8_t D3   = 0;
*static const uint8_t D4   = 2;
*static const uint8_t D5   = 14;
*static const uint8_t D6   = 12;
*static const uint8_t D7   = 13;
*static const uint8_t D8   = 15;
*static const uint8_t RX   = 3;
*static const uint8_t TX   = 1;
*/

/* Global variables */

/* Authenticator Token */
char auth[] = "37c9b92232284743b4946aa1ae4636b8";


/* Defining the A0 port */
const int rcvpin = A0;

/* Defining the timer */
SimpleTimer timer;

/* Routines */
/*
 * The timer event that is called per every
 * time clock tick.
 */
void myTimerEvent()
{
 Blynk.virtualWrite(V5, (unsigned int) analogRead(rcvpin));
}
/*
 * Routine Name: setup() - no args
 * Description: Set ups the Baud rate over which
 * we will communicate between the app and the wifi
 * module. The Baud rate is defined to 9600 Baud.  We
 * also init the framework with provided
 * credentials.
 */ 
void setup()
{
  Serial.println("Welcome to The Baby Monitor Project");
  /* Define Baud rate for USB protocol*/  
  Serial.begin(MY_BAUD_RATE);
  delay(10);
  /* Connect to wifi network and Blynk server */
  Blynk.begin(auth ,MY_ESP8266_SSID, MY_ESP8266_PASSWORD);
   while (Blynk.connect() == false) {
      Serial.println("failed to connect to the internet");
  }
  pinMode(rcvpin,INPUT);
  timer.setInterval(1000L, myTimerEvent);
}



/*
 * Routine Name: Loop() - no args
 * Description: Main program with which
 * we loop over throughout the lifetime of the 
 * program. 
 */
 
void loop()
{
        Blynk.run();
        timer.run();
     
}

