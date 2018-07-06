#include <iostream>

using namespace std;

extern "C" {
	double test();
}

int main() {
	cout << test() << endl;
}

