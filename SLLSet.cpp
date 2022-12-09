/*
 * SLLSet.cpp
 *
 *  Created on: Nov. 17, 2021
 *      Author: moham
 */

#include "SLLSet.h"
#include <iostream>

SLLSet::SLLSet()
{
	size = 0;
	head = NULL;
}

SLLSet::SLLSet(int sortedArray[], int arrSize)
{
	size = arrSize;
	head = NULL;
	for(int i=size-1; i>=0; i--){
	SLLNode*node = new SLLNode(); //creates a new node
	 node->value = sortedArray[i];
	 node->next = head;
	 head = node;

	}


}

int SLLSet::getSize()
{

	return size;
}

SLLSet SLLSet::copy()
{
    // Create a new empty set
    SLLSet nodecopy;
    // If the current set is empty, return the empty set
    if (head == NULL) {
        return nodecopy;
    }
    // Copy the linked list of the current set into the new set, node by node
    SLLNode* cur = head;
    nodecopy.head = new SLLNode(cur->value, NULL);
    SLLNode* newCur = nodecopy.head;
    while (cur->next != NULL) {
        cur = cur->next;
        newCur->next = new SLLNode(cur->value, NULL);
        newCur = newCur->next;
    }
    nodecopy.size = size;

    return nodecopy;
}

bool SLLSet::isIn(int v)
{
    SLLNode*node = head;

    for(int j=0; j<size; j++){
    	if(node->value == v){
    		return true;
    	}
    	node = node->next;
    }
	return false;
}

void SLLSet::add(int v)
{
    // If v is already an element of the set, do nothing
    SLLNode* cur = head;
    while (cur != NULL) {
        if (v == cur->value) {
            return;
        } else if (v < cur->value) {
            break;
        }
        cur = cur->next;
    }
    // Insert v into the set
    SLLNode* newNode = new SLLNode(v, cur);
    if (cur == head) {
        head = newNode;
    } else {
        SLLNode* prev = head;
        while (prev->next != cur) {
            prev = prev->next;
        }
        prev->next = newNode;
    }
    size++;
}

void SLLSet::remove(int v)
{
    // If the set is empty, do nothing
    if (head == NULL) {
        return;
    }
    // If v is the first element of the list, remove it from the list
    if (head->value == v) {
        SLLNode* temp = head;
        head = head->next;
        delete temp;
        size--;
        return;
    }
    // Find the node that contains v in the list and remove it from the list
    SLLNode* prev = head;
    SLLNode* cur = head->next;
    while (cur != NULL) {
        if (v == cur->value) {
            prev->next = cur->next;
            delete cur;
            size--;
            return;
        }
        prev = cur;
        cur = cur->next;
    }
}

SLLSet SLLSet::setUnion(SLLSet s)
{
	SLLNode*thisList = head;
	SLLNode*List_s = s.head;
	SLLSet*Unionset = new SLLSet();

	while (thisList != NULL){
		Unionset->add(thisList->value);
		thisList = thisList->next;
	}
	while(List_s != NULL){
		Unionset->add(List_s->value);
		List_s = List_s->next;
	}
	 return *Unionset;
}

SLLSet SLLSet::intersection(SLLSet s)
{
    SLLNode*theList = head;
    SLLSet*intSet = new SLLSet();

    while(theList != NULL){
    	if(isIn(theList->value) && s.isIn(theList->value)){
    		intSet->add(theList->value);
    	}
    	theList = theList->next;
    }
	 return *intSet;
}

SLLSet SLLSet::difference(SLLSet s)
{
    SLLSet*sDiff = new SLLSet();
	 if(s.head == NULL){
		 *sDiff = copy();
		 return *sDiff;
	 }
	 SLLNode*temp = head;
	 while (temp != NULL){
		 if(s.isIn(temp->value)==true){
			 remove(temp->value);
		 }
		 temp = temp->next;
	 }
	 if(head == NULL){
		 return *sDiff;
	 }
	 *sDiff = copy();
	 return *sDiff;

}
SLLSet SLLSet::setUnion(SLLSet sArray[], int size)
{
    // Create a new empty set to store the union
    SLLSet unionSet;
    // Iterate over the array of sets and call the setUnion() method for each set, starting with the first set in the array
    for (int i = 0; i < size; i++) {
        unionSet = unionSet.setUnion(sArray[i]);
    }
    return unionSet;
}

string SLLSet::toString()
{
   string str;
   SLLNode*transverse = head;
   for (int i = 0; i<size; i++){
	   str += std:: to_string(transverse->value);
	   str += (i == size-1 ? "" : ", ");
	   transverse = transverse->next;

   }
   return str;
}

