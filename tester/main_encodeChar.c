/**
 * THIS FILE MAY BE USED FOR TEST CODE. IT WILL NOT BE COLLECTED
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "common.h"
#include "encoder.h"
#include "decoder.h"
#include "test_utils.h"

void test_binaryToCode(){
	FILE *F_in = fopen("sample_binary.txt", "r");
	FILE *F_out = fopen("output_bintocode.txt", "w");
	char *expected=get_expected(F_in);
	char temp;
	fclose(F_in);
	F_in = fopen("sample_binary.txt", "r");
	int i=0;
	binaryToCode(F_in, F_out, 1);
	fflush(F_in);
	fflush(F_out);
	F_out = fopen("output_bintocode.txt", "r");
	while (1) {      
		temp = fgetc(F_out);
		if( feof(F_out) || i==599 )
		{ 
			break ;
		}
                if(extractBit_for_test(temp, 1))
			*(ch+i)='1';
		else
			*(ch+i)='0';
		i++;
	}
	TEST_CONDITION(!strncmp(ch, expected, 504), 4.0,
                   "binaryToCode", " ");
	fprintf(grader, "Expected Extracted Binary Output from the encoded file: \n");
	for (int j=0; j<504;j++)
		fprintf(grader, "%c", expected[j]);
	fprintf(grader, "\nExtracted Binary Output from your encoded file: \n");
	for (int j=0; j<i;j++)
		fprintf(grader, "%c", ch[j]);
	fprintf(grader, "\n\nYour score for binaryToCode: %.1f\n", score);
}



void test_textToBinary(){
	FILE *F_in = fopen("input.txt", "r");
	FILE *F_out = fopen("output.txt", "w");
	FILE *F_expect = fopen("sample_binary.txt", "r");
	char *expected=get_expected(F_expect);
	int i=0;	
	textToBinary(F_in, F_out);
	fflush(F_in);
	fflush(F_out);
	fclose(F_expect);
	F_out = fopen("output.txt", "r");
	while (1) {      
		*(ch+i) = fgetc(F_out);
		if( feof(F_out) || i==599 )
		{ 
			break ;
		}
		i++;
	}
	TEST_CONDITION(!strncmp(ch, expected, 504), 4.0,
                   "textToBinary", " ");
	fprintf(grader, "Expected Output: \n");
	for (int j=0; j<504;j++)
		fprintf(grader, "%c", expected[j]);
			fprintf(grader, "\nYour Output: \n");
	for (int j=0; j<i;j++)
		fprintf(grader, "%c", ch[j]);
	fprintf(grader, "\n\nYour score for textToBinary: %.1f\n", score);
}

void test_encodeChar(){
    char a, *ch;    
    a='d';
    ch = encodeChar(a);
//    fprintf(grader, "%s\n", ch);
    TEST_CONDITION(!strncmp(ch, "000011", 6), 2.0,
                   "encodeChar", "encodeChar('d') should return 000011");

    a='1';
    ch = encodeChar(a);
    TEST_CONDITION(!strncmp(ch, "011010", 6), 2.0,
                   "encodeChar", "encodeChar('1') should return 011010");
//    fprintf(grader, "%s\n", ch);
    fprintf(grader, "\n\nYour score for encodeChar: %.1f\n", score);

}

void test_implantBit() {
    char a, ch;
    a='D';
    ch = implantBit(a, 0, 2);
    //fprintf(grader, "%ch\n", ch);
    TEST_CONDITION((ch=='@'), 2.0,
                   "implantBit", "implantBit('d', 0, 2) should return '@'");

    a='1';
    ch = implantBit(a, 1, 1);
    TEST_CONDITION((ch=='3'), 2.0,
                   "implantBit", "implantBit('1', 1, 1) should return '3'");
    //fprintf(grader, "%ch\n", ch);
    fprintf(grader, "\n\nYour score for implantBit: %.1f\n", score);
}

void test_encodeFile()
{
	int i=0;
        char *final_ch=malloc(sizeof(char)*84);
	char temp_ch[6];
	FILE *F_expect = fopen("input.txt", "r");
	char *expected=get_expected(F_expect);
	fclose(F_expect);
	encodeFile("input.txt", "encode_intermediate.txt", "encode_final.txt", 1);
	FILE *F_out = fopen("encode_final.txt", "r");
	while (1) {      
		char temp = fgetc(F_out);
		if( feof(F_out) || i==599 )
		{ 
			break ;
		}
                if(extractBit_for_test(temp, 1))
			*(ch+i)='1';
		else
			*(ch+i)='0';
		i++;
	}
	i = i/6;
	for (int k = 0; k < i; k++) {
		for (int j = 0; j < 6; j++)
			temp_ch[j]=*(ch+k*6+j);
		*(final_ch+k)=(char)decodeChar_test(temp_ch);
	}


	TEST_CONDITION(!strncmp(final_ch, expected, 84), 18.0,
                   "encodeFile", " ");
	fprintf(grader, "Expected Output after decoding the encoded file: \n");
	for (int j=0; j<84;j++)
		fprintf(grader, "%c", expected[j]);
	fprintf(grader, "\nOutput after decoding your encoded file: \n");
	for (int j=0; j<i;j++)
		fprintf(grader, "%c", final_ch[j]);
	fprintf(grader, "\nYour score for encodeFile: %.1f\n", score);
        if (overall_score != 18.0)
		fprintf(grader, "\nReverting to partial credits\n");

}
void do_test_case(int i) {
	alarm(10);
	if (overall_score == 18.0)
		return;
	switch(i) {
		case 2:
			test_encodeChar();
			break;
		case 3:
			test_implantBit();
			break;
		case 4:
			test_textToBinary();
			break;
		case 5:
			test_binaryToCode();
			break;
		case 1:
			test_encodeFile();
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
		fprintf(grader, "\nYour overall score for encode section is: %.1f / 18.0\n", overall_score);
		fprintf(grader, "\n=========================================================================\n");
	}
}

char* name_test_case(int i){
	switch(i) {
		case 2:
			return "encodeChar";
		case 3:
			return "implantBit";
		case 4:
			return "textToBinary";
		case 5:
			return "binaryToCode";
		case 1:
			return "encodeFile";
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
    grader=fopen("grader_output.txt","w");
    fprintf(grader, "The files used for testing are present at /home/linux/ieng6/cs30f/public/hw3_feedback/test_final\n");
    fprintf(grader, "The maximum scores for the encoder and decoder C programs are 18.0 each and for the ARM decoder program is 30.0\n");
    fprintf(grader, "This combined with your checkpoint makes it a total of 70.0\n\n");
    fprintf(grader, "You can contend the grades the same way you did for PA3 checkpoint:\n");
    fprintf(grader, "Folks with last name from A to G please contact Ivan: ihaung@ucsd.edu\n");
    fprintf(grader, "Folks with last name from H to L please contact Jorel: jorel.ucsd@gmail.com\n");
    fprintf(grader, "Folks with last name from M to S please contact Nima: nganjehloo@gmail.com\n");
    fprintf(grader, "Folks with last name from T to Z please contact Aravind: akumark@eng.ucsd.edu\n\n");
    fprintf(grader, "If your encoder program works end to end, you get full score. Else each function is individually checked and partial score is awarded - 4.0 per function\n");
    fprintf(grader, "If your decoder program works end to end, you get full score. Else each function is individually checked and partial score is awarded - 4.0 per function\n");
    fprintf(grader, "If your decoder ARM program works end to end, you get full score. Else each function is individually checked and partial score is awarded - 6.0 per function\n");
    fprintf(grader, "Your overall score for each of the 3 sections are below in this feedback file.\n");
    fprintf(grader, "If you did not receive any credits for one of the 3 sections, your code might not have compiled for that section. Please check the makefile logs.\n");
    fprintf(grader, "Scores will be updated in gradescope a little later!\n");
    fprintf(grader, "\n");
    fprintf(grader, "\n=========================================================================\n");
    fflush(NULL);
    do_all_tests();

    fflush(grader);
    fflush(stdout);
    return 0;
}
