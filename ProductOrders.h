#pragma once
#include <string>
#include <vector>
#include "Order.h"
using namespace std;
class ProductOrders
{
private :
	string productId;
	vector<Order>productOrders;
public:
	void setProductId(string productId);
	void setProductOrders(vector<Order> productOrders);

	string getProductId();
	vector<Order> getProductOrders();

	void addOrderToProduct(Order newOrder);
};

