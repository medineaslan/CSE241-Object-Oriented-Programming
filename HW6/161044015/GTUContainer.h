#ifndef GTUCONTAINER_H
#define GTUCONTAINER_H

#include <exception>	
#include <memory> 
#include "GTUIteratorConst.h"
#include "GTUIterator.h"

using namespace std;

namespace gtu_container
{
	template<class T>
	class GTUContainer
	{
	public:

		virtual bool empty()const = 0; //Test whether container is empty

		virtual int size()const = 0; //Return container size

		virtual int max_size()const = 0; //Return maximum size

		virtual void insert(T element) throw(invalid_argument) = 0; //Insert element, throws exception

		virtual void erase(T element) = 0; //Erase element 

		virtual void clear() = 0; //Clear all content

		virtual GTUIteratorConst<T> begin() = 0; //Return iterator to beginning 

		virtual GTUIteratorConst<T> end() = 0; //Return iterator to end

	protected:

		shared_ptr<T> data;
		int size_;
		int capacity;

	}; 
}

#endif 