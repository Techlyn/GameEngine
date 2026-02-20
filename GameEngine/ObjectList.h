//
//	ObjectList.h
// 

#ifndef __OBJECT_LIST_H__
#define __OBJECT_LIST_H__

// System includes
#include <string>

// Engine Includes
#include "ObjectListIterator.h"

const int MAX_OBJECTS = 1000;

namespace df {

	class Object;

	class ObjectList {

	friend class ObjectListIterator;

	private:
		std::string CLASS_NAME = "ObjectList";

		int m_count;				  // Count of objects in list.
		Object* m_p_obj[MAX_OBJECTS]; // Array of pointers to objects.

	public:
		//Default constructor
		ObjectList();


		//Default destructor
		//~ObjectList();

		// Insert object pointer in list.
		// Return 0 if ok, else -1.
		int insert(Object* p_o);

		// Remove object pointer from list and shifts
		// all object pointers down the array and replaces
		// last pointer with nullptr.
		// Return 0 if found, else -1.
		int remove(Object* p_o);

		// Clear list (setting count to 0).
		void clear();

		// Return count of number of objects in list.
		int getCount() const;

		// returns true if array is empty
		bool isEmpty() const;

		// returns true if array is full
		bool isFull() const;

		// checks to make sure index is valid when entered
		// and not out of bounds
		Object* operator[](int index);

		// adds lists together, returns list containing both lists
		ObjectList operator+(ObjectList list);

		//lists object pointers in the array, call for debugging
		void listList() const;

	};

}
#endif // end of __OBJECT_LIST_H__
