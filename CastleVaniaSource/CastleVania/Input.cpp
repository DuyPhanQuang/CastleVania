#include "Input.h"

LPDIRECTINPUT8 dinput;
LPDIRECTINPUTDEVICE8 dkeyboard;

char keys[256];
char keysBuffer[256]; //luu trang thai cac phim vao mang~ nay de xet keypress

int InitDirectInput() {
	//khoi tao doi tuong directInput 
	HRESULT result = DirectInput8Create(GetModuleHandle(NULL),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&dinput,
		NULL);

	if (result != DI_OK)
		return 0;
	//khoi tao keyboard
	result = dinput->CreateDevice(GUID_SysKeyboard, &dkeyboard, NULL);

	if (result != DI_OK)
		return 0;
	return 1;
}

int InitKeyboard(HWND hwnd) {
	//thiet lap dinh dang du lieu
	HRESULT result = dkeyboard->SetDataFormat(&c_dfDIKeyboard);

	if (result != DI_OK)
		return 0;

	//gianh kiem soat thiet bi de gianh lay ban phim de co the bat dau kiem tra nut duoc nhan
	result = dkeyboard->Acquire();

	if (result != DI_OK)
		return 0;
	return 1;
}

int IsKeyDown(int key) {
	return (keys[key] & 0x80);
}

void PollKeyboard()
{
	for (int i = 0; i < 256; i++)
		keysBuffer[i] = keys[i];

	dkeyboard->GetDeviceState(sizeof(keys), (LPVOID)&keys);
}

int IsKeyRelease(int key)
{
	return (!IsKeyDown(key) && (keysBuffer[key] & 0x80));
}

int IsKeyPress(int key)
{
	return (IsKeyDown(key) && !(keysBuffer[key] & 0x80));
}

void KillKeyboard()
{
	if (dkeyboard != NULL)
	{
		dkeyboard->Unacquire();
		dkeyboard->Release();
		dkeyboard = NULL;
	}
}