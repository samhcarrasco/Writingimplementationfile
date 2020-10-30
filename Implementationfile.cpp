/*

Author: Samuel Carrasco
Version: 10/9/2020
Project 5
*/

#include <iostream>
#include <stdlib.h> 
#include "CSCI361Proj5.h"


namespace FHSULINKEDLIST
{
	size_t list_length(const Node* head_ptr)
	{
		size_t count = 0;
		for (; head_ptr != NULL; head_ptr = head_ptr->link)
			count++;
		return count;
		/*
		size_t result = 0;
		while (head_ptr != NULL)
		{
			result++;
			head_ptr = head_ptr->link;
		}
		return result;
		*/

	}
	void list_head_insert(Node*& head_ptr, const Node::Item& entry)
	{
		// just adds a item to the front of the list or if no list head will now 
		Node* temp = new Node;
		temp->data = entry;
		temp->link = head_ptr;
		head_ptr = temp;
	}
	void list_insert(Node* previous_ptr, const Node::Item& entry)
	{
		Node* temp = new Node;
		temp->data = entry;
		temp->link = previous_ptr->link;
		previous_ptr->link = temp;
	}
	Node* list_search(Node* head_ptr, const Node::Item& target)
	{// find and return a node with given data
		for (; head_ptr != NULL; head_ptr = head_ptr->link)
			if (head_ptr->data == target)
				return head_ptr;
		return NULL;
	}
	Node* list_locate(Node* head_ptr, size_t position)
	{// find and return a node in a given position
		if (position <= 0) return NULL;
		size_t count = 1;
		while (head_ptr != NULL && count < position)
		{
			head_ptr = head_ptr->link;
			count++;
		}
		return head_ptr;
	}
	void list_head_remove(Node*& head_ptr)
	{//remove head node
		if (head_ptr == NULL)return;
		else
		{
			Node* temp = head_ptr;
			head_ptr = temp->link;
			delete temp;
			return;
		}
	}
	void list_remove(Node* previous_ptr)
	{//remove list
		Node* remove_ptr = previous_ptr->link;
		if (remove_ptr == NULL) return;
		previous_ptr->link = remove_ptr->link;
		delete remove_ptr;
		return;
	}
	void list_clear(Node*& head_ptr)
	{//clear list
		while (head_ptr != NULL)
			list_head_remove(head_ptr);
	}
	void list_copy(Node* source_ptr, Node*& head_ptr)
	{//copy list
		if (source_ptr == NULL)
		{
			head_ptr = NULL;
			return;
		}
		head_ptr = NULL;
		list_head_insert(head_ptr, source_ptr->data);
		Node* tail_ptr = head_ptr;
		source_ptr = source_ptr->link;
		while (source_ptr != NULL)
		{
			list_insert(tail_ptr, source_ptr->data);
			source_ptr = source_ptr->link;
			tail_ptr = tail_ptr->link;
		}
		return;
	}
	size_t list_occurrences(Node* head_ptr, const Node::Item& target)
	{// count number of occurrences of a given data
		size_t count = 0;
		for (; head_ptr != NULL; head_ptr = head_ptr->link)
			if (head_ptr->data == target)
				count++;
		return count;
	}

	void list_tail_attach(Node*& head_ptr, const Node::Item& entry)
	{
		//	if	it	is	an	empty	list
		if (head_ptr == NULL)
		{
			//	call	list_head_insert	function	to	insert	the	entry	to	the	list
			list_head_insert(head_ptr, entry);
			//	return
			return;
		}
		//	declare	local	variable	Node*	tail_ptr	=	head_ptr
		Node* tail_ptr = head_ptr;
		//	while	tail_ptr	is	not	pointing	to	the	tail	yet	
		//	(how	do	you	know	when	it	points	to the	tail	of	the	list?	When	its	link	is	null)
		while (tail_ptr->link != NULL)
		{
			//	let	tail_ptr	to	be	its	link
			tail_ptr = tail_ptr->link;
		}
		//	call	list_insert function	to	insert	the	entry	after	the	tail	node
		list_insert(tail_ptr, entry);
	}
	void list_tail_remove(Node*& head_ptr)
	{
		//	if	head_ptr	is	NULL	(i.e.nothing	to	remove	from	an	empty	list)
		//					return;
		if (head_ptr == NULL)
			return;
		//	if	head_ptr->link	is	NULL	(i.e.	there	is	only	one	node	in	the	list)
		if (head_ptr->link == NULL)
		{
			// call	list_head_remove	to	remove	the	head
			// return
			list_head_remove(head_ptr);
			return;
		}
		//	declare	Node*	tail_ptr	=	head_ptr-link;
		Node* tail_ptr = head_ptr->link;
		//	declare	Node*	previous_ptr	=	head_ptr;
		Node* previous_ptr = head_ptr;
		//	while(tail_ptr->link	!=	NULL)	(i.e.	as	long	as	tail_ptr not	point	to	tail	yet
		while (tail_ptr->link != NULL)
		{
			//	set	tail_ptr	to	its	link
			tail_ptr = tail_ptr->link;
			//	set	previous_ptr	to	its	link
			previous_ptr = previous_ptr->link;
		}
		//	(please	not	that	after	the	while	loop,	tail_ptr	points	to	the	tail
		//	and	the	previous_ptr	points	to	the	node	before	tail)
		//	call	list_remove	function	by	using	the	previous_ptr	as	the	argument
		//	(i.e.	remove	the	node	after	the	node	pointed	by	previous_ptr
		//	i.e.	remove	the	tail)
		list_remove(previous_ptr);
	}
	Node* list_copy_front(Node* source_ptr, size_t n)
	{
		//	declare	Node*	head_ptr	to	be	NULL
		Node* head_ptr = NULL;
		//	if	source_ptr	is	NULL	or	n	==	0,	return	NULL	since	nothing	to	copy
		if (source_ptr == NULL || n == 0) return  head_ptr;// ?
		//	call	list_head_insert	to	copy	the	first	node
		list_head_insert(head_ptr, source_ptr->data);
		//	declare	Node*	tail_ptr	points to	the	head
		Node* tail_ptr = head_ptr;
		//	declare	size_t	count	=	1	//	mean	one	node	has	been	copied

		size_t count = 1;
		//	as	long	as	there	is	more	source	to	copy	and	the	count	is	less	than	n

		while (source_ptr->link != NULL && count < n)
		{
			//	move	source_ptr	forward
			source_ptr = source_ptr->link;
			//	call	list_insert	to	insert	the	data	of	the	node	pointed	by	source_ptr
			list_insert(tail_ptr, source_ptr->data);
			//	notice	that	you	will	insert	the	data	after	the	node	pointed	by	tail_ptr
			//	move	tail_ptr	forward
			tail_ptr = tail_ptr->link;
			//	increase	count	by	1
			count++;
		}
		//	return	the	head_ptr
		return head_ptr;
	}

}