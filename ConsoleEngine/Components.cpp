#include "Components.h"

using namespace Components;

// [ Camera Component ]
void Camera::Awake() {
	COORD CameraSize = { 128, 72 };
	graphic.SetScreenSize(CameraSize);
	graphic.CameraPos = gameobject->pos;
	graphic.CameraRotate = gameobject->rotate;
}
void Camera::Update() { graphic.Render(); }
void Camera::SetCameraScale (short Scale) { graphic.SetScreenScale({ Scale, Scale }); }
void Camera::SetCameraScale (short ScaleW, short ScaleH) { graphic.SetScreenScale({ ScaleW, ScaleH }); }
void Camera::SetCameraScale	(COORD Scale) { graphic.SetScreenScale(Scale); }
void Camera::SetCameraSize	(COORD Size ) { graphic.SetScreenSize (Size ); }

// [ PolygonRenderer Component ]
void PolygonRenderer::Awake () {
	gameobject->RemoveComponent<SpriteRenderer>();
	vertices.reserve(32);
	edges.reserve(32);
	verticesRealPos.reserve(32);

	vertexCount = 0;
	isFill = false;
	
	beforePos = new Vector3f;
}
void PolygonRenderer::Update() {
	isUpdateEdge = false;
	
	if (vertexCount <= 0) { return; }
	else { *beforePos = *vertices.front(); }

	Matrix4x4f Trans = graphic.GetTranslate(*gameobject->pos, gameobject->GetRotate(), *gameobject->scale);

	if (isVisible) {
		for (unsigned int i = 0; i < vertexCount; i++) {
			if (*vertices[i] != *beforePos) {
				graphic.Line(*vertices[i], *beforePos, Trans, color);

				*beforePos = *vertices[i];
			}
			*verticesRealPos[i] = *vertices[i] * Trans;
		}
		graphic.Line(*vertices[vertexCount - 1], *vertices[0], Trans, color);
	}
	else {
		for (unsigned int i = 0; i < vertexCount; i++) {
			*verticesRealPos[i] = *vertices[i] * Trans;
		}
	}

	if (isFill) { graphic.Mask(Vector3f::ONE * Trans, color); }
}
void PolygonRenderer::Remove() {
	if (beforePos) { delete beforePos; beforePos = nullptr; }

	for (auto& item : vertices) {
		if (item) { delete item; item = nullptr; }
	}
	for (auto& item : edges) {
		if (item) { delete item; item = nullptr; }
	}
	for (auto& item : verticesRealPos) {
		if (item) { delete item; item = nullptr; }
	}

	vertices.~vector();
	edges.~vector();
	verticesRealPos.~vector();
}
Vector3f* PolygonRenderer::AddVertex(float x, float y) {
	vertices	   .push_back(new Vector3f(x, y, 0));
	verticesRealPos.push_back(new Vector3f);
	edges		   .push_back(new Vector3f);

	return vertices[vertexCount++];
}
Vector3f* PolygonRenderer::GetVertex(unsigned int index) {
	return (index >= vertexCount) ? nullptr : vertices[index];
}
void PolygonRenderer::RemoveVertex() {
	if (vertexCount > 0) { 
		int index = --vertexCount;

		if (vertices	   [index]) { delete vertices		[index]; vertices		[index] = nullptr; }
		if (verticesRealPos[index]) { delete verticesRealPos[index]; verticesRealPos[index] = nullptr; }
		if (edges		   [index]) { delete edges			[index]; edges			[index] = nullptr; }

		vertices	   .pop_back();
		verticesRealPos.pop_back();
		edges		   .pop_back();
	}
}
const vector<Vector3f*>& PolygonRenderer::GetEdge() {
	if (isUpdateEdge) { return edges; }
	else {
		// 점이 두개 이상 있을 때
		if (vertexCount >= 2) {
			edgeCount = 0;

			for (unsigned int index = 1; index < vertexCount; index++) {
				*edges[index - 1] = *verticesRealPos[index] - *verticesRealPos[index - 1];
				edgeCount++;
			}

			*edges[edgeCount - 1] = (*verticesRealPos[0] - *verticesRealPos[vertexCount - 1]);
		}

		isUpdateEdge = true;
		return edges;
	}
}

