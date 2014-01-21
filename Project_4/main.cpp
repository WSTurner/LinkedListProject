/* 
 * File:   main.cpp
 * Author: wsturner
 *
 * Created on November 11, 2013, 1:10 PM
 */

#include <iostream>

using namespace std;

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef int element_type;
typedef element_type& reference;
typedef const element_type& const_reference;

/* linkedlist Class the struct for node is in the private because struct
 * defaults to public other than that it is quite a normal for the header */
class linkedlist
{
private:
    struct Node
    {
        element_type elem;  // data part
        Node * next;        // pointer to the next node
        Node * prev;        // pointer to the previous node
    };
    Node * head;
    Node * tail;
    Node * current;
    Node * target;
public:    
    linkedlist(); //default constructor for empty list
    ~linkedlist(); //destructor to free nodes dynamically created to support the linklist
    bool empty() const;
    void clear();
    reference back();
    const_reference back() const;
    reference front();
    const_reference front() const;
    //int size() const;
    linkedlist& operator=(const linkedlist& l);
    void populate(unsigned int n);
    void pop_back ();
    void pop_front ();
    void push_back (const element_type& x);
    void push_front (const element_type& x);
    void sort ();
    explicit linkedlist(unsigned int n);
    void check() const;
    void rcheck() const;
};
#endif

/* default constructor creates new head and tail Node sets them side by side */
linkedlist::linkedlist()
{
    head = new Node;
    tail = new Node;
    current = NULL;
    target = NULL;
    head -> next = tail;
    tail -> prev = head;
}

/* constructor to fill the list with integer values 0 to n-1 in order */
linkedlist::linkedlist(unsigned int n)
{
    head = new Node;
    tail = new Node;
    current = head;
    target = head;
    for (int i = 0; i < n; i++)
    {
        current -> next = new Node;
        current = current -> next;
        current -> elem = i;
        current -> prev = target;
        target = current;
    }
    current -> next = tail;
    tail -> prev = current;
}

/* deconstructor frees the nodes created in the linked lists */
linkedlist::~linkedlist()
{
   current = head -> next;
   delete head;
   while (current != tail) {
       head = current;
       current = current->next;
       delete head;
   }
   delete tail;       
}

/* boolean member function that checks to see if the linked list is empty by 
 * determining if head -> next is tail and vice versa */
bool linkedlist::empty() const
{
    if(head -> next == tail && tail -> prev == head)
        return true;
    else
        return false;
}

/* clear enpties the linked list and destroys all of the data within it except
 * for head and tail. it then sets head -> next to tail and tail -> prev to 
 * head */
void linkedlist::clear()
{
   current = head -> next;
   while (current != tail)
   {
       current = current->next;
       current -> prev -> elem = NULL;
       delete current -> prev;
   } 
   head -> next = tail;
   tail -> prev = head;
    
}

/* the next four functions simply check to see if the list is empty and if it is
 *  not they return either the first or last element within the list. */
reference linkedlist::back()
{
    if(tail -> prev != head)
        return tail -> prev -> elem;
}
const_reference linkedlist::back() const
{
    if(tail -> prev != head)
        return tail -> prev -> elem;
}
reference linkedlist::front()
{
    if(head -> next != tail)
        return head -> next -> elem;
}
const_reference linkedlist::front() const
{
    if(head -> next != tail)
        return head -> next -> elem;
}

/* the overloaded = operator takes in a const linked list (RHS) and mutates the
 * LHS list. The first step is calling the clear function on the LHS list and 
 * setting current equal to head. It then checks to make sure the RHS is not 
 * empty then assuming it isn't it creates a temporary node. This then is set to 
 * point to the RHS head -> next. it then uses a while loop to push the elements
 * of the RHS to the back of the LHS list. the temporary node then increments 
 * until the LHS is full and is then returned. */
linkedlist& linkedlist::operator=(const linkedlist& l)
{
    this -> clear();
    current = head;
    if(l.head -> next != l.tail)
    {
    Node * temporary = l.head -> next;
        while(temporary != l.tail)
        {
            this -> push_back(temporary ->elem);
            temporary = temporary -> next; 
        }
    }
    return *this;
}  

