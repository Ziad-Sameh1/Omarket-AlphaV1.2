#include "ProductOrders.h"

void ProductOrders::setProductId(string productId)
{
	this->productId = productId;
}

void ProductOrders::setProductOrders(vector<Order> productOrders)
{
	this->productOrders = productOrders;
}

string ProductOrders::getProductId()
{
	return this->productId;
}

vector<Order> ProductOrders::getProductOrders()
{
	return productOrders;
}

void ProductOrders::addOrderToProduct(Order newOrder)
{
	this->productOrders.push_back(newOrder);
}
