#pragma once
#include "User.h"
#include <vector>
#include "Product.h"
#include "Cart.h"
#include "Order.h"
class Customer : public User
{
private :
	string phone;
	string address;
	vector<string>favsProductsIds;
	vector<string>orders;
	int points = 0;
public :
	Customer();
	~Customer();
	void setPhone(string phone);
	void setAddress(string address);
	void setFavs(vector<string> favs);
	void setOrders(vector<string> orders);
	void setPoints(int points);
	bool addProductToFavs(Product product);
	bool removeProductFromFavs(string productId);
	void addPoints(int points);
	void removePoints(int points);
	bool convertPointstoCash(int points);
	void clearData();


	string getPhone();
	string getAddress();
	int getPoints();
	vector<string> getFavs();
	vector<string> getOrders();
	bool isProductInFavs(Product product);

	void deleteUser();
	bool ordersValidation();
	bool depositValidation();
	void clear();

	void refund(Product refundedProduct);
	void backProduct(string refundedProduct, int quantity);
	void backCash(float cash);
	void backPoints(Product refundedProduct);

	static vector<Product>browse(string productName);
	static vector<Product>browseByCategory(string categoryName);
	static vector<Product>browseByRate(float rate);
	void logOut();
	bool checkOut();
	void createOrder(Cart cart);
	int getCartPoints(Cart cart);

	static vector<Order> viewCheckoutHistory();
	static bool createCustomer(Customer customer);
	static bool loginCustomer(Customer customer);
};