// [ PolygonCollider ]
void PolygonCollider::projectPolygon(Vector3f& axis, PolygonRenderer& polygon, Vector3f* maxmin) {
#define minThis maxmin->x
#define maxThis maxmin->y

	float dp = axis.dotProduct(*polygon.verticesRealPos[0]);
	minThis = dp;
	maxThis = dp;

	for (unsigned int i = 0; i < polygon.vertexCount; i++) {
		dp = polygon.verticesRealPos[i]->dotProduct(axis);
			 if (dp < minThis) { minThis = dp; }
		else if (dp > maxThis) { maxThis = dp; }
	}
}
float PolygonCollider::distance(Vector3f& maxminA, Vector3f& maxminB) {
#define minA maxminA.x
#define maxA maxminA.y
#define minB maxminB.x
#define maxB maxminB.y

	return minA < minB ? minB - maxA : minA - maxB;
}
void PolygonCollider::Awake() {
	Polygon = gameobject->AddComponent<PolygonRenderer>();
}
bool PolygonCollider::isCollision(GameObject* object) {
	if (!object) { return false; }

	PolygonRenderer* poly = object->GetComponent<PolygonRenderer>();
	if (!poly || poly->vertexCount < 0) { return false; }

	Vector3f axis, edge;
	
	bool isCol = true;

	const vector<Vector3f*>& edgeThis = Polygon->GetEdge();
	const vector<Vector3f*>& edgeOther = poly->GetEdge();

	Vector3f This(0), Other(0);

	for (unsigned int edgeindex = 0, edgecount = Polygon->edgeCount + poly->edgeCount; edgeindex < edgecount; edgeindex++) {
		edge =
			edgeindex < Polygon->edgeCount ?
			*edgeThis[edgeindex] :
			*edgeOther[edgeindex - Polygon->edgeCount];

		axis = edge.product2D().normalize();

		projectPolygon(axis, *Polygon, &This);
		projectPolygon(axis, *poly, &Other);

		if (distance(This, Other) > 0) { isCol = false; break; }
	}

	if (isCol) { return true; }

	return isCol;
}
bool PolygonCollider::isCollision(GameObject* object, const Vector3f& velocity) {
	if (!object) { return false; }

	PolygonRenderer* poly = object->GetComponent<PolygonRenderer>();
	if (!poly || poly->vertexCount < 0) { return false; }

	Vector3f axis, edge;

	float velo = 0.0f;
	bool isCol = true;

	const vector<Vector3f*>& edgeThis = Polygon->GetEdge();
	const vector<Vector3f*>& edgeOther = poly->GetEdge();

	Vector3f This(0), Other(0);

	for (unsigned int edgeindex = 0, edgecount = Polygon->edgeCount + poly->edgeCount; edgeindex < edgecount; edgeindex++) {
		edge =
			edgeindex < Polygon->edgeCount ?
			*edgeThis[edgeindex] :
			*edgeOther[edgeindex - Polygon->edgeCount];

		axis = edge.product2D().normalize();


		projectPolygon(axis, *Polygon, &This);
		projectPolygon(axis, *poly, &Other);

		velo = axis.dotProduct(velocity);

		if (velo < 0) { This.x += velo; }
		else { This.y += velo; }

		if (distance(This, Other) > 0) { isCol = false; break; }
	}

	return isCol;
}
bool PolygonCollider::isCollision(list<GameObject*>& objects) {
	bool isCol = true;

	Vector3f axis, edge;
	Vector3f This(0), Other(0);
	for (auto& object : objects) {
		if (!object) { return false; }

		PolygonRenderer* poly = object->GetComponent<PolygonRenderer>();
		if (!poly || poly->vertexCount < 0) { return false; }

		const vector<Vector3f*>& edgeThis = Polygon->GetEdge();
		const vector<Vector3f*>& edgeOther = poly->GetEdge();

		isCol = true;

		for (unsigned int edgeindex = 0, edgecount = Polygon->edgeCount + poly->edgeCount; edgeindex < edgecount; edgeindex++) {
			edge =
				edgeindex < Polygon->edgeCount ?
				*edgeThis[edgeindex] :
				*edgeOther[edgeindex - Polygon->edgeCount];

			axis = edge.product2D().normalize();

			projectPolygon(axis, *Polygon, &This);
			projectPolygon(axis, *poly, &Other);

			if (distance(This, Other) > 0) { isCol = false; break; }
		}

		if (isCol) { return true; }
	}

	return false;
}
bool PolygonCollider::isCollision(list<GameObject*>& objects, const Vector3f& velocity) {
	float velo = 0.0f;
	bool isCol = true;

	Vector3f axis, edge;
	Vector3f This(0), Other(0);

	for (auto& object : objects) {
		if (!object) { return false; }

		PolygonRenderer* poly = object->GetComponent<PolygonRenderer>();
		if (!poly || poly->vertexCount < 0) { return false; }

		isCol = true;

		const vector<Vector3f*>& edgeThis = Polygon->GetEdge();
		const vector<Vector3f*>& edgeOther = poly->GetEdge();

		for (unsigned int edgeindex = 0, edgecount = Polygon->edgeCount + poly->edgeCount; edgeindex < edgecount; edgeindex++) {
			edge =
				edgeindex < Polygon->edgeCount ?
				*edgeThis[edgeindex] :
				*edgeOther[edgeindex - Polygon->edgeCount];

			axis = edge.product2D().normalize();


			projectPolygon(axis, *Polygon, &This);
			projectPolygon(axis, *poly, &Other);

			velo = axis.dotProduct(velocity);

			if (velo < 0) { This.x += velo; }
			else { This.y += velo; }

			if (distance(This, Other) > 0) { isCol = false; break; }
		}

		if (isCol) { return true; }
	}

	return false;
}
Vector3f PolygonCollider::isCollisionVec(GameObject* object, const Vector3f& velocity) {
	if (!object) { return false; }

	PolygonRenderer* poly = object->GetComponent<PolygonRenderer>();
	if (!poly || poly->vertexCount < 0) { return false; }

	Vector3f axis, edge;

	float velo = 0.0f;
	bool isCol = true;

	const vector<Vector3f*>& edgeThis = Polygon->GetEdge();
	const vector<Vector3f*>& edgeOther = poly->GetEdge();

	Vector3f This(0), Other(0);

	for (unsigned int edgeindex = 0, edgecount = Polygon->edgeCount + poly->edgeCount; edgeindex < edgecount; edgeindex++) {
		edge =
			edgeindex < Polygon->edgeCount ?
			*edgeThis[edgeindex] :
			*edgeOther[edgeindex - Polygon->edgeCount];

		axis = edge.product2D().normalize();


		projectPolygon(axis, *Polygon, &This);
		projectPolygon(axis, *poly, &Other);

		velo = axis.dotProduct(velocity);

		if (velo < 0) { This.x += velo; }
		else { This.y += velo; }

		if (distance(This, Other) > 0) { isCol = false; break; }
	}

	if (isCol)	{ return Vector3f(0, 0, 0); }
	else		{ return velocity; }
}
Vector3f PolygonCollider::isCollisionVec(list<GameObject*>& objects, const Vector3f& velocity) {
	float velo = 0.0f;
	bool isCol = true;

	Vector3f axis, edge;
	Vector3f This(0), Other(0);

	for (auto& object : objects) {
		if (!object) { return false; }

		PolygonRenderer* poly = object->GetComponent<PolygonRenderer>();
		if (!poly || poly->vertexCount < 0) { return false; }

		isCol = true;

		const vector<Vector3f*>& edgeThis = Polygon->GetEdge();
		const vector<Vector3f*>& edgeOther = poly->GetEdge();

		for (unsigned int edgeindex = 0, edgecount = Polygon->edgeCount + poly->edgeCount; edgeindex < edgecount; edgeindex++) {
			edge =
				edgeindex < Polygon->edgeCount ?
				*edgeThis[edgeindex] :
				*edgeOther[edgeindex - Polygon->edgeCount];

			axis = edge.product2D().normalize();


			projectPolygon(axis, *Polygon, &This);
			projectPolygon(axis, *poly, &Other);

			velo = axis.dotProduct(velocity);

			if (velo < 0) { This.x += velo; }
			else { This.y += velo; }

			if (distance(This, Other) > 0) { isCol = false; break; }
		}

		if (isCol) { return Vector3f(0, 0, 0); }
	}

	return velocity;
}

