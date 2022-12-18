/*
 "Implementation of driver for Touch sensor Interface on the FRDM-KL25Z development board"  
 By Ashfaq Khan*/

#ifndef TSI_h
#define TSI_h
#include<stdbool.h>

void configure_TSI();
void start_scan();
_Bool determine_scan_complete();
int extract_result();

#endif
