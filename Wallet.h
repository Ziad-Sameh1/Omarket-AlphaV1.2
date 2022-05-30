#pragma once
#include <string>
using namespace std;
class Wallet
{
private:
	string userId;
	float amount;
public :
	Wallet();
	~Wallet();
	void setUserId(string id);
	void setAmount(float amount);
	string getUserId();
	float getWalletAmount();
	void deposit(string userId, float amount);
	void withDraw(string userId, float amount);
	void requestDeposit(float amount);
};

