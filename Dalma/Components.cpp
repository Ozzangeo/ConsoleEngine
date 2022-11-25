#include "Components.h"

using namespace std;
using namespace Components;

void ChoiceComp::Awake() {
	manager = &SceneManager::GetInstance();
}
void ChoiceComp::Update() {
	if (keyboard.isKeyDown(KeyCode_UP)) { choice--; }
	if (keyboard.isKeyDown(KeyCode_DOWN)) { choice++; }
	if (choice < 0) { choice = max - 1; }
	else if (choice >= max) { choice = 0; }

	switch (choice) {
		case 0: { gameobject->pos->y = 5.5f; } break;
		case 1: { gameobject->pos->y = 8; } break;
		case 2: { gameobject->pos->y = 11.5f; } break;
	}

	if(keyboard.isKeyDown(KeyCode_ENTER))
	switch (choice) {
		case 0: { manager->ChangeScene<DalmaList>(); } break;
		case 1: { manager->ChangeScene<DalmaCredit>(); } break;
		case 2: { manager->StopEngine(); } break;
	}

	graphic.Text({ -3, 5, 0 },  " Start");
	graphic.Text({ -3, 8, 0 },  "Credit");
	graphic.Text({ -3, 11, 0 }, " Exit");
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

float NoteDown::speed = 5.0f;
float NoteDown::bpm = 0.0f;
float NoteDown::bpm60 = 0.0f;
void NoteDown::Update() {
	*gameobject->pos += Vector3f(0, speed, 0) * Time::GetDeltaTime();
	if (gameobject->pos->y >= 50) {
		if (!isHit) {
			if (AmladPlayer::Combo > AmladPlayer::MaxCombo) { AmladPlayer::MaxCombo = AmladPlayer::Combo; }
			AmladPlayer::Miss++;
			AmladPlayer::Combo = 0;

			scene->GetGameObject(Tag_Line)->GetComponent<PolygonRenderer>()->color = Color_LightPerple;
			isHit = true;
		}
		
		scene->RemoveGameObject(gameobject);
	}
}

void NoteEffect::Start() {
	collider = gameobject->AddComponent<PolygonCollider>();
	target = scene->GetGameObject(Tag_JudgmentLine);
}
void NoteEffect::Update() {
	if (!isEnd) {
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
			isEnd = true;
		}
	}
}
void NoteEffect::UpdateNow() {
	if (!isEnd) {
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
		isEnd = true;
	}
}

