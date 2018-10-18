#pragma once

#ifndef _INPUT_H_
#include <dinput.h>

	LPDIRECTINPUT8 dinput;
	LPDIRECTINPUTDEVICE8 dkeyboard;
	int InitDirectInput();
	int InitKeyboard(HWND);
	void PollKeyboard();

	int IsKeyDown(int key); //kiem tra trang thai phim co dang o duoi hay ko
	int IsKeyRelease(int key); //kiem tra co dang o trang thai tren hay ko
	int IsKeyPress(int key); //kiem tra xem phim co vua chuyen trang thai tu up->down hay ko

	void KillKeyboard();
#endif // !_INPUT_H_