/* this function I created to fill my lists with semi random values. */
void linkedlist::populate(unsigned int n)
{
    this -> clear();    
    srand(0);
    head = new Node;
    tail = new Node;
    current = head;
    for (int i = 0; i < n; i++)
    {
        current -> next = new Node;
        current = current -> next;
        current -> elem = rand()%99;
        current -> prev = target;
        target = current;
    }
    current -> next = tail;
    tail -> prev = current;
        
}

/* this member function places current at tail and target 2 before tail. it then
 * deletes the node before tail and reassembles the list. */
void linkedlist::pop_back ()
{
    current = tail;
    target = current;
    target = target -> prev -> prev;
    delete current -> prev;
    current -> prev = target;
    target -> next = current;
}

/* Essentially the same as pop_back this member function sets currnet to head 
 * and target 2 nodes past head. it then deletes the first node(the one after 
 * head) and reassembles the list. */
void linkedlist::pop_front ()
{
    current = head;
    target = current;
    target = target -> next -> next;
    delete current -> next;
    current -> next = target;
    target -> prev = current;
}

/* This member function creates a new node and then sets current to the node 
 * before tail and target to the new node. It then attaches target prev to  
 * current and target next to tail. finally it sets current next to tail and 
 * then sets the element of the new node. this essentially inserts it to the 
 * list at the end. */
void linkedlist::push_back (const element_type& x)
{
    target = new Node;
    current = tail;
    current = current -> prev;
    tail -> prev = target;
    target -> prev = current;
    target -> next = tail;
    current -> next = target;
    target -> elem = x;
}

/* This member function creates a new node and then sets current to the node 
 * after head and target to the new node. It then attaches head next to the 
 * new node (target) and the target next to current. next it attaches target 
 * prev to head and current prev to target, followed by placing the element for
 * the new nod. */
void linkedlist::push_front (const element_type& x)
{
    target = new Node;
    current = head;
    current = current -> next;
    head -> next = target;
    target -> next = current;
    target -> prev = head;
    current -> prev = target;
    target -> elem = x;
}

/* The sort function was probably the hardest part of this project the way I 
 * accomplished this task was using a bubble sort. the first step was to make 
 * sure the list is not empty. after this I used a nested while loops housing an
 * if statement to the loops both go until current -> next is target meaning the
 * entire list has been sorted. the if statement places the higher element of 
 * of the two being compared closer to tail until it reaches the end. in a sense 
 * what this sort is doing is moving the largest number to the node before tail
 * which is where target is. after that target moves one closer to head and 
 * current starts over moving the next highest element to target or the node 
 * before the previously found highest number. this happens until all of the
 * numbers have been sorted. */
void linkedlist::sort ()
{
    if(head -> next == tail)
        cout << "This is an empty list!" << endl;
    else
    {
        current = head;
        target = tail;
        int temp = 0;
        while (current -> next != target)
        {
            while(current -> next != target)
            {
                if (current -> elem > current -> next -> elem)
                {
                    temp = current -> elem;
                    current -> elem = current -> next -> elem;
                    current -> next -> elem = temp;
                }   
                current = current -> next;
            }
            target = target -> prev;
            current = head;
        }
    }
}

/* These are almost exactly the check functions given in lab however i slightly 
 * changed the formatting. All these do is create a temporary pointer to the 
 * passed list. it then iterates through outputting all of the information 
 * for each individual node. */
void linkedlist::check() const
{
    Node * current = head -> next;
   if (current == tail)
       cout << "The list is empty!" << endl;
   int i=1;
   while (current != tail)
   {
       cout << "node: " << i << " elem: " << '\t' << current -> elem << "\tnode address: " << current << "\tnext: " << current -> next << "\tprev: " << current -> prev << endl;
       current = current->next;
       i++;
   };
   cout << endl << endl;

   cout << "head: " << "\telem: " << '\t' << head -> elem << "\tnode address: " << head << "\tnext : " << head -> next << "\tprev: " << head -> prev << endl;
   cout << "tail: " << "\telem: " << '\t' << tail -> elem << "\tnode address: " << tail << "\tnext: " << tail -> next << "\tprev: " << tail -> prev << endl << endl;

}
void linkedlist::rcheck() const
{
    Node * current = tail -> prev;
    if (current == head)
        cout << "In the Beginning... !" << endl;
    int i=1;
    while (current != head)
    {
        cout << "node: " << i << " elem: " << '\t' << current -> elem << "\tnode address: " << current << "\tnext: " << current -> next << "\tprev: " << current -> prev << endl;
        current = current->prev;
        i++;
    };
    cout << endl << endl;

    cout << "head: " << "\telem: " << '\t' << head -> elem << "\tnode address: " << head << "\tnext: " << head -> next << "\tprev: " << head -> prev << endl;
    cout << "tail: " << "\telem: " << '\t' << tail -> elem << "\tnode address: " << tail << "\tnext: " << tail -> next << "\tprev: " << tail -> prev << endl << endl;

}

