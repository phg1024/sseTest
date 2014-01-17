#pragma once

#include <iostream>
using namespace std;

struct Point4f_Naive {
	Point4f_Naive(){}
	Point4f_Naive(float v):x(v), y(v), z(v), w(v){}
	float x, y, z, w;
};

struct Point4f {
	Point4f(){ sse = _mm_set_ps1(0); }
	Point4f(float x, float y, float z, float w) {
		sse = _mm_set_ps(w, z, y, x);
	}
	Point4f(float v){ sse = _mm_set_ps1(v); }
	Point4f(__m128 v) { sse = v; }

	Point4f& operator=(const Point4f& p) {
		sse = p.sse;
		return *this;
	}

	Point4f operator+(const Point4f& p) {
		return _mm_add_ps(sse, p.sse);
	}
	Point4f operator-(const Point4f& p) {
		return _mm_sub_ps(sse, p.sse);
	}
	Point4f operator*(const Point4f& p) {
		return _mm_mul_ps(sse, p.sse);
	}
	Point4f operator/(const Point4f& p) {
		return _mm_div_ps(sse, p.sse);
	}

	__m128 operator==(const Point4f& p) {
		return _mm_cmpeq_ps(sse, p.sse);
	}

	__m128 operator!=(const Point4f& p) {
		return _mm_cmpneq_ps(sse, p.sse);
	}

	operator __m128() {
		return sse;
	}

	float& operator[](int idx) {
		assert(idx >= 0 && idx < 4);
		return (&x)[idx];
	}

	float operator[](int idx) const {
		assert(idx >= 0 && idx < 4);
		return (&x)[idx];
	}

	friend ostream& operator << (ostream& os, const Point4f& p);
	friend istream& operator >> (istream& is, Point4f& p);

	union {
		__m128 sse;
		struct { float x, y, z, w; };
	};
};

ostream& operator << (ostream& os, const Point4f& p) {
	os << p.x << ' ' << p.y << ' ' << p.z << ' ' << p.w << endl;
	return os;
}

istream& operator >>(istream& is, Point4f& p) {
	is >> p.x >> p.y >> p.z >> p.w;
	return is;
}