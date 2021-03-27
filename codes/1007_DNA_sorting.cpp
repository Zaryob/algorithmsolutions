#include <iostream>
#include <bits/stdc++.h>

using namespace std;

struct dna
{
	int pos;
	int key;
	string str;
};

bool cmp(const dna &a, const dna &b)
{
	if (a.key != b.key)
	{
		return a.key < b.key;
	}
	else
	{
		return a.pos < b.pos;
	}
}

int main()
{
	int n, m, count;
	dna inv[110];
	string str;
	cin >> n >> m;
	
	for (int i = 0; i < m; i++)
	{
		cin >> str;
		count = 0;
		for (int j = 0; j < n - 1; j++)
		{
			for (int k = j + 1; k < n; k++)
			{
				if (str[j] > str[k]) count++;
			}
		}
		inv[i].key = count;
		inv[i].pos = i;
		inv[i].str = str;
	}
	
	sort(inv, inv + m, cmp);
	
	for (int i = 0; i < m; i++)
	{
		cout << inv[i].str << endl;
	}
	
	return 0;
}