/* This is the testing of all the functions. The main ones are denoted with 
 * cout text while some of the more behind the scenes ones are simply used to
 * implement the other functions */
int main()
{
    cout << "------------Testing empty------------" << endl << endl;
    linkedlist list1;
    linkedlist list2;
    list2.populate(23);
    cout << "*****list1*****" << endl;
    list1.check();
    cout << "*****list2*****" << endl;
    list2.check();
    
    cout << "*****list1*****" << endl;
    if(list1.empty())
        cout << "The list is empty!" << endl << endl;
    else
        cout << "The list is not empty!" << endl << endl;
    
    cout << "*****list2*****" << endl;
    if(list2.empty())
        cout << "The list is empty!" << endl << endl;
    else
        cout << "The list is not empty!" << endl << endl;
        
    
    cout << "------------Testing back------------" << endl << endl;
    linkedlist list3(7);
    list3.check();
    cout << "The final element is: " << list3.back() << endl << endl;
    
    
    cout << "------------Testing const back------------" << endl << endl;
    linkedlist list4(9);
    list4.check();
    cout << "The final element is: " << list4.back() << endl << endl;
    
    
    cout << "------------Testing front------------" << endl << endl;
    linkedlist list5(21);
    list5.check();
    cout << "The final element is: " << list5.front() << endl << endl;
    
    
    cout << "------------Testing const front------------" << endl << endl;
    linkedlist list6(29);
    list6.check();
    cout << "The final element is: " << list6.front() << endl << endl;
    
    
    cout << "------------Testing = operator------------" << endl << endl;
    linkedlist list7;
    list7.populate(17);
    cout << "*****list1*****" << endl;
    list1.check();
    cout << "*****list7*****" << endl;
    list7.check();
    list1 = list7;
    cout << "*****list1 after operation*****" << endl;
    list1.check();
    cout << "*****list7 after operation*****" << endl;
    list7.check();
    
    
    cout << "------------Testing pop_back------------" << endl << endl;
    cout << "*****list1*****" << endl;
    list1.check();
    list1.pop_back();
    cout << "*****list1 after operation*****" << endl;
    list1.check();
    
    
    cout << "------------Testing pop_front------------" << endl << endl;
    cout << "*****list1*****" << endl;
    list1.check();
    list1.pop_front();
    cout << "*****list1 after operation*****" << endl;
    list1.check();
    
    cout << "------------Testing push_back------------" << endl << endl;
    cout << "*****list7*****" << endl;
    list7.check();
    list7.push_back(1234);
    cout << "*****list7 after operation*****" << endl;
    list7.check();
    
    cout << "------------Testing push_front------------" << endl << endl;
    cout << "*****list7*****" << endl;
    list7.check();
    list7.push_front(5678);
    cout << "*****list7 after operation*****" << endl;
    list7.check();
    
    cout << "------------Testing sort (output forward and reverse)------------" << endl << endl;
    cout << "*****list7*****" << endl;
    list7.check();
    list7.sort();
    cout << "*****list7 after sorting*****" << endl;
    list7.check();
    cout << "*****list7 after sorting (reversed)*****" << endl;
    list7.rcheck();
    

    cout << "------------Testing clear------------" << endl << endl;
    cout << "*****before clear*****" << endl;
    list2.check();
    list2.clear();
    cout << "*****after clear*****" << endl;
    list2.check();
}
/* I understood most everything we did in this lab. After multiple labs using linked lists I have gained a fairly good understanding of how they work. Probably the hardest part of this lab was converting my knowledge of bubble sort to work for a linked list. The test cases are simply calls to each of the functions I was required to implement for this homework. One of the things I found interesting about the lab was the implementation of the overloaded = operator because the const makes it more difficult to maneuver. I accomplished this by creating a temporary pointer to the const list and iterated through it in this way. */