int AmladPlayer::Perfect = 0;
int AmladPlayer::Great = 0;
int AmladPlayer::Miss = 0;
int AmladPlayer::Combo = 0;
int AmladPlayer::MaxCombo = 0;
wstring AmladPlayer::path = L"";
void AmladPlayer::Start() {
	Nums[0] = scene->GetGameObject(L"100")->GetComponent<SpriteNum>();
	Nums[1] = scene->GetGameObject(L"10")->GetComponent<SpriteNum>();
	Nums[2] = scene->GetGameObject(L"1")->GetComponent<SpriteNum>();

	audio = gameobject->AddComponent<Audio>();
}
void AmladPlayer::Update() {
	if (isReady && PlayTime > 1.0f) { isReady = false; audio->PlayAudio(1); }

	Nums[0]->ChangeNum(static_cast<int>(Combo * 0.01f));
	Nums[1]->ChangeNum(static_cast<int>(Combo * 0.1f));
	Nums[2]->ChangeNum(Combo);

	while (!Notes.empty()) {
		NoteInfo noteInfo = Notes.front();
		noteInfo.Time = noteInfo.Distance * NoteDown::bpm60;
		if (noteInfo.Time >= ExTime) {
			ExTime += Time::GetDeltaTime();
			PlayTime += Time::GetDeltaTime();
			break;
		}

		auto* nowNote = scene->AddGameObject<Note>(L"Note", Tag_Note);
		auto* Jud = nowNote->AddComponent<NoteJudgment>();

		auto* noteEffect = nowNote->AddComponent<NoteEffect>();
		noteEffect->effects = noteInfo.Effects;
		Jud->noteEffect = noteEffect;

		float BpmMul = (NoteDown::bpm * multiplespeed);
		 switch (static_cast<int>(noteInfo.Line)) {
		 case 1: { *nowNote->pos = Vector3f(-11, -BpmMul * 0.1f, nowNote->pos->z); Jud->code = GearButtonComp::code[0]; } break;
		 case 2: { *nowNote->pos = Vector3f(-4,  -BpmMul * 0.1f, nowNote->pos->z); Jud->code = GearButtonComp::code[1]; } break;
		 case 3: { *nowNote->pos = Vector3f( 3,  -BpmMul * 0.1f, nowNote->pos->z); Jud->code = GearButtonComp::code[2]; } break;
		 case 4: { *nowNote->pos = Vector3f(10,  -BpmMul * 0.1f, nowNote->pos->z); Jud->code = GearButtonComp::code[3]; } break;
		 default: { scene->RemoveGameObject(nowNote); } break;
		 }
		NoteDown::speed = BpmMul * 0.1f;

		ExTime -= noteInfo.Time;
		Notes.pop();

		PlayTime += Time::GetDeltaTime();
		ExTime += Time::GetDeltaTime();

		if (Notes.empty()) {
			isEnd = true;
			start = chrono::system_clock::now();
		}
	}

	if (isEnd && duration<float>(chrono::system_clock::now() - start).count() > 5.0f) {
		audio->CloseAudio(1);

		OutResult();
		SceneManager::GetInstance().ChangeScene<DalmaResult>();
	}
}
void AmladPlayer::Remove() {}
void AmladPlayer::OutResult() {
	if (Combo > MaxCombo) { MaxCombo = Combo; }
	ofstream result("DalmaResult.txt");

	result << "PlaySong=" << artist << "\n";
	result << "Perfect=" << to_string(Perfect) << "\n";
	result << "Great=" << to_string(Great) << "\n";
	result << "Miss=" << to_string(Miss) << "\n";
	result << "Avg=" << to_string(((Perfect * 100.0f) + (Great * 60.0f) + (Miss * 0.0f)) / (Perfect + Great + Miss)) << "%\n";
	result << "MaxCombo=" << to_string(MaxCombo) << "\n";

	result.close();
}
bool AmladPlayer::OpenAmlad(wstring path) {
	if (!isStart) {
		Perfect = 0;
		Great = 0;
		Miss = 0;
		Combo = 0;
		MaxCombo = 0;

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
bool AmladPlayer::OpenAmlad() {
	return OpenAmlad(path);
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
void GearButtonComp::Update() {
	Vector3f Pos[2];
	float y1 = 26, y2 = 34;

	Pos[0] = { -8 , y1, 1 };
	Pos[1] = { -13, y2, 1 };
	switch (keyboard.isKey(code[0])) {
	case KeyType_DOWN:
	case KeyType_HOLD: { graphic.Fill(Pos[0], Pos[1], Color); } break;
	case KeyType_NON: { graphic.Fill(Pos[0], Pos[1], Color_Red); } break;
	}

	Pos[0] = { -1, y1, 1 };
	Pos[1] = { -6, y2, 1 };
	switch (keyboard.isKey(code[1])) {
	case KeyType_DOWN:
	case KeyType_HOLD: { graphic.Fill(Pos[0], Pos[1], Color); } break;
	case KeyType_NON: { graphic.Fill(Pos[0], Pos[1], Color_Red); } break;
	}

	Pos[0] = { 1, y1, 1 };
	Pos[1] = { 6, y2, 1 };
	switch (keyboard.isKey(code[2])) {
	case KeyType_DOWN:
	case KeyType_HOLD: { graphic.Fill(Pos[0], Pos[1], Color); } break;
	case KeyType_NON: { graphic.Fill(Pos[0], Pos[1], Color_Red); } break;
	}

	Pos[0] = { 8 , y1, 1 };
	Pos[1] = { 13, y2, 1 };
	switch (keyboard.isKey(code[3])) {
	case KeyType_DOWN:
	case KeyType_HOLD: { graphic.Fill(Pos[0], Pos[1], Color); } break;
	case KeyType_NON: { graphic.Fill(Pos[0], Pos[1], Color_Red); } break;
	}

	graphic.Fill({ -14, 35, 1 }, { 14, 23, 1 }, Color_Perple);
}

void SceneMover::Update() {
	if (keyboard.isKeyDown(KeyCode_0)) { SceneManager::GetInstance().ChangeScene<Dalma>(); }
}

void NoteJudgment::Start() {
	objects[0] = scene->GetGameObject(Tag_Perfect);
	objects[1] = scene->GetGameObject(Tag_Great);
	objects[2] = scene->GetGameObject(Tag_Miss);

	collider = gameobject->AddComponent<PolygonCollider>();
	noteDown = gameobject->AddComponent<NoteDown>();
	renderer = scene->GetGameObject(Tag_Line)->AddComponent<PolygonRenderer>();
}
void NoteJudgment::Update() {
	if (keyboard.isKeyDown(code)) {
		if (collider->isCollision(objects[0])) {
			AmladPlayer::Perfect++;
			AmladPlayer::Combo++;
			
			renderer->color = Color_LightSkyBlue;
			noteDown->isHit = true;

			if (noteEffect) { noteEffect->UpdateNow(); }
		}
		else if (collider->isCollision(objects[1])) {
			AmladPlayer::Great++;
			AmladPlayer::Combo++;

			renderer->color = Color_LightRed;
			noteDown->isHit = true;

			if (noteEffect) { noteEffect->UpdateNow(); }
		}
		else if (collider->isCollision(objects[2])) {
			if (AmladPlayer::Combo > AmladPlayer::MaxCombo) { AmladPlayer::MaxCombo = AmladPlayer::Combo; }
			AmladPlayer::Miss++;
			AmladPlayer::Combo = 0;
			
			renderer->color = Color_LightPerple;
			noteDown->isHit = true;

			if (noteEffect) { noteEffect->UpdateNow(); }
		}
	}
}

void SpriteNum::Start() {
	renderer = gameobject->AddComponent<SpriteRenderer>();

	nums[0].LoadSprite("Text/Zero");
	nums[1].LoadSprite("Text/One");
	nums[2].LoadSprite("Text/Two");
	nums[3].LoadSprite("Text/Three");
	nums[4].LoadSprite("Text/Four");
	nums[5].LoadSprite("Text/Five");
	nums[6].LoadSprite("Text/Six");
	nums[7].LoadSprite("Text/Seven");
	nums[8].LoadSprite("Text/Eight");
	nums[9].LoadSprite("Text/Nine");

	renderer->sprite = nums[0];
}
void SpriteNum::ChangeNum(int num) {
	renderer->sprite = nums[(num % 10)];
}

void Result::Start() {
	/* 이런 간편한 괄호가 어째서 밖에서는 region으로만.. */ {
		string text;
		string buf;
		ifstream result("DalmaResult.txt");

		// 아티스트 - 노래
		getline(result, text);
		stringstream ss(text);

		getline(ss, buf, '=');
		getline(ss, buf, '=');
		artist = buf;

		// Perfect
		getline(result, text);
		ss.clear();
		ss.str(text);

		getline(ss, buf, '=');
		getline(ss, buf, '=');
		try { perfect = stof(buf); }
		catch (exception e) { perfect = 0; }

		// Great
		getline(result, text);
		ss.clear();
		ss.str(text);

		getline(ss, buf, '=');
		getline(ss, buf, '=');
		try { great = stof(buf); }
		catch (exception e) { great = 0; }

		// Miss
		getline(result, text);
		ss.clear();
		ss.str(text);

		getline(ss, buf, '=');
		getline(ss, buf, '=');
		try { miss = stof(buf); }
		catch (exception e) { miss = 0; }

		// Avg
		getline(result, text);
		ss.clear();
		ss.str(text);

		getline(ss, buf, '=');
		getline(ss, buf, '=');
		try { avg = stof(buf); }
		catch (exception e) { avg = 0; }

		// Max Combo
		getline(result, text);
		ss.clear();
		ss.str(text);

		getline(ss, buf, '=');
		getline(ss, buf, '=');
		try { maxCombo = stof(buf); }
		catch (exception e) { maxCombo = 0; }

		result.close();
	}
	
	nums[0] = scene->GetGameObject(L"100")->GetComponent<SpriteNum>();
	nums[1] = scene->GetGameObject(L"10")->GetComponent<SpriteNum>();
	nums[2] = scene->GetGameObject(L"1")->GetComponent<SpriteNum>();

	isDone = true;
}
void Result::Update() {
	if (isDone) {
		if (perfect > round(nowPerfect))	{ nowPerfect += perfect * Time::GetDeltaTime() * 0.4f; }
		else { nowPerfect = perfect; }

		if (great > round(nowGreat))		{ nowGreat += great * Time::GetDeltaTime() * 0.4f; }
		else { nowGreat = great; }

		if (miss > round(nowMiss))			{ nowMiss += miss * Time::GetDeltaTime() * 0.25f; }
		else { nowMiss = miss; }

		if (round(avg) > round(nowAvg))		{ nowAvg += avg * Time::GetDeltaTime() * (25.0f / avg); }
		else { nowAvg = avg; }

		if (maxCombo > round(nowCombo))		{ nowCombo += maxCombo * Time::GetDeltaTime() * 0.2f; }
		else { nowCombo = maxCombo; }

		if (nowPerfect == perfect &&
			nowGreat == great &&
			nowMiss == miss && 
			nowAvg == avg &&
			nowCombo == maxCombo) { isDone = false; }
	}
	nums[0]->ChangeNum(static_cast<int>(nowCombo * 0.01f));
	nums[1]->ChangeNum(static_cast<int>(nowCombo * 0.1f));
	nums[2]->ChangeNum(static_cast<int>(nowCombo));

	string avg = to_string(nowAvg);
	avg.erase(avg.length() - 4, avg.length());

	graphic.Text(Vector3i(-30, -8, 0), artist);
	graphic.Text(Vector3i(-30, -2, 0), "Perfect : " + to_string(static_cast<int>(nowPerfect)));
	graphic.Text(Vector3i(-30, -1, 0), "Great : " + to_string(static_cast<int>(nowGreat)));
	graphic.Text(Vector3i(-30, 0, 0), "Miss : " + to_string(static_cast<int>(nowMiss)));
	graphic.Text(Vector3i(-30, 2, 0), "Avg : " + avg + "%");
		
	if (!isDone && keyboard.isKeyDown(KeyCode_ENTER)) { SceneManager::GetInstance().ChangeScene<DalmaMain>(); }
}