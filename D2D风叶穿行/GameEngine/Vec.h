#pragma once
#include <iostream>
#define PI 3.14159265

namespace shu
{
	// 二维向量
	class vec2f
	{
	public:
		float x, y;
		vec2f() : x(0.0f), y(0.0f) {}
		vec2f(float x, float y) : x(x), y(y) {}
		~vec2f() {}

		friend std::ostream& operator << (std::ostream& io, const vec2f& o) { std::cout << "x: " << o.x << " y: " << o.y; return io; }
		vec2f& operator >> (vec2f& o) { o.x = x; o.y = y; return o; }

		vec2f operator + (const vec2f& o) const { return vec2f(x + o.x, y + o.y); }
		vec2f operator - (const vec2f& o) const { return vec2f(x - o.x, y - o.y); }
		vec2f operator * (const vec2f& o) const { return vec2f(x * o.x, y * o.y); }
		vec2f operator / (const vec2f& o) const { return vec2f(x / o.x, y / o.y); }

		//vec2f& operator = (const vec2f& o) { x = o.x; y = o.y; return *this; }

		friend vec2f operator / (float o, const vec2f& t) { return vec2f(o / t.x, o / t.y); }
		friend vec2f operator / (const vec2f& o, float t) { return vec2f(o.x / t, o.y / t); }

		friend vec2f operator * (float o, const vec2f& t) { return vec2f(o * t.x, o * t.y); }
		friend vec2f operator * (const vec2f& o, float t) { return vec2f(o.x * t, o.y * t); }

		vec2f& operator += (const vec2f& o) { x += o.x; y += o.y; return *this; }
		vec2f& operator -= (const vec2f& o) { x -= o.x; y -= o.y; return *this; }
		vec2f& operator *= (const vec2f& o) { x *= o.x; y *= o.y; return *this; }
		vec2f& operator /= (const vec2f& o) { x /= o.x; y /= o.y; return *this; }

		vec2f operator + () const { return vec2f(-x, -y); }
		vec2f operator - () const { return vec2f(-x, -y); }

		bool operator == (const vec2f& o) const { return ((x == o.x) && (y == o.y)); }
		bool operator != (const vec2f& o) const { return ((x != o.x) && (y != o.y)); }

		vec2f norm() { float len = 1 / std::sqrt(x * x + y * y); return vec2f(len * x, len * y); }
		float len() { return std::sqrt(x * x + y * y); }
	};

	static float ator(float angle) { return float(PI / 180 * angle); }
	static float rtoa(float radian) { return float(180 / PI * radian); }

	class vec2i
	{
	public:
		int x, y;
		vec2i() : x(0), y(0) {}
		vec2i(int x, int y) : x(x), y(y) {}
		~vec2i() {}

		friend std::ostream& operator << (std::ostream& io, const vec2i& o) { std::cout << "x: " << o.x << " y: " << o.y; return io; }
		vec2i& operator >> (vec2i& o) { o.x = x; o.y = y; return o; }

		vec2i operator + (const vec2i& o) const { return vec2i(x + o.x, y + o.y); }
		vec2i operator - (const vec2i& o) const { return vec2i(x - o.x, y - o.y); }
		vec2i operator * (const vec2i& o) const { return vec2i(x * o.x, y * o.y); }
		vec2i operator / (const vec2i& o) const { return vec2i(x / o.x, y / o.y); }

		vec2i& operator += (const vec2i& o) { x += o.x; y += o.y; return *this; }
		vec2i& operator -= (const vec2i& o) { x -= o.x; y -= o.y; return *this; }
		vec2i& operator *= (const vec2i& o) { x *= o.x; y *= o.y; return *this; }
		vec2i& operator /= (const vec2i& o) { x /= o.x; y /= o.y; return *this; }

		vec2i operator + () const { return vec2i(-x, -y); }
		vec2i operator - () const { return vec2i(-x, -y); }

		bool operator == (const vec2i& o) const { return ((x == o.x) && (y == o.y)); }
		bool operator != (const vec2i& o) const { return ((x != o.x) && (y != o.y)); }
	};

	// 颜色
	class color4f
	{
	public:
		color4f() : r(0.0f), g(0.0f), b(0.0f), a(0.0f) {}
		color4f(float r, float g, float b, float a = 1.0f) : r(r), g(g), b(b), a(a) {}
		~color4f() {}
		float r, g, b, a;
	};

	namespace Color
	{
		const color4f Red(1.0f, 0.0f, 0.0f, 1.0f),
			Green(0.0f, 1.0f, 0.0f, 1.0f),
			Blue(0.0f, 0.0f, 1.0f, 1.0f),
			White(1.0f, 1.0f, 1.0f, 1.0f),
			Yellow(1.0f, 1.0f, 0.0f, 1.0f),
			Black(0.0f, 0.0f, 0.0f, 1.0f)
			
			
			;
	}

}