#include <iostream>

#include "GTUIterator.h"

using namespace std;

namespace gtu_container
{
	template <class T>
	GTUIterator<T>::GTUIterator() 
			: p(nullptr)
	{}

	template <class T>
	GTUIterator<T>::GTUIterator(T * new_ptr)
			: p(new_ptr)
	{}

	template<class T>
	GTUIterator<T> &GTUIterator<T>::operator++() //Operator for increasing
	{
		++p;
		return *this;
	}

	template<class T>
	GTUIterator<T> &GTUIterator<T>::operator++(int ignoreMe) 
	{
		GTUIterator temp = *this;
		++p;
		return temp;
	}

	template<class T>
	GTUIterator<T> &GTUIterator<T>::operator--() //Operator for decreasing
	{
		--p;
		return *this;
	}

	template<class T>
	GTUIterator<T> &GTUIterator<T>::operator--(int ignoreMe)
	{
		GTUIterator temp = *this;
		--p;
		return temp;
	}

	template<class T>
	GTUIterator<T> &GTUIterator<T>::operator=(const GTUIterator& other) //Assign operator
	{
		if(this != &other){
			p = other.p;
			return *this;
		}
		else
			return *this;
	}

	template<class T>
	bool GTUIterator<T>::operator==(const GTUIterator& other)const
	{
		if(p == other.p)
			return true;
		else
			return false;
	}

	template<class T>
	bool GTUIterator<T>::operator!=(const GTUIterator& other)const
	{
		if(p != other.p)
			return true;
		else
			return false;
	}

	template<class T>
	T &GTUIterator<T>::operator*()const
	{
		return *p;
	}

	template<class T>
	T* GTUIterator<T>::operator->()const
	{
		return p;
	}
}