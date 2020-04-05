#include <Bangtal.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>

#pragma comment(lib,"Bangtal.lib")


const char* IMAGES[8] = { "Images/1.png", "Images/2.png", "Images/3.png",
						"Images/4.png", "Images/5.png", "Images/6.png", 
						"Images/7.png", "Images/8.png"};


SceneID scene1, scene2, scene3;
ObjectID button1, button2, button3;
ObjectID pieces[8];

int arr[3][3];

time_t t;



void init() {
	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			arr[x][y] = x + y * 3;
		}
	}
}

void move(int x, int y) {
	if (x > 0 && arr[x - 1][y] == 8) {
		locateObject(pieces[arr[x][y]], scene2, 300 + (x - 1) * 200, 460 - y * 200);
		arr[x - 1][y] = arr[x][y];
		arr[x][y] = 8;
	}
	else if (x < 2 && arr[x + 1][y] == 8) {
		locateObject(pieces[arr[x][y]], scene2, 300 + (x + 1) * 200, 460 - y * 200);
		arr[x + 1][y] = arr[x][y];
		arr[x][y] = 8;
	}
	else if (y > 0 && arr[x][y - 1] == 8) {
		locateObject(pieces[arr[x][y]], scene2, 300 + x * 200, 460 - (y - 1) * 200);
		arr[x][y - 1] = arr[x][y];
		arr[x][y] = 8;
	}
	else if (y < 2 && arr[x][y + 1] == 8) {
		locateObject(pieces[arr[x][y]], scene2, 300 + x * 200, 460 - (y + 1) * 200);
		arr[x][y + 1] = arr[x][y];
		arr[x][y] = 8;
	}
}

void shuffle() {
	srand((unsigned int)time(0));
	for (int i = 0; i < 1000; i++) {
		move(rand() % 3, rand() % 3);
	}
}

bool check() {
	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			if (arr[x][y] != x + y * 3) return false;
		}
	}
	return true;
}

void start() {
	enterScene(scene2);
	init();
	shuffle();
	t = time(0);
}

void end() {
	enterScene(scene3);

	char str1[10];
	char str2[40] = "소요 시간 :";
	char str3[3] = "초";
	sprintf_s(str1, "%d", (int)difftime(time(0), t));
	strcat_s(str2, str1);
	strcat_s(str2, str3);
	showMessage(str2);
}

void mouseCallback(ObjectID object, int x, int y, MouseAction action) {
	if (object == button1) {
		start();
	}
	else if (object == button2) {
		shuffle();
	}
	else if (object == button3) {
		enterScene(scene1);
	}
	else {
		for (int i = 0; i < 9; i++) {
			if (object == pieces[i]) {
				for (int n = 0; n < 9; n++) {
					if (arr[n % 3][n / 3] == i) {
						move(n % 3, n / 3);
						if (check()) end();
						break;
					}
				}
			}
		}
	}
}



int main() {
	setMouseCallback(mouseCallback);


	scene1 = createScene("scene1", "Images\\원본.png");

	button1 = createObject("button1", "Images\\start.png");
	locateObject(button1, scene1, 590, 300);
	showObject(button1);


	scene2 = createScene("scene2", "Images\\배경.png");

	button2 = createObject("button2", "Images\\restart.png");
	locateObject(button2, scene2, 0, 620);
	scaleObject(button2, 0.5f);
	showObject(button2);

	for (int i = 0; i < 8; i++) {
		pieces[i] = createObject("piece", IMAGES[i]);
		locateObject(pieces[i], scene2, 300 + (i % 3) * 200, 460 - (i / 3) * 200);
		showObject(pieces[i]);
	}


	scene3 = createScene("scene3", "Images\\원본.png");

	button3 = createObject("button3", "Images\\restart.png");
	locateObject(button3, scene3, 544, 300);
	showObject(button3);


	startGame(scene1);
	init();
	return 0;
}