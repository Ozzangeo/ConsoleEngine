#include "../ConsoleEngine/Engine.h"

using namespace std;
using namespace chrono;

int main() {
	Field2D Field({ 16, 16, 1 });
	Camera2D Camera({ 128, 72 },&Field);
	Engine engine(&Camera);
	 
	engine.FontSetting({ 8, 8 });
	engine.Run(L"Engine", 60);
	engine.FontSetting({ 4, 4 });
	engine.Run(L"Not Engine", 60);

	Engine::Release();

	return 0;
}