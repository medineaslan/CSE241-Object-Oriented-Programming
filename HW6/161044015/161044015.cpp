#include <iostream>

#include "GTUIterator.cpp"
#include "GTUIteratorConst.cpp"
#include "GTUSet.cpp"
#include "GTUContainer.cpp"
#include "GTUVector.cpp"

using namespace std;
using namespace gtu_container;

//It makes iterator find function for gtuIterator.
//Returning last element if it is not found.
template<class myIterator, class T>
myIterator find(myIterator begin, myIterator end, const T& value)
{
	cout << "Element is : " << value << endl;
	while(true){
		if(begin != end)
		{
			if (*begin == value) return begin;
	    	++begin;
		}
		else
			break;
	}
	return end;
}

//It makes iterator find_if function for gtuIterator.
//Returning last element if it is not found.
template<class myIterator, class UnaryPredicate>
myIterator find_if(myIterator begin, myIterator end, UnaryPredicate myPred)
{
	while(true){
		if(begin != end){
			if (myPred(*begin)){
				return begin;
			} 
	    	++begin;
		}
		else
			break;
	}
	return end;
}

//Function for find_if function.
bool isEvenNumber(int number)
{
	if(number % 2 == 0)
		return true;
	else
		return false;
}

//Function for for_each function.
//Takes square of elements in container.
void functionForForEach(int element) 
{
	cout << ' ' << element*element;
}

//It makes iterator for_each function for gtuIterator.
//Find each element in the range.
template<class myIterator, class Function>
Function for_each(myIterator begin, myIterator end, Function myFunction)
{
	while(true){
		if(begin != end){
			myFunction(*begin);
			++begin;
		}
		else
			break;
	}
	return myFunction;
}

