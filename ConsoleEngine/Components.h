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

namespace Components {
	class Camera : public Component {
	private:
		void Awake() final override;
		void Update() final override;
		void Remove() final override;

	public:
		void SetCameraScale(COORD Scale);
		void SetCameraSize(COORD Size);
	};
	class PolygonRenderer : public Component {
	private:
		int vertexCount = 0;
		list<pair<int, Vector4f*>> vertexs;

		Vector4f* start = nullptr;
		Vector4f* end = nullptr;
		Vector4f* beforePos = nullptr;

		void Awake() final override;
		void Update() final override;
		void Remove() final override;
	public:
		Vector4f* AddVertex(float x, float y);
		Vector4f* GetVertex(int index);
		void RemoveVertex();

		EnumColor color = Color_NULL;
		bool isVisible;
	};
	class SpriteRenderer : public Component {
	private:
		void Awake() final override;
		void Update() final override;
		void Remove() final override;

	public:
		Sprite sprite;
		bool isVisible = true
	};
	class Animator : public Component {
	private:
		SpriteRenderer* spriterenderer = nullptr;
		float time = 0.0f;
		size_t index = 0;

		void Awake() final override;
		void Update() final override;
		void Remove() final override;

	public:
		Animation animation;
	};
}

#endif // !___DEFAULTCOMPONENTS___

