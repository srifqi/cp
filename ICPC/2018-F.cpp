// International Collegiate Programming Contest (ICPC)
// 2018 World Finals
// Problem F: Go with the Flow
// Code by srifqi

#include <iostream>

int traceRiver(char* map, int w, int h, int si, int sj, int len) {
	if (sj >= h - 1)
		return len + 1;
	int maxLen = 1;
	int nowLen = 0;
	if (si > 0 && map[(sj + 1) * w + si - 1] == ' ') {
		nowLen = traceRiver(map, w, h, si - 1, sj + 1, 1);
		if (nowLen > maxLen)
			maxLen = nowLen;
	}
	if (map[(sj + 1) * w + si] == ' ') {
		nowLen = traceRiver(map, w, h, si, sj + 1, 1);
		if (nowLen > maxLen)
			maxLen = nowLen;
	}
	if (si < w - 1 && map[(sj + 1) * w + si + 1] == ' ') {
		nowLen = traceRiver(map, w, h, si + 1, sj + 1, 1);
		if (nowLen > maxLen)
			maxLen = nowLen;
	}
	return len + maxLen;
}

int main() {
	int n;
	std::cin >> n;
	std::string words_[n];
	int words[n];
	int textLen = n - 1;
	int maxLen = 0;
	for (int i = 0; i < n; i ++) {
		std::string word;
		std::cin >> word;
		words_[i] = word;
		words[i] = word.length();
		textLen += words[i];
		if (words[i] > maxLen)
			maxLen = words[i];
	}
	int globalMaxRiverLen = 0;
	int globalMinTextWidth = maxLen;
	for (int w = maxLen; w <= textLen; w ++) {
		char map[2500 * w];
		for (int q = 0; q < 2500; q ++)
		for (int r = 0; r < w; r ++)
			map[q * w + r] = 4;
		int wi = 0;
		int li = words[wi];
		bool checkWord = true;
		int j = 0;
		while (wi < n) {
			if (li == 0)
				li = words[++ wi];
			for (int i = 0; i < w; i ++) {
				if (wi >= n)
					break;
				if (checkWord) {
					checkWord = false;
					if (words[wi] > w - i)
						break;
					else
						map[j * w + i - 1] = ' ';
				}
				if (li > 0)
					map[j * w + i] = words_[wi][words[wi] - li];
				li --;
				if (li < 0) {
					wi ++;
					if (wi < n) {
						li = words[wi];
						checkWord = true;
					}
				}
			}
			j ++;
		}
		int maxRiverLen = 0;
		for (int y = 0; y < j; y ++) {
		for (int x = 0; x < w; x ++) {
			int riverLen = 0;
			if (map[y * w + x] == ' ') {
				riverLen = traceRiver(map, w, j, x, y, 0);
				if (riverLen > maxRiverLen)
					maxRiverLen = riverLen;
			}
		}
		}
		if (maxRiverLen > globalMaxRiverLen) {
			globalMaxRiverLen = maxRiverLen;
			globalMinTextWidth = w;
		}
	}
	std::cout << globalMinTextWidth << " " << globalMaxRiverLen << std::endl;
}