// [ SpriteRenderer Component ]
void SpriteRenderer::Awake() {
	gameobject->RemoveComponent<PolygonRenderer>();
	isVisible = true;
}
void SpriteRenderer::Update() {
	if (isVisible && sprite.sprite) {
		graphic.DrawSprite(*gameobject->pos, gameobject->GetRotate(), *gameobject->scale, sprite);
	}
}
void SpriteRenderer::Remove() {
	if (!isNotRemoveSprite) { sprite.~Sprite(); }
}

// [ CircleRenderer Component ]
void CircleRenderer::Awake() {
	radius = 0.0f;
	curvature = 0.0f;
}
void CircleRenderer::Update() {
	if (isVisible) {
		graphic.Circle(*gameobject->pos, gameobject->GetRotate(), *gameobject->scale, color, radius, static_cast<int>(curvature));
		if (isFill) { graphic.Mask(*gameobject->pos, color); }
	}
}

// [ Animator Component ]
void Animator::Awake() {
	spriterenderer = gameobject->AddComponent<SpriteRenderer>();
	spriterenderer->isNotRemoveSprite = true;
	
	time = 0.0f;
	index = 0;
}
void Animator::Update() {
#define animations animation.animations
	if (animations.empty()) { return; }

	if (time >= animations[index].first) {
		time -= animations[index].first;
		spriterenderer->sprite = animations[index].second;

		if (++index >= animations.size()) { index = 0; }
	}
	else {
		spriterenderer->sprite = animations[index].second;
		time += Time::GetDeltaTime();
	}
}
void Animator::Remove() {
	animations.~vector();
}

