#include <string>

#include "TextAnalyzer.h"

TextAnalyzer::TextAnalyzer()
{
	_count = 0;
	_size = 27;
	//_hash = &TextAnalyzer::HashFunction;
	// Allocate a new array of size 27
	_hashTable = new LinkedList*[_size];
	for (int i = 0; i < _size; i++)
	{
		_hashTable[i] = NULL;
	}
}

//TextAnalyzer::TextAnalyzer(unsigned int size, unsigned int(*hash)(std::string&))
//{
//	//_ActualHashFunction = &hash;
//	_hash = hash;
//	_count = 0;
//	_size = size;
//	// Allocate a new array with size passed in
//	_hashTable = new LinkedList*[_size];
//	for (int i = 0; i < _size; i++)
//	{
//		_hashTable[i] = NULL;
//	}
//}

void TextAnalyzer::Insert(std::string& key)
{
	if (HashFunction(key) >= _size) // Safety precautions to not index out of range
	{
		return;
	}
	if (_hashTable[HashFunction(key)] == NULL) // If the slot has nothin in it
	{
		_hashTable[HashFunction(key)] = new LinkedList();
		_hashTable[HashFunction(key)]->AppendItem(key);
	}

	if (_hashTable[HashFunction(key)]->CheckMultiple(key) == -1) // If word is NOT already in the list, add it
	{
		_hashTable[HashFunction(key)]->AppendItem(key);
	}
	// Increase the word count if it already exists in the list
	_hashTable[HashFunction(key)]->AddToCount(key);
}

unsigned int TextAnalyzer::GetCount(std::string& key)
{
	return _hashTable[HashFunction(key)]->WordCount(key);
}

void TextAnalyzer::PrintHashEntries()
{
	for (int i = 0; i < _size; i++)
	{
		if(_hashTable[i] != NULL)
		_hashTable[i]->Print();
	}
}

void TextAnalyzer::PrintHashStats()
{
// Variables for storing stats
	int totalWords = 0, uniuqueWords = 0, slotsUsed = 0, maxEntries = 0;
	cout << "\n";
	cout << "Hash table entries per slot: ";
	for (int i = 0; i < _size; i++)
	{
		if (_hashTable[i] != NULL)
		{
			cout << _hashTable[i]->GetSize() << " "; // # of entries per slot
			slotsUsed++;  // keeping track of the slots that are used in the hash table
			if (maxEntries < _hashTable[i]->GetSize()) // keeping track of the largest entry
				maxEntries = _hashTable[i]->GetSize();
			uniuqueWords += _hashTable[i]->GetSize(); // total # of unique words
			totalWords += _hashTable[i]->GetGrandTotal(); // total # of words counted
		}
	}
	cout << "\n";
	cout << slotsUsed << " hash table slots used out of " << _size << " total.\n";
	cout << maxEntries << " max entries in a table slot. " << uniuqueWords / _size << " avg entries in a table slot.\n";
	cout << uniuqueWords << " unique words found.\n";
	cout << totalWords << " total words counted.\n";
}

unsigned int TextAnalyzer::HashFunction(std::string& key)
{
	// Make word all lower case
	for (int i = 0; i < key.length(); i++)
	{
		key[i] = tolower(key[i]);
	}
	// Make sure only alpha chars
	int pos = key.find_first_not_of("abcdefghijklmnopqrstuvwxyz");
	if (pos == -1)
	{
		return 0;
	}
	pos = key[0] - 'a' + 1; // Get pos in alphabet
	return pos;
}

TextAnalyzer::~TextAnalyzer()
{
	delete _hashTable;
}