#include "Sprite.h"

using namespace std;

Sprite::Sprite() {
	sprite = nullptr;
	size = { 0, 0 };
}
Sprite::~Sprite() {
	if (sprite) {
		delete[] sprite;
		sprite = nullptr;
	}
}
bool Sprite::LoadSprite(string filename) {
	ifstream sp(filename + ".sprite");
	if (sp.fail() || sp.eof()) { sp.close(); return false; }
	else { if (sprite) { delete[] sprite; sprite = nullptr; } }

	string lines;
	int length = 0;
	int index = 0;

	size = { SHRT_MAX, 0 };

	while (!sp.eof()) {
		getline(sp, lines);
		if (lines == "") { continue; }

		length = static_cast<int>(lines.length());
		if (size.X > length) { size.X = length; }
		size.Y++;
	}
	sprite = new EnumColor[size.Y * size.X];

	sp.close();
	sp.open(filename + ".sprite");

	while (!sp.eof()) {
		getline(sp, lines);
		if (lines == "") { continue; }

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

	return true;
}