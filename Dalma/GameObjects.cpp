#include "GameObjects.h"

void ServerObject::Components() {
	auto* server = AddComponent<Server>();
	server->OpenServer(3197);
}
