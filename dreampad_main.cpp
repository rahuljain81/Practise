#include <stdio.h>

const int INIT_METHOD = 0;
const int WRITE_METHOD = 1;
const int MOVE_CURSOR_METHOD = 2;
const int UNDO_METHOD = 3;
const int REDO_METHOD = 4;
const int SHOW_METHOD = 5;

const int MAX_STR_SIZE = 50000;

void init(char* str);
void write(char ch);
void moveCursor(int pos);
void undo();
void redo();
char* show();

int compare(char str1[], char str2[]);
char getChar(char ch);
int getStrLen(char* str);

int main(){
	//freopen("input.txt", "r", stdin);

	int tests;
	scanf("%d", &tests);
	int totalActualPoints = 0;
	int totalUserPoints = 0;
	for (int i = 0; i<tests; i++){
		int actualPoints = 0;
		int userPoints = 0;

		int numberOfMethodCalls;
		scanf("%d", &numberOfMethodCalls);
		for (int j = 0; j<numberOfMethodCalls; j++){
			int methodName;
			scanf("%d", &methodName);

			switch (methodName){
				case INIT_METHOD:
				{
					char str[MAX_STR_SIZE];
					scanf(" %[^\r\n]", str);
					init(str);
				}
				break;
				case WRITE_METHOD:
				{
					char charArray[MAX_STR_SIZE];
					scanf(" %[^\r\n]", charArray);
					for(int k=0; charArray[k]; k++){
						char ch = charArray[k];
						if(ch == '\\'){
							k++;
							write(getChar(charArray[k]));
						}else{
							write(ch);
						}
					}
				}
				break;
				case MOVE_CURSOR_METHOD:
				{
					int pos;
					scanf("%d", &pos);
					moveCursor(pos);
				}
				break;
				case UNDO_METHOD:
				{
					undo();
				}
				break;
				case REDO_METHOD:
				{
					redo();
				}
				break;
				case SHOW_METHOD:
				{
					char answer[MAX_STR_SIZE];
					scanf(" %[^\r\n]", answer);
					char* userAnswer = show();
					actualPoints += getStrLen(answer);
					userPoints += compare(answer, userAnswer);
				}
				break;
			}
		}

		printf("Test-%d points: %d of %d\n", (i + 1), userPoints, actualPoints);
		totalUserPoints += userPoints;
		totalActualPoints += actualPoints;
	}
	printf("-----------------------------\n");
	printf("Total points: %d of %d\n", totalUserPoints, totalActualPoints);

	fclose(stdin);
	return 0;
}

int compare(char str1[], char str2[]){
	int points = 0;
	
	for (int i = 0; str1[i]; i++){
		if (str1[i] == str2[i]){
			points++;
		}
		else{
			break;
		}
	}

	return points;
}

char getChar(char ch){
	if (ch == 'b'){
		return '\b';
	}if (ch == 'n'){
		return '\n';
	}if (ch == 's'){
		return ' ';
	}
	else {
		return ' ';
	}
}

int getStrLen(char* str){
	int len = 0;

	while(str[len]){
		len++;
	}

	return len;
}
