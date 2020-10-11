#ifndef GTUSET_H
#define GTUSET_H

#include "GTUContainer.h"
#include "GTUIteratorConst.h"
#include "GTUIterator.h"
#include <exception>
#include <memory>

using namespace std;

namespace gtu_container
{
	template<class T>
	class GTUSet : public GTUContainer<T>
	{
	public:

		GTUSet();

		virtual bool empty()const;

		virtual int size()const;

		virtual int max_size()const;

		virtual void insert(T element) throw(invalid_argument);

		virtual void erase(T element);

		virtual void clear();

		virtual GTUIteratorConst<T> begin();

		virtual GTUIteratorConst<T> end();

	}; 
}

#endif 