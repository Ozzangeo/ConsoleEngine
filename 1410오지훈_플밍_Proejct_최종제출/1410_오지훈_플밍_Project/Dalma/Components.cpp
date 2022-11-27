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
	case 0: { manager->ChangeScene<DalmaList>(); system("cls"); } break;
	case 1: { manager->ChangeScene<DalmaCredit>(); system("cls"); } break;
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
string AmladPlayer::path = "";
void AmladPlayer::Start() {
	Nums[0] = scene->GetGameObject(L"100")->GetComponent<SpriteNum>();
	Nums[1] = scene->GetGameObject(L"10")->GetComponent<SpriteNum>();
	Nums[2] = scene->GetGameObject(L"1")->GetComponent<SpriteNum>();

	audio = gameobject->AddComponent<Audio>();
}
void AmladPlayer::Update() {
	if (isReady && PlayTime > 1.0f) { isReady = false; audio->PlayAudio(1); }
	if (keyboard.isKeyDown(KeyCode_ESC)) {
		audio->CloseAudio(1);

		SceneManager::GetInstance().ChangeScene<DalmaList>();
	}

	Nums[0]->ChangeNum(static_cast<int>(Combo * 0.01f));
	Nums[1]->ChangeNum(static_cast<int>(Combo * 0.1f));
	Nums[2]->ChangeNum(Combo);

	while (!Notes.empty()) {
		NoteInfo noteInfo = Notes.front();
		noteInfo.Time *= NoteDown::bpm60;

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
		Notes.pop();

		PlayTime += Time::GetDeltaTime();
		ExTime += Time::GetDeltaTime() - noteInfo.Time;

		if (Notes.empty()) {
			isEnd = true;
			start = chrono::system_clock::now();
		}
	}

	if (isEnd && duration<float>(chrono::system_clock::now() - start).count() > 5.0f) {
		audio->CloseAudio(1);

		if (Combo > MaxCombo) { MaxCombo = Combo; }
		ofstream result("Datas/DalmaResult.txt");
		if(result.fail()) {
			SceneManager::GetInstance().ChangeScene<DalmaMain>();

			result.close();
			SceneManager::GetInstance().ChangeScene<DalmaResult>();
		}

		result << "PlaySong=" << artist << "\n";
		result << "Perfect=" << to_string(Perfect) << "\n";
		result << "Great=" << to_string(Great) << "\n";
		result << "Miss=" << to_string(Miss) << "\n";

		try { result << "Accuracy=" << to_string(((Perfect * 100.0f) + (Great * 60.0f) + (Miss * 0.0f)) / (Perfect + Great + Miss)) << "%\n"; }
		catch (exception e) { result << "Accuracy=" << to_string(0) << "%\n"; }

		result << "MaxCombo=" << to_string(MaxCombo) << "\n";

		result.close();

		SceneManager::GetInstance().ChangeScene<DalmaResult>();
	}
}
void AmladPlayer::Remove() {}
bool AmladPlayer::OpenAmlad(string path) {
	if (!isStart) {
		Perfect = 0;
		Great = 0;
		Miss = 0;
		Combo = 0;
		MaxCombo = 0;

		ifstream Amlad("Amlads/" + path);
		if (Amlad.fail()) { Amlad.close(); return false; }

		string text;
		string buf;

/*  [ �о���� ���� ] �۰ - ���̸� - ���� ���� ���(path) - bpm - ������ */ #pragma region ...
		getline(Amlad, artist);		// �۰ ��
		getline(Amlad, text);		// �� �̸�
		artist += " - " + text;		// Artist - Song ����

		getline(Amlad, text);		// ���� Path
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

		// ���� ����
		while (getline(Amlad, text)) {
			// ��Ȯ�� ������ ���� �� ���� ����
			for (int i = 0, size = text.length(); i < size; i++) { if (text[i] != ' ') { text.erase(0, i); break; } }
			if (text == "[ Start ]") { break; }
		}

		// ��Ʈ �ҷ�����
		while (getline(Amlad, text)) {
			if (text == "[ End ]") { break; }

			stringstream ss(text);

			NoteInfo note;

/* ([����], [�Ÿ�]), [����Ʈ].. */ #pragma region ...
			// [ ���� ]
			getline(ss, buf, ',');
			for (int i = 0, size = buf.length(); i < size; i++) { if (buf[i] != ' ') { buf.erase(0, i); break; } }
			if (buf[0] == '(') { buf.erase(0, 1); }

			try { note.Line = stof(buf); }
			catch (exception e) { note.Line = 0; }

			// [ �ð� ]
			getline(ss, buf, ',');
			try { note.Time = stof(buf); }
			catch (exception e) { note.Time = 0; }
#pragma endregion

			// [ ����Ʈ ]
			vector<float> para;

			while (getline(ss, buf, ',')) {
				para.clear();

				for (int i = 0, size = buf.length(); i < size; i++) { if (buf[i] != ' ') { buf.erase(0, i); break; } }

				// ���ڸ� ���� �����ؼ� �׿� �´� ����Ʈ �Լ� ��ȣ �߰�
				switch (buf[0]) {
				case Set_BPM: {
					// �չ�ȣ ����
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

	graphic.Fill({ -14, 35, 1 }, { 14, 21, 1 }, Color_Perple);
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
	color.SetColor({ 51, 102, 51 }, 0);
	/* �̷� ������ ��ȣ�� ��°�� �ۿ����� region���θ�.. */ {
		string text;
		string buf;
		ifstream result("Datas/DalmaResult.txt");

		if (result.fail()) {
			SceneManager::GetInstance().ChangeScene<DalmaList>();
		}

		// ��Ƽ��Ʈ - �뷡
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

		// Accuracy
		getline(result, text);
		ss.clear();
		ss.str(text);

		getline(ss, buf, '=');
		getline(ss, buf, '=');
		try { accuracy = stof(buf); }
		catch (exception e) { accuracy = 0; }

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

		if (round(accuracy) > round(nowAccuracy))		{ nowAccuracy += accuracy * Time::GetDeltaTime() * (25.0f / accuracy); }
		else { nowAccuracy = accuracy; }

		if (maxCombo > round(nowCombo))		{ nowCombo += maxCombo * Time::GetDeltaTime() * 0.4f; }
		else {
			nowCombo = maxCombo;
			if (miss == 0) { isFull = true; }
		}
		
		if (nowPerfect == perfect &&
			nowGreat == great &&
			nowMiss == miss && 
			nowAccuracy == accuracy &&
			nowCombo == maxCombo) { isDone = false; }
	}
	nums[0]->ChangeNum(static_cast<int>(nowCombo * 0.01f));
	nums[1]->ChangeNum(static_cast<int>(nowCombo * 0.1f));
	nums[2]->ChangeNum(static_cast<int>(nowCombo));

	string accuracy = to_string(nowAccuracy);
	accuracy.erase(accuracy.length() - 4, accuracy.length());

	graphic.Text(Vector3i(-30, -8, 0), artist);
	graphic.Text(Vector3i(-30, -2, 0), "Perfect : " + to_string(static_cast<int>(nowPerfect)));
	graphic.Text(Vector3i(-30, -1, 0), "Great : " + to_string(static_cast<int>(nowGreat)));
	graphic.Text(Vector3i(-30, 0, 0), "Miss : " + to_string(static_cast<int>(nowMiss)));
	graphic.Text(Vector3i(-30, 2, 0), "Accuracy : " + accuracy + "%");
	if(isFull) { graphic.Text(Vector3i(18, 3, 0), "Full Combo!"); }
		
	if (!isDone && keyboard.isKeyDown(KeyCode_ENTER)) { SceneManager::GetInstance().ChangeScene<DalmaList>(); }
}

void AmladList::Awake() {
	int i = 0;
	Amlads = new vector<pair<string, string>>;
	Amlads->reserve(64);

	string filename;
	string artist;
	string song;
	
	for (auto& file : filesystem::directory_iterator("Amlads")) {
		filename = file.path().filename().string();

		ifstream amlad("Amlads/" + filename);

		try {
			getline(amlad, artist);
			getline(amlad, song);

			Amlads->push_back({ artist + " - " + song, filename });
		}
		catch (exception e) { Debug::Log(e.what()); }

		amlad.close();
	}

	choice = static_cast<int>(round(Amlads->size() * 0.5f));
}
void AmladList::Update() {
	int i = 0;
	
	if (keyboard.isKeyDown(KeyCode_ESC)) {
		SceneManager::GetInstance().ChangeScene<DalmaMain>();
		system("cls");
		return;
	}
	if (keyboard.isKeyDown(KeyCode_ENTER)) {
		AmladPlayer::path = (*Amlads)[choice].second;
		SceneManager::GetInstance().ChangeScene<Dalma>();
		system("cls");
		return;
	}

	if (keyboard.isKeyDown(KeyCode_DOWN)) { choice++; }
	if (keyboard.isKeyDown(KeyCode_UP)) { choice--; }

	if (choice < 0) { choice = Amlads->size() - 1; }
	else if (choice >= static_cast<int>(Amlads->size())) { choice = 0; }
	
	for (auto& item : *Amlads) {
		graphic.Text({ 0, choice - i, 1 }, item.first);
		i++;
	}
}
void AmladList::Remove() {
	if (Amlads) { delete Amlads; Amlads = nullptr; }
}

void Credit::Awake() {
	start = system_clock::now();
}
void Credit::Update() {
	if (keyboard.isKeyDown(KeyCode_ESC)) {
		SceneManager::GetInstance().ChangeScene<DalmaMain>();
		system("cls");
		return;
	}

	if (!Egg && duration<float>(system_clock::now() - start).count() >= 523.0f) { Egg = true; scene->AddGameObject<NoneObject>(L"Sans")->AddComponent<SpriteRenderer>()->sprite.LoadSprite("Sprites/Sans"); }

	graphic.Text({ -17, -10, 0 }, "Console Engine v1.0 by 1410 Ozi");
	graphic.Text({ -5, -8, 0 }, "Dalma[RE]");
	graphic.Text({ -5, -5, 0 }, "[ Thanks ]");
	graphic.Text({ -6, -4, 0 }, "Teachar Umm");
	graphic.Text({ -4, -3, 0 }, "3401 Kdg");

	graphic.Text({ 40, 17, 0 }, "Latest Update 2022-11-25");
}

