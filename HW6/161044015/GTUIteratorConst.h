#ifndef GTUITERATORCONST_H
#define GTUITERATORCONST_H

using namespace std;

#include <memory>

namespace gtu_container
{
	template<class T>

	class GTUIteratorConst 
	{
	public:
		GTUIteratorConst();

		GTUIteratorConst(T *);

	    const T& operator*()const; 

	    const T* operator->()const;

		GTUIteratorConst<T> &operator++();

		GTUIteratorConst<T> &operator++(int ignoreMe);

		GTUIteratorConst<T> &operator--();

		GTUIteratorConst<T> &operator--(int ignoreMe);

		GTUIteratorConst<T> &operator=(const GTUIteratorConst& other);

		bool operator==(const GTUIteratorConst& other)const;

	    bool operator!=(const GTUIteratorConst& other)const;

	private:
		T *p;
	};
}
#endif