// [ Audio Component ]
void Audio::Awake() {
	SoundList.reserve(16);
}
void Audio::Remove() {
	for (const SoundInfo Item : SoundList) {
		mciSendCommand(Item.ID, MCI_CLOSE, 0, NULL);
	}
	SoundList.clear();
}
void Audio::LoadAudio(CString path, SoundType Type) {
	switch (Type) {
	case MP3: { AudioType = "mpegvideo"; } break;
	case WAV: { AudioType = "waveaudio"; } break;
	case AVI: { AudioType = "avivideo"; } break;
	}

	mciOpen.lpstrDeviceType = AudioType;
	mciOpen.lpstrElementName = path;
	SoundInfo soundinfo;
	soundinfo.Sound = mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)(LPVOID)&mciOpen);
	soundinfo.ID = mciOpen.wDeviceID;

	SoundList.push_back(soundinfo);
}
bool Audio::PlayAudio(UINT ID, bool isLoop) {
	for (auto& Sound : SoundList) {
		if (ID == Sound.ID) {
			mciSendCommand(ID, MCI_SEEK, MCI_SEEK_TO_START, NULL);
			if (isLoop) { Sound.Sound = mciSendCommand(ID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&mciPlay); }
			else		{ Sound.Sound = mciSendCommand(ID, MCI_PLAY, MCI_NOTIFY		   , (DWORD)(LPVOID)&mciPlay); }
			return true;
		}
	}
	return false;
}
void Audio::RePlayAudio(UINT ID) { mciSendCommand(ID, MCI_RESUME, 0, NULL); }
void Audio::PauseAudio (UINT ID) { mciSendCommand(ID, MCI_PAUSE, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay); }
void Audio::CloseAudio(UINT ID) { mciSendCommand(ID, MCI_CLOSE, 0, NULL); }

// [ Server Component ]
const int Server::PACKET_SIZE = 4096;
void Server::Awake() {
#define sSocket server.socket
#define sAddrIn server.addr_in
#define sAddrSz server.addr_size
	gameobject->RemoveComponent<Client>();
	clients.reserve(16);
	isServerOpen = false;
}
void Server::Update() {
	if (!recvMsg.empty()) {
		nowMsg = recvMsg.front();
		recvMsg.pop();
	}
	else { nowMsg.clear(); }
}
void Server::Remove() {
	CloseServer();
}
void Server::acceptClient() {
	while (!WSAGetLastError()) {
		SOCKET_ Client{};
		Client.addr_in = {};
		Client.addr_size = sizeof(Client.addr_in);
		Client.socket = accept(sSocket, (SOCKADDR*)&Client.addr_in, &Client.addr_size);

		if (Client.socket == INVALID_SOCKET) {
			Debug::Log("[ Server ] Client Connect Error!");
			closesocket(Client.socket);
			continue;
		}
		clients.push_back(Client);

		thread([&]() { recvClient(&clients[clients.size() - 1]); }).detach();
	}
}
void Server::recvClient(SOCKET_* Client) {
	int recvResult = 0;
	char Msg[PACKET_SIZE];

	while (!WSAGetLastError()) {
		ZeroMemory(Msg, PACKET_SIZE);
		recvResult = recv(Client->socket, Msg, PACKET_SIZE, 0);

		if (recvResult == 0 || recvResult == SOCKET_ERROR) { break; }

		recvMsg.push(Msg);
	}
}
bool Server::OpenServer(int port) {
	if (isServerOpen) { return true; }

	if (WSAStartup(MAKEWORD(2, 2), &wsaData)) {
		Debug::Log("[ Server ] WSA Error!");
		WSACleanup();
		return false;
	}

	sSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sSocket == INVALID_SOCKET) {
		Debug::Log("[ Server ] Socket Error!");
		WSACleanup();
		return false;
	}

	sAddrIn.sin_family = AF_INET;
	sAddrIn.sin_port = htons(port);
	sAddrIn.sin_addr.s_addr = htonl(INADDR_ANY);

	sAddrSz = sizeof(sAddrIn);
	if (bind(sSocket, (SOCKADDR*)&sAddrIn, sAddrSz)) {
		Debug::Log("[ Server ] bind Error!");
		closesocket(sSocket);
		WSACleanup();
		return false;
	}
	if (listen(sSocket, SOMAXCONN)) {
		Debug::Log("[ Server ] listen Error!");
		closesocket(sSocket);
		WSACleanup();
		return false;
	}
	
	thread([&]() { acceptClient(); }).detach();

	isServerOpen = true;
	return true;
}
bool Server::CloseServer() {
	if (!isServerOpen) { return true; }

	closesocket(sSocket);
	for (auto& Client : clients) { closesocket(Client.socket); }
	
	WSACleanup();
	isServerOpen = false;
	return true;
}
void Server::sendMsgAll(string msg) {
	if (msg.length() > PACKET_SIZE) { msg.erase(PACKET_SIZE, msg.length()); }

	for (auto& Client : clients) {
		send(Client.socket, msg.c_str(), msg.length(), 0);
	}
}
string Server::GetMsg() {
	return nowMsg;
}

