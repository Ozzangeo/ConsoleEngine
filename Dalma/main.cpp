#include "stdafx.h"
#include "Scenes.h"

int main() {
	ConsoleEngine engine;

	// 아니 이거 왜 하나의 콘솔에서 실행함? 개에바인데
	// 일단 유사 해결책 : 텍스트 출력을 선택사항으로해서 Dalma를 server로, 텍스트 출력 콘솔을 Client로 해서 선택사항으로 만들자
	system("ServerTest.exe");
	engine.Run<Dalma>();

	engine.Release();

	return 0;
}