#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "test_utils.h"

void test_extractBit() {
  char ch;
  double score = 0.0;
  ch = extractBit((char)2, 1);
  //fprintf(grader, "%ch\n", ch);
  TEST_CONDITION((ch==1), 2.0,
		  "extractBit", "extractBit((char)2, 1) should return 1");
  ch = extractBit((char)32, 2);
  TEST_CONDITION((ch==0), 2.0,
		  "extractBit", "extractBit((char)32, 2) should return 0");

  //fprintf(grader, "%ch\n", ch);
  fprintf(grader, "Your score for extractBit: %.1f\n", score);
}

void test_decodeChar() {
  char ch;
  double score = 0.0;
  char ch_arr[6] = {'0', '1', '1', '0', '1', '0'};
  char ch_arr1[6] = {'1', '0', '1', '0', '1', '1'};
  ch = decodeChar(ch_arr);
  TEST_CONDITION((ch==MAPPING[26]), 2.0,
		  "decodeChar", "decodeChar({'0', '1', '1', '0', '1', '0'}) should return 1");
  ch = decodeChar(ch_arr1);
  TEST_CONDITION((ch==MAPPING[43]), 2.0,
		  "decodeChar", "decodeChar({'1', '0', '1', '0', '1', '1'}) should return '");
  fprintf(grader, "Your score for decodeChar: %.1f\n", score);

}

void test_codeToBinary() {
	FILE *F_in = fopen("in_codetobin.txt", "r");
	FILE *F_out = fopen("out_codetobin.txt", "w");
	FILE *F_expect = fopen("sample_binary.txt", "r");
	char *expected=get_expected(F_expect);
	int i=0;	
	codeToBinary(F_in, F_out, 1);
	fflush(F_in);
	fflush(F_out);
	fclose(F_expect);
	F_out = fopen("out_codetobin.txt", "r");
	while (1) {      
		*(ch+i) = fgetc(F_out);
		if( feof(F_out) || i==599 )
		{ 
			break ;
		}
		i++;
	}
	TEST_CONDITION(!strncmp(ch, expected, 504), 4.0,
                   "codeToBinary", " ");
	fprintf(grader, "Expected Output: \n");
	for (int j=0; j<504;j++)
		fprintf(grader, "%c", expected[j]);
	fprintf(grader, "\nYour Output: \n");
	for (int j=0; j<i;j++)
		fprintf(grader, "%c", ch[j]);
	fprintf(grader, "\nYour score for codeToBinary: %.1f\n", score);
}

void test_binaryToText() {
	FILE *F_in = fopen("input.txt", "r");
	FILE *F_out = fopen("output_bintotext.txt", "w");
	char *expected=get_expected(F_in);
	fclose(F_in);
	F_in = fopen("sample_binary.txt", "r");
	int i=0;
	binaryToText(F_in, F_out);
	fflush(F_in);
	fflush(F_out);
	F_out = fopen("output_bintotext.txt", "r");
	while (1) {      
		*(ch+i) = fgetc(F_out);
		if( feof(F_out) || i==599 )
		{ 
			break ;
		}
		i++;
	}
	TEST_CONDITION(!strncmp(ch, expected, 84), 4.0,
                   "binaryToText", " ");
	for (int j=0; j<84;j++)
		fprintf(grader, "%c", expected[j]);
	fprintf(grader, "\nYour Output: \n");
	for (int j=0; j<i;j++)
		fprintf(grader, "%c", ch[j]);
	fprintf(grader, "\nYour score for binaryToText: %.1f\n", score);
}

