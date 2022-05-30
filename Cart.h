#pragma once
#include <string>
#include <vector>
#include "Product.h"

using namespace std;
class Cart
{
private:
	string userId;
	vector<Product>productsInCart;
	float totalPrice = 0;

public:
	Cart();
	~Cart();
	void setUserId(string userId);
	bool addProductToCart(Product product);
	void setProductsinCart(vector<Product> products);
	void setTotalPrice(float totalPrice);
	void emptyCart();
	void removeProduct(Product product);

	string getUserId();
	vector<Product> getProductsInCart();
	float getTotalPrice();
};

