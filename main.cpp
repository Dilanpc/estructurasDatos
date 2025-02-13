#include <iostream>
#include "DisjunctSets.hpp"

void dsu()
{
	unsigned int N, Q;
	std::cin >> N >> Q;

	DisjunctSetsPC set(N);

	for (unsigned int i = 0; i < Q; ++i)
	{
		bool query;
		unsigned int u, v;

		std::cin >> query >> u >> v;

		if (query) // Is in the same commponent?
		{
			std::cout << set.isSameSet(u, v) << '\n';
		}
		else
		{
			set.join(u, v);
		}
	}

}


int main(int argc, const char* argv[])
{
	std::ios_base::sync_with_stdio(false);

	dsu();
	
}
