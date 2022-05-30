#include "DepositRequests.h"

void DepositRequests::setUserId(string id)
{
	this->userId = id;
}

void DepositRequests::setAmount(float amount)
{
	this->amount = amount;
}

void DepositRequests::approve()
{
	this->isApproved = true;
}

void DepositRequests::setIsApproved(bool value)
{
	this->isApproved = value;
}

string DepositRequests::getUserId()
{
	return this->userId;
}

float DepositRequests::getAmount()
{
	return this->amount;
}

bool DepositRequests::status()
{
	return this->isApproved;
}

string DepositRequests::toString() {
	return "\n*****************************\nUser Id: " + userId + "\nAmount: " + to_string(amount) + "\n*****************************";
}