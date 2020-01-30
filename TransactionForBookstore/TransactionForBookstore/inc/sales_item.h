#ifndef __SALE_ITEM__H
#define __SALE_ITEM__H
#include <string.h>
#include <iostream>
using namespace std;

class sales_item {

/*
 *define member of class
*/
private:
	int sale_count;
	double price;
	string isbn;

public:
	/*member function, implicit this pointer*/
	sales_item(int, double, string);

	/*default constructor without parameters*/
	sales_item();

	/*copy constructor*/
	sales_item(const sales_item&);

	/*copy control*/
	explicit sales_item(string);

	/**/
	~sales_item() {};

	sales_item& operator+=(const sales_item& item);
	bool operator==(const sales_item& item);
	bool operator!=(const sales_item& item);

	/* const member function can't modify the member of object
	 * it can be called by non-const/const object. const object can only
	 * call the const member
	 */
	bool IsSameItem(const sales_item& item) const;

#ifdef COUT_IS_MEMBER
	ostream& operator<<(ostream& os);
/*
 *non-class friend member, friend must be declared in class, can't be declared out scope of class
*/
#else
friend ostream& operator<<(ostream& os, const sales_item& s_item);
friend istream& operator>>(istream& is, sales_item& item);
#endif /*COUT_IS_MEMBER*/

};

/*
* non-class member
*/
sales_item operator+(const sales_item& item1, const sales_item& item2);

#endif /*__SALE_ITEM__H*/