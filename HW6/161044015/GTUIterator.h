#ifndef GTUITERATOR_H
#define GTUITERATOR_H

using namespace std;

namespace gtu_container
{
	template<class T>
	class GTUIterator
	{
	public:
		GTUIterator();

		GTUIterator(T *);

	    T& operator*()const; 

	    T* operator->()const;

		GTUIterator<T> &operator++();

		GTUIterator<T> &operator++(int ignoreMe);

		GTUIterator<T> &operator--();

		GTUIterator<T> &operator--(int ignoreMe);

		GTUIterator<T> &operator=(const GTUIterator& other);

		bool operator==(const GTUIterator& other)const;

	    bool operator!=(const GTUIterator& other)const;
	    
	private:
		T *p;
	};
}
#endif