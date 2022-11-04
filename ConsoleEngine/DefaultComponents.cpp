#include "DefaultComponents.h"

using namespace DefaultComponents;

void Camera::Awake() {
	COORD CameraSize = { 128, 72 };
	graphic.SetScreenSize(CameraSize);
	graphic.CameraPos = &gameobject->pos;
}
void Camera::Update() {
	graphic.Render();
}
void Camera::Remove() {
	
}

void Camera::SetCameraScale(COORD Scale) {
	graphic.SetScreenScale(Scale);
}
void Camera::SetCameraSize(COORD Size) {
	graphic.SetScreenSize(Size);
}

void PolygonRenderer::Awake() {
	gameobject->RemoveComponent<SpriteRenderer>();

	vertexCount = 0;
	color = Color_Black;
	isVisible = true;
}
void PolygonRenderer::Update() {
	Vector4 beforePos;

	if (!isVisible || vertexs.size() == 0) { return; }
	else { beforePos = vertexs.front().second; }

	for (auto& item : vertexs) {
		if (item.second != beforePos) {
			// Line에 좌표 넣기 전에 행렬 연산을 해야할거같음
			graphic.Line(item.second + gameobject->pos, beforePos + gameobject->pos, gameobject->pos.z, color);
			beforePos = item.second;
		}
	}

	graphic.Line(vertexs.back().second + gameobject->pos, vertexs.front().second + gameobject->pos, gameobject->pos.z, color);
}
void PolygonRenderer::Remove() {
	vertexs.clear();
}
Vector4* PolygonRenderer::AddVertex(Vector4 vertex) {
	vertexs.push_back({ ++vertexCount, vertex });

	return GetVertex(vertexCount);
}
Vector4* PolygonRenderer::GetVertex(int index) {
	for (auto& item : vertexs) {
		if (item.first == index) { return &item.second; }
	}
	return nullptr;
}
void PolygonRenderer::RemoveVertex() {
	vertexs.pop_back();
	vertexCount--;
}

void SpriteRenderer::Awake() {
	gameobject->RemoveComponent<PolygonRenderer>();

	sprite = nullptr;
	isVisible = true;
}
void SpriteRenderer::Update() {
	if (isVisible && sprite) {
		graphic.Sprite(gameobject->pos, size, sprite);
	}
}
void SpriteRenderer::Remove() {
	if (sprite) { delete[] sprite; sprite = nullptr; }
}

void SpriteRenderer::LoadSprite(string filename) {
	ifstream sp(filename + ".sprite");
	if (!sp.is_open() || sp.eof()) { sp.close(); return; }
	else { if (sprite) { delete[] sprite; sprite = nullptr; } }
	
	string lines;
	int length = 0;
	int index = 0;

	size = { SHRT_MAX, 0 };

	while (!sp.eof()) {
		getline(sp, lines);
		length = static_cast<int>(lines.length());
		if (size.X > length) { size.X = length; }
		size.Y++;
	}

	sp.close();


	sp.open(filename + ".sprite");
	sprite = new EnumColor[size.Y * size.X];

	while (!sp.eof()) {
		getline(sp, lines);
		for (int i = 0; i < size.X; i++) {
			switch (toupper(lines[i])) {
#pragma warning(push)
#pragma warning(disable:6386)
			case '0': { sprite[i + index] = Color_NULL;			} break;
			case '1': { sprite[i + index] = Color_Black;		} break;
			case '2': { sprite[i + index] = Color_Blue;			} break;
			case '3': { sprite[i + index] = Color_Green;		} break;
			case '4': { sprite[i + index] = Color_SkyBlue;		} break;
			case '5': { sprite[i + index] = Color_Red;			} break;
			case '6': { sprite[i + index] = Color_Perple;		} break;
			case '7': { sprite[i + index] = Color_Yellow;		} break;
			case '8': { sprite[i + index] = Color_White;		} break;
			case '9': { sprite[i + index] = Color_LightBlack;	} break;
			case 'A': { sprite[i + index] = Color_LightBlue;	} break;
			case 'B': { sprite[i + index] = Color_LightGreen;	} break;
			case 'C': { sprite[i + index] = Color_LightSkyBlue; } break;
			case 'D': { sprite[i + index] = Color_LightRed;		} break;
			case 'E': { sprite[i + index] = Color_LightPerple;	} break;
			case 'F': { sprite[i + index] = Color_LightYellow;	} break;
			case 'G': { sprite[i + index] = Color_LightWhite;	} break;
			default:  { sprite[i + index] = Color_NULL;			} break;
#pragma warning(pop)
			}
		}

		index += size.X;
	}

	sp.close();
}