void test_decodeFile() {
	int i=0;
	FILE *F_expect = fopen("input.txt", "r");
	char *expected=get_expected(F_expect);
	fclose(F_expect);
	decodeFile("sample_bintocode.txt", "decode_intermediate.txt", "decode_final.txt", 1);
	FILE *F_out = fopen("decode_final.txt", "r");
	while (1) {      
		*(ch+i) = fgetc(F_out);
		if( feof(F_out) || i==599 )
		{ 
			break ;
		}
		i++;
        }

	TEST_CONDITION(!strncmp(ch, expected, 84), 18.0,
                   "decodeFile", " ");
	fprintf(grader, "Expected Output: \n");
	for (int j=0; j<84;j++)
		fprintf(grader, "%c", expected[j]);
	fprintf(grader, "\nYour Output: \n");
	for (int j=0; j<i;j++)
		fprintf(grader, "%c", ch[j]);
	fprintf(grader, "\nYour score for decodeFile: %.1f\n", score);
        if (overall_score != 18.0)
		fprintf(grader, "\nReverting to partial credits\n");


}
 
void do_test_case(int i) {
	alarm(10);
	if (overall_score == 18.0)
		return;
	switch(i) {
		case 2:
			test_extractBit();
			break;
		case 3:
			test_decodeChar();
			break;
		case 4:
			test_codeToBinary();
			break;
		case 5:
			test_binaryToText();
			break;
		case 1:
			test_decodeFile();
			break;
	}
	score=0.0;
        fprintf(grader, "\n=========================================================================\n");
}



void do_all_tests() {
	while (cur_test <= MAX_TESTS) {
		do_test_case(cur_test);
		++cur_test;
	}
	if (cur_test==MAX_TESTS+1) {
		fprintf(grader, "\nYour overall score for decode section is: %.1f / 18.0\n", overall_score);
		fprintf(grader, "\n=========================================================================\n");
	}
}

char* name_test_case(int i){
	switch(i) {
		case 2:
			return "extractBit";
		case 3:
			return "decodeChar";
		case 4:
			return "codeToBinary";
		case 5:
			return "binaryToText";
		case 1:
			return "decodeFile";
		default:
			return "Unknown";
	}
}



void handle_segfault();
void handle_loop();
void handle_sigabrt();

void handle_sigabrt() {
    signal(SIGSEGV, handle_segfault);
    signal(SIGALRM, handle_loop);
    signal(SIGABRT, handle_sigabrt);
 
    if (cur_test<=MAX_TESTS) { 
	    fprintf(grader, "Program had a sigabrt (glibc) for test case: %s\n", name_test_case(cur_test));
	    fprintf(grader, "\n=========================================================================\n");
    }
	++cur_test;
        fflush(grader);
        do_all_tests();
        fflush(grader);
        exit(0);
}


void handle_segfault() {
    signal(SIGSEGV, handle_segfault);
    signal(SIGALRM, handle_loop);
    signal(SIGABRT, handle_sigabrt);
 
    if (cur_test<=MAX_TESTS) { 
	    fprintf(grader, "Program segfaulted for test case: %s\n", name_test_case(cur_test));
	    fprintf(grader, "\n=========================================================================\n");
    }
	++cur_test;
        fflush(grader);
        do_all_tests();
        fflush(grader);
        exit(0);
}

void handle_loop() {
    signal(SIGSEGV, handle_segfault);
    signal(SIGALRM, handle_loop);
    signal(SIGABRT, handle_sigabrt);
 
    if (cur_test<=MAX_TESTS) { 
	    fprintf(grader, "Program has gone to an infinite loop for test case: %s\n", name_test_case(cur_test));
	    fprintf(grader, "\n=========================================================================\n");
    }
	++cur_test;
        fflush(grader);
        do_all_tests();
        fflush(grader);
        exit(0);
}




int main() {
ch_exp=malloc(sizeof(char)*600);
ch=malloc(sizeof(char)*600);
    signal(SIGSEGV, handle_segfault);
    signal(SIGALRM, handle_loop);
    signal(SIGABRT, handle_sigabrt);
    createReverseMapping();
    grader=fopen("grader_output.txt","a");
    do_all_tests();
    fflush(grader);
    return 0;
}
