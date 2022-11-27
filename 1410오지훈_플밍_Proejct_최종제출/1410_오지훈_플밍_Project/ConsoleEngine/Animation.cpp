#include "Animation.h"

Animation::Animation() {}
Animation::~Animation() {
	animations.reserve(0);
}

bool Animation::LoadAnimaition(string filename) {
	ifstream ai(filename + ".anima");
	if (ai.fail() || ai.eof()) { ai.close(); return false; }
	else { animations.clear(); }

	string lines;
	size_t anicount = 0;
	size_t anisize = 0;
	int length = 0;
	int index = 0;

	// Sprite 갯수 세기
	while (!ai.eof()) {
		getline(ai, lines);
		if (lines[0] == '=') { anicount++; }
	}
	animations.resize(anicount);
	anisize = anicount;

	ai.close();
	ai.open(filename + ".anima");

#define AniSize animations[anicount].second.size
#define AniSprite animations[anicount].second.sprite

	// Sprite 용량 재기
	anicount = 0;
	while (!ai.eof()) {
		AniSize = { SHRT_MAX, 0 };

		while(!ai.eof()) {
			getline(ai, lines);
			if (lines == "") { continue; }
			if (lines[0] == '=') { break; }

			length = static_cast<int>(lines.length());
			if (AniSize.X > length) { AniSize.X = length; }
			AniSize.Y++;
		}

		if (AniSize.X * AniSize.Y != 0) { AniSprite = new EnumColor[AniSize.X * AniSize.Y]; }
		else { AniSprite = nullptr; }

		anicount++;
	}

	ai.close();
	ai.open(filename + ".anima");

#define AniTime animations[anicount].first

	// Time 정하고 Sprite 받기
	anicount = 0;
	while (!ai.eof()) {
		getline(ai, lines);
		if (lines == "") { continue; }

		if (lines[0] == '=') {
			// '=' 문자 제거
			lines.erase(0, 1);

			length = static_cast<int>(lines.length());
			for (int i = 0; i < length; i++) {
				// 만약 숫자가 아니라면
				if(lines[i] > 57 || 48 > lines[i]) {
					lines.erase(i, length);
					break;
				}
			}
			AniTime = (stoi(lines) * 0.001f);
			anicount++;
			index = 0;

			getline(ai, lines);
			if (lines == "") { continue; }
		}

		if (anicount == anisize) { break; }

		for (int i = 0; i < AniSize.X; i++) {
			switch (toupper(lines[i])) {
#pragma warning(push)
#pragma warning(disable:6386)
			case '0': { AniSprite[i + index] = Color_NULL;			} break;
			case '1': { AniSprite[i + index] = Color_Black;			} break;
			case '2': { AniSprite[i + index] = Color_Blue;			} break;
			case '3': { AniSprite[i + index] = Color_Green;			} break;
			case '4': { AniSprite[i + index] = Color_SkyBlue;		} break;
			case '5': { AniSprite[i + index] = Color_Red;			} break;
			case '6': { AniSprite[i + index] = Color_Perple;		} break;
			case '7': { AniSprite[i + index] = Color_Yellow;		} break;
			case '8': { AniSprite[i + index] = Color_White;			} break;
			case '9': { AniSprite[i + index] = Color_LightBlack;	} break;
			case 'A': { AniSprite[i + index] = Color_LightBlue;		} break;
			case 'B': { AniSprite[i + index] = Color_LightGreen;	} break;
			case 'C': { AniSprite[i + index] = Color_LightSkyBlue;	} break;
			case 'D': { AniSprite[i + index] = Color_LightRed;		} break;
			case 'E': { AniSprite[i + index] = Color_LightPerple;	} break;
			case 'F': { AniSprite[i + index] = Color_LightYellow;	} break;
			case 'G': { AniSprite[i + index] = Color_LightWhite;	} break;
			default:  { AniSprite[i + index] = Color_NULL;			} break;
#pragma warning(pop)
			}
		}

		index += AniSize.X;
	}

	ai.close();

    return true;
}
