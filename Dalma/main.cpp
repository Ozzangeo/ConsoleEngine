#include "stdafx.h"
#include "Scenes.h"

int main() {
	ConsoleEngine engine;

	// �ƴ� �̰� �� �ϳ��� �ֿܼ��� ������? �������ε�
	// �ϴ� ���� �ذ�å : �ؽ�Ʈ ����� ���û��������ؼ� Dalma�� server��, �ؽ�Ʈ ��� �ܼ��� Client�� �ؼ� ���û������� ������
	system("ServerTest.exe");
	engine.Run<Dalma>();

	engine.Release();

	return 0;
}