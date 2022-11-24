#include "Components.h"

void Text::Awake() {
	COORD size = { 8, 16 };
	graphic.SetScreenScale(size);

	size = { 64, 18 };
	graphic.SetScreenSize(size);
	
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}
void Text::Start() {
	client = gameobject->AddComponent<Client>();
	client->JoinServer(client->GetMyIP(), 3197);
}
void Text::Update() {
	Message = client->GetMsg();
	if (Message != "") { cout << '\n' << Message; }
}
