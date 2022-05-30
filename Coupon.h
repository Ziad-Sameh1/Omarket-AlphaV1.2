#pragma once
#include <string>
using namespace std;
class Coupon
{
public:
	void setId(string id);
	void setCoupon(string coupon);
	void setDiscountAmount(float amount);

	string getId();
	string getCoupon();
	float getDiscountAmount();
private:
	string id;
	string coupon;
	float discountAmount = 0.0;
};

