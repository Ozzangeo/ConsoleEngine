#include "Components.h"

using namespace std;
using namespace Components;

void DownNote::Update() {
	*gameobject->pos += Vector3f(0, speed, 0) * Time::GetDeltaTime();
	if (gameobject->pos->y >= 64) { scene->RemoveGameObject(this->gameobject); }
}

void AmladPlayer::Update() {
	if (!Notes.empty()) {
		NoteInfo note = Notes.front();

		if (note.Time >= ExTime) {
			/* ���� ��Ʈ ��� */ note.Line;

			for (auto& effect : note.Effects) {
				switch (effect) {
				case /*��ò���*/1: { /* ���� ����Ʈ ���� �߰� */ /*gameobject->AddComponent<>();*/ } break;
				}
			}

			ExTime -= note.Time;
			Notes.pop_front();
		}

		ExTime += Time::GetDeltaTime();
	}
}
bool AmladPlayer::OpenAmlad(wstring path) {
	wifstream Amlad(L"Amlads/" + path + L".amlad");
	if (Amlad.fail()) { Amlad.close(); return false; }

	int dcount = 0;

	wstring text;
	wstring buf;

	while (!Amlad.eof()) {
		NoteInfo note;

		getline(Amlad, text);
		wstringstream ss(text);
		// Amlad ���� ���� ���� ���̵��
		// (��ġ, �ð�), ����Ʈ..

		getline(ss, buf, L',');	// ��ġ
		note.Line = stoi(buf);

		getline(ss, buf, L',');	// �ð�
		note.Line = stof(buf);

		while (getline(ss, buf, L',')) {	// ����Ʈ
			switch (buf[0]) // ���ڸ� ���� �����ؼ� �׿� �´� ����Ʈ �Լ� ��ȣ �߰� ( �ٵ� �߰� �Ű������� ��� ���� ) <- ����ؾ��Ұ�
			{
			default:
				break;
			}
			
		}
	}

	Amlad.close();

	return false;
}
