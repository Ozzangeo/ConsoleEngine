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
		list<pair<int, Vector4f*>> vertexs;

		Vector4f* start;
		Vector4f* end;
		Vector4f* beforePos;

		void Awake() override;
		void Update() override;
		void Remove() override;
	public:
		Vector4f* AddVertex(float x, float y);
		Vector4f* GetVertex(int index);
		void RemoveVertex();

		EnumColor color;
		bool isVisible;
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

