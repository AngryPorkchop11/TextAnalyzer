#ifndef _TEXTANALYZER
#define _TEXTANALYZER
#include <iostream>
#include <iomanip>

using namespace std;
//typedef unsigned int(TextAnalyzer::*_ActualHashFunction)(std::string&);
//typedef unsigned int(*_ActualHashFunction)(std::string&);

class LinkedList
{
public:
	void Print()
	{
		Node *ptr = _head;
		while (ptr)
		{
			for (int i = 0; i < ptr->_word.length(); i++)
			{
				cout << ptr->_word[i];
			}
			cout << setw(5) << "   Count: " << ptr->_count << endl;
			ptr = ptr->next;
		}
	}
	// Constructor	
	LinkedList()
	{
		_head = NULL;
		_tail = NULL;
	}

	int CheckMultiple(std::string& key) //Checks if a word is already in the list
	{
		Node *ptr = _head;
		while (ptr)
		{
			if (ptr->_word == key)
				return 1;
			ptr = ptr->next;
		}
		return -1;
	}

	void AddToCount(std::string& key) // Adds to a words count
	{
		Node *ptr = _head;
		while (ptr)
		{
			if (ptr->_word == key)
			{
				ptr->_count++;
				_grandTotal++;
			}
			ptr = ptr->next;
		}
	}

	int WordCount(std::string& key) // Returns how many times the words appears in the list so far
	{
		Node *ptr = _head;
		while (ptr)
		{
			if (ptr->_word == key)
				return ptr->_count;
			ptr = ptr->next;
		}
		return 0;
	}

	unsigned int GetSize()
	{
		return _size;
	}
	int GetGrandTotal()
	{
		return _grandTotal;
	}
	// Add item at back in O(1) time
	void AppendItem(std::string& key)
	{
		// Allocate a new node and fill data with current object 
		Node *ptrNew = new Node;
		ptrNew->_word = key;
		ptrNew->_count = 0;

		// If the list is empty
		if (_size == 0)
		{
			_head = ptrNew;
			_tail = ptrNew;

			_tail->next = NULL;
			_tail->prev = NULL;

			_head->next = NULL;
			_head->prev = NULL;
			_size++;
			_grandTotal++;
			return;
		}
		// Insert at end O(1)
		ptrNew->prev = _tail;
		_tail->next = ptrNew;
		ptrNew->next = NULL;
		_tail = ptrNew;
		_size++;
		_grandTotal++;
	}
	// Destructor
	~LinkedList()
	{
		if (_size == 0)
		{
			return;
		}

		Node *ptr = _head;
		Node *run = _head;
		while (ptr)
		{
			run = ptr->next;
			delete ptr;
			ptr = run;
		}
		delete run;

	}
private:
	unsigned int _size = 0;
	int _grandTotal;

	struct Node
	{
		std::string _word;
		int _count;
		Node* next;
		Node* prev;
	};
	Node* _head;
	Node* _tail;
};

class TextAnalyzer
{
public:
	// Default Constructor: Initalize a hash table with a size of 27 using default hash function
	TextAnalyzer();
	// Constructor #2
	TextAnalyzer(unsigned int size, unsigned int(*hash)(std::string&));

	// Inserts a string into the hash table
	void Insert(std::string& key);

	// Returns the number of times the word has been counted so far
	unsigned int GetCount(std::string& key);

	// Prints all of the words and their occurence counts in no particular order
	void PrintHashEntries();

	// Prints the number of entries in each hash table slot, the number of used slots versus total,
	// the maximum number of entries in a single slot, the average entries per hash table slot, 
	// the number of unique words present, and finally the total number of words.
	// Shoot for: O(table size)
	void PrintHashStats();

	// looks only at the first character of the string and returns zero for any non-alphabetic character and 1 through 27 for the letters a through z.
	unsigned int HashFunction(std::string& word);

	//Destructor
	~TextAnalyzer();
private:
	int _size;
	static unsigned int(TextAnalyzer::*_hash) (std::string&);
	LinkedList **_hashTable;
	int _count;
};
#endif
