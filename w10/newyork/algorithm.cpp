#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <queue>

void testcase()
{
	int n, m, k;
	std::cin >> n >> m >> k;
	std::vector<int> h(n);
	std::vector<int> parent(n);
	parent[0] = -1;
	std::vector<bool> is_leaf(n, true);
	is_leaf[0] = false;
	for (int i = 0; i < n; i++)
	{
		std::cin >> h[i];
	}

	for (int i = 1; i < n; i++)
	{
		int u, v;
		std::cin >> u >> v;
		is_leaf[u] = false;
		parent[v] = u;
	}

	std::vector<int> leaf;
	for (int i = 0; i < n; i++)
	{
		if (is_leaf[i])
		{
			leaf.push_back(i);
		}
	}
	std::vector<bool> vis(n, false);
	std::set<int> result;
	for (auto i : leaf)
	{
		int current = i;
		std::queue<int> path;
		path.push(current);
		std::multiset<int> heat;
		heat.insert(h[current]);
		current = parent[current];
		while (current != -1 && !vis[path.front()])
		{
			path.push(current);
			heat.insert(h[current]);

			if (*heat.rbegin() - *heat.begin() > k)
			{
				vis[path.front()] = true;
				heat.erase(heat.find(h[path.front()]));
				path.pop();
			}
			else if (path.size() == m)
			{
				//if size == m, check if it fulfills da condition
				result.insert(current);
				vis[path.front()] = true;
				heat.erase(heat.find(h[path.front()]));
				path.pop();
			}
			current = parent[current];
		}
	}

	if (result.size())
	{
		for (int a : result)
			std::cout << a << " ";
	}
	else
		std::cout << "Abort mission";
	std::cout << std::endl;
}

int main()
{
	std::ios_base::sync_with_stdio(false);

	int t;
	std::cin >> t;
	for (int i = 0; i < t; ++i)
		testcase();
}
