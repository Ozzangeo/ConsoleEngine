#include "stdafx.h"
#include "Scenes.h"

int main() {
	Debug::DisableDebugging();
	ConsoleEngine engine;

	engine.Run<TextBox>(L"Dalma[RE] Text Box", 1000);

	engine.Release();

	return 0;
}