// [ Client Component ]
const int Client::PACKET_SIZE = 4096;
void Client::Awake() {
#define cSocket client.socket
#define cAddrIn client.addr_in
#define cAddrSz client.addr_size
	gameobject->RemoveComponent<Server>();
	isJoinServer = false;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData)) {
		Debug::Log("[ Client ] WSA Error!");
		WSACleanup();
	}
}
void Client::Update() {
	if (!recvMsg.empty()) {
		try {
			nowMsg = recvMsg.front();
			recvMsg.pop();
		}
		catch (exception e) {
			cout << e.what();
			nowMsg.clear();
			return;
		}
	}
	else { nowMsg.clear(); }
}
void Client::Remove() {
	ExitServer();
}
void Client::recvServer() {
	int recvResult = 0;
	char Msg[PACKET_SIZE];

	while (!WSAGetLastError()) {
		ZeroMemory(Msg, PACKET_SIZE);
		recvResult = recv(cSocket, Msg, PACKET_SIZE, 0);

		if (recvResult == 0 || recvResult == SOCKET_ERROR) { break; }

		recvMsg.push(Msg);
	}

	ExitServer();
}
bool Client::JoinServer(string ip, int port) {
	if (isJoinServer) { return true; }

	cSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (cSocket == INVALID_SOCKET) {
		Debug::Log("[ Client ] Socket Error! in " + ip + " [port:" + to_string(port) + "]");
		closesocket(cSocket);
		WSACleanup();
		return false;
	}

	cAddrIn.sin_family = AF_INET;
	cAddrIn.sin_port = htons(port);
	cAddrIn.sin_addr.s_addr = inet_addr(ip.c_str());

	cAddrSz = sizeof(client.addr_in);
	if (connect(cSocket, (SOCKADDR*)&cAddrIn, cAddrSz)) {
		Debug::Log("[ Client ] Connect Error! in " + ip + " [port:" + to_string(port) + "]");
		closesocket(cSocket);
		WSACleanup();
		return false;
	}

	thread([&]() { recvServer(); }).detach();

	isJoinServer = true;
	return true;
}
bool Client::ExitServer() {
	if (!isJoinServer) { return true; }

	closesocket(cSocket);

	WSACleanup();
	isJoinServer = false;
	return true;
}
void Client::sendMsg(string msg) {
	if (msg.length() > PACKET_SIZE) { msg.erase(PACKET_SIZE, msg.length()); }
	send(cSocket, msg.c_str(), msg.length(), 0);
}
string Client::GetMsg() {
	return nowMsg;
}

string Client::GetMyIP() {
	if (myIP != "") { return myIP; }
	 
	char HostName[255];
	if (gethostname(HostName, sizeof(HostName))) { return ""; }

	PHOSTENT Info = gethostbyname(HostName);
	if (!Info) { return ""; }

	in_addr* pAddr = (in_addr*)Info->h_addr_list[0];
	if (!pAddr) { return ""; }

	return (myIP = to_string(pAddr->s_net) + "." + to_string(pAddr->s_host) + "." + to_string(pAddr->s_lh) + "." + to_string(pAddr->s_impno));
}
bool Client::isJoin() {
	return isJoinServer;
}