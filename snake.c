#include <stdio.h>
#include <termios.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <pthread.h>

int size = 121;
int appos;
int lenth = 2;
int score = 0;
char face = 'w';	
int pos;
char gui[121]; 
int rootsize = 1;
int tail[121]; 
char lastinp = 'w';
// there is probably a better solution for this
int appvar = 0;
int ret = 0;

//sets face to input value
void mvsnake(){
	void mvsnake_sub(){
		face = lastinp;
		mvsnake();}

	if (pos -5 < 0 && face == 'w'){
            ret =1;} 
    else if (pos +5 > size && face == 's'){
            ret =1;}
    else if (pos % rootsize - 1 < 0 && face == 'a'){
            ret =1;}
    else {int var = pos+1; if (var % rootsize == 0 && face == 'd'){
            ret =1;}}

	printf("%d\n", ret);
	if (face == 'w'){
		if (lastinp != 's'){
		pos -= rootsize;}
		else {mvsnake_sub();}}
	else if (face == 's'){
		if (lastinp != 'w'){
		pos += rootsize;}
		else {mvsnake_sub();}}		
	else if (face == 'a'){
			if (lastinp != 'd'){
		pos -= 1;}
		else {mvsnake_sub();}}
	else if (face == 'd'){
		if (lastinp != 'a'){
		pos += 1;}
		else {mvsnake_sub();}}
	else {
		mvsnake_sub();
		printf("invalid input");}}

//prints the ui
void printui(){
	int i, j;
	printf("\n");
	for (i=0; i < rootsize;i++){
		printf("|");
		for (j=0; j < rootsize; j++){
			printf("%c ", gui[i * rootsize + j]);}
		printf("|\n");}}

//generate head and tail in gui
void gensnake(/*int arg*/){
	gui[pos] = 'G';
	for (int i=0; i < lenth; i++){
		if (gui[i+1] != 0){
			gui[tail[i+1]-1] = 'o';}}} 

//code I stole from stackoverflow to get input
static struct termios old, current; // <-- what the fuck does this do?

void initTermios(void){
  tcgetattr(0, &old); /* grab old terminal i/o settings */
  current = old; /* make new settings same as old settings */
  current.c_lflag &= ~ICANON; /* disable buffered i/o */
  current.c_lflag &= ~ECHO; /* set no echo mode */
  tcsetattr(0, TCSANOW, &current); /* use these new terminal i/o settings now */
}

void resetTermios(void){
  tcsetattr(0, TCSANOW, &old);}

void sleep_ms(int a){
	usleep(a * 1000);}

void* getinp(void* arg){
	while (ret == 0){ 
		face = getchar();
		if (face == 'A'){face = 'a';}
		else if (face == 'S'){face = 's';}
		else if (face == 'D'){face = 'd';}
		else if (face == 'W'){face = 'w';}
		sleep_ms(3);}}

void genApple(){
	srand(time(NULL));
	do {
		appos = rand() % size;
	} while (gui[appos] != ' ');}

void checkNom(){
	if (appos ==  pos){
		lenth++;
		score++;
		genApple();}}

void win(){
	int temp = 1;
	for (int i = 0; i<size; i++){
		if (gui[i] == ' ' || gui[i] == 'A'){
			temp = 0;
			break;}}			
		if (temp == 1){ret = 2;}}

void rsetui(){
	for (int i=0; i<size; i++){
		gui[i] = ' ';}}

void apndTail(){
	for (int i=size;i>0;i--){
		tail[i] = tail[i-1];}
	tail[0] = pos + 1;}

void death(){
	if (gui[pos] == 'o'){
		ret = 1;}}
	
int main(){
	pthread_t inpth; //create thread for getting input
	rootsize = sqrt(size);
	pos = size / 2;
	lastinp = face;
	rsetui();
	genApple();
	initTermios();
	pthread_create(&inpth, NULL, getinp, NULL); //start input thread
//	mainloop
	while(ret == 0){
		system("clear"); 
		rsetui();
		apndTail();
		gensnake();
		checkNom();
		gui[appos] = 'A';
		printui();
		lastinp = face;
		sleep_ms(500);
		mvsnake();
		win();
		death();
	}
//mainloop END
	printf("%d\n", ret);
	if (ret == 1){printf("you died\nyour score is %d\n", score);}
	else if (ret == 2){printf("you won\n");}
	resetTermios();
	pthread_cancel(inpth);
	pthread_join(inpth, NULL);
	return 0;}
