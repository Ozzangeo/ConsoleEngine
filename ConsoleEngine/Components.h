#ifndef ___DEFAULTCOMPONENTS___
#define ___DEFAULTCOMPONENTS___

#include "stdafx.h"
#include "Component.h"
#include "GameObject.h"
#include "Graphic.h"
#include "Color.h"
#include "Math.h"

#include "Vector.h"
#include "Matrix.h"

#include "Sprite.h"
#include "Animation.h"

using namespace std;
using namespace chrono;

class Scene;
namespace Components {
	// 이 컴포넌트는 씬당 웬만하면 하나만 있게 하는걸 추천
	class Camera : public Component {					  
	private:											  
		void Awake() final override;					  
		void Update() final override;			  
														  
	public:												  
		void SetCameraScale(COORD Scale);				  
		void SetCameraScale(short Scale);				  
		void SetCameraScale(short ScaleW, short ScaleH);  
		void SetCameraSize (COORD Size );				  
	};													  
	///////////////////////////////////////////////////////
	
	class PolygonRenderer : public Component {
		friend class PolygonCollider;
	private:
		unsigned int vertexCount = 0;
		vector<Vector3f*> vertices;
		vector<Vector3f*> verticesRealPos;

		bool isUpdateEdge = false;
		unsigned int edgeCount = 0;
		vector<Vector3f*> edges;

		Vector3f* beforePos = nullptr;

		void Awake() final override;
		void Update() final override;
		void Remove() final override;
	public:
		EnumColor color = Color_LightWhite;
		bool isVisible = true;

		// 사실상 베타적 기능
		bool isFill;

		Vector3f* AddVertex(float x, float y);
		Vector3f* GetVertex(unsigned int index);
		void RemoveVertex();

		const vector<Vector3f*>& GetEdge();
	};
	class PolygonCollider : public Component {
	private:
		PolygonRenderer* Polygon = nullptr;

		void projectPolygon(Vector3f& axis, PolygonRenderer& polygon, Vector3f* maxmin);
		float distance(Vector3f& maxminA, Vector3f& maxminB);

		void Awake() final override;

	public:
		// OBB(SAT) 알고리즘 이용
		bool isCollision(GameObject* object);
		bool isCollision(GameObject* object, const Vector3f& velocity);
		bool isCollision(list<GameObject*>& objects);
		bool isCollision(list<GameObject*>& objects, const Vector3f& velocity);

		Vector3f isCollisionVec(GameObject* object, const Vector3f& velocity);
		Vector3f isCollisionVec(list<GameObject*>& objects, const Vector3f& velocity);
	};
	class SpriteRenderer : public Component {
	private:
		void Awake() final override;
		void Update() final override;

	public:
		Sprite sprite;
		bool isVisible = true;
	};
	class CircleRenderer : public Component {
	private:
		void Awake() override;
		void Update() override;
		
	public:
		EnumColor color = Color_LightWhite;
		bool isVisible = true;
		bool isFill = false;

		float radius;
		float curvature;
	};
	class Animator : public Component {
	private:
		SpriteRenderer* spriterenderer = nullptr;
		float time = 0.0f;
		size_t index = 0;

		void Awake() final override;
		void Update() final override;

	public:
		Animation animation;
	};
	class Audio : public Component {
	private:
		class SoundInfo {
		public:
			DWORD Sound;
			UINT ID;
			SoundInfo(DWORD Sound = NULL, UINT ID = 0) {
				this->Sound = Sound;
				this->ID = ID;
			}
		};

		MCI_OPEN_PARMS mciOpen;
		MCI_PLAY_PARMS mciPlay;

		// mpegvideo : .mp3
		// waveaudio : .wav
		// avivideo  : .avi
		CString AudioType = "mpegvideo";
		vector<SoundInfo> SoundList;

		void Awake() final override;
		void Remove() final override;
	public:
		enum SoundType {
			MP3,
			WAV,
			AVI
		};
		void LoadAudio(CString path, SoundType Type = MP3);
		bool PlayAudio	(UINT ID, bool isLoop = false);
		void RePlayAudio(UINT ID);
		void PauseAudio	(UINT ID);
		void CloseAudio (UINT ID);
	};
	class Server : public Component {
	private:
		struct SOCKET_ {
			SOCKET socket;
			SOCKADDR_IN addr_in;
			int addr_size;
		};

		WSADATA wsaData;
		bool isServerOpen;

		SOCKET_ server;
		vector<SOCKET_> clients;

		queue<string> recvMsg;
		string nowMsg;

		void Awake() override;
		void Update() override;
		void Remove() override;

		void acceptClient();
		void recvClient(SOCKET_* Client);

	public:
		static const int PACKET_SIZE;

		bool OpenServer(int port);
		bool CloseServer();
		
		void sendMsgAll(string msg);
		string GetMsg();
	};
	class Client : public Component {
	private:
		struct SOCKET_ {
			SOCKET socket;
			SOCKADDR_IN addr_in;
			int addr_size;
		};

		WSADATA wsaData;
		bool isJoinServer;

		SOCKET_ client;

		queue<string> recvMsg;
		string nowMsg;
		string myIP = "";

		void Awake() override;
		void Update() override;
		void Remove() override;

		void recvServer();

	public:
		static const int PACKET_SIZE;

		bool JoinServer(string ip, int port);
		bool ExitServer();

		void sendMsg(string msg);
		string GetMsg();

		string GetMyIP();
		bool isJoin();
	};
};

#endif // !___DEFAULTCOMPONENTS___

