#include "Components.h"

using namespace std;
using namespace Components;

void NoteJudgment::Update() {

}

float NoteDown::speed = 5.0f;
float NoteDown::bpm = 0.0f;
float NoteDown::bpm60 = 0.0f;
void NoteDown::Update() {
	*gameobject->pos += Vector3f(0, speed, 0) * Time::GetDeltaTime();
	if (gameobject->pos->y > 500) { scene->RemoveGameObject(gameobject); }
}

void AmladPlayer::Start() {
	audio = gameobject->AddComponent<Audio>();
	server = scene->GetGameObject(Tag_Server)->GetComponent<Server>();
}
void AmladPlayer::Update() {
	//if (isReady && PlayTime > 1.0f) { isReady = false; audio->PlayAudio(1); }

	while (!Notes.empty()) {
		NoteInfo noteInfo = Notes.front();
		noteInfo.Time = noteInfo.Distance * NoteDown::bpm60;
		if (noteInfo.Time >= ExTime) {
			ExTime += Time::GetDeltaTime();
			PlayTime += Time::GetDeltaTime();
			break;
		}

		auto* nowNote = scene->AddGameObject<Note>(L"Note", Tag_Note);
		auto* noteEffect = nowNote->AddComponent<NoteEffect>();
		noteEffect->effects = noteInfo.Effects;

		float BpmMul = (NoteDown::bpm * multiplespeed);
		 switch (static_cast<int>(noteInfo.Line)) {
		 case 1: { *nowNote->pos = Vector3f(-11, -BpmMul * 0.1f, nowNote->pos->z); } break;
		 case 2: { *nowNote->pos = Vector3f(-4,  -BpmMul * 0.1f, nowNote->pos->z); } break;
		 case 3: { *nowNote->pos = Vector3f( 3,  -BpmMul * 0.1f, nowNote->pos->z); } break;
		 case 4: { *nowNote->pos = Vector3f(10,  -BpmMul * 0.1f, nowNote->pos->z); } break;
		 default: { scene->RemoveGameObject(nowNote); } break;
		 }
		NoteDown::speed = BpmMul * 0.1f;

		ExTime -= noteInfo.Time;
		Notes.pop();

		PlayTime += Time::GetDeltaTime();
		ExTime += Time::GetDeltaTime();
	}
}
bool AmladPlayer::OpenAmlad(wstring path) {
	if (!isStart) {
		ifstream Amlad(L"Amlads/" + path + L".amlad");
		if (Amlad.fail()) { Amlad.close(); return false; }

		string text;
		string buf;

/*  [ 읽어오는 순서 ] 작곡가 - 곡이름 - 음악 파일 경로(path) - bpm - 오프셋 */ #pragma region ...
		getline(Amlad, artist);		// 작곡가 명
		getline(Amlad, text);		// 곡 이름
		artist += " - " + text;		// Artist - Song 형식

		getline(Amlad, text);		// 음악 Path
		audio->LoadAudio(text.c_str(), Audio::MP3);

		getline(Amlad, text);		// BPM
		try {
			NoteDown::bpm = stof(text);
			NoteDown::bpm60 = 60 / NoteDown::bpm;
		}
		catch (exception e) {
			NoteDown::bpm = -1;
			NoteDown::bpm60 = 60 / NoteDown::bpm;

			Debug::Log("[ AmladPlayer::OpenAmlads(wstring path) ] BPM Error!");
		}

		getline(Amlad, text);		// offset (ms)
		try { ExTime = -stof(text) * 0.001f; }
		catch (exception e) {
			ExTime = -1;
			Debug::Log("[ AmladPlayer::OpenAmlads(wstring path) ] Offset Error!");
		}
#pragma endregion

		// 시작 감지
		while (getline(Amlad, text)) {
			// 정확한 측정을 위해 앞 공백 제거
			for (int i = 0, size = text.length(); i < size; i++) { if (text[i] != ' ') { text.erase(0, i); break; } }
			if (text == "[ Start ]") { break; }
		}

		// 노트 불러오기
		while (getline(Amlad, text)) {
			if (text == "[ End ]") { break; }

			stringstream ss(text);

			NoteInfo note;

/* ([라인], [거리]), [이펙트].. */ #pragma region ...
			// [ 라인 ]
			getline(ss, buf, ',');
			for (int i = 0, size = buf.length(); i < size; i++) { if (buf[i] != ' ') { buf.erase(0, i); break; } }
			if (buf[0] == '(') { buf.erase(0, 1); }

			try { note.Line = stof(buf); }
			catch (exception e) { note.Line = 0; }

			// [ 거리 ]
			getline(ss, buf, ',');
			try { note.Distance = stof(buf); }
			catch (exception e) { note.Distance = 0; }
#pragma endregion

			// [ 이펙트 ]
			vector<float> para;

			while (getline(ss, buf, ',')) {
				para.clear();

				for (int i = 0, size = buf.length(); i < size; i++) { if (buf[i] != ' ') { buf.erase(0, i); break; } }

				// 앞자리 문자 감지해서 그에 맞는 이펙트 함수 번호 추가
				switch (buf[0]) {
				case Set_BPM: {
					// 앞번호 제거
					buf.erase(0, 1);

					for (int i = 0, size = buf.length(); i < size; i++) { if (buf[i] != ' ') { buf.erase(0, i); break; } }
					while (buf[0] == '(') { buf.erase(0, 1); }

					try { para.push_back(stof(buf)); }	// BPM 
					catch (exception e) { para.push_back(0); }

					note.Effects.push_back(EFunc(Set_BPM, para));
				} break;
				case Gradation: {
					buf.erase(0, 1);

					for (int i = 0, size = buf.length(); i < size; i++) { if (buf[i] != ' ') { buf.erase(0, i); break; } }
					while (buf[0] == '(') { buf.erase(0, 1); }

					// [ Red 1 ]
					try { para.push_back(stof(buf)); }
					catch (exception e) { para.push_back(0); }

					// [ Green 1 ]
					getline(ss, buf, ',');
					try { para.push_back(stof(buf)); }
					catch (exception e) { para.push_back(0); }

					// [ Blue 1 ]
					getline(ss, buf, ',');
					try { para.push_back(stof(buf)); }
					catch (exception e) { para.push_back(0); }


					// [ Red 2 ]
					getline(ss, buf, ',');

					for (int i = 0, size = buf.length(); i < size; i++) { if (buf[i] != ' ') { buf.erase(0, i); break; } }
					while (buf[0] == '(') { buf.erase(0, 1); }

					try { para.push_back(stof(buf)); }
					catch (exception e) { para.push_back(0); }

					// [ Green 2 ]
					getline(ss, buf, ',');
					try { para.push_back(stof(buf)); }
					catch (exception e) { para.push_back(0); }

					// [ Blue 2 ]
					getline(ss, buf, ',');
					try { para.push_back(stof(buf)); }
					catch (exception e) { para.push_back(0); }

					// [ ColorNum ]
					getline(ss, buf, ',');
					try {
						float num = stof(buf);

						para.push_back((num > 15) ? 15 : (num < 0) ? 0 : num);
					}
					catch (exception e) { para.push_back(0); }

					// [ Second ]
					getline(ss, buf, ',');
					try { para.push_back(stof(buf)); }
					catch (exception e) { para.push_back(0); }

					note.Effects.push_back(EFunc(Gradation, para));
				} break;
				case Set_Camera: {
					buf.erase(0, 1);
					for (int i = 0, size = buf.length(); i < size; i++) { if (buf[i] != ' ') { buf.erase(0, i); break; } }
					while (buf[0] == '(') { buf.erase(0, 1); }

					// [ Camera Now X ]
					try { para.push_back(stof(buf)); }
					catch (exception e) { para.push_back(0); }

					// [ Camera Now Y ]
					getline(ss, buf, ',');
					try { para.push_back(stof(buf)); }
					catch (exception e) { para.push_back(0); }


					// [ Camera Next X ]
					getline(ss, buf, ',');

					for (int i = 0, size = buf.length(); i < size; i++) { if (buf[i] != ' ') { buf.erase(0, i); break; } }
					while (buf[0] == '(') { buf.erase(0, 1); }

					try { para.push_back(stof(buf)); }
					catch (exception e) { para.push_back(0); }

					// [ Camera Next Y ]
					getline(ss, buf, ',');
					try { para.push_back(stof(buf)); }
					catch (exception e) { para.push_back(0); }

					// [ Camera Move Time ]
					getline(ss, buf, ',');
					try { para.push_back(stof(buf)); }
					catch (exception e) { para.push_back(0); }

					note.Effects.push_back(EFunc(Set_Camera, para));
				} break;
				default: {} break;
				}
			}

			Notes.push(note);
		}

		Amlad.close();

		isStart = true;
		isReady = true;

		return true;
	}
	return false;
}

