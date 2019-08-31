// International Collegiate Programming Contest (ICPC)
// 2018 World Finals
// Problem A: Catch the Plane
// Code by srifqi

#include <iostream>

typedef long s32;
typedef long long s64;

typedef struct {
	s32 a, b;
	s64 s, t;
	double p;
	
} entry;

double followBus(entry *sched, s32 m, s64 k, s32 bi, double p);

void mSMerger(entry *list, s32 a, s32 m, s32 b);
void mergeSort(entry *list, s32 a, s32 b);

int main() {
	s32 m, n;
	s64 k;
	std::cin >> m >> n >> k;
	entry schedule[m];
	for (s32 i = 0; i < m; i ++) std::cin >> schedule[i].a >>
		schedule[i].b >> schedule[i].s >> schedule[i].t >> schedule[i].p;
	mergeSort(schedule, 1, m);
	std::cout << followBus(schedule, m, k, 0, 1.0) << std::endl;
}

double followBus(entry *sched, s32 m, s64 k, s32 bi, double p) {
	entry e_bus = sched[bi];
	double pNext = p * e_bus.p;
	if (e_bus.b != 1) {
		for (s32 i = bi + 1; i < m; i ++) {
			if (sched[i].a == e_bus.b && sched[i].s > e_bus.t && sched[i].t <= k) {
				pNext = followBus(sched, m, k, i, p * e_bus.p);
				break;
			}
		}
	}
	double pMax = 0;
	for (s32 i = bi + 1; i < m; i ++) {
		if (sched[i].a != e_bus.a || sched[i].s <= e_bus.s || sched[i].t > k) continue;
		double pF = followBus(sched, m, k, i, p * (1 - e_bus.p));
		if (pF > pMax) pMax = pF;
	}
	return pNext + pMax;
}

void mSMerger(entry *list, s32 a, s32 m, s32 b) {
	s32 nL = m - a + 1;
	s32 nR = b - m;
	entry L[nL];
	entry R[nR];
	s32 q = a;
	for (s32 p = 0; p < nL; p ++) L[p] = list[q ++];
	for (s32 p = 0; p < nR; p ++) R[p] = list[q ++];
	s32 i = 0, j = 0, k = a;
	while (i < nL && j < nR)
		if (L[i].s < R[j].s) list[k ++] = L[i ++];
		else list[k ++] = R[j ++];
	while (i < nL) list[k ++] = L[i ++];
	while (j < nR) list[k ++] = R[j ++];
}

void mergeSort(entry *list, s32 a, s32 b) {
	if (a >= b) return;
	s32 m = (a + b) / 2;
	mergeSort(list, a, m);
	mergeSort(list, m + 1, b);
	mSMerger(list, a, m, b);
}
