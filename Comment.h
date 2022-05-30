#pragma once
#include <string>
#include <vector>
using namespace std;
class Comment
{
private :
	string id;
	string customerId;
	string date;
	int numOfLikes = 0;
	int numOfDislikes = 0;
	vector<string>peopleLiked;
	vector<string>peopleDisliked;
	string content;

public:
	Comment();
	~Comment();
	void setId(string id);
	void setCustomerId(string customerId);
	void setDate(string date);
	void setNumOfLikes(int numOfLikes);
	void setNumOfDislikes(int numOfDislikes);
	void setContent(string content);
	bool addLike(string userId);
	bool removeLike(string userId);
	bool addDisLike(string userId);
	bool removeDislike(string userId);
	void setPeopleLiked(vector<string>likes);
	void setPeopleDisliked(vector<string>dislikes);


	string getId();
	string getCustomerId();
	string getDate();
	int getNumOfLikes();
	int getNumOfDislikes();
	string getContent();
	bool isUserLiked(string userId);
	bool isUserDisliked(string userId);
	vector<string> getPeopleLiked();
	vector<string> getPeopleDisliked();
	string toString();
};

