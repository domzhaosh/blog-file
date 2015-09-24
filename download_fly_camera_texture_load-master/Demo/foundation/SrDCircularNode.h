/************************************************************************		
\link	www.twinklingstar.cn
\author Twinkling Star
\date	2013/11/22
****************************************************************************/
#ifndef SR_FOUNDATION_SRDEQUE_H_
#define SR_FOUNDATION_SRDEQUE_H_
#include <stdio.h>

/** \addtogroup foundation
  @{
*/

/**
 \brief The Node of Double Circular List.
 
 This class provides with a basic template of the node of double circular list.
 It's recommended that allocating memory by using "new" or "malloc" and deallocating 
 memory by using "delete" or "free" is not appreciated.Instead, please use the method of 
 createObject() to create an object and destroy() to free. Copy constructor easily gives rise
 to exception,especially when pointers are used as the member viriables. If you want to apply
 this class to other purposes, just override the method  createObject() and destroy() 
 according to the actual conditions.
*/
class SrDCircularNode
{
public:
	/**
	\brief return the next node of this one.
	*/
	SrDCircularNode* getNextNode()
	{
		return nextNode;
	}
	/**
	\brief return the last node of this one.
	*/
	SrDCircularNode* getLastNode()
	{
		return lastNode;
	}
	/**
	\brief If you want to initialize a double circular list, the first node should be set.
	\param[in] node It must be first node of your double circular list.
	*/
	static void initialize(SrDCircularNode* node)
	{
		node->nextNode = node;
		node->lastNode = node;
	}
	/**
	\brief Erase the node from the list.
	\param[in] node The node erased from the list,but the memory isn't deallocated.
	\return false The node is the last one in the list.
	*/
	static bool erase(SrDCircularNode* node)
	{
		if( node->nextNode==node )
			return false;
		SrDCircularNode* last = node->lastNode;
		last->nextNode = node->nextNode;
		SrDCircularNode* next = node->nextNode;
		next->lastNode = node->lastNode;
		return true;
	}
	/**
	\brief Create a SrDCircularNode node.
	*/
	static SrDCircularNode* createObject(){ return new SrDCircularNode();}
	/**
	\brief Insert a node after this one.
	\param[in] node It's the inserted node.
	*/
	bool insertBefore(SrDCircularNode* node)
	{
		if( lastNode==nextNode && lastNode==NULL )
			return false;
		node->lastNode = lastNode;
		node->nextNode = this;
		lastNode->nextNode = node;
		lastNode = node;
		return true;
	}
	/**
	\brief Insert a node before this one.
	\param[in] node It's the inserted node.
	*/
	bool insertAfter(SrDCircularNode* node)
	{
		if( lastNode==nextNode && lastNode==NULL )
			return false;
		node->lastNode = this;
		node->nextNode = nextNode;
		nextNode->lastNode = node;
		nextNode = node;

		return true;
	}
	/**
	\brief Destroy the memory of this node.
	*/
	virtual void destroy(){ delete this;}

protected:
	SrDCircularNode* lastNode,*nextNode;
	SrDCircularNode(SrDCircularNode&);
	SrDCircularNode()
	{
		nextNode = this;
		lastNode = this;
	}
};

/** @} */
#endif
