/**
 * THIS FILE MAY BE USED FOR TEST CODE. IT WILL NOT BE COLLECTED
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "common.h"
#include "encoder.h"
#include "decoder.h"

int main(int argc, char *argv[]){
  char ch;
  double score = 0.0;
  char ch_arr[6] = {'0', '1', '1', '0', '1', '0'};
  char ch_arr1[6] = {'1', '0', '1', '0', '1', '1'};
  ch = decodeChar(ch_arr);
  if (ch == MAPPING[26])
     score = score + 0.5;

  printf("Expected Answer for decodeChar {'0', '1', '1', '0', '1', '0'}: %c\n", MAPPING[26]);
  printf("Your Output: %c\n", ch);
  ch = decodeChar(ch_arr1);
  if (ch == MAPPING[43])
     score = score + 0.5;

  printf("Expected Answer for decodeChar {'1', '0', '1', '0', '1', '1'}: %c\n", MAPPING[43]);
  printf("Your Output: %c\n", ch);
  printf("Your score for the decodeChar part of the submission: %f\n", score);
  return 0;
}
