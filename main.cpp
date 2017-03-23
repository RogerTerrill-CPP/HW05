/* BagInterface ADT - Abstract Base Class */


/** Listing 4-4. */
#include "BagInterface.h"
#include "ArrayBag.h"
#include "LinkedBag.h"
#include <iostream>
#include <string>
#include <cctype>

using namespace std;


void displayBag(BagInterface<string>* bagPtr)
{
   cout << "The bag contains " << bagPtr->getCurrentSize()
   << " items:" << endl;
	vector<string> bagItems = bagPtr->toVector();
   
   int numberOfEntries = (int)bagItems.size();
   for (int i = 0; i < numberOfEntries; i++)
   {
      cout << bagItems[i] << " ";
   }  // end for
   cout << endl;
}  // end displayBag

void bagTester(BagInterface<string>* bagPtr1, BagInterface<string>* bagPtr2)
{
   
   string items1[] = {"a", "b", "c"};
   string items2[] = {"b", "b", "d", "e"};
   
   /*string items1[] = {"one", "six", "three", "four", "five", "one", "three"};
   string items2[] = {"one", "two", "three", "four", "five", "three"};*/
   for (int i = 0; i < 3; i++)
   {
      bagPtr1->add(items1[i]);
   }  // end for
   
   for (int i = 0; i < 4; i++)
   {
      bagPtr2->add(items2[i]);
   }  // end forA

   displayBag(bagPtr1);
   cout << boolalpha << "contains 'one' for bag1 returns : " 
	<< bagPtr1->contains("one")
           << " frequency: " << bagPtr1-> getFrequencyOf("one")
           <<endl<<endl;

   displayBag(bagPtr2);
   cout << boolalpha << "contains 'one' for bag1 returns : " 
	<< bagPtr2->contains("one")
           << " frequency: " << bagPtr2-> getFrequencyOf("one")
           <<endl<<endl;
}  // end bagTester

int main()
{
   BagInterface<string>* bagPtr1 = nullptr;
   BagInterface<string>* bagPtr2 = nullptr;
   BagInterface<string>* bagPtr3 = nullptr;
   char userChoice;
   cout << "Enter 'A' to test the array-based implementation\n"
   << " or 'L' to test the link-based implementation: ";
   cin >> userChoice;
   if (toupper(userChoice) == 'A')
   {
      bagPtr1 = new ArrayBag<string>();
      bagPtr2 = new ArrayBag<string>();
      bagPtr3 = new ArrayBag<string>();
      cout << "Testing the Array-Based Bag:" << endl;
   }
   else
   {
      bagPtr1 = new LinkedBag<string>();
      bagPtr2 = new LinkedBag<string>();
      bagPtr3 = new LinkedBag<string>();
      cout << "Testing the Link-Based Bag:" << endl;
   }  // end if
   // test both bags have items
   cout << "Running Bag Tester" << endl;
   bagTester(bagPtr1, bagPtr2);



	//test Bag version 2.0 new methods
	bagPtr3 = bagPtr1->combine(bagPtr2);
	cout << endl << "#########DISPLAYING combine...." << endl;//Added
	displayBag(bagPtr3);

	bagPtr3 = bagPtr1->diff(bagPtr2);
	cout << endl << "#########DISPLAYING diff...." << endl;//Added
 	displayBag(bagPtr3);

	bagPtr3 = bagPtr1 -> intersection(bagPtr2);
	cout << endl << "#########DISPLAYING intersection...." << endl;//Added
 	displayBag(bagPtr3);



   delete bagPtr1;
   bagPtr1 = nullptr;
   delete bagPtr2;
   bagPtr2 = nullptr;
   delete bagPtr3;
   bagPtr3 = nullptr;
   cout << "All done!" << endl;
   
   return 0;
}  // end main


