#include <iostream>
#include "List.h"

using namespace std;

List::List(){
	size = 0;
}

bool List::add(ItemType newItem){
	//Create a new node
	Node *newNode = new Node;
	newNode->item = newItem;	//Store item to node
	newNode->next = NULL;		//Initialize to NULL

	//Check if list empty
	if (size == 0){
		//Set first pointer to point at new node
		firstNode = newNode;
	}
	else {
		//Move to last node
		Node *tempNode = firstNode;
		while (tempNode->next != NULL) {
			tempNode = tempNode->next;
		}
		//Set lastNode to point to newNode
		tempNode->next = newNode;

	}
	size++;	//Increse list size
	return true;
}

bool List::add(int index, ItemType newItem){
	//Check if index is valid
	if ((index >= 1) && (index <= size)){
		//Create a new node
		Node *newNode = new Node;
		newNode->item = newItem;	//Store item to node
		newNode->next = NULL;		//Initialize to NULL

		//If inserting in front
		if (index == 1){
			//Set new node to point to tmpNode
			newNode->next = firstNode;
			//Set FirstNode to point to newNode
			firstNode = newNode;
		}
		else {
			//Move to node just before index
			Node *tmpNode = firstNode;
			for (int i = 0; i < index - 2; i++){
				tmpNode = tmpNode->next;
			}
			//Set new node to point at indexed node
			newNode->next = tmpNode->next;
			tmpNode->next = newNode;
		}
		size++;
		return true;
	}
	else {
		return false;
	}
}

void List::remove(int index){
	//Check if index valid
	if ((index >= 1) && (index <= size)){
		//If node removed is first node
		if (index == 1){
			//Check if there is anymore
			if (size == 1){
				//Set firstNode to null
				firstNode = NULL;
			}
			else {
				//Set firstNode to 2nd node
				firstNode = firstNode->next;
			}
		}
		else {
			//Move to node
			Node *tmpNode = firstNode;
			for (int i = 0; i < index - 2; i++){
				tmpNode = tmpNode->next;
			}
			Node *removedNode = tmpNode->next;
			//Set node to point to node after removed node
			tmpNode->next = removedNode->next;
		}
		size--;
	}
}

ItemType List::get(int index){
	//Check if index valid
	if ((index >= 1) && (index <= size)){
		//Move to node
		Node *tmpNode = firstNode;
		for (int i = 0; i <= index - 2; i++){
			tmpNode = tmpNode->next;
		}
		return tmpNode->item;
	}
}

bool List::isEmpty(){
	if (size == 0){
		return true;
	}
	return false;
}

int List::getLength(){
	return size;
}

void List::print(){
	//Set tmp pointer to first Node
	Node *tmpPointer = firstNode;
	cout << "=====" << endl;
	while (tmpPointer != NULL){
		//Retrive and display item
		cout << tmpPointer->item << endl;
		//Point tmpPointer to next node
		tmpPointer = tmpPointer->next;
	}
	cout << "=====" << endl;
}