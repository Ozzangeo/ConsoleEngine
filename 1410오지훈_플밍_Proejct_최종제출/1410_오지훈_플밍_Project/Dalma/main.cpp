#include "stdafx.h"
#include "Scenes.h"

int main() {
	ConsoleEngine engine;

	// �ڰ� �Ͼ�� �Ұ�
	// 1. ���� Ʈ�� ����� ( ���� )
	// 2. �� ���� ����? �����
	// 3. PPT �����
	// ��

	engine.Run<DalmaMain>(L"Dalma[RE]", 120);

	engine.Release();

	return 0;
}