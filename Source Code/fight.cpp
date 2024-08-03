//File name "fight.cpp"
//the main c++ FILE 
#include"fight_method.h"

int main() {
	thread left(to_left);
	thread right(to_right);
	thread up(to_up);
	thread down(to_down);

	thread play_bk_music(play_bk);
	thread play_shot_music(play_shot);

	thread take_fire(shot);
	thread move_one(move_1);
	thread move_two(move_2);
	thread monitor_crash(monitor);

	init();
	show();
	
	left.join();
	right.join();
	up.join();
	down.join();

	play_bk_music.join();
	play_shot_music.join();

	take_fire.join();	
	monitor_crash.join();
	cout << Death_Times << endl;
	while (window.isOpen()) {
		Sleep(100);
		
		if (Death_Times == 0) {
			move_one.join();
		}
		else {
			move_two.join();
		}
	}
}