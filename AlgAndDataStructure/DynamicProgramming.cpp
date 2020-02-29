#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include "common.h"

int cut_rod(int p[], int n) {
	int q = 0;
	int i = 0;
	if (n == 0)
	{
		return 0;
	}

	q = INT_MIN;

	for (i = 0; i < n; i++)
	{
		q = max(q, p[i] + cut_rod(p, n - i));
	}

	return q;
}

int memorized_cut_rod_aux(int p[], int r[], int n) {
	int q = 0;
	if (r[n] >= 0)
	{
		return r[n];
	}

	if (n == 0)
		q = 0;
	else
	{
		q = INT_MIN;
		for (int i = 0; i < n; i++)
		{
			q = max(q, p[i] + memorized_cut_rod_aux(p, r, n - i));
		}
	}

	r[n] = q;
	return q;
}

int extend_memorized_cut_rod_aux(int p[], int r[], int n, int s[]) {
	int q = 0;
	int t = 0;
	int j = 0;
	if (r[n] >= 0)
	{
		return r[n];
	}

	if (n == 0)
		q = 0;
	else
	{
		q = INT_MIN;
		j = 0;
		for (int i = 1; i <= n; i++)
		{
			t = p[i] + extend_memorized_cut_rod_aux(p, r, n - i, s);
			if (q < t)
			{
				q = t;
				j = i;
			}
			//q = max(q, p[i] + memorized_cut_rod_aux(p, r, n - i));
		}
	}

	r[n] = q;
	s[n] = j;
	return q;
}



int memorized_cut_rod(int p[], int r[], int n) {
	int i = 0;
	for (i = 0; i < n; i++)
	{
		r[i] = INT_MIN;
	}

	return memorized_cut_rod_aux(p, r, n);
}

void print_cut_rod_solution()
{
	int p[11] = {-1, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30 };
	int r[11] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
	int s[11] = { 0 };
	int n = 7;

	extend_memorized_cut_rod_aux(p, r, n, s);

	while (n) {
		cout << s[n]  << " ";
		n = n - s[n];
	}

	cout << "\n";

}

int fib(int array[], int n) {
	if (n == 0 || n == 1)
	{
		array[n] = 1;
		return array[n];
	}

	array[n] = array[n - 2] + fib(array, n - 1);

	return array[n];
}

#define MATRIX_CHAIN_NUM 6

int lookup_chain(int m[][MATRIX_CHAIN_NUM + 1], vector<int> p, int i, int j) {

	if (m[i][j] < INT_MAX)
	{
		return m[i][j];
	}

	if (i == j)
	{
		m[i][j] = 0;
	}
	else
	{
		for (int k = i; k <= j - 1; k++)
		{
			int q = 0;
			q = lookup_chain(m, p, i, k) + lookup_chain(m, p, k + 1, j) + p[i - 1] * p[k] * p[j];
			if (q < m[i][j])
			{
				m[i][j] = q;
			}
		}
	}

	return m[i][j];
}

int memorized_matrix_multiply_chain(vector<int> matrix_dimonstion) {
	int n = matrix_dimonstion.size() - 1;
	int m[MATRIX_CHAIN_NUM + 1][MATRIX_CHAIN_NUM + 1];

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			m[i][j] = INT_MAX;
		}
	}

	return 0;
}

int LCS_length_recursive(char X[], char Y[], int i, int j) {
	if (i == 0 || j == 0)
	{
		return 0;
	}

	if (X[i] == Y[j])
	{
		return LCS_length_recursive(X, Y, i - 1, j - 1) + 1;
	}
	else
	{
		int lcs1 = 0, lcs2 = 0;
		lcs1 = LCS_length_recursive(X, Y, i - 1, j);
		lcs2 = LCS_length_recursive(X, Y, i, j - 1);
		return max(lcs1, lcs2);
	}
}

const int lcs_x = 7;
const int lcs_y = 6;

int lcs_len_memorized(char X[], char Y[], int i, int j, int c[][lcs_y + 1]) {
	if (i == 0 || j == 0)
	{
		c[i][j] = 0;
		return c[i][j];
	}

	if (c[i][j] > INT_MIN)
	{
		return c[i][j];
	}

	if (X[i] == Y[j])
	{
		c[i][j] = lcs_len_memorized(X, Y, i - 1, j - 1, c) + 1;
	}
	else
	{
		int lcs1 = 0, lcs2 = 0;
		lcs1 = lcs_len_memorized(X, Y, i - 1, j, c);
		lcs2 = lcs_len_memorized(X, Y, i, j - 1, c);
		c[i][j] = max(lcs1, lcs2);
	}

	return c[i][j];
}

int c[lcs_x + 1][lcs_y + 1];
void test_lcs()
{
	char X[lcs_x + 1] = { '0','A', 'B', 'C', 'B','D', 'A', 'B' };
	char Y[lcs_y + 1] = { '0','B', 'D','C','A','B','A' };


	int lcs_len = 0;
	for (int i = 0; i < lcs_x + 1; i++)
	{
		for (int j = 0; j < lcs_y + 1; j++)
		{
			c[i][j] = INT_MIN;
		}
	}
	for (int i = 0; i < lcs_x + 1; i++)
	{
		for (int j = 0; j < lcs_y + 1; j++)
		{
			c[i][j] =  lcs_len_memorized(X, Y, i, 5, c);
		}
	}
	
}




int knapsack(int v[], int wt[], int n, int w) {
	int i = 0;
	int total_value = 0;
	int q;

	if (n == 1 && w < wt[n - 1])
	{
		return 0;
	}
	else if (n == 1 && w > wt[n - 1])
	{
		return v[0];
	}

	for (i = 0; i < n; i++)
	{
		swap(v[i], v[n - 1]);
		swap(wt[i], wt[n - 1]);
		q = v[n - 1] + knapsack(v, wt, n - 1, w - wt[n - 1]);
		if (total_value < q)
		{
			total_value = q;
		}
		//total_value = max(total_value, v[n - 1] + knapsack(v, wt, n - 1, w - wt[n - 1]));
	}

	return total_value;
}

int f[10000];

int knapsack_memorized(int v[], int wt[], int n, int w, int r[]) {
	int q = INT_MIN;

	for (int i = n ; i >= 1; i--)
	{
		q = max(q, f[w - wt[i - 1]] + v[i - 1]);
		f[w] = q;
		w -= wt[i - 1];
	}

	return q;
}

void knapsack_test() {
	int v[3] = { 60, 100, 120 };
	int wt[3] = { 10, 20, 30 };
	int r[3];
	int w, i = 0;

	int val = -1;
	return;
	val = knapsack(v, wt, 3, 50);
	for (int i = 1; i < 3; i++)
	{
		r[i] = INT_MIN;
	}

	w = 50;
	while (w)
	{
		val = knapsack_memorized(v, wt, 3, w, r);
		w -= wt[i];
		i++;
	}
	
}