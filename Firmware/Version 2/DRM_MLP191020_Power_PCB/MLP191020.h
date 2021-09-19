/***************************************************************************************************************************/
/*
    A simple library that reads an MLP191020 - 1-channel CT sesnor boards
    Based On:   EmonLib https://github.com/openenergymonitor/EmonLib
    Auther:     David Mottram
    Updated:    4th September 2021
*/
/***************************************************************************************************************************/

#ifndef MLP191020_Lib
#define MLP191020_Lib

// check of legacy IDE
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class MLP191020
{
  public:

    MLP191020(double _ICAL);
    double power_sample();

  private:

    #define Samples_Taken 400                                   // sample to be taken per channel, 1000 is approx 100mS or 5 cycles @ 50Hz
    const float Calibration = 1;                                // calibration value
    const float Volts_Conv = ((2.048 / 0.512) / Calibration);   // volts conversion value A/D 12-bit

    #define Mux_delay 500                                       // delay in uS to allow mux to settle
    #define AD_delay 1000                                       // A/D delay in uS 

    // new bits
    double ICAL;
    int sampleI;                                                // sample_ holds the raw analog read value

    double offsetI = 320;                                       // low-pass filter output
    double Irms;                                                // useful value variables
    double filteredI;                                           // filtered_ is the raw analog value minus the DC offset
    double sqI, sumI;                                           // sq = squared, sum = Sum
    #define SupplyVoltage 3.3                                   // supply voltage 3.3V
    #define ADC_COUNTS 1024                                     // 10-bit A/D

};
#endif
