/***************************************************************************************************************************/
/*
    A simple library that reads an MLP191020 - 1-channel CT sesnor boards
    Based On:   EmonLib https://github.com/openenergymonitor/EmonLib
    Auther:     David Mottram
    Updated:    4th September 2021
*/
/********************************************************************************************************************************/

#include "Arduino.h"
#include "MLP191020.h"

// ------------------------------------------------------------------------------------------------------------------------
// constructor
// ------------------------------------------------------------------------------------------------------------------------
MLP191020::MLP191020(double _ICAL) {

  ICAL = _ICAL;

} // end of function


/*
  take several samples and return result
*/
double MLP191020::power_sample() {

  // reset accumulators
  sumI = 0;


  // A/D engine
  for (unsigned int zz = 0; zz < Samples_Taken; zz++) {
    
    // sample A/D value
    sampleI = analogRead(A0);

    // delay to slow A/D reading speed
    delayMicroseconds(AD_delay);

    // digital low pass filter extracts the 1.65 V (0-3.3V) dc offset, stored as offsetI.
    offsetI = (offsetI + (sampleI - offsetI) / 1024);

    // then subtract this - signal is now centered on 0 counts.
    filteredI = sampleI - offsetI;

    // Root-mean-square method current
    // 1) square current values
    sqI = filteredI * filteredI;
    // 2) sum (add sqI to sumI)
    sumI += sqI;

  } // end for samples loop

  // ICAL=1500 - SupplyVoltage = 3.3V - ADC_COUNTS = 1024
  double I_RATIO = ICAL * (SupplyVoltage / ADC_COUNTS);

  // Number_of_Samples = 400
  Irms = I_RATIO * sqrt(sumI / Samples_Taken);

  //--------------------------------------------------------------------------------------

  return Irms;

} // end of function