int main()
{

	GTUSet<int> myGtuSet;
	GTUVector<double> myGtuVector;
	GTUIteratorConst<int> myGtuIt;
	GTUIteratorConst<double>myGtuItDouble;

	cout << endl;

	cout << "=========================TEST SET=========================" << endl;

	cout << endl;

	cout << "Initially size of set is : " << myGtuSet.size() << endl;

	if(myGtuSet.empty())
		cout << "Set is empty" << endl;
	else
		cout << "Set is not empty" << endl;

	cout << endl;

	cout <<"INSERT ELEMENT" << endl;
	cout << endl;
	try{
		myGtuSet.insert(1);
		myGtuSet.insert(4);
		myGtuSet.insert(2);
		myGtuSet.insert(3);
		myGtuSet.insert(8);
		myGtuSet.insert(6);
		myGtuSet.insert(10);
		myGtuSet.insert(2);
	}
	catch(invalid_argument bad_param) {
		cerr <<  bad_param.what() << endl;
 	}
 	for(myGtuIt = myGtuSet.begin(); myGtuIt != myGtuSet.end(); ++myGtuIt)
		cout << *myGtuIt << endl;

	cout << endl;
	cout << "ERASE ELEMENT" << endl;
	cout << endl;

	myGtuSet.erase(4);
	myGtuSet.erase(4);
	myGtuSet.erase(8);

	for(myGtuIt = myGtuSet.begin(); myGtuIt != myGtuSet.end(); ++myGtuIt)
		cout << *myGtuIt << endl;

	cout << endl;

	cout << "Size of set is : " << myGtuSet.size() << endl;

	if(myGtuSet.empty())
		cout << "Set is empty" << endl;
	else
		cout << "Set is not empty" << endl;

	cout << endl;
	cout << "GLOBAL FUNCTION FIND" << endl;
	cout << endl;

	auto myIt1 = find(myGtuSet.begin(), myGtuSet.end(), 3);

	if(myIt1 == myGtuSet.end())
		cout << "Element is not found." << endl;
	else
		cout << "Element is found." << endl;

	cout << endl;

	cout << "GLOBAL FUNCTION FIND_IF" << endl;

	cout << endl;
			
	auto myIt2 = find_if (myGtuSet.begin(), myGtuSet.end(), isEvenNumber);
  	cout << "First even number is in my set: " << *myIt2 << endl;

	cout << endl;
	cout << "GLOBAL FUNCTION FOR_EACH" << endl;
	cout << endl;

	cout << "Square of elements in vector." << endl;

	cout << endl;

	for_each (myGtuSet.begin(), myGtuSet.end(), functionForForEach);
	cout << endl;
	
	cout << endl;
	cout << "Max_size of set is : " << myGtuSet.max_size() << endl;

	cout << endl;
	cout << "CLEAR SET" << endl;

	myGtuSet.clear();

	for(myGtuIt = myGtuSet.begin(); myGtuIt != myGtuSet.end(); ++myGtuIt)
		cout << *myGtuIt << endl;

	cout << endl;

	cout << "=========================TEST VECTOR=========================" << endl;

	cout << endl;

	cout << "Initially size of vector is : " << myGtuVector.size() << endl;

	if(myGtuVector.empty())
		cout << "Vector is empty" << endl;
	else
		cout << "Vector is not empty" << endl;

	cout << endl;

	cout <<"INSERT ELEMENT" << endl;

	cout << endl;
	
	myGtuVector.insert(3.2);
	myGtuVector.insert(1.1);
	myGtuVector.insert(8.7);
	myGtuVector.insert(18.2);
	myGtuVector.insert(7.1);
	myGtuVector.insert(7.1);
	myGtuVector.insert(15.6);
	myGtuVector.insert(4.3);

 	for(myGtuItDouble = myGtuVector.begin(); myGtuItDouble != myGtuVector.end(); ++myGtuItDouble)
		cout << *myGtuItDouble << endl;

	cout << endl;

	cout << "ERASE ELEMENT" << endl;

	cout << endl;

	myGtuVector.erase(3.2);
	myGtuVector.erase(3.2);
	myGtuVector.erase(8.7);

	for(myGtuItDouble = myGtuVector.begin(); myGtuItDouble != myGtuVector.end(); ++myGtuItDouble)
		cout << *myGtuItDouble << endl;

	cout << endl;

	cout << "Size of vector is : " << myGtuVector.size() << endl;

	if(myGtuVector.empty())
		cout << "Vector is empty" << endl;
	else
		cout << "Vector is not empty" << endl;

	cout << endl;

	cout << "GLOBAL FUNCTION FIND" << endl;

	cout << endl;

	auto myIt3 = find(myGtuVector.begin(), myGtuVector.end(), 7.1);

	if(myIt3 == myGtuVector.end())
		cout << "Element is not found." << endl;
	else
		cout << "Element is found." << endl;

	cout << endl;

	cout << "GLOBAL FUNCTION FIND_IF" << endl;

	cout << endl;

	auto myIt4 = find_if (myGtuVector.begin(), myGtuVector.end(), isEvenNumber);
  	cout << "First even number is in my vector: " << *myIt4 << endl;

	cout << endl;

	cout << "GLOBAL FUNCTION FOR_EACH" << endl;

	cout << endl;

	cout << "Square of elements in vector." << endl;
	
	cout << endl;

	for_each (myGtuVector.begin(), myGtuVector.end(), functionForForEach);
	cout << endl;

	cout << endl;

	cout << "Max_size of vector is : " << myGtuVector.max_size() << endl;

	cout << endl;

	cout << "=======================================" << endl;

	cout << "Test iterator operators " << endl;

	auto newIt = myGtuVector.begin();

	--newIt;

	if(newIt == myGtuVector.begin())
		cout << "This iterators is equal" << endl;
	else
		cout << "This iterators is not equal" << endl;

	cout << "=======================================" << endl;

	cout << endl;

	cout << "CLEAR VECTOR" << endl;

	myGtuVector.clear();

	for(myGtuItDouble = myGtuVector.begin(); myGtuItDouble != myGtuVector.end(); ++myGtuItDouble)
		cout << *myGtuItDouble << endl;

	return 0;
}