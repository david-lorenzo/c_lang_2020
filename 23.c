#include <stdio.h>

void print_array(int n, int *arr)
{
	printf("[%d", arr[0]);
	for(int i=1; i < n; i++) {
		printf(", %d", arr[i]);
	}
	printf("]\n");
}

void print_seq(int *arr)
{
	int a = 1;
	printf("[%d", a);
	a = arr[a];
	while (a != 1) {
		printf(", %d", a);
		a = arr[a];
	}
	printf("]\n");
}

//static inline int decr(int n, int i)
int decr(int n, int i)
{
	if (i==1) return n;
	return (i-1);
}

//static inline int dest(int n, int x, int x1, int x2, int x3)
int dest(int n, int x, int x1, int x2, int x3)
{
	int a = decr(n, x);
	if (a != x1 && a != x2 && a != x3) return a;
	a = decr(n, a);
	if (a != x1 && a != x2 && a != x3) return a;
	a = decr(n, a);
	if (a != x1 && a != x2 && a != x3) return a;
	return decr(n, a);
}

void run(int iters, int n, int *xs)
{
	int c, c1, c2, c3, c4, d, d1;
	for(int i=0; i<iters; i++) {
		c  = xs[0];
		c1 = xs[c];
		c2 = xs[c1];
		c3 = xs[c2];
		c4 = xs[c3];
		d  = dest(n, c, c1, c2, c3);
		d1 = xs[d];
		xs[c3] = d1;
		xs[d]  = c1;
		xs[c]  = c4;
		xs[0]  = c4;
	}
}

void main(void)
{
	int data[9] = {5, 9, 8, 1, 6, 2, 7, 3, 4};
	int res1[10];

	int idx, val;
	for (int i=0; i < 8; i++) {
		idx = data[i];
		val = data[i+1];
		res1[idx] = val;
	}
	res1[0] = data[0];
	res1[data[8]] = data[0];

	int size = 1000000;
	int data2[size];
	for (int i=0; i<10; i++)
		data2[i] = res1[i];

	//print_array(9, data);
	//print_array(10, res1);
	run(100, 9, res1);
	print_seq(res1);

	// part 2
	int iterations = 10000000;
	data2[data[8]] = 10;
	for (int j=10; j <= size; j++) {
		data2[j] = j+1;
	}
	data2[size] = data2[0];

	run(iterations, size, data2); 
	long int m1 = data2[1];
	long int m2 = data2[m1];
	printf("%ld\n", m1*m2);
}

