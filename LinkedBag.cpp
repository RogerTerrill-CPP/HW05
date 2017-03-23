#pragma once
/** ADT bag: Link-based implementation.
    @file LinkedBag.cpp */

#include "LinkedBag.h"
#include "Node.h"
#include <iostream>
using namespace std;
#include <cstddef>

template<class ItemType>
LinkedBag<ItemType>::LinkedBag() : headPtr(nullptr), itemCount(0)
{
}  // end default constructor

template<class ItemType>
LinkedBag<ItemType>::LinkedBag(const LinkedBag<ItemType>& aBag)
{
	itemCount = aBag.itemCount;
   Node<ItemType>* origChainPtr = aBag.headPtr;  // Points to nodes in original chain
   
   if (origChainPtr == nullptr)
      headPtr = nullptr;  // Original bag is empty
   else
   {
      // Copy first node
      headPtr = new Node<ItemType>();
      headPtr->setItem(origChainPtr->getItem());
      
      // Copy remaining nodes
      Node<ItemType>* newChainPtr = headPtr;      // Points to last node in new chain
      origChainPtr = origChainPtr->getNext();     // Advance original-chain pointer
      
      while (origChainPtr != nullptr)
      {
         // Get next item from original chain
         ItemType nextItem = origChainPtr->getItem();
              
         // Create a new node containing the next item
         Node<ItemType>* newNodePtr = new Node<ItemType>(nextItem);
         
         // Link new node to end of new chain
         newChainPtr->setNext(newNodePtr);
         
         // Advance pointer to new last node
         newChainPtr = newChainPtr->getNext();

         // Advance original-chain pointer
         origChainPtr = origChainPtr->getNext();
      }  // end while
      
      newChainPtr->setNext(nullptr);              // Flag end of chain
   }  // end if
}  // end copy constructor

template<class ItemType>
LinkedBag<ItemType>::~LinkedBag()
{
   clear();
}  // end destructor

template<class ItemType>
bool LinkedBag<ItemType>::isEmpty() const
{
	return itemCount == 0;
}  // end isEmpty

template<class ItemType>
int LinkedBag<ItemType>::getCurrentSize() const
{
	return itemCount;
}  // end getCurrentSize

template<class ItemType>
bool LinkedBag<ItemType>::add(const ItemType& newEntry)
{
   // Add to beginning of chain: new node references rest of chain;
   // (headPtr is null if chain is empty)        
   Node<ItemType>* nextNodePtr = new Node<ItemType>();
   nextNodePtr->setItem(newEntry);
   nextNodePtr->setNext(headPtr);  // New node points to chain
//   Node<ItemType>* nextNodePtr = new Node<ItemType>(newEntry, headPtr); // alternate code

   headPtr = nextNodePtr;          // New node is now first node
   itemCount++;
   
   return true;
}  // end add

template<class ItemType>
vector<ItemType> LinkedBag<ItemType>::toVector() const
{
   vector<ItemType> bagContents;
   Node<ItemType>* curPtr = headPtr;
   int counter = 0;
	while ((curPtr != nullptr) && (counter < itemCount))
   {
		bagContents.push_back(curPtr->getItem());
      curPtr = curPtr->getNext();
      counter++;
   }  // end while
   
   return bagContents;
}  // end toVector

template<class ItemType>
bool LinkedBag<ItemType>::remove(const ItemType& anEntry)
{
   Node<ItemType>* entryNodePtr = getPointerTo(anEntry);
   bool canRemoveItem = !isEmpty() && (entryNodePtr != nullptr);
   if (canRemoveItem)
   {
      // Copy data from first node to located node
      entryNodePtr->setItem(headPtr->getItem());
      
      // Delete first node
      Node<ItemType>* nodeToDeletePtr = headPtr;
      headPtr = headPtr->getNext();
      
      // Return node to the system
      nodeToDeletePtr->setNext(nullptr);
      delete nodeToDeletePtr;
      nodeToDeletePtr = nullptr;
      
      itemCount--;
   } // end if
   
	return canRemoveItem;
}  // end remove

template<class ItemType>
void LinkedBag<ItemType>::clear()
{
   Node<ItemType>* nodeToDeletePtr = headPtr;
   while (headPtr != nullptr)
   {
      headPtr = headPtr->getNext();

      // Return node to the system
      nodeToDeletePtr->setNext(nullptr);
      delete nodeToDeletePtr;
      
      nodeToDeletePtr = headPtr;
   }  // end while
   // headPtr is nullptr; nodeToDeletePtr is nullptr
   
	itemCount = 0;
}  // end clear

template<class ItemType>
int LinkedBag<ItemType>::getFrequencyOf(const ItemType& anEntry) const
{
	int frequency = 0;
   int counter = 0;
   Node<ItemType>* curPtr = headPtr;
   while ((curPtr != nullptr) && (counter < itemCount))
   {
      if (anEntry == curPtr->getItem())
      {
         frequency++;
      } // end if
      
      counter++;
      curPtr = curPtr->getNext();
   } // end while
   
	return frequency;
}  // end getFrequencyOf

template<class ItemType>
bool LinkedBag<ItemType>::contains(const ItemType& anEntry) const
{
	return (getPointerTo(anEntry) != nullptr);
}  // end contains

/* ALTERNATE 1
template<class ItemType>
bool LinkedBag<ItemType>::contains(const ItemType& anEntry) const
{
   return getFrequencyOf(anEntry) > 0;
} 
*/
/* ALTERNATE 2 
template<class ItemType>
bool LinkedBag<ItemType>::contains(const ItemType& anEntry) const
{
   bool found = false;
   Node<ItemType>* curPtr = headPtr;
   int i = 0;
   while (!found && (curPtr != nullptr) && (i < itemCount))
   {
      if (anEntry == curPtr-<getItem())
      {
         found = true;
      }
      else
      {
         i++;
         curPtr = curPtr->getNext();
      }  // end if
   }  // end while

   return found;
}  // end contains
*/

// private
// Returns either a pointer to the node containing a given entry 
// or the null pointer if the entry is not in the bag.
template<class ItemType>
Node<ItemType>* LinkedBag<ItemType>::getPointerTo(const ItemType& anEntry) const
{
   bool found = false;
   Node<ItemType>* curPtr = headPtr;
   
   while (!found && (curPtr != nullptr))
   {
      if (anEntry == curPtr->getItem())
         found = true;
      else
         curPtr = curPtr->getNext();
   } // end while
   
   return curPtr;
} // end getPointerTo

template<class ItemType>
BagInterface<ItemType>* LinkedBag<ItemType>::combine(BagInterface<ItemType>* aBag) const
{
	vector<ItemType> items1 = aBag->toVector();
	vector<ItemType> items2 = this->toVector();
	
	BagInterface<ItemType>* newBag = new LinkedBag<ItemType>();

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
BagInterface<ItemType>* LinkedBag<ItemType>::diff(BagInterface<ItemType>* aBag) const
{
	vector<ItemType> items1 = this->toVector();
	vector<ItemType> items2 = aBag->toVector();
	
	BagInterface<ItemType>* newBag = new LinkedBag<ItemType>();

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
BagInterface<ItemType>* LinkedBag<ItemType>::intersection(BagInterface<ItemType>* aBag) const
{
	vector<ItemType> items1 = this->toVector();
	vector<ItemType> items2 = aBag->toVector();
	
	
	BagInterface<ItemType>* newBag = new LinkedBag<ItemType>();

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