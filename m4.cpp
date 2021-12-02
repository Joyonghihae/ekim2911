#include<stdio.h>
#include <string.h>
#include<cstdlib>
#pragma warning(disable:4996)


int parseLine(char resultArray[], char nameArray[], int* pScore, int* pOpponent);
int processGames(char fileName[]);
int main() {

	FILE* fp = NULL;
	char leng[40] = { 0 };
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
		
		// leng 는 1차팀(기존팀)
		
		printf("Processing %s: \n", leng);
		processGames(leng);
		// close the file, thus creating the file
		if (fclose(fp) != 0) {
			// the closing of the file failed
			printf("Can't close file opened\n");

			return -3;
		}
		
		
		return 0;
	}
}
int processGames(char fileName[]){

	//opens files, outputs values?????, lists them in order of size, and calculates them.
	FILE* fp1 = NULL;
	char leng01[40] = { 0 };
	strcpy(leng01, fileName);
	fp1 = fopen(leng01, "r");
	if (fp1 == NULL) {
		printf("Can't open the file\n");

		return -4;
	}
	while (fgets(leng01, sizeof leng01, fp1) > 0) {
		if (ferror(fp1)) {
			printf("Error reading line from file\n");
			// close the file, thus creating the file
			if (fclose(fp1) != 0) {
				// the closing of the file failed
				printf("Can't close file opened for reading\n");
			}

			return -2;
		}
		printf("This is check line: %s\n", leng01);
		char number[40] = { 0 };
		char name[40] = { 0 };
		int scoreNumber = 0;
		int opponent = 0;
		strcpy(number, leng01);
		parseLine(number, name, &scoreNumber, &opponent);
		//// (2 * wins + ties) /(2 * (wins + losses + ties))

		/*
		int test = 0;
		int count = 0;
		int score = 0;
		for (int i = 0; leng01[i]; i++) {

			if (leng01[i] >= '0' && leng01[i] <= '9') {
				test = leng01[i] - '0';
				printf("This is number: %d\n", test);
				count++;
				if (count == 2) {
					if (score > test) {
						printf("이겼다\n");
					}
					else if (score < test) {
						printf("졌다?\n");
					}
					else if (score == test) {
						printf("비겼네?\n");
					}
				}
				score = test;
			}
		}*/
		//char* ptr = strchr(number, ',')+1;
		//printf("Finally%s\n", ptr);


	}

	if (fclose(fp1) != 0) {
		// the closing of the file failed
		printf("Can't close file opened\n");

		return -4;
	}
	

	
	return 0;
	}
	/*
	문자열에서 숫자만 가져와서 비교 -> 크기순으로 다시정렬해서 출력
	
	*/
	//여기서 parseling호출 
	//여기서 전체 점수 결과  

// return int???? void???? ??????????????? 
int parseLine(char resultArray[], char nameArray[], int *pScore, int *pOpponent) {
	//게임 결과줄을 분석해야함 
	/*
	*   Arizona,3-2
		St. Louis,2-2
		New York Rangers,4-5
	*/
	// 게임 결과 문자열 :Toronto beat Winnipeg 4-2 / 상대팀만뽑아온 배열 / 1차팀 점수 포인터/ 상대팀 점수 포인
	// , = 44
	int test = 0;
	int count = 0;
	int test01 = 0;

	
	for (int i = 0; resultArray[i]; i++) {

		if ((resultArray[i] >= 'A' && resultArray[i] <= 'Z')||(resultArray[i] >= 'a' && resultArray[i] <= 'z')||resultArray[i]=='.'||resultArray[i] == ' ') {
			test01 = resultArray[i];
			nameArray[i] = test01;
		}
		
		if (resultArray[i] >= '0' && resultArray[i] <= '9') {
			test = resultArray[i] - '0';
			printf("This is number: %d\n", test);
			count++;
			if (count == 1) {
			*pScore = test;
			}else if (count == 2) {
				if (*pScore > test) {
					printf("win!\n"); //return this?
				}
				else if (*pScore < test) {
					printf("lost!\n");
				}
				else if (*pScore == test) {
					printf("tied\n");
				}
				*pOpponent = test;
			} 
		}

	}

	printf("finally.... %s\n", nameArray);
	 
	return 0;
}