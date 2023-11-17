#include "pch.h"
#include "TimeManager.h"

void TimeManager::Init()
{
	QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&_frequency));
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&_prevCount));	//CPUŬ��
}

void TimeManager::Update()
{
	long long currentCount;
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currentCount));

	_deltaTime = (currentCount - _prevCount) / static_cast<float>(_frequency);
	_prevCount = currentCount;

	_frameCount++;
	_frameTime += _deltaTime;

	if (_frameTime >= 1.f) {
		_fps = static_cast<int>(_frameCount / _frameTime);

		_frameTime = 0.f;
		_frameCount = 0;
	}
}
