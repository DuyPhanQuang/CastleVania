#include "GameTime.h"

GameTime::GameTime(void){}
GameTime::~GameTime(void){}

bool GameTime::Initialize() {
	LARGE_INTEGER i;

	//lay tan so tu bo dem. tan so se khong thay doi khi he thong dang chay, vi vay minh chi can lam 1 lan cai nay
	if (!QueryPerformanceCounter(&i))
		return FALSE;

	//dua num,ber of ticks per count
	m_frequencySeconds = (float)(i.QuadPart);

	//lay gia tri hien tai cua bo dem(counter)
	QueryPerformanceCounter(&i);
	m_start = i.QuadPart;
	m_totalGameTime = 0;
	m_elapsedGameTime = 0;

	return TRUE;
}

void GameTime::Update() {
	LARGE_INTEGER i;

	QueryPerformanceCounter(&i);
	m_elapsedGameTime = (float)(i.QuadPart - m_start) / m_frequencySeconds;
	m_totalGameTime += m_elapsedGameTime;
	m_start = i.QuadPart;
}