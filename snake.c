#include <stdio.h>
#include <stdlib.h>

int tail[25];		
int appos;
int lenth = 1;
int score = 0;
char face;	
int pos = 13;
char inp;
char gui[] = {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',};
int tail[25];

void mvsnk(char face){
	if (face == 'w'){
		pos -= 5;}
	else if (face == 's'){
		pos += 5;}
	else if (face == 'a'){
		pos -= 1;}
	else if (face == 'd'){
		pos += 1;}
	else {
		printf("invalid input");}
}
void printui(){
	int i, j;
	for (i=0; i<5;i++){
		printf("|");
		for (j=0; j<5;j++){
			printf("%d ", gui[j+i*5]);}
		printf("|\n");}}

void gensnake(char position, char b[]){
	b[position] = 'G';
	int i;
	for (i = lenth; i < lenth; i++){
		b[i] = 'o';}
} 

int main(){
	//char gui[] = {"cheese"};
	printui();

	return 0;
}
