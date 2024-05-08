#include"Date.h"






int main(){

	Date d1(2024, 1,1);
	Date d2 = d1;
	cout << d1 << endl;
	d1++;
	cout << d1 << endl;
	d2 += 10000;
	cout << d2 << endl;
	int x = d2 -d1;
	cout << x << endl;
	return 0;
}












