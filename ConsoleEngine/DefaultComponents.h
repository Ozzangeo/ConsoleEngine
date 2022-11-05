#ifndef ___DEFAULTCOMPONENTS___
#define ___DEFAULTCOMPONENTS___

#include "stdafx.h"
#include "Component.h"
#include "GameObject.h"
#include "Graphic.h"
#include "Color.h"
#include "Vector.h"

#include "Sprite.h"
#include "Animation.h"

using namespace std;
using namespace chrono;

namespace DefaultComponents {
	class Camera : public Component {
	private:
		void Awake() override;
		void Update() override;
		void Remove() override;

	public:
		void SetCameraScale(COORD Scale);
		void SetCameraSize(COORD Size);
	};
	class PolygonRenderer : public Component {
	private:
		int vertexCount;
		list<pair<int, Vector4>> vertexs;

		void Awake() override;
		void Update() override;
		void Remove() override;
	public:
		Vector4* AddVertex(Vector4 vertex);
		Vector4* GetVertex(int index);
		void RemoveVertex();

		EnumColor color;
		bool isVisible;
		float depth;
	};
	class SpriteRenderer : public Component {
	private:
		void Awake() override;
		void Update() override;
		void Remove() override;

	public:
		Sprite sprite;
		bool isVisible;
	};
	class Animator : public Component {
	private:
		SpriteRenderer* spriterenderer;
		float time;
		size_t index;

		void Awake() override;
		void Update() override;
		void Remove() override;

	public:
		Animation animation;
	};
}

#endif // !___DEFAULTCOMPONENTS___

