/*This program takes in data files with the ranking of the most popular baby names for the given year
sorts them, and outputs the data into a csv file*/
#include <stdio.h> 
#include <string.h>

#define MAX_NAMES_COLUMNS 15
#define MAX_NAMES_ROWS 1000
#define MAX_RANK_COLUMNS 10
#define MAX_RANK_ROWS 1001

void testNum(int *num) {
	*num += 10;
}

/*This method writes both arrays to a csv file called summary.csv; It takes in the name array, the rank array
as well as the number of names. */
void writeToFile( int (*rank)[10], int *numNames, char(*names)[15]) {
	int k, l;
	int m = 1920;
	for(k = 0; k < 1; k++) {
		for(l = 0; l < 10; l++) {
			rank[k][l] = m;
			m = m + 10;
		}
	}
	
	strcpy(names[0], "Names");
	
	FILE *outfile = fopen("summary.csv", "w");
	int j, i;
	for(j = 0; j < *numNames; j++) {
		fputs(names[j], outfile);
		fputc(' ', outfile);
		//printf("%s ", names[j]);
			for(i = 0; i < 10; i++) {
				fprintf(outfile, ",%d", rank[j][i]);
				//printf("%d ",  rank[j][i]);
			}
			fputc('\n', outfile);
			//printf("\n");
			
		}
	
}

/*This method takes in the name array, rank array, and the number of names and uses bubble sort to put
the name array and their corresponding ranks into alphabetical order*/
void sortArrays(int (*rank)[10], int *numNames, char(*names)[15]) {
	int i, j, l;
	char temp[15];
	char rank_temp[1][10];
	//printf("numbers %d ", *numNames);
	for(j = 1; j < *numNames; j++) {
		for(i = 0; i < *numNames; i++) {
			//printf("hallo");
			if(strcmp(names[i-1], names[i]) > 0) {
				strcpy(temp, names[i]);
				for(l = 0; l < 10; l++) {
					rank_temp[0][l] = rank[i][l];
				}
				strcpy(names[i], names[i-1]);
				for(l = 0; l < 10; l++) {
					rank[i][l] = rank[i-1][l];
				}
				strcpy(names[i-1], temp);
				for(l = 0; l < 10; l++) {
					rank[i-1][l] = rank_temp[0][l];
				}
			//printf("hallo %s ", names[i]);
			}
		}
    }
}

/*Prints the ranks array with their corresponding names*/
void printRankArray(int (*rank)[10], int *numNames, char(*names)[15]) {
	int j, i;
		for(j = 0; j < *numNames; j++) {
			printf("%s ", names[j]);
			for(i = 0; i < 10; i++) {
				printf("%d ",  rank[j][i]);
			}
			printf("\n");
			
		}
}

/*Prints the name array*/
void printArray(char (*names)[15], int *numNames) {
	int j;
		for(j = 0; j < *numNames; j++) {
			printf("name %s\n",  names[j]);
		}
}

/*Extracts the name from a line of input from the original file*/
char *getName(char *arr) {
	char name[15];
	int i = 0;
	
	while(arr[i] != ',') {
		name[i] = arr[i];
		i++;
	}
	return strcpy(arr, name);
	
}

/*Takes in one name and searches the name array for it. If it is there it places the rank in the appropriate
spot in the rank array; if not it adds it to the end*/
void createArrays(char *the_name, char (*names)[15], int (*rank)[10], int *numNames, int year, int name_rank, int column){
	
	//strcpy(names[*numNames], the_name);
	//int column;
	int j;
	char temp[50];
	//boolean present = false;
	int i, row = 0;
	for(i = 1; i < *numNames; i++) {
		if (strcmp(the_name, names[i]) == 0) {
			row = i;
			//*numNames -= 1;
			rank[row][column] = name_rank;
			//row = i;
			break;
		} 
		
		 
	}
	if(row == 0) {
		strcpy(names[*numNames], the_name);
		
		row = *numNames;
		
		*numNames += 1;
		rank[row][column] = name_rank;
	}
	

}



/*Takes in one file as well as the name and rank arrays, and extracts one name at a time from the file*/

void processFile(FILE *file, char (*names)[15], int (*rank)[10], int *numNames, int year, int column) {
	int j = 1;
	char s[100];
	
	
	while(j < 101 && s != NULL) {
		char s2[50];
		//gcc HW3.c -o hw3printf("here");
		fgets(s, sizeof(s2), file);
		//printf("s at j %s ", s[j]);
		strcpy(s2, getName(s));
		//printf("s at j %s\n ", s[j]);
		//printf("here3");
		
		createArrays(s2, names, rank, numNames, year, j, column);
		//*numNames += 1;
		//printf("here4");
		
		j++;
	}
	
	//printArray(s);
}

/*Opens all ten files and sends them to be processed*/
void processAllFiles(char (*names)[15], int (*rank)[10], int *numNames) {
	FILE *nineteentwenty = fopen("yob1920.txt", "r");
	processFile(nineteentwenty, names, rank, numNames, 1920, 0);
	
	FILE *nineteenthirty = fopen("yob1930.txt", "r");
	processFile(nineteenthirty, names, rank, numNames, 1930, 1);
	
	FILE *nineteenfourty = fopen("yob1940.txt", "r");
	processFile(nineteenfourty, names, rank, numNames, 1940, 2);
	
	FILE *nineteenfifty = fopen("yob1950.txt", "r");
	processFile(nineteenfifty, names, rank, numNames, 1950, 3);
	
	FILE *nineteensixty = fopen("yob1960.txt", "r");
	processFile(nineteensixty, names, rank, numNames, 1960, 4);
	
	FILE *nineteenseventy = fopen("yob1970.txt", "r");
	processFile(nineteenseventy, names, rank, numNames, 1970, 5);
	
	FILE *nineteeneighty = fopen("yob1980.txt", "r");
	processFile(nineteeneighty, names, rank, numNames, 1980, 6);
	
	FILE *nineteenninety = fopen("yob1990.txt", "r");
	processFile(nineteenninety, names, rank, numNames, 1990, 7);
	
	FILE *twothousand = fopen("yob2000.txt", "r");
	processFile(twothousand, names, rank, numNames, 2000, 8);
	
	FILE *twothousandten = fopen("yob2010.txt", "r");
	processFile(twothousandten, names, rank, numNames, 2010, 9);
	
	
	//printArray(names, numNames);
	//printRankArray(rank, numNames);
	
	
}

int main(void) {
	char myNames[MAX_NAMES_ROWS][MAX_NAMES_COLUMNS];
	int myRanks[MAX_RANK_ROWS][MAX_RANK_COLUMNS];
	int num_names = 1;
	processAllFiles(myNames, myRanks, &num_names);
	//testNum(&num_names);
	//printf("num %d ", num_names);
	//printArray(myNames);
	
	sortArrays(myRanks, &num_names, myNames);
	//printArray(myNames, &num_names);
	//printRankArray(myRanks, &num_names, myNames);
	writeToFile(myRanks, &num_names, myNames);
	
}