void GradationEffect::Awake() {
	RGBcount = new Vector3f;
	RGBcountPlus = new Vector3f;
}
void GradationEffect::Update() {
	if (isStart) {
		*RGBcount += *RGBcountPlus * Time::GetDeltaTime();
		Vector3i rgbi = RGBcount->round();

		time += Time::GetDeltaTime();
		if (time >= maxTime) { color.SetColor(EndRGB, num); gameobject->RemoveComponent<GradationEffect>(); }
		else if (EndRGB != rgbi) { color.SetColor(rgbi, num); }
	}
}
void GradationEffect::Remove() {
	if (RGBcount) { delete RGBcount; RGBcount = nullptr; }
	if (RGBcountPlus) { delete RGBcountPlus; RGBcountPlus = nullptr; }
}
void GradationEffect::GradationStart(Rgb255 start, Rgb255 end, float second, int Colornum) {
	StartRGB = start;
	EndRGB = end;

	*RGBcount = start;
	if (second == 0) { *RGBcountPlus = Vector3f(end - start); }
	else { *RGBcountPlus = Vector3f(end - start) / second; }

	num = Colornum;
	maxTime = second;
	
	isStart = true;
}

void MoveCamera::Awake() {
	StartPos = new Vector3f;
	EndPos = new Vector3f;
	PosCount = new Vector3f;
	PosCountPlus = new Vector3f;
}
void MoveCamera::Start() {
	camera = scene->GetGameObject<GameObjects::Camera>(Tag_Camera);
}
void MoveCamera::Update() {
	if (isStart) {
		*PosCount += *PosCountPlus * Time::GetDeltaTime();

		time += Time::GetDeltaTime();
		if (time >= maxTime) { *camera->pos = *EndPos; gameobject->RemoveComponent<MoveCamera>(); }
		else if (*EndPos != *PosCount) { *camera->pos = *PosCount; }
	}
}
void MoveCamera::Remove() {
	if (StartPos) { delete StartPos; StartPos = nullptr; }
	if (EndPos) { delete EndPos; EndPos = nullptr; }
	if (PosCount) { delete PosCount; PosCount = nullptr; }
	if (PosCountPlus) { delete PosCountPlus; PosCountPlus = nullptr; }
}
void MoveCamera::CameraStart(Vector3f start, Vector3f end, float second) {
	*StartPos = start;
	*EndPos = end;

	*PosCount = start;
	if (second == 0) { *PosCountPlus = (end - start); }
	else { *PosCountPlus = (end - start) / second; }

	maxTime = second;
	isStart = true;
}

