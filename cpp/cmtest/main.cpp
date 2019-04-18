#include <iostream>
#include "duktape.h"
int main(int argc, char *argv[])
{
	fs::path libPath = "./math/MathLib.cpp";
	std::priority_queue<int> queue;
	for (int n : {1, 8, 5, 6, 3, 4, 0, 9, 7, 2}) {
		queue.push(n);
	}
	std::greater<int>
	return 0;
}