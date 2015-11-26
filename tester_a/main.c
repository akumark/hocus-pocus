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
  ch = extractBit((char)28, 1);
  if (ch == 0)
     score = score + 0.5;
  printf("Expected Answer for extractBit((char)28, 1): %d\n", 0);
  printf("Your Output: %d\n", ch);
  ch = extractBit((char)125, 5);
  if (ch == 1)
     score = score + 0.5;

  printf("Expected Answer for extractBit((char)125, 5): %d\n", 1);
  printf("Your Output: %d\n", ch);
  printf("Your score for the extractBit part of the submission: %f\n", score);
  return 0;
}
