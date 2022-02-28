// a[0] = 1 / x
// a[i] = cos(i / x) + x / i,	i = 1..N

#include <omp.h>
#include <iostream>
#include <cmath>

using namespace std;

void enter_data(int& N, double& x) {
	cout << "Enter N: ";
	cin >> N;
	cout << "Enter x: ";
	cin >> x;
}

void init_mas(long double* arr, double x, int N) {
	arr[0] = 1 / x;

#pragma omp parallel for
	for (int i = 1; i < N; i++) {
		arr[i] = cos(i / x) + x / i;
	}

}

long double posled_sum_mas(long double* arr, int& n) {
	long double sum = 0;
	for (int i = 0; i < n; i++) {
		sum += arr[i];
	}
	return sum;
}

long double paral_incorrect_sum_mas(long double* arr, int& n) {
	long double sum = 0;
#pragma omp parallel for
	for (int i = 0; i < n; i++) {
		sum += arr[i];
	}
	return sum;
}

long double paral_correct_sum_mas(long double* arr, int& n) {
	long double sum = 0;
#pragma omp parallel for reduction(+:sum)
	for (int i = 0; i < n; i++) {
		sum += arr[i];
	}
	return sum;
}

void print_time(double& start_time, double& end_time, double& all_time) {
	cout << "\nTime begin: " << start_time << endl;
	cout << "End time: " << end_time << endl;
	cout << "Time: " << all_time << endl;
	cout << "Wtick: " << omp_get_wtick() << endl;
}

int main() {
	int N;
	double x, start_time, end_time, all_time;
	long double sum = 0.0;

	enter_data(N, x);

	long double* a = new long double[N];
	init_mas(a, x, N);

	start_time = omp_get_wtime();

	//sum = posled_sum_mas(a, N);
	sum = paral_incorrect_sum_mas(a, N);
	//sum = paral_correct_sum_mas(a, N);

	end_time = omp_get_wtime();
	all_time = end_time - start_time;

	print_time(start_time, end_time, all_time);

	delete[] a;
	system("PAUSE");
}