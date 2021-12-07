/*
FILE : m4.cpp
PROJECT : Major4
PROGRAMMER : Eunyoung Kim
FIRST VERSION : 2021/12/06
DECRIPTION : Open the teams.txt file to read the result files in that file. 
			Output the results with the corresponding result files. Finally, 
			calculate and indicate the total score.

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
	char fileLength[kArrayLength] = { 0 };
	int resultGame = 0;
	fp = fopen("teams.txt", "r");
	if (fp == NULL) {
		printf("Can't open teams.txt\n");

		return -1;
	}
	
	while (fgets(fileLength, sizeof fileLength, fp) > 0) {
		if (ferror(fp)) {
			printf("Error reading line from file\n");
			// close the file, thus creating the file
			if (fclose(fp) != 0) {
				// the closing of the file failed
				printf("Can't close file opened for reading\n");
			}

			return -2;
		} 

		int checkEnter = strlen(fileLength);
		if (fileLength[checkEnter - 1] == '\n') {
			fileLength[checkEnter - 1] = 0;
		}
		if (strlen(fileLength) == 0) {
			continue;
		}
		resultGame = processGames(fileLength);
		if (resultGame == -1) {
			printf("There is no result file");
		}
	}
	// close the file, thus creating the file
	if (fclose(fp) != 0) {
		// the closing of the file failed
		printf("Can't close file opened\n");

		return -3;
	}

	return 0;
}



/*
FUNCTION	: processGames
DESCRIPTION : Get the values of the files and output the results. 
			  It also outputs the final score.
PARAMENTERS :
	char fileName :  Read the file name.
RETURNS		:
	int 			: The corresponding value is returned.
*/
int processGames(char fileName[]){
	FILE* fp1 = NULL;
	char resultFile[kArrayLength] = { 0 };
	char separateArray[kArrayLength] = { 0 };
	char resultScore[kArrayLength] = { 0 };
	char opponentArray[kArrayLength] = { 0 };
	int seperateName = 0;
	int scoreNumber = 0;
	int opponent = 0;
	double winScore = 0;
	double lostScore = 0;
	double tiedScore = 0;
	int win = 0;
	int lost = 0;
	int tied = 0;
	int second = 2;
	double result = 0;
	int check = -1;
	if (fileName == NULL) {
		return check;
	}
	else {

		strcpy(resultFile, fileName);
		fp1 = fopen(resultFile, "r");
		if (fp1 == NULL) {
			printf("Warning: Can't open %s Skipping team.\n\n", resultFile);

			return -4;
		}
		printf("Processing %s: \n", resultFile);
		while (fgets(resultFile, sizeof resultFile, fp1) > 0) {
			if (ferror(fp1)) {
				printf("Error reading line from file\n");
				if (fclose(fp1) != 0) {
					printf("Can't close file opened for reading\n");
				}

				return -5;
			}

			if ((strchr(resultFile, ',') == 0) || (strchr(resultFile, '-') == 0)) {
				printf("\tWarning: malformed line. Skipping game.\n");
				continue;
			}


			if (strlen(resultFile) == 1) {
				continue;
			}
			else {
				
				strcpy(resultScore, resultFile);
				parseLine(resultScore, opponentArray, &scoreNumber, &opponent);

				if (parseLine(resultScore, opponentArray, &scoreNumber, &opponent) == -1) {
					printf("\tThere is no game result\n");
				}
				else {
					for (int i = 0; i < fileName[i]; i++) {

						//Output the rest of the string except for txt.
						if ((fileName[i] >= 'A' && fileName[i] <= 'Z') || (fileName[i] >= 'a' && fileName[i] <= 'z') || fileName[i] == ' ') {
							seperateName = fileName[i];
							separateArray[i] = seperateName;
						}

					}

					//It represents win, lost, and tied.
					if (scoreNumber > opponent) {
						printf("\t%s best %s %d-%d\n", separateArray, opponentArray, scoreNumber, opponent);
						winScore += scoreNumber;
						win++;
					}
					else if (scoreNumber < opponent) {
						printf("\t%s lost to %s %d-%d\n", separateArray, opponentArray, opponent, scoreNumber);
						lostScore += scoreNumber;
						lost++;
					}
					else if (scoreNumber == opponent) {
						printf("\t%s and %s tied at %d\n", separateArray, opponentArray, scoreNumber);
						tiedScore += scoreNumber;
						tied++;
					}
				}
			}
		}

		//It's a calculation formula for the total score.
		result = (second * (winScore + tiedScore)) / (second * (winScore + lostScore + tiedScore));
		printf("Seasn result for %s: %.3f (%d-%d-%d)\n\n", separateArray, result, win, lost, tied);

		if (fclose(fp1) != 0) {
			// the closing of the file failed
			printf("Can't close file opened\n");

			return -6;
		}

	}
	
	return 0;
	}



/*
FUNCTION	: parseLine
DESCRIPTION : Get the values of the files and output the results.
			  It also outputs the final score.
PARAMENTERS :
	char resultArray[]	: Get the full length of the game result.
	char nameArray[]	: Only the other team's name is indicated in the entire length.
	int *pScore			: Only team scores are displayed on the entire length.
	int *pOpponent		: Only the opponent's score is displayed on the entire length.
RETURNS		:
	int 				: The corresponding value is returned.
*/
int parseLine(char resultArray[], char nameArray[], int *pScore, int *pOpponent) {
	int opponentName = 0;
	int errorNumber = -1;
	if (resultArray == NULL) {
		return errorNumber;

	} else {
		char gameArray[kArrayLength] = {0};
		char* opponentScore[kArrayLength] = {0};
		char* myScore[kArrayLength] = {0};
		
		//Put a string in an array
		strcpy(gameArray, resultArray);

		//Check the specific value
		if (strchr(gameArray, '-') && strchr(gameArray, ',') != NULL) {
			*opponentScore = strchr(gameArray, ',') + 1;
			*pScore = atoi(*opponentScore);
			*myScore = strchr(gameArray, '-') + 1;
			*pOpponent = atoi(*myScore);
		} 

		//Check the name of the other team
		for (int i = 0; resultArray[i]; i++) {
			if ((resultArray[i] >= 'A' && resultArray[i] <= 'Z') || (resultArray[i] >= 'a' && resultArray[i] <= 'z') || resultArray[i] == '.' || resultArray[i] == ' ') {
				opponentName = resultArray[i];
				nameArray[i] = opponentName;
			}
		}

		return 0;
	}

	return 0;
}