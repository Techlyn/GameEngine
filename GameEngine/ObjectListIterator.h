//
// ObjectListIterator.h
//

#ifndef __OBJECT_LIST_ITERATOR_H__
#define __OBJECT_LIST_ITERATOR_H__

#include <string>

namespace df {

	class ObjectList;
	class Object;

	class ObjectListIterator {

	private:
		std::string CLASS_NAME = "ObjectListIterator";

		ObjectListIterator();      // Must be given list when created.
		int m_index;			   // Index into list.
		const ObjectList* m_p_list; // List iterating over.

	public:
		// Create iterator, over indicated list.
		ObjectListIterator(const ObjectList* p_l);

		void first();			// Set iterator to first item in list
		void next();			// Set iterator to next item in list.
		bool isDone() const;    // Return true if at end of list.

		Object* currentObject() const;
	};
}

#endif // __OBJECT_LIST_ITERATOR_H__