void NoteEffect::Start() {
	collider = gameobject->AddComponent<PolygonCollider>();
	target = scene->GetGameObject(Tag_JudgmentLine);
}
void NoteEffect::Update() {
	if (collider->isCollision(target) || gameobject->pos->y >= *JudgmentLine::PosY) {
		auto* effector = scene->GetGameObject<NoneObject>(L"Effector");

		for (auto& effect : effects) {
		#define EP effect.EPara

			switch (effect.EType) {
			case Set_BPM: {
				NoteDown::bpm = EP[0];
				NoteDown::bpm60 = 60 / NoteDown::bpm;
			} break;
			case Gradation: {
				effector->AddComponent<GradationEffect>()
					->GradationStart(Vector3f{ EP[0], EP[1], EP[2] }, Vector3f{ EP[3], EP[4], EP[5] }, EP[6], static_cast<int>(EP[7]));
			} break;
			case Set_Camera: {
				effector->AddComponent<MoveCamera>()->CameraStart(Vector3f(EP[0], EP[1], 0), Vector3f(EP[2], EP[3], 0), EP[4]);
			} break;
			default: {} break;
			}
		}

		gameobject->RemoveComponent<NoteEffect>();
	}
}

void Filler::Awake() {
	Start = new Vector3f;
	End = new Vector3f;
}
void Filler::Update() {
	graphic.Fill(*gameobject->pos + *Start, *gameobject->pos + *End, color);
}
void Filler::Remove() {
	if (Start) { delete Start; Start = nullptr; }
	if (End) { delete End; End = nullptr; }
}

KeyCode GearButtonComp::code[4] = { KeyCode_D, KeyCode_F, KeyCode_J, KeyCode_K };
void GearButtonComp::Awake() {
	//color.SetColor(, GButton); 얘는 원래 색상이 예뻐서 건들일 필요 없을듯
	color.SetColor({ 51, 51, 51 }, GButtonBack);
	color.SetColor({ 102, 102, 153 }, GBottom);
}
void GearButtonComp::Update() {
	Vector3f Pos[2];

	Pos[0] = { -8 , 24, 1 };
	Pos[1] = { -13, 32, 1 };
		 if (keyboard.isKeyDown(code[0])) { graphic.Fill(Pos[0], Pos[1], Color); }
	else if (keyboard.isKeyHold(code[0])) { graphic.Fill(Pos[0], Pos[1], Color); }
	else								  { graphic.Fill(Pos[0], Pos[1], Color_Red); }

	Pos[0] = { -1, 24, 1 };
	Pos[1] = { -6, 32, 1 };
		 if (keyboard.isKeyDown(code[1])) { graphic.Fill(Pos[0], Pos[1], Color); }
	else if (keyboard.isKeyHold(code[1])) { graphic.Fill(Pos[0], Pos[1], Color); }
	else								  { graphic.Fill(Pos[0], Pos[1], Color_Red); }

	Pos[0] = { 1, 24, 1 };
	Pos[1] = { 6, 32, 1 };
		 if (keyboard.isKeyDown(code[2])) { graphic.Fill(Pos[0], Pos[1], Color); }
	else if (keyboard.isKeyHold(code[2])) { graphic.Fill(Pos[0], Pos[1], Color); }
	else								  { graphic.Fill(Pos[0], Pos[1], Color_Red); }

	Pos[0] = { 8 , 24, 1 };
	Pos[1] = { 13, 32, 1 };
		 if	(keyboard.isKeyDown(code[3])) { graphic.Fill(Pos[0], Pos[1], Color); }
	else if (keyboard.isKeyHold(code[3])) { graphic.Fill(Pos[0], Pos[1], Color); }
	else								  { graphic.Fill(Pos[0], Pos[1], Color_Red); }

	graphic.Fill({ -14, 35, 1 }, { 14, 23, 1 }, Color_Perple);
}
