#include "stdafx.h"
#include "Scenes.h"

int main() {
	ConsoleEngine engine;

	engine.Run<DalmaMain>(L"Dalma[RE]");

	engine.Release();

	return 0;
}