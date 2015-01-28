#ifndef _SSLL_H_
#define _SSLL_H_

// SSLL.H
//
// Singly-linked list (non-polymorphic)
//
// by Sangeetha Matchanickal
// for COP 3530

#include <iostream>
#include <iterator>
#include <stdexcept>
#include <stdlib.h>

namespace cop3530 {

  template <typename T>
  class SSLL
  {
      private:
        struct Node
         {
             T value;
             struct Node* next; // pointer to the next node

        };// end struct Node

        Node* head; // a pointer that points to the first node in the list
        size_t capacity; // variable to count the number of nodes in the list

      public:

    class SSLL_Iter//: public std::iterator<std::forward_iterator_tag, T>
     {
         public:
           // inheriting from std::iterator<std::forward_iterator_tag, T>
           // automagically sets up these typedefs...
           typedef T value_type;
           typedef std::ptrdiff_t difference_type;
           typedef T& reference;
           typedef T* pointer;
           typedef std::forward_iterator_tag iterator_category;

           // but not these typedefs...
           typedef SSLL_Iter self_type;
           typedef SSLL_Iter& self_reference;

         private:
           Node* here;

         public:
           explicit SSLL_Iter( Node* start = NULL ) : here( start ) {} // set here as the value of the constructor
           SSLL_Iter( const SSLL_Iter& src ) : here( src.here ) {} // copy constructor

           reference operator*() const
           {
                return here->value;
           }

           pointer operator->() const // only used if we have a object type
           {
                return &(here->value); // return *this

           }
           self_reference operator=( const SSLL_Iter& src )
            {
                /*if (src == *this)
					return *this;
				else
					here = src.here;
				return *this;*/

               here = src.here;
               return *this;

            }
           self_reference operator++() //returns reference
            {
                here = here->next;
                return *this;
            } // preincrement
           self_type operator++(int) // returns by value
            {
                SSLL_Iter results = *this;
                here = here->next;
                return results;
            } // postincrement

           bool operator==(const SSLL_Iter& rhs) const
            {
                return (here == rhs.here);
            }
           bool operator!=(const SSLL_Iter& rhs) const
           {
               return (here != rhs.here);
           }
     }; // end SSLL_Iter


     class SSLL_Const_Iter//: public std::iterator<std::forward_iterator_tag, T>
     {
         public:
           // inheriting from std::iterator<std::forward_iterator_tag, T>
           // automagically sets up these typedefs...
           typedef T value_type;
           typedef std::ptrdiff_t difference_type;
           typedef const T& reference;
           typedef const T* pointer;
           typedef std::forward_iterator_tag iterator_category;

           // but not these typedefs...
           typedef SSLL_Const_Iter self_type;
           typedef SSLL_Const_Iter& self_reference;

         private:
           const Node* here;

         public:
           explicit SSLL_Const_Iter( Node* start = NULL ) : here( start ) {}
           SSLL_Const_Iter( const SSLL_Const_Iter& src ) : here( src.here ) {}

           reference operator*() const
            {
                return here->value;
            }
           pointer operator->() const
            {
                return &(here->value);
            }

           self_reference operator=( const SSLL_Const_Iter& src )
           {
                /*if (src == *this)
					return *this;
				else
					here = src.here;
				return *this;*/
                here = src.here;
                return *this;
           }
           self_reference operator++() // returns reference
            {
                here = here->next;
                return *this;
            } // preincrement
           self_type operator++(int) // returns by value
           {
                SSLL_Const_Iter results = *this;
                here = here->next;
                return results;
           } // postincrement

           bool operator==(const SSLL_Const_Iter& rhs) const
           {
               return (here == rhs.here);
           }
           bool operator!=(const SSLL_Const_Iter& rhs) const
           {
               return (here != rhs.here);
           }
    }; // end SSLL_Const_Iter

        typedef std::size_t size_t;
        typedef T value_type;
        typedef SSLL_Iter iterator;
        typedef SSLL_Const_Iter const_iterator;

     iterator begin()
      {
          return SSLL_Iter( head );
      }
     iterator end()
      {
           Node* nodePtr = head;
			while(!nodePtr)
			{
				nodePtr = nodePtr->next;
			}

          return SSLL_Iter(&nodePtr);
          //return SSLL_Iter();
      }
     const_iterator begin() const
     {
         return SSLL_Const_Iter( head );
     }
     const_iterator end() const
     {
            Node* nodePtr = head;
			while(!nodePtr)
			{
				nodePtr = nodePtr->next;
			}
            return SSLL_Const_Iter(&nodePtr);
            //return SSLL_Const_Iter();
     }
        SSLL()
        {
            head = NULL;
            capacity = 0;
        }
        //Copy Constructor
        SSLL( const SSLL& src )
        {
            head = src.head;
            capacity = src.capacity;
        }

