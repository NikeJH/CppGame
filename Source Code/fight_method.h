//File name fight_method.h
//Included by fight.cpp
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<thread>
#include<Windows.h>
#include<iostream>

using namespace std;
using namespace sf;

RenderWindow window(VideoMode(800, 1000), "FIGHT!");
RectangleShape bk(Vector2f(800,1000));

Sprite fighter;
Sprite bullet;
Sprite enemy;

Texture bk_jpg;
Texture fighter_jpg;
Texture bullet_jpg;
Texture enemy_jpg;
//Music
SoundBuffer bk_buffer;
SoundBuffer shot_buffer;
SoundBuffer explor_buffer;
Sound explor_music;
Sound bk_music;
Sound shot_music;

int Death_Times = 0;

struct info {
	int x;
	int y;
	bool status;
};
enum BODY_STATUS {
	DEAD = 1,
	LIVE = 0
};
info fighter_info = { 380,890,LIVE };
info enemy_info = { 20,200 ,LIVE };

void init();
void draw();
void show();

void init() {
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	window.setVerticalSyncEnabled(true);
}

void draw () {
	if (!bk_jpg.loadFromFile("backgroud.png")) {
		throw "Coudle Not Load the PNG!";
	}
	else {
		bk.setTexture(&bk_jpg);
	}

	if (!fighter_jpg.loadFromFile("fighter.png")) {
		throw "Coudle Not Load the PNG!";
	}
	else {
		fighter.setScale(Vector2f(0.39f, 0.39f));
		fighter.setTexture(fighter_jpg);
	}

	if (!bullet_jpg.loadFromFile("bullet.png")) {
		throw "Coudle Not Load the PNG!";
	}
	else {
		bullet.setScale(Vector2f(0.35f, 0.35f));
		bullet.setTexture(bullet_jpg);
	}
	if (!enemy_jpg.loadFromFile("enemy.png")) {
		throw "Coudle Not Load the PNG!";
	}
	else {
		enemy.setScale(Vector2f(0.40f, 0.40f));
		enemy.setTexture(enemy_jpg);
		enemy.setOrigin(enemy.getGlobalBounds().width / 2, enemy.getGlobalBounds().height / 2);
		float angle = 180.0f;
		enemy.setRotation(angle);
	}
}

void show() {
	draw();
	
	while (window.isOpen()) {
		fighter.setPosition(fighter_info.x, fighter_info.y);
		enemy.setPosition(enemy_info.x, enemy_info.y);
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
				ExitProcess(0);
			}
		}
		window.clear(Color::White);
		window.draw(bk);
		window.draw(fighter);
		window.draw(bullet);
		window.draw(enemy);
		window.display();
	}
}
#pragma region MOVE
void to_left() {
	while (window.isOpen()) {
		if (Keyboard::isKeyPressed(Keyboard::A)) {
			if (fighter_info.x > 20) {
				fighter_info.x -= 4;
			}
			else {
				fighter_info.x = 20;
			}
			Sleep(20);
		}
	}
}
void to_right() {
	while (window.isOpen()) {
		if (Keyboard::isKeyPressed(Keyboard::D)) {
			if (fighter_info.x < 700) {
				fighter_info.x += 4;
			}
			else {
				fighter_info.x = 700;
			}
			Sleep(20);
		}
	}
}
void to_up() {
	while (window.isOpen()) {
		if (Keyboard::isKeyPressed(Keyboard::W)) {
			if (fighter_info.y > 50) {
				fighter_info.y -= 4;
			}
			else {
				fighter_info.y = 50;
			}

			Sleep(20);
		}
	}
}
void to_down() {
	while (window.isOpen()) {
		if (Keyboard::isKeyPressed(Keyboard::S)) {
			if (fighter_info.y < 900) {
				fighter_info.y += 4;
			}
			else {
				fighter_info.y = 900;
			}

			Sleep(20);
		}
	}
}
#pragma endregion

#pragma region PLAY_MUSIC
void play_bk() {
	bk_buffer.loadFromFile("backgroud.ogg");
	bk_music.setBuffer(bk_buffer);
	bk_music.setLoop(true);
	bk_music.play();
}
void play_shot() {
	while (window.isOpen()) {
		shot_buffer.loadFromFile("shot.mp3");
		shot_music.setBuffer(shot_buffer);
		if (Keyboard::isKeyPressed(Keyboard::Space)) {
			shot_music.play();
		}
		Sleep(300);
	}
}
void play_explor() {
	explor_buffer.loadFromFile("explor.mp3");
	explor_music.setBuffer(explor_buffer);
	explor_music.play();
}
#pragma endregion

#pragma region SHOT
void shot() {
	while (window.isOpen()) {
		int temp_x, temp_y;
		if (window.isOpen()) {
			if (Keyboard::isKeyPressed(Keyboard::Space)) {
				temp_x = fighter_info.x;
				temp_y = fighter_info.y;
				while (1) {
					temp_y -= 7;
					bullet.setPosition(temp_x, temp_y);
					if (temp_y <= 20) {
						bullet.setPosition(-10, -10);
						break;
					}
					Sleep(20);
				}
			}
		}
	}
}

#pragma endregion

void move_1() {
	while (window.isOpen()) {
		enemy_info.x += 2;
		Sleep(20);
	}
}
void move_2() {
	while (window.isOpen()) {
		enemy_info.x += 1;
		enemy_info.y += 1;
		Sleep(30);
	}
}
void monitor() {
	while (window.isOpen()) {
		Sleep(200);
		if (bullet.getGlobalBounds().intersects(enemy.getGlobalBounds())) {
			play_explor();
			enemy_info = { -1000,-1000,DEAD };
			Death_Times += 1;
		}
		else if (enemy_info.x >= 900) {
			Sleep(200);
			enemy_info = { 20,200,LIVE };
		}
		
	}
}