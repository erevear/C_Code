#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*This program uses bit shifts to change an input decimal number into an IEEE normalized binary*/
/*This method takes in a doubleing point number and calculates a power of two that is great than in
The method returns an integer representation of the results.*/
int findPowTwo(float result) {
	//int i;
	int powTwo = 2;
	while(result > powTwo) {
		powTwo = powTwo * 2;	
	}
	if(powTwo == result) {
		powTwo = powTwo * 2;
	}
	return powTwo;
}

/*This method takes in the float, as well as the nearest power of two and writes
the binary translation of the float to the character string that is passed through 
as a pointer*/
void decimalToBinary(float result, int powTwo, char *binary) {
	//printf("power of two %d ", powTwo);
	int j = 0;
	powTwo = powTwo/2;
	double otherPowTwo = 0.5;
	double temp = result;
	int i = 0;
	while(powTwo >= 1) {
		if((result - powTwo) >= 0) {
			//printf("%c", '1');
			strcat(binary, "1");
			result = result - powTwo;
		} else {
			//printf("%c", '0');
			strcat(binary, "0");
		}
		powTwo = powTwo/2;
	}
	//printf("%c", '.');
	strcat(binary, ".");
	while(result > 0) {
		result = result * 2;
		if(result < 1) {
			//printf("%c", '0');
			strcat(binary, "0");
		} else if (result >= 1) {
			//printf("%c", '1');
			strcat(binary, "1");
			result = result - 1;
		}
		
	}
	//printf("\n");
	
}

/*This method takes in a binary represenation of the input fraction, and puts the decimal place
behind the first nonzero digit and counts how many places it has to move and returns that
number as the exponent*/
int normalize(char *binary, char *fraction) {
	int first_nonzero = 1;
	int decimal_point = 0;
	char temp[70];
	int i = 0;
	while(binary[i] != '1') {
		if(binary[i] != '.') {
			first_nonzero++;
		}
		i++;
	}
	//printf("first nonzero %d\n", first_nonzero);
	while(binary[decimal_point] != '.') {
		decimal_point++;
	}
	//printf("decimal point is in space %d\n", decimal_point);
	int j = 0;
	int k = 0;
	while(binary[j] != '\0') {
		if(binary[j] != '.') {
			temp[k] = binary[j];
			k++;
		}
		j++;
	}
	
	if(k < 23) {
		while(k <= 23) {
			temp[k] = '0';
			k++;
		}
	} else {
		temp[(23 + first_nonzero)] = '\0';
	}
	temp[k] = '\0';
	//printf("k: %d\n", k);
	strcpy(fraction, &temp[first_nonzero]);
	//printf("temp: %s\n", temp);
	return (decimal_point-first_nonzero) + 127;
}

/*This method takes in the binary representation of the exponent and ensures that it will take up
its allotted eight bits*/
void format_exponent(char *exponent) {
	int i = 0;
	char *str = (char *)malloc(8);
	while(exponent[i] != '\0' && exponent[i] != '.') {
		i++;
	}
	//strcat("0", exponent);
	int j = 0;
	while(i < 8) {
		strcat(str, "0");
		i++;
	}
	strcat(str, exponent);
	i = 0;
	while(str[i] != '\0' && str[i] != '.') {
	
		i++;
	}
	str[i] = '\0';
	strcpy(exponent, str);
	//printf("str: %s\n", str);
}

// /*This method */
// void create_sign(float num, char *sign) {
// 	if(num < 0) {
// 		strcpy(sign, "1");
// 	} else {
// 		strcpy(sign, "0");
// 	}
// }

/*This method takes in the binary representations of all of the pieces and puts them
together into the 32 bits*/
void combine(char *sign, char *exponent, char *fraction, char *floating_point) {
	strcat(floating_point, sign);
	strcat(floating_point, exponent);
	strcat(floating_point, fraction);
}

/*This method takes in the binary representation of the fraction and moves through it, either adding
the power or not, then returs the numerical representation of the fraction*/
float get_fraction(char *bin_fraction) {
	float fraction = 1.0;
	printf("fraction = %f with implied 1\n", fraction);
	float power = .5;
	int i = 0;
	while(bin_fraction[i] != '\0') {
		if(bin_fraction[i] == '1') {
			fraction = fraction + power;
			printf("fraction = %f after adding power %f\n", fraction, power);
			
		} else {
			printf("fraction = %f after adding power %f\n", fraction, power);
		}
		power = power * .5;
		i++;
	}
	
	return fraction;
}

/*This method takes in the numerical representations of the fraction and exponent and 
takes the fraction to the power represented by the exponent, then returns it*/
float apply_exponent(float fraction, int exponent) {
	int i = 0;
	printf("unbiased exponent %d\n", exponent);
	if(exponent < 0) {
		while(i > exponent) {
			fraction = fraction / 2;
			i--;
			printf("divided by 2 = %f\n", fraction);
		}
	} if(exponent > 0) {
		while(i < exponent) {
			fraction = fraction * 2;
			i++;
			printf("times 2 = %f\n", fraction);
		}
	}
	return fraction;
	//printf("after applied exponenet %f\n", fraction);
}

int main() {
	float i;
	printf("Enter a float value: ");
	scanf("%f", &i);
	printf("Your float was read as = %f\n", i);
	 char *binary = (char*)malloc(23);
	 char *fraction = (char *)malloc(23);
	 char *binary_exponent = (char *)malloc(8);
	 char *sign = (char *)malloc(1);
	 char *floating_point = (char *)malloc(32);
 	if(i < 0) {
 		strcpy(sign, "1");
 		i = i * -1;
 	} else {
 		strcpy(sign, "0");
 	}
	 int power = findPowTwo(i);
	 decimalToBinary(i, power, binary);
	 printf("binary fraction: %s\n", binary);
	 int exponent = normalize(binary, fraction);
	 printf("exponent: %d\n", exponent);
	 int exponent_power = findPowTwo(exponent);
	 decimalToBinary(exponent, exponent_power, binary_exponent);
	 format_exponent(binary_exponent);
	 printf("binary exponent %s\n", binary_exponent);
	 printf("fraction binary: %s\n", fraction);
	 combine(sign, binary_exponent, fraction, floating_point);
	 printf("floating point: %s\n", floating_point);
	 float float_fraction = get_fraction(fraction);
	 int exp = exponent - 127;
	 float decimal = apply_exponent(float_fraction, exp);
	 if(sign[0] == '1') {
		 decimal = decimal * -1;
	 }
	 printf("Final Answer %f\n", decimal);
	
}
