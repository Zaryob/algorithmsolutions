#include <iostream>

using namespace std;

int main() {
	float a, len;

	while(cin >> a, a) {
		len = 0;
		int i = 0;
		while(len < a) {
			len += 1.0 / (i + 2);
			i ++;
		}
		cout << i << " card(s)" << endl;
	}
	return 0;
}
