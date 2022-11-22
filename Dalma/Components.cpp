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
			/* 대충 노트 출력 */ note.Line;

			for (auto& effect : note.Effects) {
				switch (effect) {
				case /*모시깽이*/1: { /* 대충 이펙트 컴포 추가 */ /*gameobject->AddComponent<>();*/ } break;
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
		// Amlad 파일 저장 형식 아이디어
		// (위치, 시간), 이펙트..

		getline(ss, buf, L',');	// 위치
		note.Line = stoi(buf);

		getline(ss, buf, L',');	// 시간
		note.Line = stof(buf);

		while (getline(ss, buf, L',')) {	// 이펙트
			switch (buf[0]) // 앞자리 문자 감지해서 그에 맞는 이펙트 함수 번호 추가 ( 근데 추가 매개변수는 어떻게 받지 ) <- 고민해야할거
			{
			default:
				break;
			}
			
		}
	}

	Amlad.close();

	return false;
}