        ~SSLL()
        {
            Node* nodePtr;
			Node* next;
			nodePtr = head;
			while(nodePtr != NULL)
			{
				next = nodePtr->next;
				delete &nodePtr;
				nodePtr = next;
			}
			head = NULL;
        } // safely dispose of this SSLL's contents

        SSLL& operator=( const SSLL& src )
        {
          if ( &src == this ) // check for self-assignment
                return *this;  // do nothing
          else
          {
              clear();// safely dispose of this SSLL's contents
              head = src.head; // populate this SSLL with copies of the other SSLL's contents
              return *head;
          }
        }
        //--------------------------------------------------
        // member functions
        //--------------------------------------------------

        T replace( const T& element, int position )
		  {
		  	if(position >= size() || position <0)
		  		throw std::out_of_range("replace() method: Position is out of bounds");
		  	if(is_empty())
                throw std::logic_error("replace() method: List is empty");
		  	else
		  	{
		  		Node* nodePtr;
		  		Node* toReplace = new Node();
		  		Node* temp = new Node();
			  	int index = position;
			  	nodePtr = head;

			  	if(index == 0)
                {
                        toReplace = nodePtr;
			  			temp->value = toReplace->value;
			  			toReplace->value = element;
			  			return temp->value;
                }
                else
                {
                    for(int i = 0; i < index; i++)
                    {
                        if(i+1 == index)
                        {
                            toReplace = nodePtr->next;
                            temp->value = toReplace->value;
                            toReplace->value = element;
                            return temp->value;
                        }
                        nodePtr = nodePtr->next;
                    }
                }
		  	}
		  }
        //--------------------------------------------------

        void insert( const T& element, int position )
         {
             if(position > size() || position <0)
		  		throw std::out_of_range("insert() method: Position is out of bounds");

		  	 else if (position == 0)
		  		push_front(element);

             else if (position == size())
                push_back(element);

		  	else
		  	{
		  		Node* nodePtr;
		  		Node* newNode = new Node();
		  		newNode->value = element;
			  	int index = position;
			  	nodePtr = head;

			  	for(int i = 0; i < index; i++)
			  	{
			  		if(i+1 == index)
			  		{
			  			newNode->next = nodePtr->next;
			  			nodePtr->next = newNode;
			  			capacity = capacity+1;
			  		}
			  		else
			  			nodePtr = nodePtr->next;
			  	}
		  	}
         }

        //--------------------------------------------------
        void push_front( const T& element  )
         {
             Node* newNode = new Node();
             newNode->value = element;
             newNode->next = NULL;

             if(head == NULL)
             {
                 head = newNode;
             }
             else
             {
                 newNode->next = head;
                 head = newNode;
             }
			 capacity = capacity+1;
         }
        //--------------------------------------------------
        void push_back( const T& element )
        {
            Node* newNode; // to point to a new node
            Node* nodePtr; // to travel through the list
            // allocating new node and store value
            newNode = new Node();
            newNode->value = element;
            newNode->next = NULL;

            if(!head) // if the list is empty (head is pointing to NULL), make the newNode the first node
            {
                head = newNode;
            }
            else // insert newNode at the end of the list
            {
                // making nodePtr to head of the list
                nodePtr = head;
                while(nodePtr->next) // finding the last node
                {
                    nodePtr = nodePtr->next;
                }
                nodePtr->next = newNode; // inserting newNode at the end of list
            }
            capacity = capacity+1;
        }
        //--------------------------------------------------
        T pop_front()
          {
             if(!head)
               throw std::logic_error("pop_front() method: List is empty"); //exception
             else
             {
				 Node* t = head;
				 Node* first = new Node();

                 head = t->next;
                 first->value = t->value;
            	 capacity = capacity-1;
                 delete t;
                 return first->value;
             }
         }
        //--------------------------------------------------
        T pop_back()
         {
            if(!head) // if the list is empty
		 		throw std::logic_error("pop_back() method: List is empty");
            else if(head->next == NULL)
            {
                Node* newNode = new Node();
                newNode->value = head->value;
                head = NULL;
                capacity = capacity-1;
                return newNode->value;
            }
            else
            {
                Node* newNode = new Node(); // to point to a new node
                Node* nodePtr = new Node(); // to travel through the list
               // making nodePtr to head of the list
                nodePtr = head;
				for(int i = 0; i < size()-1; i++)
				{
					if(nodePtr->next->next == NULL)
					{
						newNode->value = nodePtr->next->value;
						delete nodePtr->next;
						nodePtr->next = NULL;
					}
					else
                        nodePtr = nodePtr->next;
				}
				capacity = capacity-1;
				return newNode->value;
            }
         }

