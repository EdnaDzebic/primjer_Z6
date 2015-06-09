#ifndef H_orderedListType
#define H_orderedListType

#include "lista.h"
#include <iostream>

using namespace std;
template <class Type>
class List: public linkedListType<Type>
{
  public:
    	  class iterator;
	  bool search(const Type& searchItem) const;	
	  void insertFirst(const Type& newItem);	
	  void insertLast(const Type& newItem);	
	  void deleteNode(const Type& deleteItem);
    	  iterator begin() const { return linkedListType<Type>::first; }
    	  iterator end() const { return linkedListType<Type>::last->getLink(); }
	  void mergeSort();
	  void recMergeSort(Cvor<Type>* &first);
	  void divideList(Cvor<Type>* first1,Cvor<Type>* &first2);
	  Cvor<Type>* mergeList(Cvor<Type>*first1, Cvor<Type>* first2);
};


template <class Type>
bool List<Type>::search(const Type& searchItem) const
{
	bool found = false;
	Cvor<Type> *current; //pokazivač za prolazak kroz listu
	current = this->first;	//počni pretragu od prvog čvora u listi

	while (current != nullptr && !found) //dok ima elemenata za pretragu i dok ne nađemo element kojeg tražimo
		if ((*current).getInfo() == searchItem)// ako je na trenutnom čvoru info dio jednak traženom, našli smo željeni čvor
			found = true;
		else
			current = (*current).getLink(); //ako nije, onda pomjeri pokazivač na sljedeći čvor
	
	return found;
}//end search

template <class Type>
void List<Type>::insertFirst(const Type& newItem)
{
	Cvor<Type> *newNode;  //pokazivač za kreiranje novog čvora
	newNode = new Cvor<Type>; //kreiraj novi čvor
	(*newNode).setInfo(newItem);//postavi info dio novog čvora
	(*newNode).setLink(this->first);//postavi link dio novog čvora na trenutni prvi čvor u listi
	this->first = newNode;	//postavi first da pokazuje na trenutni prvi čvor
	this->count++;	//povećaj veličinu
	if (this->last == nullptr) //ako je lista bila prazna, onda je ovo prvi element u listi i također posljednji, pa last treba da pokazuje na taj novi čvor
		this->last = newNode;
}//end insertFirst


template <class Type>
void List<Type>::insertLast(const Type& newItem)
{
	Cvor<Type> *newNode;  //pokazivač za kreiranje novog čvora
	newNode = new Cvor<Type>; //kreiraj novi čvor
	(*newNode).setInfo(newItem);	//postavi info dio novog čvora
	(*newNode).setLink(nullptr);//postavi link novog čvora na nullptr vrijednost jer će biti posljednji u listi
	if (this->first == nullptr) //ako je lista prazna, novi čvor će biti ujedno i prvi, i postavi first i last da pokazuju na taj novi čvor
	{
		this->first = newNode;
		this->last = newNode;
		this->count++; //povećaj veličinu
	}
	else
	//lista nije prazna, ubaci element na kraj
	{
		this->last->setLink(newNode); //ubaci novi element na kraj (trenutno posljednjem elementu postavi link na novi čvor)
		this->last = newNode; //postavi last da pokazuje na novi čvor jer je on sada posljednji
		this->count++; //povećaj veličinu
	}
}//end insertLast


template <class Type>
void List<Type>::deleteNode(const Type& deleteItem)
{
	Cvor<Type> *current; //pokazivač za prolazak kroz listu
	Cvor<Type> *trailCurrent; //pokazivač na čvor prije trenutnog
	bool found;
	if (this->first == nullptr) //Case 1; lista je prazna.
		cout << "Cannot delete from an empty list."<< endl;
	else
	{
	if (this->first->getInfo() == deleteItem) //Case 2
	{ 	//brišemo prvi čvor u listi
		current = this->first; //postavi pokazivač trenutni na prvi čvor
		this->first = this->first->getLink();   //preusmjeri first na drugi čvor
		this->count--; //smanji veličinu
		if (this->first == nullptr) //ako je to bio jedini čvor, last je pokazivao na njega, sad treba postaviti ga na nullptr
			this->last = nullptr;
		
		delete current;//obriši čvor
	}
	else //pretraži listu da se nađe čvor kojeg treba obrisati
	{
		found = false;
		trailCurrent = this->first; //postavi trailCurrent da pokazuje na prvi čvor
		current = this->first->getLink(); //postavi current da pokazuje na drugi čvor

		while (current != nullptr && !found)//dok ne dođemo do kraja i ne nađemo šta tražimo
		{
			if (current->getInfo() != deleteItem) //pomjeraj se kroz listu dalje dok ne nađemo element kojeg želimo obrisati
			{
				trailCurrent = current;
				current = current->getLink();
			}
			else
				found = true;
		}//end while
		if (found) //Case 3; ako smo našli element kojeg želimo obrisati, current pokazuje na čvor kojeg želimo obrisati
		{
			trailCurrent->setLink(current->getLink()); //trailcurrent pokazuje na čvor prije čvora kojeg želimo obrisati
			//tom čvoru postavi link da čvor koji se nalazi iza čvora kojeg želimo obrisati
			this->count--;//smanji veličinu
			if (this->last == current) //čvor kojeg želimo obrisati je bio posljednji u listi
				this->last = trailCurrent; // postavi last da pokazuje na trenutno predzadnji čvor u listi

			delete current; //obriši čvor
		}
		else //čvor kojeg želimo obrisati nije u listi
			cout << "The item to be deleted is not in the list." << endl;
	}//end else
	}//end else
}//end deleteNode

