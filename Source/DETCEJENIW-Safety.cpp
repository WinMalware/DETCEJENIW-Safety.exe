#include <windows.h>
#define _USE_MATH_DEFINES 1
#include <cmath>
#pragma comment(lib, "winmm.lib")
#include <tchar.h>


DWORD WINAPI cur(LPVOID lpParam) {
	while (1) {
		int X = rand() % 1367;
		int Y = rand() % 769;
		SetCursorPos(X, Y);
	}
}
DWORD WINAPI patblt(LPVOID lpParam)
{
	HDC hdc = 0;
	int sx = 0, sy = 0;
	int rx = 0, ry = 0;

	while (1)
	{
		hdc = GetWindowDC(GetDesktopWindow());
		sx = GetSystemMetrics(SM_CXSCREEN);
		sy = GetSystemMetrics(SM_CYSCREEN);
		rx = rand() % sx;
		ry = rand() % sy;
		SelectObject(hdc, CreateSolidBrush(RGB(rand() % 225, rand() % 225, rand() % 225)));
		PatBlt(hdc, 0, 0, sx, sy, PATINVERT);
		Sleep(10);
	}
}
DWORD WINAPI payload2(LPVOID lpParam) {
	HDC desktop = GetDC(NULL);
	int xs = GetSystemMetrics(SM_CXSCREEN);
	int ys = GetSystemMetrics(SM_CYSCREEN);
	while (true) {
		desktop = GetDC(NULL);
		BitBlt(desktop, rand() % 10, rand() % 10, xs, ys, desktop, rand() % 10, rand() % 10, 0x999999);
		Sleep(10);
	}
}
DWORD WINAPI payload3(LPVOID lpParam) {
	HDC hdc = GetDC(HWND_DESKTOP);
	int X = GetSystemMetrics(SM_CXSCREEN);
	int Y = GetSystemMetrics(SM_CYSCREEN);

	while (TRUE)
	{
		HDC hdc = GetDC(HWND_DESKTOP);
		int X = GetSystemMetrics(SM_CXSCREEN);
		int Y = GetSystemMetrics(SM_CYSCREEN);
		BitBlt(hdc, rand() % (X - 0), rand() % (Y - 0), rand() % (X - 0), rand() % (Y - 0), hdc, rand() % (X - 0), rand() % (Y - 0), 0x999999);
		Sleep(10); // to prevent memleak
	}
}
DWORD WINAPI spiral(LPVOID lpParam) {
	HDC desk = GetDC(0);
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1), counter = M_PI*M_PI*M_PI, xSize = sh, ySize = sw / 45;
	RECT rekt; POINT pt[3];
	while (1) {
		for (int i = 0; i < sh / 3; i++) {
			HDC desk = GetDC(0);
			GetWindowRect(GetDesktopWindow(), &rekt);
			pt[0].x = rekt.left + counter;
			pt[0].y = rekt.top - sin(i / ((float)xSize) * M_PI) * (ySize);
			pt[1].x = rekt.right + counter;
			pt[1].y = rekt.top + counter;
			pt[2].x = rekt.left - counter;
			pt[2].y = rekt.bottom - counter;
			PlgBlt(desk, pt, desk, rekt.left, rekt.top, rekt.right - rekt.left, rekt.bottom - rekt.top, 0, 0, 0);
			Sleep(5.9);
		}
	}
}
DWORD WINAPI payload5(LPVOID lpParam) {
	HDC desktop = GetDC(NULL);
	int xs = GetSystemMetrics(SM_CXSCREEN);
	int ys = GetSystemMetrics(SM_CYSCREEN);
	while (true) {
		desktop = GetDC(NULL);
		BitBlt(desktop, rand() % 10, rand() % 10, xs, ys, desktop, rand() % 10, rand() % 10, NOTSRCCOPY);
		Sleep(10);
	}
}
VOID WINAPI ci(int x, int y, int w, int h)
{
	HDC hdc = GetDC(0);
	HRGN hrgn = CreateEllipticRgn(x, y, w + x, h + y);
	SelectClipRgn(hdc, hrgn);
	BitBlt(hdc, x, y, w, h, hdc, x, y, NOTSRCCOPY);
	DeleteObject(hrgn);
	ReleaseDC(NULL, hdc);
}
DWORD WINAPI wef(LPVOID lpParam) {
	RECT rect;
	GetWindowRect(GetDesktopWindow(), &rect);
	int w = rect.right - rect.left - 500, h = rect.bottom - rect.top - 500;

	for (int t = 0;; t++)
	{
		const int size = 1000;
		int x = rand() % (w + size) - size / 2, y = rand() % (h + size) - size / 2;

		for (int i = 0; i < size; i += 100)
		{
			ci(x - i / 2, y - i / 2, i, i);
			Sleep(10);
		}
	}
}
DWORD WINAPI textout1(LPVOID lpParam)
{
	HDC hdc;
	int sx = 0, sy = 0;
	LPCWSTR lpText = L"DETCEJENIW";
	while (1)
	{
		hdc = GetWindowDC(GetDesktopWindow());
		sx = GetSystemMetrics(0);
		sy = GetSystemMetrics(1);
		TextOutW(hdc, rand() % sx, rand() % sy, lpText, wcslen(lpText));
		Sleep(10);
	}
}
DWORD WINAPI textout2(LPVOID lpParam)
{
	HDC hdc;
	int sx = 0, sy = 0;
	LPCWSTR lpText = L"WINEJECTED";
	while (1)
	{
		hdc = GetWindowDC(GetDesktopWindow());
		sx = GetSystemMetrics(0);
		sy = GetSystemMetrics(1);
		TextOutW(hdc, rand() % sx, rand() % sy, lpText, wcslen(lpText));
		Sleep(10);
	}
}
VOID WINAPI sound1() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t / 8) >> (t >> 9) * t / ((t >> 14 & 3) + 4);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound2() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 11025, 11025, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[11025 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t*(t & 16384 ? 7 : 5)*(3 - (3 & t >> 9) + (3 & t >> 8)) >> (3 & -t >> (t % 65536<59392 ? (t & 4096 ? 2 : 16) : 2)) | t >> 3);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound3() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(10 * (t >> 6 | t | t >> (t >> 16)) + (7 & t >> 11));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound4() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(17 * t | (t >> 2) + (t & 32768 ? 13 : 14)*t | t >> 3 | t >> 5);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound5() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t >> (t % 16 ? 4 : 6) | t >> (t % 128 ? 10 : 4));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound6() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t*((t & 4096 ? t % 65536<59392 ? 7 : t >> 6 : 16) + (1 & t >> 14)) >> (3 & -t >> (t & 2048 ? 2 : 10)) | t >> (t & 16384 ? t & 4096 ? 4 : 3 : 2));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
int CALLBACK WinMain(
	HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine, int       nCmdShow
)
{
	if (MessageBoxW(NULL, L"This is a GDI Software Only Are you sure you wanted to run it?", L"DETCEJENIW", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
	{
		ExitProcess(0);
	}
	else
	{
		if (MessageBoxW(NULL, L"Are you sure? It can cause serious damages to your own eyes.", L"DETCEJENIW", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
		{
			ExitProcess(0);
		}
		else
		{
			Sleep(5000);
			//HANDLE thread1 = CreateThread(0, 0, cur, 0, 0, 0);
			HANDLE thread2 = CreateThread(0, 0, patblt, 0, 0, 0);
			sound1();
			Sleep(30000);
			TerminateThread(thread2, 0);
			CloseHandle(thread2);
			InvalidateRect(0, 0, 0);
			Sleep(1000);
			HANDLE thread3 = CreateThread(0, 0, payload2, 0, 0, 0);
			sound2();
			Sleep(30000);
			TerminateThread(thread3, 0);
			CloseHandle(thread3);
			InvalidateRect(0, 0, 0);
			Sleep(1000);
			HANDLE thread4 = CreateThread(0, 0, payload3, 0, 0, 0);
			sound3();
			Sleep(30000);
			TerminateThread(thread4, 0);
			CloseHandle(thread4);
			InvalidateRect(0, 0, 0);
			Sleep(1000);
			HANDLE thread5 = CreateThread(0, 0, spiral, 0, 0, 0);
			HANDLE thread6 = CreateThread(0, 0, patblt, 0, 0, 0);
			sound4();
			Sleep(30000);
			TerminateThread(thread5, 0);
			CloseHandle(thread5);
			InvalidateRect(0, 0, 0);
			TerminateThread(thread6, 0);
			CloseHandle(thread6);
			InvalidateRect(0, 0, 0);
			Sleep(1000);
			HANDLE thread7 = CreateThread(0, 0, payload5, 0, 0, 0);
			HANDLE thread8 = CreateThread(0, 0, wef, 0, 0, 0);
			sound5();
			Sleep(30000);
			TerminateThread(thread7, 0);
			CloseHandle(thread7);
			InvalidateRect(0, 0, 0);
			TerminateThread(thread8, 0);
			CloseHandle(thread8);
			InvalidateRect(0, 0, 0);
			Sleep(1000);
			HANDLE thread9 = CreateThread(0, 0, patblt, 0, 0, 0);
			HANDLE thread10 = CreateThread(0, 0, textout1, 0, 0, 0);
			HANDLE thread11 = CreateThread(0, 0, textout2, 0, 0, 0);
			sound6();
			Sleep(30000);
		}
	}
}
