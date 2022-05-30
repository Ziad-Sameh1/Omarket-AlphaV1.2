#include "Comment.h"
#include "Utils.h"

Comment::Comment() {};

Comment::~Comment() {};

void Comment::setId(string id) {
	this->id = id;
};

void Comment::setCustomerId(string customerId) {
	this->customerId = customerId;
};

void Comment::setDate(string date) {
	this->date = date;
};

void Comment::setNumOfLikes(int numOfLikes) {
	this->numOfLikes = numOfLikes;
}
void Comment::setNumOfDislikes(int numOfDislikes)
{
	this->numOfDislikes = numOfDislikes;
}
;

void Comment::setContent(string content) {
	this->content = content;
}

string Comment::getId() {
	return this->id;
}

string Comment::getCustomerId() {
	return this->customerId;
}

string Comment::getDate() {
	return this->date;
}

int Comment::getNumOfLikes() {
	return this->numOfLikes;
}

int Comment::getNumOfDislikes()
{
	return this->numOfDislikes;
}

string Comment::getContent() {
	return this->content;
}

bool Comment::isUserLiked(string userId)
{
	size_t likesCnt = peopleLiked.size();
	for (int i = 0; i < likesCnt; i++) {
		if (peopleLiked[i] == userId) {
			return true;
		}
	}
	return false;
}

bool Comment::isUserDisliked(string userId)
{
	size_t dislikesCnt = peopleDisliked.size();
	for (int i = 0; i < dislikesCnt; i++) {
		if (peopleDisliked[i] == userId) {
			return true;
		}
	}
	return false;
}

vector<string> Comment::getPeopleLiked()
{
	return this->peopleLiked;
}

vector<string> Comment::getPeopleDisliked()
{
	return peopleDisliked;
}

bool Comment::addLike(string userId) {
	if (isUserLiked(userId)) {
		return false;
	}
	numOfLikes++;
	peopleLiked.push_back(userId);
	return true;
}

bool Comment::removeLike(string userId) {
	for (int i = 0; i < peopleLiked.size(); i++) {
		if (peopleLiked[i] == userId) {
			numOfLikes--;
			peopleLiked.erase(peopleLiked.begin() + i);
			return true;
		}
	}
	return false;
}

bool Comment::addDisLike(string userId) {
	if (isUserDisliked(userId)) {
		return false;
	}
	numOfDislikes++;
	peopleDisliked.push_back(userId);
	return true;
}

bool Comment::removeDislike(string userId) {
	for (int i = 0; i < peopleDisliked.size(); i++) {
		if (peopleDisliked[i] == userId) {
			numOfDislikes--;
			peopleLiked.erase(peopleDisliked.begin() + i);
			return true;
		}
	}
	return false;
}

void Comment::setPeopleLiked(vector<string> likes)
{
	this->peopleLiked = likes;
}

void Comment::setPeopleDisliked(vector<string> dislikes)
{
	this->peopleDisliked = dislikes;
}

string Comment::toString() {
	Utils* utils = Utils::getInstance();
	string customerName = "";
	for (int i = 0; i < utils->customers.size(); i++) {
		if (utils->customers[i].getId() == customerId) {
			customerName = utils->customers[i].getName();
		}
	}
	return "=====================================\nComment added by: " + customerName + "\nDate: " + date + "\nNumber of Likes: " + to_string(numOfLikes) + "\nNumber of Dislikes: " + to_string(numOfDislikes) + "\nContent: " + content + "=====================================\n";
}