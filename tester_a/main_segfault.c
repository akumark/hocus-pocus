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
  decodeChar(NULL);
  printf("Segfault check passed: 1.0\n");
  return 0;
}
