#include "GameTime.h"

GameTime::GameTime(void){}

GameTime::~GameTime(void){}

bool GameTime::Initialize() {
	LARGE_INTEGER largeInteger;

	//get tan so tu counter. tan so kothay doi khi he thong dang chay, nen chi can thuc hien viec nay 1 lan
	if (!QueryPerformanceFrequency(&largeInteger))
		return FALSE;

	//cung cap number of ticks moi giay
	m_frequencySeconds = (float)(largeInteger.QuadPart);

	//get gia tri hien tai cua couter
	QueryPerformanceCounter(&largeInteger);
	m_start = largeInteger.QuadPart;
	m_totalGameTime = 0;
	m_elapseGameTime = 0;
	return TRUE;

}

void GameTime::Update() {
	LARGE_INTEGER largeInteger;
	QueryPerformanceCounter(&largeInteger);
	m_elapseGameTime = (float)(largeInteger.QuadPart - m_start) / m_frequencySeconds;
	m_totalGameTime += m_elapseGameTime;
	m_start = largeInteger.QuadPart;
}