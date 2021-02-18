// Adafruit IO Digital Input Example
// Tutorial Link: https://learn.adafruit.com/adafruit-io-basics-digital-input
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Todd Treece for Adafruit Industries
// Copyright (c) 2016 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.

/************************** Configuration ***********************************/

// edit the config.h tab and enter your Adafruit IO credentials
// and any additional configuration needed for WiFi, cellular,
// or ethernet clients.
#include "config.h"

/************************ Example Starts Here *******************************/

// digital pin 16
#define BUTTON_PIN A0
#define LED_PIN 13 

// button state
bool current = false;
bool last = false;
int potenVal=0;
int newPotenVal = 0;
int lastVal = -1;

// set up the 'digital' feed
// change "myFeed" to the feed name you have created in Adafruit IO
AdafruitIO_Feed *button = io.feed("button"); //New!

void setup() {

  // set button pin as an input, set led pin as output
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT); //New!

  // start the serial connection
  Serial.begin(115200);

  // wait for serial monitor to open
  while(! Serial);

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());

}

void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();
  potenVal = analogRead(BUTTON_PIN);
  newPotenVal = map(potenVal,0,179,0,120);
  //newPotenVal = potenVal;
  
  if(newPotenVal == lastVal){
    return;
  }
  
  // save the current state to the 'digital' feed on adafruit io
  Serial.print("sending button -> ");
  Serial.println(newPotenVal);

//  place your specific feed name
 button->save(newPotenVal); //New!

  // store last button state
  lastVal = newPotenVal;

  delay(10000);

}
