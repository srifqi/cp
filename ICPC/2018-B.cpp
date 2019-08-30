// International Collegiate Programming Contest (ICPC)
// 2018 World Finals
// Problem B: Comma Sprinkler
// Code by srifqi

#include <iostream>

enum separator {SPACE, COMMA, FULL_STOP};

int main() {
	std::string input;
	int wordCount = 1;
	std::getline(std::cin, input);
	for (int i = 0; i < input.length(); i ++) if (input[i] == ' ') wordCount ++;
	std::string words[wordCount];
	separator seps[wordCount];
	std::string wordbuf = "";
	for (int i = 0, wi = 0; i < input.length(); i ++) {
		if (input[i] >= 'a' && input[i] <= 'z')
			wordbuf += input[i];
		else if (input[i] == ' ') {
			words[wi] = wordbuf;
			seps[wi ++] = SPACE;
			wordbuf = "";
		}
		else if (input[i] == '.') {
			words[wi] = wordbuf;
			seps[wi ++] = FULL_STOP;
			wordbuf = "";
			i ++;
		}
		else if (input[i] == ',') {
			words[wi] = wordbuf;
			seps[wi ++] = COMMA;
			wordbuf = "";
			i ++;
		}
	}
	bool changed = true;
	while (changed) {
		changed = false;
		for (int wi = 1; wi < wordCount; wi ++) {
			if (seps[wi - 1] == COMMA) {
				for (int wj = 0; wj < wordCount; wj ++) {
					if (words[wj] == words[wi] && seps[wj - 1] == SPACE) {
						seps[wj - 1] = COMMA;
						changed = true;
					}
				}
			}
		}
		for (int wi = 0; wi < wordCount; wi ++) {
			if (seps[wi] == COMMA) {
				for (int wj = 0; wj < wordCount; wj ++) {
					if (words[wj] == words[wi] && seps[wj] == SPACE) {
						seps[wj] = COMMA;
						changed = true;
					}
				}
			}
		}
	}
	for (int wi = 0; wi < wordCount; wi ++) {
		std::cout << words[wi];
		if (seps[wi] == SPACE) std::cout << " ";
		if (seps[wi] == COMMA) std::cout << ", ";
		if (seps[wi] == FULL_STOP && wi < wordCount - 1) std::cout << ". ";
		if (seps[wi] == FULL_STOP && wi == wordCount - 1) std::cout << ".";
	}
	std::cout << std::endl;
}
