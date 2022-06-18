#include <stdio.h>

#include "../hdr/common.h"
#include "../hdr/segment.h"

gpio_num_t segmentPin[8] = 
{
  SEGMENT_PIN_1,
  SEGMENT_PIN_2,
  SEGMENT_PIN_3,
  SEGMENT_PIN_4,
  SEGMENT_PIN_5,
  SEGMENT_PIN_6,
  SEGMENT_PIN_7,
  SEGMENT_PIN_8,
  
};

gpio_num_t segmentComPin[4] = 
{
  SEGMENT_COM_PIN_1,
  SEGMENT_COM_PIN_2,
  SEGMENT_COM_PIN_3,
  SEGMENT_COM_PIN_4,
  
};

unsigned int segmentNumber[10][8] = 
{
  	{ 1, 1, 1, 1, 1, 1, 1, 0 },	  // 0
		{ 0, 1, 1, 0, 0, 0, 0, 0 },	  // 1
		{ 1, 1, 0, 1, 1, 0, 1, 0 },	  // 2
		{ 1, 1, 1, 1, 0, 0, 1, 0 },	  // 3
		{ 0, 1, 1, 0, 0, 1, 1, 0 }, 	// 4
		{ 1, 0, 1, 1, 0, 1, 1, 0 }, 	// 5
		{ 1, 0, 1, 1, 1, 1, 1, 0 }, 	// 6
		{ 1, 1, 1, 0, 0, 0, 0, 0 }, 	// 7
		{ 1, 1, 1, 1, 1, 1, 1, 0 }, 	// 8
		{ 1, 1, 1, 0, 0, 1, 1, 0 }	  // 9
};

void SegmentInit()
{
  #if DEBUG
  printf("SegmentInit\n");
  #endif

  int i;

  for(i = 0; i < 4; i++) {
    gpio_set_direction(segmentComPin[i], OUTPUT);
  }

  for(i = 0; i < 8; i++) {
    gpio_set_direction(segmentPin[i], OUTPUT);
  }
}

void SegmentShow(int number, int digit)
{
  #if DEBUG
  printf("SegmentShow number : %d, digit : %d\n", number ,digit);
  #endif

  int i;

  for(i = 0; i < 4; i++) {
    if(i + 1 == digit) {
      gpio_set_level(segmentComPin[i], LOW);
    }
    else {
      gpio_set_level(segmentComPin[i], HIGH);
    }
  }

  for(i = 0; i < 8; i++) {
    if(segmentNumber[number][i] == 1) {
      printf("1 : %d\n", segmentNumber[number][i]);
    }
    else {
      printf("0 : %d\n", segmentNumber[number][i]);
    }
  }
}
