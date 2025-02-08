#include <iostream>
#include <cmath>
#include <complex>


void get_error() {
	std::cout << "error complex numbers";
}

void print(double root1, double root2) {
	std::cout << root1 << root2 << std::endl;
}

void print(double root1) {
	std::cout << root1 << std::endl;
}

void find_roots(int a,int b,int c) {
	int discrim = b * b - 4 * a * c;
	if (discrim < 0) {
		get_error();
	}
	else if (discrim == 0) {
		double root1 = -b / (2 * a);
		print(root1);
	}
	else {
		double root1 = (-b + sqrt(discrim)) / (2 * a);
		double root2 = (-b - sqrt(discrim)) / (2 * a);
		print(root1, root2);
	}
}


void get_coefs(double& a, double& b, double &c) {
	std::cin >> a >> b >> c;
}

int main() {
	double a, b, c;
	get_coefs(a, b, c);
	find_roots(a, b, c);

	return 0;

}
