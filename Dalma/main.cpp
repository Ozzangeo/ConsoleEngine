#include "stdafx.h"
#include "Scenes.h"

int main() {
	ConsoleEngine engine;

	// 자고 일어나서 할거
	// 1. 마저 트랙 만들기 ( 절반 )
	// 2. 그 뭐냐 보정? 만들기
	// 3. PPT 만들기
	// 끝

	engine.Run<DalmaMain>(L"Dalma[RE]", 120);

	engine.Release();

	return 0;
}