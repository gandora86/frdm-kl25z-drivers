/*
 "Implementation of driver functions for Touch Sensor Interface on the FRDM-KL25Z development board" 
  By Ashfaq Khan
*/

#include "TSI.h"
#include <MKL25Z4.h>



void configure_TSI()    //Configuting TSI
{

 SIM->SCGC5 |= SIM_SCGC5_TSI_MASK;
 
 TSI0->GENCS = TSI_GENCS_STM(0) | TSI_GENCS_TSIIEN(0)
		| TSI_GENCS_NSCN(1)|TSI_GENCS_PS(4)
		| TSI_GENCS_EXTCHRG(7)|TSI_GENCS_DVOLT(0)
		| TSI_GENCS_REFCHRG(4)|TSI_GENCS_MODE(0);
TSI0->GENCS |= TSI_GENCS_TSIEN(1);

}

void start_scan()       //starting scan
{
	TSI0->DATA = TSI_DATA_SWTS_MASK | TSI_DATA_TSICH(9);
}

 _Bool determine_scan_complete()
{
	return TSI0->GENCS & TSI_GENCS_EOSF_MASK;
}

int extract_result()       // Holding scan value
{
    TSI0->GENCS |= TSI_GENCS_EOSF_MASK;
	return TSI0->DATA & TSI_DATA_TSICNT_MASK;
}
