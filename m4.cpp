/*
FILE : m4.cpp
PROJECT : Major4
PROGRAMMER : Eunyoung Kim
FIRST VERSION : 2021/12/06
DECRIPTION : 

*/


#include<stdio.h>
#include <string.h>
#include<cstdlib>
#pragma warning(disable:4996)


#define kArrayLength 40
int parseLine(char resultArray[], char nameArray[], int* pScore, int* pOpponent);
int processGames(char fileName[]);


int main() {

	FILE* fp = NULL;
	char leng[kArrayLength] = { 0 };
	fp = fopen("teams.txt", "r");
	if (fp == NULL) {
		printf("Can't open teams.txt\n");

		return -1;
	}

	while (fgets(leng, sizeof leng, fp) > 0) {
		if (ferror(fp)) {
			printf("Error reading line from file\n");
			// close the file, thus creating the file
			if (fclose(fp) != 0) {
				// the closing of the file failed
				printf("Can't close file opened for reading\n");
			}

			return -2;
		} 

		int len = strlen(leng);
		if (leng[len - 1] == '\n') {
			leng[len - 1] = 0;
		}
		if (strlen(leng) == 0) {
			continue;
		} 

		processGames(leng);
		
		

	}


	// close the file, thus creating the file
	if (fclose(fp) != 0) {
		// the closing of the file failed
		printf("Can't close file opened\n");

		return -3;
	}

	return 0;
}


// check error
int processGames(char fileName[]){

	FILE* fp1 = NULL;
	char leng01[kArrayLength] = { 0 };
	int test02 = 0;
	char blbl[kArrayLength] = { 0 };
	double score01 = 0;
	double score02 = 0;
	double score03 = 0;
	int win = 0;
	int lost = 0;
	int tied = 0;
	int check = -1;
	int check01 = 0;
	if (fileName == NULL) {
		return check;
	}
	else {

		strcpy(leng01, fileName);
		fp1 = fopen(leng01, "r");
		if (fp1 == NULL) {
			printf("Warning: Can't open %s Skipping team.\n\n", leng01);

			return -4;
		}
		printf("Processing %s: \n", leng01);
		while (fgets(leng01, sizeof leng01, fp1) > 0) {
			if (ferror(fp1)) {
				printf("Error reading line from file\n");
				if (fclose(fp1) != 0) {
					printf("Can't close file opened for reading\n");
				}

				return -2;
			}

			if ((strchr(leng01, ',') == 0) || (strchr(leng01, '-') == 0)) {
				printf("\tWarning: malformed line. Skipping game.\n");
				continue;
			}


			if (strlen(leng01) == 1) {

				continue;
			}
			else {
				char number[kArrayLength] = { 0 };
				char name[kArrayLength] = { 0 };
				int scoreNumber = 0;
				int opponent = 0;
				strcpy(number, leng01);
				parseLine(number, name, &scoreNumber, &opponent);

				if (parseLine(number, name, &scoreNumber, &opponent) == -1) {
					printf("\tThere is no game result\n");
				}
				else {
					for (int i = 0; i < fileName[i]; i++) {

						if ((fileName[i] >= 'A' && fileName[i] <= 'Z') || (fileName[i] >= 'a' && fileName[i] <= 'z') || fileName[i] == ' ') {
							test02 = fileName[i];
							blbl[i] = test02;
						}

					}

					if (scoreNumber > opponent) {
						printf("\t%s best %s %d-%d\n", blbl, name, scoreNumber, opponent);
						score01 += scoreNumber;
						win++;
					}
					else if (scoreNumber < opponent) {
						printf("\t%s lost to %s %d-%d\n", blbl, name, opponent, scoreNumber);
						score02 += scoreNumber;
						lost++;
					}
					else if (scoreNumber == opponent) {
						printf("\t%s and %s tied at %d\n", blbl, name, scoreNumber);
						score03 += scoreNumber;
						tied++;
					}
				}
			}
		}
		double result = 0;
		result = (2 * (score01 + score03)) / (2 * (score01 + score02 + score03));
		printf("Seasn result for %s: %.3f (%d-%d-%d)\n\n", blbl, result, win, lost, tied);

		if (fclose(fp1) != 0) {
			// the closing of the file failed
			printf("Can't close file opened\n");

			return -4;
		}

	}
	
	return check01;
	}



int parseLine(char resultArray[], char nameArray[], int *pScore, int *pOpponent) {
	int test = 0;
	int count = 0;
	int test01 = 0;
	int check = -1;
	int checkNumber = 1;

	if (resultArray == NULL) {
		return check;

	} else {
		
		for (int i = 0; resultArray[i]; i++) {

			if ((resultArray[i] >= 'A' && resultArray[i] <= 'Z') || (resultArray[i] >= 'a' && resultArray[i] <= 'z') || resultArray[i] == '.' || resultArray[i] == ' ') {
				test01 = resultArray[i];
				nameArray[i] = test01;
			}

			if (resultArray[i] >= '0' && resultArray[i] <= '9') {
				test = resultArray[i] - '0';
				count++;
				if (count == 1) {
					*pScore = test;
				} else if (count == 2) {
					*pOpponent = test;
				}
			}	
		}
		if (count != 2) {
			return check;
		}	
	}

	return checkNumber;
}