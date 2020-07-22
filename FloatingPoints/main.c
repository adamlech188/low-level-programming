#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void  floatToBits(char*  bitStr, float *number); 
void  bitsToFloat(char* bitStr, int *number);
void  bitsToShort(char* bitStr, short *number);
void  extractSign(char* bitStr, short *number);
void  extractExponent(char* bitStr, short *number, bool *normal);
void  extractMantissa(char* bitStr, float *number, bool normal);
void  integerToBits(char* bitStr, int *number);
void  bitsToInt(char* bitStr, int *number);
void  printValuesForNumber(float number);


int main() {
	float number1 = 1.5f;
	printValuesForNumber(6.75f);
	printValuesForNumber(6.75765f);
	printValuesForNumber(0.0f);
	printValuesForNumber(-0.0f);
	printValuesForNumber(1.0f);
	printValuesForNumber(-1.0f);
	printValuesForNumber(6.674e-11);
	printValuesForNumber(1.0e38);
	printValuesForNumber(1.0e39);
	printValuesForNumber(1.0e-38);
	printValuesForNumber(1.0e-39);
	return 0;
}

void printValuesForNumber(float number) {
        printf("------------------------------------------------------------------------\n");
	char bitStr[33];
	floatToBits(bitStr, &number);
	printf ("Number %.5f  in bits is %s\n" , number, bitStr);
	short sign;
	extractSign(bitStr, &sign);
	printf ("Sign of number %.5f is %d\n",number,  sign); 
	short exponent;
	bool normal = true;	
	extractExponent(bitStr, &exponent, &normal);
	short binaryBias = normal? 127 : 126;
	printf ("Exponent of number %.5f is %d\n", number, exponent-binaryBias);
	float mantissa;
	extractMantissa(bitStr, &mantissa, normal);
	printf ("Mantissa  of number %.5f is %.23f\n", number, mantissa);
}

void  floatToBits(char*  bitStr, float *number) {

	int numberAsInt;
	int *pNumber = number;
	numberAsInt = *pNumber;
        int mask = 1;
	int i;
	for(i=0; i<32; i++) {
	     
	     int bit = numberAsInt&1<<i;
	     char bitchar;
	     if (bit == 0) {
		     bitchar = '0';
	     }
	     else {
		     bitchar = '1';

             }
	     bitStr[31-i]  = bitchar;
	}
	bitStr[32] ='\0';
}

void  integerToBits(char*  bitStr, int *number) {

	int numberValue=*number;
        int mask = 1;
	int i;
	for(i=0; i<32; i++) {
	     
	     int bit = numberValue&1<<i;
	     char bitchar;
	     if (bit == 0) {
		     bitchar = '0';
	     }
	     else {
		     bitchar = '1';

             }
	     bitStr[31-i]  = bitchar;
	}
	bitStr[32] ='\0';
}

void extractExponent(char* bitStr, short *number, bool *normal) {
    char expbits[17];
    memcpy(expbits, "00000000", 8);
    memcpy(expbits+8,bitStr+1, 8);
    expbits[16] = '\0';
    bitsToShort(expbits, number);
    if(*number == 0) {
	*normal = false;
    }
}


void extractMantissa(char* bitStr,  float *number, bool normal) {
    char mantissabits[24];
    memcpy(mantissabits,bitStr+9, 23);
    mantissabits[23] = '\0';
    float floatNumber = normal ? 1.0f : 0.0f;
    float reminder = 0.0f;
    int i;
    for (i=0; i<23; i++) {
	   char bit = mantissabits[i];
           if (bit == '1') {
        	float result;
		int divisor = 2<<i;
      		result = 1.0f/divisor; 		
		reminder += result;
  	   }
    }    
    *number = floatNumber + reminder;
     
}



void extractSign(char* bitStr, short *number) {
      short returnValue = 0;
      char charBit = bitStr[0];
      if(charBit == '0') {
	*number = 0;
      }
      if(charBit == '1') {
	*number = 1;       	
      } 
}




void  bitsToInt(char*  bitStr,int *number) {

	int numberAsInt = 0;
        int mask = 1;
	int i;
	for(i=0; i<32; i++) {
	     
	     char bit = bitStr[i];
	     if (bit == '1') {
		numberAsInt = numberAsInt^1<<(31-i);	
	     }
	}
	*number = numberAsInt;
	
}

void bitsToShort(char* bitStr, short *number) {
	
	int numberAsInt = 0;
        int mask = 1;
	int i;
	for(i=0; i<16; i++) {
	     
	     char bit = bitStr[i];
	     if (bit == '1') {
		numberAsInt = numberAsInt^1<<(15-i);	
	     }
	}
	*number = numberAsInt;
	

}
