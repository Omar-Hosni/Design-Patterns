#pragma once
#include <vector>
#include <string>
#include <mutex>
using namespace std;

template<typename> struct Observer;

template<typename T>
class SaferObservable
{
	vector<Observer<T>*> observers;
	typedef std::mutex mutex_t;
	mutex_t mtx;
public:

	void notify(T& source, const string& field_name)
	{
		std::scoped_lock<mutex_t> lock(mtx);


		for (auto observer : observers)
		{
			observer->field_changed(source, field_name);
		}
	}
	void subscribe(Observer<T>& observer)
	{
		observers.push_back(&observer);
	}

	void unsubscribe(Observer<T>& observer)
	{
		observers.erase(
			remove(observers.begin(), observers.end(), observer), observers.end()
		);
	}
};

