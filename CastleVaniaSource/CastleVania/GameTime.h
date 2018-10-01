#pragma once
#ifndef _GAME_TIME_H

#include <Windows.h>

class GameTime
{
public:
	GameTime(void);
	~GameTime(void);

	float m_elapseGameTime;
	float m_totalGameTime;

	bool Initialize();
	bool Initialize(int fps);

	void Update();
	void SetFPS(int fps);

private:
	LONGLONG m_start;
	float m_frequencySeconds; //seconds per count
	float m_fps; //frame per seconds
};

//GameTime::GameTime()
//{
//}
//
//GameTime::~GameTime()
//{
//}

#endif // !_GAME_TIME_H

