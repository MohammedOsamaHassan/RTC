/*
 * BCD27Segment.h
 *
 * Created: 10/15/2023 7:19:25 PM
 *  Author: M Osama
 */ 


#ifndef BCD27SEGMENT_H_
#define BCD27SEGMENT_H_

#include "DIO.h"

void seven_seg_init (ports port);
void seven_seg_write (ports port, unsigned char val);




#endif /* BCD27SEGMENT_H_ */