// parallel_lab2.cpp: главный файл проекта.

#include "stdafx.h"

#define _USE_MATH_DEFINES // for C++
#include <cmath>
#include <intrin.h>
#include <iostream>
#include <omp.h>
#include <iomanip>
using namespace std;

#pragma intrinsic(__rdtsc)

const double l = 1;
const double max_x = l / 2; //double min_x = 0;
const double max_fi = M_PI; //double min_fi = 0; //double max_fi = 2 * M_PI;

void print(__int64 count,__int64 n, unsigned __int64 t0, unsigned __int64 t)
{
	double my_pi = 2 * count / (double)n;
	double my_err = abs(M_PI - my_pi);
	double my_time = (double)(t - t0) / 4000000000;

	cout << my_pi << "\t" << my_err << "\t" << (double)count << "\t" << my_time << endl;
}

void main()
{
	cout << "my_pi\terror\tcount\ttime" << endl;
	unsigned __int64 t0, t;

	omp_set_num_threads(6); //как оптимально выбрать??????????
	__int64 i = 0; //не unsigned __int64 тк должно быть целое со знаком
				//где то читал что в openmp 3.0 можно без знака
				//ѕќ„≈ћ””””””” ѕочему нельз€ сразу присвоить?  i2 = *i ????????????????????
	__int64 start_i = 0;
	__int64 n = 0;
	__int64 count = 1000;

back:
	t0 = __rdtsc();
	#pragma omp parallel for reduction(+ : n)
	for (i = start_i; i < count; i++)
	{
		if ((double)rand() / RAND_MAX <= sin(rand()*max_fi / RAND_MAX)) n++;
	}
	t = __rdtsc();

	print(count, n, t0, t);

	//изменение диапазона дл€ следующего измерени€
	start_i = count;
	count *= 10;

	goto back;
};