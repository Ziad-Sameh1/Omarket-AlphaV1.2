#pragma once
#include <vector>
#include <string>
#include "Comment.h"

using namespace std;
class Product
{
private :
	string id;
	string name;
	string description;
	string imagePath;
	string sellerId;
	float price = 0;
	int quantity = 0;
	string category;
	int numOfRates = 0;
	float totalRates = 0.0;
	float averageRate = 0;	
	int points = 0;
	vector<Comment>comments;
	bool isActivated = false;
public : 
	Product();
	string getId();
	string getName();
	string getDescription();
	string getImagePath();
	string getSellerId();
	float getPrice();
	int getQuantity();
	string getCategory();
	int getNumOfRates();
	float getAverageRate();
	float getTotalRates();
	int getPoints();
	bool getIsActivated();
	void decreaseQuantity(int quantity);
	void increaseQuantity(int quantity);
	void setComments(vector<Comment> comments);


	void setId(string id);
	void setName(string name);
	void setDescription(string description);
	void setImagePath(string imagePath);
	void setSellerId(string sellerId);
	void setPrice(float price);
	void setQuantity(int quantity);
	void setCategory(string category);
	void setNumOfRates(int numOfRates);
	void setAverageRate(float averageRate);
	void setTotalRate(float totalRates);
	void setPoints(int points);
	void setIsActivated(bool newValue);
	void updateRating(float newRate);
	void addComment(Comment comment);
	vector<Comment> getComments();
	string toString();
};


