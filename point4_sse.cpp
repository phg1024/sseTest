#include <iostream>
#include <algorithm>
#include <vector>
#include <assert.h>
#include <time.h>

#include "alignedallocator.hpp"
#include "Point.h"

using namespace std;

int main() {
	float vref = sqrtf(7.0f);
	__m128 m1 = _mm_set_ps1(7.0);
	__m128 mref = _mm_set_ps1(vref);
	float res_val[4] = { 0 };

	int runs = 1;
	int n = 32 * 1024 * 1024;
	//vector<Point4f, aligned_allocator<Point4f, 16>> vec(n, m1);
	vector<Point4f> vec(n, m1);

	clock_t start, stop;
	start = clock();
	for (int j = 0; j < runs;j++)
	for (int i = 0; i < n;i++) {
		vec[i] = _mm_sqrt_ps(vec[i]);
	}
	stop = clock();
	cout << "time cost with SIMD = " << (stop - start) / (float)CLOCKS_PER_SEC * 1000.0 << "ms" << endl;

	// verify
	bool flag = false;
	for (int i = 0; i < n; i++) {
		Point4f res = (vec[i] != mref);
		if (res[0] || res[1] || res[2] || res[3]) {
			cout << vec[i] << '\t' << mref << endl;
			flag = true;
			break;
		}
	}
	if (flag) cout << "Failed." << endl;
	else cout << "Succeeded." << endl;

	// initialize the vector
	vector<Point4f_Naive> vec2(n, 7.0f);

	start = clock();
	for (int j = 0; j < runs; j++)
	for (int i = 0; i < n; i++) {
		Point4f_Naive& p = vec2[i];
		p.x = sqrtf(p.x);
		p.y = sqrtf(p.y);
		p.z = sqrtf(p.z);
		p.w = sqrtf(p.w);
	}
	stop = clock();
	cout << "time cost with SIMD = " << (stop - start) / (float)CLOCKS_PER_SEC * 1000.0 << "ms" << endl;
	// verify
	flag = false;
	for (int i = 0; i < n; i++) {	
		Point4f_Naive& p = vec2[i];
		if ( (p.x != vref) || (p.x != vref) || (p.x != vref) || (p.x != vref)) {
			flag = true;
			break;
		}
	}
	if (flag) cout << "Failed." << endl;
	else cout << "Succeeded." << endl;

	Point4f zero;
	cout << zero << endl;
	zero = zero + Point4f(1, 2, 3, 4);
	cout << zero << endl;
	zero = zero * zero;
	cout << zero << endl;
	zero = zero / zero;
	cout << zero << endl;
	return 0;
}