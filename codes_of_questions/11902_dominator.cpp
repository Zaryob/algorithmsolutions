#include <cstdio>
#include <bitset>
#include <vector>
#include <cstring>

using namespace std;

typedef vector<int> vi;

int tc, count = 1;
vector<vi> AdjList;
bitset<105> initVisited, curVisited;
bool first;

void deep_first_search(int u, int del) {
	bitset<105> *visited;
	if (first)
		visited = &initVisited;
	else
		visited = &curVisited;

	visited->set(u);
	if (u == del)
		return;

	for (int i = 0; i < (int) AdjList[u].size(); i++) {
		int v = AdjList[u][i];
		if (!visited->test(v))
			deep_first_search(v, del);
	}
}

int main() {
    int input;
	scanf("%d", &tc);
	while (tc--) {
		scanf("%d", &input);
		AdjList.assign(input, vi());
		for (int i = 0; i < input; i++) {
			for (int j = 0; j < input; j++) {
				int e;
				scanf("%d", &e);
				if (e)
					AdjList[i].push_back(j);
			}
		}

		first = true;
		for (int i = 0; i < input; i++)
			initVisited.reset(i);
		deep_first_search(0, input);
		first = false;

		printf("Case %d:", count++);
		for (int i = 0; i < input; i++) {
			for (int k = 0; k < input; k++)
				curVisited.reset(k);
			deep_first_search(0, i);

			printf("\n+");
			for (int j = 0; j < input* 2 - 1; j++) {
				printf("-");
			}
			printf("+\n|");
			for (int j = 0; j < input; j++) {
				if (initVisited.test(j) && (i == j || !curVisited.test(j)))
					printf("Y");
				else
					printf("N");
				printf("|");
			}
		}
		printf("\n+");
		for (int j = 0; j < input* 2 - 1; j++) {
			printf("-");
		}
		printf("+\n");
	}

	return 0;
}

