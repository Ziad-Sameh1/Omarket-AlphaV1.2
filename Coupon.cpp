#include "Coupon.h"

void Coupon::setId(string id)
{
	this->id = id;
}

void Coupon::setCoupon(string coupon)
{
	this->coupon = coupon;
}

void Coupon::setDiscountAmount(float amount)
{
	this->discountAmount = amount;
}

string Coupon::getId()
{
	return this->id;
}

string Coupon::getCoupon()
{
	return this->coupon;
}

float Coupon::getDiscountAmount()
{
	return this->discountAmount;
}
