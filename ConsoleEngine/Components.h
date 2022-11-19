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
	class Camera : public Component {
	private:
		void Awake() final override;
		void Update() final override;
		void Remove() final override {}

	public:
		void SetCameraScale(COORD Scale);
		void SetCameraSize (COORD Size );
	};
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
		EnumColor color = Color_NULL;
		bool isVisible;

		Vector3f* AddVertex(float x, float y);
		Vector3f* GetVertex(unsigned int index);
		void RemoveVertex();

		const vector<Vector3f*>& GetEdge();
	};
	class PolygonCollider : public Component {
	private:
		PolygonRenderer* Polygon;

		void projectPolygon(Vector3f& axis, PolygonRenderer& polygon, Vector3f* maxmin);
		float distance(Vector3f& maxminA, Vector3f& maxminB);

		void Awake() final override;
		void Update() final override {}
		void Remove() final override {}

	public:
		bool isCollision(GameObject* object);
		bool isCollision(GameObject* object, const Vector3f& velocity);
		bool isCollision(list<GameObject*>& objects);
		bool isCollision(list<GameObject*>& objects, Vector3f& velocity);
	};
	class SpriteRenderer : public Component {
	private:
		void Awake() final override;
		void Update() final override;
		void Remove() final override {}

	public:
		Sprite sprite;
		bool isVisible = true;
	};
	class Animator : public Component {
	private:
		SpriteRenderer* spriterenderer = nullptr;
		float time = 0.0f;
		size_t index = 0;

		void Awake() final override;
		void Update() final override;
		void Remove() final override {}

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
		list<SoundInfo> SoundList;

		void Awake() final override {}
		void Update() final override {}
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
	};
};

#endif // !___DEFAULTCOMPONENTS___

