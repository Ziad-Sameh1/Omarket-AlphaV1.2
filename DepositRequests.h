#pragma once
#include <string>
using namespace std;
class DepositRequests
{
public:
	void setUserId(string userId);
	void setAmount(float amount);
	void approve();
	void setIsApproved(bool value);

	string getUserId();
	float getAmount();
	bool status();
	string toString();
private:
	string userId;
	float amount = 0.0;
	bool isApproved = false;
};

