#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <memory>
#include "Observer.h"
#include "Observable.h"
#include <boost/signals2.hpp>

using namespace boost;
using namespace boost::signals2;

using namespace std;


class Person : public Observable<Person>//observable
{
	int age;
public:
	Person(int a) {
		age = a;
	}

	int getAge() {
		return age;
	}

	void setAge(int age) {
		if (this->age == age)return;

		this->age = age;
		notify(*this, "age");
	}

};

//observer & observable
struct ConsolePersonObserver: public Observer<Person>
{
private:
	void field_changed(Person& source, const string& field_name) override {
		cout << "Person's " << field_name << " has changed to ";
		if (field_name == "age") cout << source.getAge();
		cout << "\n";
	}

};

template<typename T> 
struct Observable2
{
	signal<void(T&, const string&)> field_changed;
	
};

class Person2 : public Observable2<Person2>
{
	int age;
public:
	int get_age()const {
		return age;
	}

	void set_age(int age)
	{
		if (this->age == age)return;
		this->age = age;
		field_changed(*this, "age");

	}
};


int main()
{
	Person person(10);
	ConsolePersonObserver cpo;

	person.subscribe(cpo);
	
	person.setAge(11);
	person.setAge(12);
	person.unsubscribe(cpo);
	person.setAge(13);

	Person2 person2;
	auto connect = person2.field_changed.connect(
		[](Person2& p, const string& field_name) {
			cout << field_name << " has changed\n";
		}
	);

	person2.set_age(20);
	person2.set_age(30);

	connect.disconnect(); //equivalent to unsubscribing


}
