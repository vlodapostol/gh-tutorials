#pragma once
#pragma commment(lib,"OpenGL32.lib")
#include <Windows.h>
#include <stdio.h>
#include <gl/GL.h>
#include "mem.h"

struct vec3 { float x, y, z; };

namespace GL {
	class Font {
	public:
		bool bBuilt = false;
		unsigned int base;
		HDC hdc = nullptr;
		int height;
		int width;

		void Build(int height);
		void Print(float x, float y, const unsigned char color[3], const char* format, ...);

		vec3 centerText(float x, float y, float width, float heigt, float textWidth, float textHeight);
		float centerText(float x, float width, float textWidth);

	};
}