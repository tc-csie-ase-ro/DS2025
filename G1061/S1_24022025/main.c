#include <stdio.h>

int suma(int x, int y) {
	return x + y;
}

void suma1(int x, int y, int* z) {
	*z = x + y;
}

int sumaP(int x, int y, int (*pf) (int, int)) {
	x++;
	y++;
	int suma = (*pf) (x, y);
	return suma;
}
	
int main() {

	int a;
	a = suma(10, 14);
	printf("Suma = %d", a);

	int b;
	suma1(10, 15, &b);
	printf("\nb = %d", b);

	int (*sumaPointer) (int, int); 
	sumaPointer = suma;
	
	int c;
	c = sumaPointer(20, 30);
	printf("\nc = %d", c);

	int d;
	d = sumaP(10, 20, sumaPointer);
	printf("\nd = %d", d);

	//int* p;

	//int a = 10;

	//p = &a;

	//*p = 12;
	
	//printf("a = %d", a);

	//int v[10];
	//for (int i = 0; i < 10; i++) {
	//		v[i] = i + 1;
	//}

	//int* pv;
	// 
	//pv = v;
	//pv = &v;

	//printf(*\npv[4] = %d", pv[4]);
	//printf(*\n*pv++ = %d", *pv++);
	//printf (*\npv[11] = %d", pv[11]);

	return 0;
}
