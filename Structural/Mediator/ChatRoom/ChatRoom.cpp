#include "ChatRoom.h"

void ChatRoom::broadcast(const string& origin, const string& message)
{
	for(auto p: people)
		if(p->name != origin)
			p->recieve(origin, message);
}

void ChatRoom::join(Person* p) 
{
	string join_msg = p->name + " joined the chat";
	broadcast("room", join_msg);
	p->room = this;
	people.push_back(p);
}