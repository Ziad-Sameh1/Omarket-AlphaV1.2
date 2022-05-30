#include "Product.h"
#include "Utils.h"

Product::Product() {
}

string Product::getId() {
	return this->id;
}

string Product::getName() {
	return this->name;
}

string Product::getDescription() {
	return this->description;
}

string Product::getImagePath() {
	return this->imagePath;
}

string Product::getSellerId() {
	return this->sellerId;
}

float Product::getPrice() {
	return this->price;
}

int Product::getQuantity() {
	return this->quantity;
}

string Product::getCategory() {
	return this->category;
}

int Product::getNumOfRates() {
	return this->numOfRates;
}

float Product::getAverageRate() {
	return this->averageRate;
}

int Product::getPoints() {
	return this->points;
}

bool Product::getIsActivated()
{
	return this->isActivated;
}

void Product::decreaseQuantity(int quantity)
{
	if (this->quantity - quantity >= 0) {
		this->quantity -= quantity;
		return;
	}
	// todo: show error
}

void Product::increaseQuantity(int quantity)
{
	this->quantity += quantity;
}

void Product::setComments(vector<Comment> comments)
{
	this->comments = comments;
}

float Product::getTotalRates()
{
	return this->totalRates;
}


void Product::setId(string id) {
	this->id = id;
}

void Product::setName(string name) {
	this->name = name;
}

void Product::setDescription(string description) {
	this->description = description;
}

void Product::setImagePath(string imagePath) {
	this->imagePath = imagePath;
}

void Product::setSellerId(string sellerId) {
	this->sellerId = sellerId;
}

void Product::setPrice(float price) {
	this->price = price;
}

void Product::setQuantity(int quantity) {
	this->quantity = quantity;
}

void Product::setCategory(string category) {
	this->category = category;
}

void Product::setNumOfRates(int numOfRates) {
	this->numOfRates = numOfRates;
}

void Product::setAverageRate(float averageRate) {
	this->averageRate = averageRate;
}

void Product::setTotalRate(float totalRates)
{
	this->totalRates = totalRates;
}

void Product::setPoints(int points) {
	this->points = points;
}

void Product::setIsActivated(bool newValue)
{
	this->isActivated = newValue;
}

// Rating system
void Product::updateRating(float newRate) {
	this->numOfRates++;
	this->totalRates += newRate;
	this->averageRate = totalRates / numOfRates;
}

void Product::addComment(Comment comment)
{
	Utils* utils = Utils::getInstance();
	utils->comments.push_back(comment);
	comments.push_back(comment);
}

vector<Comment> Product::getComments()
{
	return this->comments;
}

string Product::toString() {
	return "\n********************************************\nName: " + name + "\nDescription: " + description + "\nPrice: " + to_string(price) + "\nQuantity: " + to_string(quantity) + "\nCategory: " + category + "\nRating: " + to_string(averageRate) + "\nPoints: " + to_string(points) + "\nIs in Stock: " + to_string(isActivated) + "\n********************************************";
}