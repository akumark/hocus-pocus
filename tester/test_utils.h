#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#define MAX_TESTS 5
#include "common.h"
#include "encoder.h"
#include "decoder.h"

FILE* grader;
int cur_test=1;

float score=0.0;
float overall_score=0.0;

void sig_handler(int sig);
char *ch;
char *ch_exp;
char* get_expected(FILE *sample){
	int i=0;	
	while (1) {      
		*(ch_exp+i) = fgetc(sample);
		if( feof(sample) )
		{ 
			break ;
		}
		i++;
	}
        //fprintf(grader, "length %d", i);
	return ch_exp;
}

char decodeChar_test(char *b){
    // TODO Implement me!

	if(b == NULL)
	{
		return -1;
	}
	int i, j;
	int index = 0;
	for(i = 0, j = 5; i < 6 && j >=0 ; i++, j--)
	{
		int k = 1 << j;
		
		if(b[i] == '1')
		{
			index = index + k;
		}
	}
			
	return MAPPING[index];
}


int extractBit_for_test(char c, int index){
    // TODO Implement me!
	int value = (c >> index) & 0x1;
	
	return value;
	
}


#define TEST_CONDITION(cond, addition, category, message)   \
{ \
    if(cond==1){ \
        overall_score += addition; \
        score += addition; \
        fprintf(grader, "+%.1f:\t%s\t%s\n", addition, category, message); \
    } else {\
        fprintf(grader, "+%.1f:\t%s\t%s\n", 0.0, category, message); \
    } \
}