template <class Type>
class List<Type>::iterator : public std::iterator<std::forward_iterator_tag, Type>
{
  private:
    Cvor<Type> *pointer = nullptr;
  public:
    iterator() = default;
    iterator(Cvor<Type> *p) : pointer(p) {}

    Type& operator*() { return pointer->getInfo(); }
    const Type& operator*() const { return pointer->getInfo(); }
    const Type* operator->() const { return &pointer->getInfo(); }
    iterator operator++(int) 
    { 
      Cvor<Type> *temp = pointer;
      pointer=pointer->getLink();
      return temp;
    }
    iterator& operator++()
    {
      pointer=pointer->getLink();
      return *this;
    }
    bool operator==(const iterator& it) const
    {
      return pointer==it.pointer;
    }
    bool operator!=(const iterator& it) const
    {
      return pointer!=it.pointer;
    }
    iterator& operator=(Cvor<Type> *p)
    {
      pointer=p;
      return *this;
    }
   
};



/* 	MERGE SORT */

template <class Type>
void List<Type>::divideList(Cvor<Type>* first1,Cvor<Type>* &first2)
{
	Cvor<Type>* middle;
	Cvor<Type>* current;
	if (first1 == nullptr)	//list is empty
		first2 = nullptr;
	else if (first1->getLink() == nullptr) //list has only one node
		first2 = nullptr;
	else
	{
		middle = first1;
		current = first1->getLink();
		if (current != nullptr)
		//list has more than two nodes
		current = current->getLink();
		while (current != nullptr)
		{
			middle = middle->getLink();
			current = current->getLink();
			if (current != nullptr)
				current = current->getLink();
		} //end while
		first2 = middle->getLink(); //first2 points to the first
		//node of the second sublist
		middle->setLink(nullptr);
		//set the link of the last node
		//of the first sublist to nullptr
	} //end else
} //end divideList

template <class Type>
Cvor<Type>* List<Type>::mergeList(Cvor<Type>*first1, Cvor<Type>* first2)
{
	Cvor<Type> *lastSmall; //pointer to the merged
	Cvor<Type> *newfirst;//pointer to the last node of list the merged list
	if (first1 == nullptr)//the first sublist is empty
		return first2;
	else if (first2 == nullptr)//the second sublist is empty
		return first1;
	else
	{
	if (first1->getInfo() < first2->getInfo()) //compare the first nodes
	{
		newfirst = first1;
		first1 = first1->getLink();
		lastSmall = newfirst;
	}
	else
	{
		newfirst = first2;
		first2 = first2->getLink();
		lastSmall = newfirst;
	}
	while (first1 != nullptr && first2 != nullptr)
	{
		if (first1->getInfo() < first2->getInfo())
		{
			lastSmall->setLink(first1);
			lastSmall = lastSmall->getLink();
			first1 = first1->getLink();
		}
		else
		{
			lastSmall->setLink(first2);
			lastSmall = lastSmall->getLink();
			first2 = first2->getLink();
		}
	} //end while
	if (first1 == nullptr) //first sublist is exhausted first
		lastSmall->setLink(first2);
	else 	//second sublist is exhausted first
		lastSmall->setLink(first1);
	return newfirst;
	}
}//end mergeList

template <class Type>
void List<Type>::recMergeSort(Cvor<Type>* &first)
{
	Cvor<Type> *otherfirst;
	if (first != nullptr) //if the list is not empty
	if (first->getLink() != nullptr) //if the list has more than one node
	{
		divideList(first, otherfirst);
		recMergeSort(first);
		recMergeSort(otherfirst);
		first = mergeList(first, otherfirst);
	}
} //end recMergeSort

template<class Type>
void List<Type>::mergeSort()
{
	recMergeSort(this->first);
	if (this->first == nullptr)
		this->last = nullptr;
	else
	{
		this->last = this->first;
		while (this->last->getLink() != nullptr)
			this->last = this->last->getLink();
	}
} //end mergeSort



#endif
