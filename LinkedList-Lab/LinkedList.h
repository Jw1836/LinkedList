//YOU MAY NOT MODIFY THIS DOCUMENT
#pragma once
#include <string>
#include<istream>
#include<set>
#include<sstream>
#include <stdexcept>
#include "LinkedListInterface.h"


using namespace std;

template<typename T>
class LinkedList : public LinkedListInterface<T>{

private: // creates a private class of Node

    struct Node{
        Node(T _value){
            value = _value;
            next = NULL; 
        }
        
        T value;
        Node *next; 

    };

    Node *head; // the pointer that points to the first part of the linked List

public:
	int numElements = 0; 
	LinkedList() {
        cout << "called constructor for linked list" << endl; 
        head = NULL;
		
    }
    ~LinkedList() {
		clear();
	}

	/*
	insertHead

	A node with the given value should be inserted at the beginning of the list.

	Do not allow duplicate values in the list.
	*/
	void insertHead(T value){
		// do not allow duplicates
		Node* check = head;
		for(int i = 0; i < numElements; i++){
			if(check->value == value){
				return; // the element is already in the list so bad 
			}
			check = check->next; 
		}
		Node* ptr = head; 
		while(ptr != NULL){
			if(ptr->value == value){
				return; // this item is found in the list
			}
			ptr = ptr->next; 
		}
		numElements = numElements + 1;
        Node* temp = head;  // a temp pointer points to the same thing as head
        head = new Node(value); // allocates new memory with the new keyword, assigns value to head , so the front of the list
        head->next = temp; // next, our new node will point at what head was pointing to , what does -> mean? 
		
    }

	/*
	insertTail

	A node with the given value should be inserted at the end of the list.

	Do not allow duplicate values in the list.
	*/
	void insertTail(T value){
		// do not allow duplicates
		Node* check = head;
		for(int i = 0; i < numElements; i++){
			if(check->value == value){
				return; // the element is already in the list so bad 
			}
			check = check->next; 
		}

		Node* newNode = new Node(value);
		Node* last = head; 
		newNode->next = NULL; // because this is going to be the new end of the Linked List
		if(head == NULL){
			head = newNode;  // if there are no elements in the list
			numElements++; 
			return; 
		}

		while(last->next != NULL){
			last = last->next; 
		}
		last->next = newNode; 
		numElements++; 
	
    }

	/*
	insertAfter

	A node with the given value should be inserted immediately after the
	node whose value is equal to insertionNode.

	A node should only be added if the node whose value is equal to
	insertionNode is in the list. Do not allow duplicate values in the list.
	*/
	void insertAfter(T value, T insertionNode){
		// check to make insertion node is in the lists, and that value is not in the list 
		Node* check = head;
		bool found = false; 
		for(int i = 0; i < numElements; i++){
			if(check->value == insertionNode){
				found = true;
				//break;
			}
			if(check->value == value){
				return; // the value is already in the list, so we do not want to insert it in the list
			}
			check = check->next; 
		}
		if(found == false){
			return; // return if instertion node is not in the list
		}


		Node* find = head; 
		while(find->value != insertionNode){
			// if the find pointer is equal to the value, let us know
			find = find->next; // updates find until it hits a pointer pointing at the value
		}
		Node* newNode = new Node(value);
		newNode->next = find->next; 
		find->next = newNode;  
		numElements++; 
    }

	/*
	remove

	The node with the given value should be removed from the list.

	The list may or may not include a node with the given value.
	*/
	void remove(T value){
		//check to see if the value is in the list
		Node* check = head; 
		bool found = false;
		for(int i = 0; i < numElements; i++){
			if(check->value == value){
				found = true; 
				break; 
			}
			check = check->next; 
		}
		if(found == false){
			return; // this element is not found in the list
		}
		if(head->value == value){ // if the node we want to delete is at the beginning
			Node* temp = head; 
			head = head->next; 
			delete temp;
			temp = NULL;  
			numElements = numElements - 1; // updates size of linked list
		}
		else{
			Node* ptr = head; 
			while(ptr->next->value != value){ // find the element we want to move 
				ptr = ptr->next; 
			}
			Node* temp = ptr->next;
			ptr->next = ptr->next->next;  
			delete temp; 
			temp = NULL; 
			numElements = numElements-1; 
		}
		
    }

	/*
	clear

	Remove all nodes from the list.
	*/
	void clear(){
		Node* ptr = head;
		while(ptr != NULL){
			Node* temp = ptr; 
			ptr = ptr-> next; 
			delete temp;
			temp = NULL; 
		}
		numElements = 0; 
		head = NULL; 
		return; 
    }

	/*
	at

	Returns the value of the node at the given index. The list begins at
	index 0.

	If the given index is out of range of the list, throw an out of range exception.
	*/
	T at(int index){
		Node* ptr = head;  
		int startingpt = 0;
		if(index >= numElements || index < 0){
			throw out_of_range(""); 
		}
		else{
        	while(ptr != NULL){
				if(index == startingpt){
					break; 
			}
			ptr = ptr->next; 
			startingpt++; 
			}
		}
	return ptr->value; 
    }

	/*
	size

	Returns the number of nodes in the list.
	*/
	int size(){
        return numElements;
    }

	/*
	toString
	
	Returns a string representation of the list, with the value of each node listed in order (Starting from the head) and separated by a single space
	There should be no trailing space at the end of the string

	For example, a LinkedList containing the value 1, 2, 3, 4, and 5 should return
	"1 2 3 4 5"
	*/
	string toString(){
        stringstream ss; 
	
        Node *current = head; 
        while(current != NULL){ // at the end of the list current will eventually point to null
            if(current->next == NULL){
                ss << current->value; 
            }
            else{
            ss << current->value << " ";
            }
            current = current->next; // updates the pointer to point to the next one 
        }

        return ss.str();
    }

};
