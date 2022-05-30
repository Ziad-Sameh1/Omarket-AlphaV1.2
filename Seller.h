#pragma once
#include "User.h"
#include <vector>
#include <set>
#include "Order.h"
#include "Product.h"

class Seller : public User
{
private :
	vector<string>productsAdded;
	int numOfReports = 0;
	float totalRates = 0.0;
	float averageRate = 0;
	int numOfRates = 0;
	vector<string>peopleReported;
public:
	Seller();
	~Seller();
	float getAverageRate();
	float getTotalRates();
	int getNumOfRates();
	int getNumOfReports();
	vector<string> getProductsAdded();
	vector<string> getPeopleReported();


	void setAverageRate(float averageRate);
	void setTotalRate(float totalRates);
	void setNumOfRates(int numOfRates);
	void setNumOfReports(int numOfReports);
	void setPeopleReported(vector<string> peopleReported);
	void setProductsAdded(vector<string> products);

	static bool signUp(Seller newSeller);
	static bool login(Seller seller);
	void updateRating(float newRate);
	vector<Order> getActiveOrders();
	void addNewProduct(Product product);
	void addReport(string userId);
	void removeReport(string userId);
	bool isUserReported(string userId);

	bool productsValidation();
	void deleteUser();
	void clear();
	void clearData();
};