        //--------------------------------------------------
        T remove( int position )
         {
            if(is_empty())
		  		throw std::logic_error("remove() method : List is empty");
            if(position >= size() || position < 0)
		  		throw std::out_of_range("remove()method : Position is out of bounds");
		  	else if (position == 0)
		  		return pop_front();
		  	else if (position == size()-1)
		  		return pop_back();
		  	else
		  	{
		  		Node* nodePtr;
		  		Node* toDelete = new Node();
		  		Node* temp = new Node();
			  	int index = position;

			  	nodePtr = head;

			  	for(int i = 0; i < index; i++)
			  	{
			  		if(i+1 == index)
			  		{
			  			toDelete = nodePtr->next;
			  			nodePtr->next = toDelete->next;
			  			temp->value = toDelete->value;
			  			delete toDelete;
			  			capacity = capacity-1;
			  			return temp->value;

			  		}
			  		nodePtr = nodePtr->next;
			  	}
         }
         }

        //--------------------------------------------------
        T item_at( int position ) const
		  {
		  	if(position >= size() || position < 0)
		  		throw std::out_of_range("Item_at() method: Position out of bounds");
		  	if(is_empty())
                throw std::logic_error("item_at() method: List is empty");
		  	else
		  	{
		  		Node* nodePtr = head;
			  	int index = position;

			  	for(int i = 0; i <= index; i++)
			  	{
			  		if(i==index)
			  		{
			  			//cout << "Node at position " << index+1 << "is " << nodePtr->value;
			  			return nodePtr->value;
			  		}
			  		nodePtr = nodePtr->next;
			  	}
		  	}
		  }
        //--------------------------------------------------
        bool is_empty() const
		  {
		  	return (head == 0);
		 }

        size_t size() const
        {
        	return capacity;
        }
        //--------------------------------------------------
        void clear()
         {
            Node* nodePtr = head;
            Node* next;

            while(nodePtr != NULL)
			{
				next = nodePtr->next;
				delete &nodePtr;
				nodePtr = next;
			}
			head = NULL;
			capacity = 0;
         }
        //--------------------------------------------------
        bool contains( const T& element, bool equals(const T& a, const T& b)) const
         {
            Node* t= new Node();
            t = head;
        	while(t)
            {
        		if(equals(element, t->value))
        		{
        		    return true;
        		}
        		t = t->next;
        	}
        	return false;
         }

        //--------------------------------------------------
        std::ostream& print( std::ostream& out ) const
         {
            if(is_empty())
            {
            	return out << "<empty list>";
            }
            else
            {
            	Node* nodePtr = head;
                out << "[";
	            while(nodePtr)
	            {
	                if(nodePtr->next == NULL)
	            	{
	            		out << nodePtr->value;
	                }
                    else
                    {
                        out << nodePtr->value << ", ";
                    }
	                nodePtr = nodePtr->next;
	            }
	            out << "]";
	            return out;
            }
         }

         T& operator[](int i)
         {
			if (i < 0 || i >= size() )
            {
                throw std::out_of_range("operator[]: Index out of bounds of the array!");
            }

            if (is_empty())
				throw std::logic_error("operator[]: List is empty!");

			Node* nodePtr = head;
			for (int j = 0; j != i; j++)
            {
                nodePtr = nodePtr->next;
            }
			return nodePtr->value;
		}

		T const& operator[](int i) const
		{
			return item_at(i);
		}


  }; //end class SSLL
} // end namespace cop3530

#endif // _SSLL_h_

/*
int main()
 {
      cop3530::SSLL<char> l;

      l.print( std::cout );
      std::cout << std::endl;
      l.insert( 'Y', 0 );
      l.print( std::cout );
      std::cout << std::endl;
      l.insert( 'X', 0 );
      l.print( std::cout ); std::cout << std::endl;

      in_list( l, 'x', std::cout );
      in_list( l, 'X', std::cout );

      std:: cout << "\n\n\n";

    return 0;
}*/
