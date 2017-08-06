#pragma once
#include <Windows.h>
#include <time.h>


inline int Random(int min, int max) {
	return rand() % (max - min + 1) + min;
}