#pragma once
/** Implementation file for the class ArrayBag.
 @file ArrayBag.cpp */

#include "ArrayBag.h"
#include <cstddef>
#include <iostream>

using namespace std;

template<class ItemType>
ArrayBag<ItemType>::ArrayBag(): itemCount(0), maxItems(DEFAULT_CAPACITY)
{
}  // end default constructor

template<class ItemType>
int ArrayBag<ItemType>::getCurrentSize() const
{
	return itemCount;
}  // end getCurrentSize

template<class ItemType>
bool ArrayBag<ItemType>::isEmpty() const
{
	return itemCount == 0;
}  // end isEmpty

template<class ItemType>
bool ArrayBag<ItemType>::add(const ItemType& newEntry)
{
	bool hasRoomToAdd = (itemCount < maxItems);
	if (hasRoomToAdd)
	{
		items[itemCount] = newEntry;
		itemCount++;
	}  // end if
    
	return hasRoomToAdd;
}  // end add

/*
*/   
 
template<class ItemType>
bool ArrayBag<ItemType>::remove(const ItemType& anEntry)
{
   int locatedIndex = getIndexOf(anEntry);
	bool canRemoveItem = !isEmpty() && (locatedIndex > -1);
	if (canRemoveItem)
	{
		itemCount--;
		items[locatedIndex] = items[itemCount];
	}  // end if
    
	return canRemoveItem;
}  // end remove


template<class ItemType>
void ArrayBag<ItemType>::clear()
{
	itemCount = 0;
}  // end clear

template<class ItemType>
int ArrayBag<ItemType>::getFrequencyOf(const ItemType& anEntry) const
{
   int frequency = 0;
   int curIndex = 0;       // Current array index
   while (curIndex < itemCount)
   {
      if (items[curIndex] == anEntry)
      {
         frequency++;
      }  // end if
      
      curIndex++;          // Increment to next entry
   }  // end while
   
   return frequency;
}  // end getFrequencyOf

template<class ItemType>
bool ArrayBag<ItemType>::contains(const ItemType& anEntry) const
{
	return getIndexOf(anEntry) > -1;
}  // end contains

template<class ItemType>
vector<ItemType> ArrayBag<ItemType>::toVector() const
{
	vector<ItemType> bagContents;
	for (int i = 0; i < itemCount; i++)
		bagContents.push_back(items[i]);
      
   return bagContents;
}  // end toVector

// private
template<class ItemType>
int ArrayBag<ItemType>::getIndexOf(const ItemType& target) const
{
	bool found = false;
   int result = -1;
   int searchIndex = 0;
   
   // If the bag is empty, itemCount is zero, so loop is skipped
   while (!found && (searchIndex < itemCount))
   {
      if (items[searchIndex] == target)
      {
         found = true;
         result = searchIndex;
      } 
      else
      {
         searchIndex++;
      }  // end if
   }  // end while
   
   return result;
}  // end getIndexOf

template<class ItemType>
BagInterface<ItemType>* ArrayBag<ItemType>::combine(BagInterface<ItemType>* aBag) const
{
	vector<ItemType> items1 = aBag->toVector();
	vector<ItemType> items2 = this->toVector();
	
	BagInterface<ItemType>* newBag = new ArrayBag<ItemType>();

	if(!aBag->isEmpty())
	{
		for(unsigned int i=0; i < items1.size();i++)
		{
			newBag->add(items1[i]);
		}
	}
	
	if(!this->isEmpty())
	{
		for(unsigned int i=0; i < items2.size();i++)
		{
			newBag->add(items2[i]);
		}
	}
	
	return newBag;
}

template<class ItemType>
BagInterface<ItemType>* ArrayBag<ItemType>::diff(BagInterface<ItemType>* aBag) const
{
	vector<ItemType> items1 = this->toVector();
	vector<ItemType> items2 = aBag->toVector();
	
	BagInterface<ItemType>* newBag = new ArrayBag<ItemType>();

	if(!aBag->isEmpty() && !this->isEmpty())
	{
		for(unsigned int i=0; i<items1.size();i++)
		{
			for(unsigned int j=0; j<items2.size();j++)
			{
				if(items1[i] == items2[j])
				{
					items1.erase(items1.begin()+i); 
					items2.erase(items2.begin()+j);
					i=0;
					j=-1;
				}
			}
		}
	}
	for(unsigned int i=0; i<items1.size();i++)
	{
		newBag->add(items1[i]);
	}
	return newBag;
}

template<class ItemType>
BagInterface<ItemType>* ArrayBag<ItemType>::intersection(BagInterface<ItemType>* aBag) const
{
	vector<ItemType> items1 = this->toVector();
	vector<ItemType> items2 = aBag->toVector();
	
	
	BagInterface<ItemType>* newBag = new ArrayBag<ItemType>();

	if(!aBag->isEmpty() && !this->isEmpty())
	{
		for(unsigned int i=0; i<items1.size();i++)
		{
			for(unsigned int j=0; j<items2.size();j++)
			{
				if(items1[i] == items2[j])
				{
					newBag->add(items1[i]);
					items1.erase(items1.begin()+i);
					items2.erase(items2.begin()+j);
					i=0;
					j=-1;
				}
			}
		}
	}
	return newBag;
}