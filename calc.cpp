#include <iostream>
#include <math.h>
#include <fstream>
#include <iomanip>
#include <chrono>

using namespace std;

double f1(double x)
{
	return x * x - sin(3 * x) - 1;
}

double f2(double x)
{
	return x * x * x - 2 * x * x + 1.2 * x - 0.226146;
}

double f3(double x)
{
	return x * x + x + 4 * cos(x) - 4;
}

void FindRootS(double x0, double &x1, double eps, int &N, double f(double), int &time)
{
	auto begin = std::chrono::steady_clock::now();
	double x;
  
	while (fabs(x1 - x0) > eps) {
		x = x1;
		x1 = x1 - f(x1)*(x1 - x0) / (f(x1) - f(x0));
		x0 = x;
		N++;
	}
  
	auto end = std::chrono::steady_clock::now();
	auto es = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
  
	time = es.count();
}

void FindRootP(double &a, double b, double eps, int &N, double f(double), int &time)
{
	auto begin = std::chrono::steady_clock::now();
  
	double c = (b + a) / 2;
  
	while (fabs(c - a) > eps) {
		double f1 = f(a);
		double f2 = f(b);
		double f3 = f(c);
    
		double d1 = f1 - f3;
		double d2 = f2 - f3;
    
		double h1 = a - c;
		double h2 = b - c;
    
		double A = ((d2 / h2) - (d1 / h1)) / (b - a);
		double B = (d1 / h1) + ((d2 / h2) - (d1 / h1))*h1 / (b - a);
		double C = f1;
    
		double x = a - 2 * C / (B + sqrt(B * B - 4 * A * C));
		double y = a - 2 * C / (B - sqrt(B * B - 4 * A * C));
    
		if ((((x < a) && (x > b)) || ((x > a) && (x < b)) || ((x < a) && (x > c)) || ((x > a) && (x < c))) && ((B + sqrt(B * B - 4 * A * C)) != 0)) {
			b = c;
			c = a;
			a = x;
		}
		else if ((B - sqrt(B * B - 4 * A * C)) != 0) {
			b = c;
			c = a;
			a = y;
		}
		else break;
    
		N++;
		if ((a == b) || (a == c) || (b == c)) break;
	}
  
	auto end = std::chrono::steady_clock::now();
	auto es = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
  
	time = es.count();
}

void main()
{
	ofstream fout("func.txt", ios_base::out | ios_base::trunc);
	fout << "first function" << endl;
  
	double a = -1.3;
	double b = -1.25;
	double c = a;
	double d = b;
  
	double eps = pow(10, -10);
  
	int N = 0;
	int M = 0;
	int t = 0;
	int k = 0;
  
	FindRootS(a, b, eps, N, *f1, t);
	FindRootP(c, d, eps, M, *f1, k);
  
	fout << fixed << setprecision(10) << "Secant x1=" << b << " iterations: " << N << " time: " << t << endl;
	fout << fixed << setprecision(10) << "Parabol x1=" << c << " iterations: " << M << " time: " << k << endl;
  
	a = -1.2;
	b = -1.15;
	c = a;
	d = b;
  
	N = 0;
	M = 0;
  
	t = 0;
	k = 0;
  
	FindRootS(a, b, eps, N, *f1, t);
	FindRootP(c, d, eps, M, *f1, k);
  
	fout << fixed << setprecision(10) << "Secant x2=" << b << " iterations: " << N << " time: " << t << endl;
	fout << fixed << setprecision(10) << "Parabol x2=" << c << " iterations: " << M << " time: " << k << endl;
  
	a = -0.4;
	b = -0.35;
	c = a;
	d = b;
  
	N = 0;
	M = 0;
  
	t = 0;
	k = 0;
  
	FindRootS(a, b, eps, N, *f1, t);
	FindRootP(c, d, eps, M, *f1, k);
  
	fout << fixed << setprecision(10) << "Secant x3=" << b << " iterations: " << N << " time: " << t << endl;
	fout << fixed << setprecision(10) << "Parabol x3=" << c << " iterations: " << M << " time: " << k << endl;
  
	a = 1;
	b = 1.05;
	c = a;
	d = b;
  
	N = 0;
	M = 0;
  
	t = 0;
	k = 0;
	FindRootS(a, b, eps, N, *f1, t);
	FindRootP(c, d, eps, M, *f1, k);
  
	fout << fixed << setprecision(10) << "Secant x4=" << b << " iterations: " << N << " time: " << t << endl;
	fout << fixed << setprecision(10) << "Parabol x4=" << c << " iterations: " << M << " time: " << k << endl;
  
	fout << "second function" << endl;
  
	a = 0.454;
	b = 0.455;
	c = a;
	d = b;
  
	N = 0;
	M = 0;
  
	t = 0;
	k = 0;
  
	FindRootS(a, b, eps, N, *f2, t);
	FindRootP(c, d, eps, M, *f2, k);
  
	fout << fixed << setprecision(10) << "Secant x1=" << b << " iterations: " << N << " time: " << t << endl;
	fout << fixed << setprecision(10) << "Parabol x1=" << c << " iterations: " << M << " time: " << k << endl;
  
	a = 0.456;
	b = 0.458;
	c = a;
	d = b;
  
	N = 0;
	M = 0;
  
	t = 0;
	k = 0;
  
	FindRootS(a, b, eps, N, *f2, t);
	FindRootP(c, d, eps, M, *f2, k);
  
	fout << fixed << setprecision(10) << "Secant x2=" << b << " iterations: " << N << " time: " << t << endl;
	fout << fixed << setprecision(10) << "Parabol x2=" << c << " iterations: " << M << " time: " << k << endl;
  
	a = 1.088;
	b = 1.09;
	c = a;
	d = b;
  
	N = 0;
	M = 0;
  
	t = 0;
	k = 0;
  
	FindRootS(a, b, eps, N, *f2, t);
	FindRootP(c, d, eps, M, *f2, k);
  
	fout << fixed << setprecision(10) << "Secant x3=" << b << " iterations: " << N << " time: " << t << endl;
	fout << fixed << setprecision(10) << "Parabol x3=" << c << " iterations: " << M << " time: " << k << endl;
  
	fout << "third function" << endl;
  
	a = -3.4;
	b = -3.35;
	c = a;
	d = b;
  
	N = 0;
	M = 0;
  
	t = 0;
	k = 0;
  
	FindRootS(a, b, eps, N, *f3, t);
	FindRootP(c, d, eps, M, *f3, k);
  
	fout << fixed << setprecision(10) << "Secant x1=" << b << " iterations: " << N << " time: " << t << endl;
	fout << fixed << setprecision(10) << "Parabol x1=" << c << " iterations: " << M << " time: " << k << endl;
  
	a = -0.03;
	b = 0.02;
	c = a;
	d = b;
  
	N = 0;
	M = 0;
  
	t = 0;
	k = 0;
  
	FindRootS(a, b, eps, N, *f3, t);
	FindRootP(c, d, eps, M, *f3, k);
  
	fout << fixed << setprecision(10) << "Secant x2=" << b << " iterations: " << N << " time: " << t << endl;
	fout << fixed << setprecision(10) << "Parabol x2=" << c << " iterations: " << M << " time: " << k << endl;
  
	fout.close();
}
