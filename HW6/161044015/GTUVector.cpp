#include <iostream>
#include "GTUVector.h"

using namespace std;

namespace gtu_container
{
	template<class T>
	GTUVector<T> :: GTUVector() //Constructor
	{
		this->size_ = 0;
		this->capacity = 5;
		shared_ptr<T> temp(new T[this->capacity],default_delete<T[]>());
		this->data = temp;
	}

	template<class T>
	GTUIteratorConst<T> GTUVector<T>::end()
	{
		T *temp = this->data.get();

		temp = temp + this->size_;

		return GTUIteratorConst<T>(temp);//Return end of the iterator.
	}

	template<class T>
	GTUIteratorConst<T> GTUVector<T>::begin()
	{
		T *temp = this->data.get(); 

		return GTUIteratorConst<T>(temp);//Return beginning of the iterator.
	}

	template<class T>
	void GTUVector<T> :: clear()
	{
		this->size_= 0;
		this->data = nullptr;
		this->capacity = 5;
		shared_ptr<T> temp(new T[this->capacity],default_delete<T[]>());
		this->data = temp;
	}

	template<class T>
	void GTUVector<T>::erase(T element)
	{
		int i, indexOfErase;
		bool isErase = false;

		for(i=0; i < this->size_; i++)
		{
			//condition to have the element to be deleted
			if(this->data.get()[i] == element)
			{
				isErase = true; 
				indexOfErase = i;
				break;
			}
		}

		if(isErase)
		{
			int i;

			i = indexOfErase;

			this->size_--;

			//Shifting indexes
			while(i < this->size_){
				this->data.get()[i] = this->data.get()[i+1]; 
				i++;
			}
		}
	}

	template<class T>
	void GTUVector<T>::insert(T element) throw(invalid_argument)
	{
		if(this->size_ >= this->capacity ){//if size >= capacity makes capacity*2.

			int i;

			shared_ptr<T> temp(new T[this->capacity],default_delete<T[]>()); 

			for(i=0; i < this->size_; i++)////Backup old data.      
				temp.get()[i] = this->data.get()[i];

			this->capacity *= 2; //Allocation for capacity*2

			shared_ptr<T> new_ptr(new T[this->capacity],default_delete<T[]>()); //allocation for capacity * 2 

			this->data = nullptr;
			this->data = new_ptr;

			for(int i = 0;i < this->size_;i++)
				this->data.get()[i] = temp.get()[i];
			
			this->data.get()[this->size_] = element;
		}
		else if(this->size_ != this->capacity)
			this->data.get()[this->size_] = element;
		
		this->size_++;
	}

	template<class T>
	int GTUVector<T> :: max_size()const
	{
		return 10000000; //Returns max_size;
	}

	template<class T>
	int GTUVector<T> :: size()const
	{
		return this->size_; //Returns set size;
	}

	template<class T>
	bool GTUVector<T> :: empty()const
	{
		if(this->size_ == 0)
			return true;
		else 
			return false;
	}

	template<class T>
	T GTUVector<T>::operator[](int index)
	{
		return this->data[index];
	}
}

