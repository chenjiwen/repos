#include <iostream>
#include "sales_item.h"

using namespace std;

int main(int argc, char** argv)
{
	sales_item item=sales_item(1, 1.2, "xxxx-yyyy-zzzz");
	sales_item item2;
	//sales_item item2;
	string all_nines = "999999";
	int val = 0;
	const int val1 = 2;
	const int& refval = val;
	const int& refval2 = val1;

#ifdef COUT_IS_MEMBER
	item << cout;
#else
	cout << item;
#endif /*COUT_IS_MEMBER*/
	return 0;
}