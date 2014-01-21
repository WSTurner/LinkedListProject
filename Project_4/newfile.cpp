///*
//* File:   main.cpp
//* Author: wingning
//*
//* Basic doubly linked list
//*/
//
//#include <cstdlib>
//#include <iostream>
//
//using namespace std;
//
///*
//*
//*/
//// data element type, for now it is int
//typedef int element_type;
//// basic node
//struct Node
//{
//   element_type elem;  // data part
//   Node * next;        // pointer to the next node
//   Node * prev;        // pointer to the previous node, not used for lab 6
//};
//// show the value of a singly linked list, one node per line
//void show(const Node * head, const Node * tail){
//   Node * current = head -> next;
//   if (current == tail)
//       cout << "It is an empty list!" << endl;
//   int i=1;
//   while (current != tail) {
//       cout << "node " << i << "\telem: " << '\t' << current -> elem << "\tnode address: " << current << "\tnext: " << current -> next << "\tprev: " << current -> prev << endl;
//       current = current->next;
//       i++;
//   };
//   cout << endl << endl;
//
//   cout << "head node " << "\telem: " << '\t' << head -> elem << "\tnode address: " << head << "\tnext: " << head -> next << "\tprev: " << head -> prev << endl;
//   cout << "tail node " << "\telem: " << '\t' << tail -> elem << "\tnode address: " << tail << "\tnext: " << tail -> next << "\tprev: " << tail -> prev << endl;
//}
//
//void reverse_show(Node* head, Node* tail){
//   Node * current = tail -> prev;
//   if (current == head)
//       cout << "In the Beginning... !" << endl;
//   int i=1;
//   while (current != head) {
//       cout << "node " << i << "\telem: " << '\t' << current -> elem << "\tnode address: " << current << "\tnext: " << current -> next << "\tprev: " << current -> prev << endl;
//       current = current->prev;
//       i++;
//   };
//   cout << endl << endl;
//
//   cout << "head node " << "\telem: " << '\t' << head -> elem << "\tnode address: " << head << "\tnext: " << head -> next << "\tprev: " << head -> prev << endl;
//   cout << "tail node " << "\telem: " << '\t' << tail -> elem << "\tnode address: " << tail << "\tnext: " << tail -> next << "\tprev: " << tail -> prev << endl;
//
//}
//
//int main(int argc, char** argv) {
//
//
//   const int size = 15;
//
//   Node * head;
//   head = new Node;
//   Node * current = head;
//   // the next two lines are added from lab 6 file
//   Node * previous = current;
//   Node * tail = new Node;
//
//   // makeing a doubly linked list of size many nodes
//   for (int i = 0; i < size; i++){
//       current -> next = new Node;
//       current = current -> next;
//       current -> elem = i;
//       // the next two lines are added from lab 6 file
//       current -> prev = previous;
//       previous = current;
//   }
//   // the line current -> next = NULL; is removed from lab 6
//   // and the next two lines are added from lab 6 file
//   current -> next = tail;
//   tail -> prev = current;
//
//   show(head, tail);
//   reverse_show(head, tail);
//
//   // actions for lab 7
//
//   // insert a node with elem value of 100 to the front of the list
//   previous = new Node;
//   current = head;
//   current = current -> next;
//   head -> next = previous;
//   previous -> next = current;
//   previous -> prev = head;
//   current -> prev = previous;
//   previous -> elem = 100;
//   show(head, tail);
//   reverse_show(head, tail);
//
//   // insert a node with elem value of -99 to the back of the list
//   previous = new Node;
//   current = tail;
//   current = current -> prev;
//   tail -> prev = previous;
//   previous -> prev = current;
//   previous -> next = tail;
//   current -> next = previous;
//   previous -> elem = -99;
//   show(head, tail);
//   reverse_show(head, tail);
//
//   // remove the first node from the front
//   current = head;
//   previous = current;
//   previous = previous -> next -> next;
//   delete current -> next;
//   current -> next = previous;
//   previous -> prev = current;
//   show(head, tail);
//   reverse_show(head, tail);
//
//   // remove the frist node from the back
//   current = tail;
//   previous = current;
//   previous = previous -> prev -> prev;
//   delete current -> prev;
//   current -> prev = previous;
//   previous -> next = current;
//   show(head, tail);
//   reverse_show(head, tail);
//
//   // make node pointer 'tmp' points to the third node from the back, use a loop so we may change third to any number
//   Node * tmp;
//   int var = 3;
//   tmp = tail;
//   for (int i = 0; i < var; i++)
//       tmp = tmp -> prev;
//   show(head, tail);
//   reverse_show(head, tail);
//   
//   // delete the node pointed by tmp
//   previous = tmp -> next;
//   current = tmp -> prev;
//   delete tmp;
//   current -> next = previous;
//   previous -> prev = current;
//   show(head, tail);
//   reverse_show(head, tail);
//   
//   // free all space
//   current = head -> next;
//   delete head;
//   while (current != tail) {
//       head = current;
//       current = current->next;
//       delete head;
//   }
//   delete tail;
//   return 0;
//}
