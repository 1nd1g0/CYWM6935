/*
 * CypressTest -- Example for Cypress CYWM6935 Library
 *
 * Based on code written by Miguel A. Vallejo, Jason Hecker, and Richard Ulrich <richi@paraeasy.ch>
 * Author       :  Leigh L. Klotz, Jr. WA5ZNU
 * License      :  GPL 3.0 http://opensource.org/licenses/gpl-3.0
 */


/*
 * Arduino Pin usage
 * 13 SPI SCLK
 * 12 SPI MISO -> data from devices to Arduino 
 * 11 SPI MOSI -> data from Arduino to devices
 * 10 SPI SS   -> must be output
 *  9 
 *  8 
 *  7 
 *  6 RADIO SS
 *  5 RADIO RESET
 *  4 
 *  3
 *  2 
 *  1 TX
 *  0 TX
 */

/**
 * Cypress RADIO module 12-pin connector pins
 * Note that VCC=logic=3.3v
 * Name:    GND VCC  IRQ  RESET MOSI SS SCK MISO GND PD
 * Pin:     1   2    3    4     5    6  7   8    9   10
 * Arduino: GND 3.3v NC   D5    D11  D6 D13 D12  GND PULLUP
 */

#include <CYWM6935.h>
#include <SPI.h>

#define RADIO_RESET 5
#define RADIO_SS 6
#define SPI_SS 10

#define CLOCK_RADIO SPI_CLOCK_DIV64

// From 2400 to 2500 MHz 
#define NBINS 100

CYWM6935 radio(RADIO_RESET, RADIO_SS);

void setup()   
{
  Serial.begin(57600);

  SPI.begin();
  SPI.setClockDivider(CLOCK_RADIO);
  // Send most significant bit first when transferring a byte.
  SPI.setBitOrder(MSBFIRST);
  // Base value of clock is 0, data is captured on clock’s rising edge.
  SPI.setDataMode(SPI_MODE0);

  radio.init();

}

void loop() {
  for (byte i=0; i<NBINS; i++) {
    byte n = radio.RSSI_peak(i, 2);
    if (n != 0) {
      Serial.print(i);
      Serial.print(" ");
      Serial.println(n);
    }
  }
}
