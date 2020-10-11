#include <iostream>

#include "GTUIteratorConst.h"

using namespace std;

namespace gtu_container
{
	template <class T>
	GTUIteratorConst<T>::GTUIteratorConst() 
			: p(nullptr)
	{}

	template <class T>
	GTUIteratorConst<T>::GTUIteratorConst(T * new_ptr) 
			: p(new_ptr)
	{}
	
	template<class T>
	GTUIteratorConst<T> &GTUIteratorConst<T>::operator++()
	{
		++p;
		return *this;
	}

	template<class T>
	GTUIteratorConst<T> &GTUIteratorConst<T>::operator++(int ignoreMe)
	{
		GTUIteratorConst temp = *this;
		++p;
		return temp;
	}

	template<class T>
	GTUIteratorConst<T> &GTUIteratorConst<T>::operator--()
	{
		--p;
		return *this;
	}

	template<class T>
	GTUIteratorConst<T> &GTUIteratorConst<T>::operator--(int ignoreMe)
	{
		GTUIteratorConst temp = *this;
		--p;
		return temp;
	}

	template<class T>
	GTUIteratorConst<T> &GTUIteratorConst<T>::operator=(const GTUIteratorConst& other)
	{
		if(this != &other){
			p = other.p;
			return *this;
		}
		else
			return *this;
	}

	template<class T>
	bool GTUIteratorConst<T>::operator==(const GTUIteratorConst& other)const
	{
		if(p == other.p)
			return true;
		else
			return false;
	}

	template<class T>
	bool GTUIteratorConst<T>::operator!=(const GTUIteratorConst& other)const
	{
		if(p != other.p)
			return true;
		else
			return false;
	}

	template<class T>
	const T &GTUIteratorConst<T>::operator*()const
	{
		return *p;
	}

	template<class T>
	const T* GTUIteratorConst<T>::operator->()const
	{
		return p;
	}
}