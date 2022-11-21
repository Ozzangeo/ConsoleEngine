#include "stdafx.h"
#include "Scenes.h"

int main() {
	ConsoleEngine engine;

	engine.Run<Dalma>(L"Dalma[RE]");

	engine.Release();

	return 0;
}