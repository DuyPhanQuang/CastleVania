#pragma once
#ifndef GAMETIME_H

#include <Windows.h>
#include "Input.h"

class GameTime {
private:
	LONGLONG m_start;
	float m_frequencySeconds; //second per count
	float m_fps;
public:
	float m_elapsedGameTime; //time troi
	float m_totalGameTime; 

	bool Initialize();
	bool Initialize(int fps);

	void Update();
	void SetFPS(int fps);

	GameTime(void);
	~GameTime(void);
};

#endif // !GAMETIME_H

