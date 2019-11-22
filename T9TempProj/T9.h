#pragma once
#include <string>
#include <memory>
#include <vector>
#include "RwayTrie.h"

struct Word
{
	std::string word;
	int popularity;

	Word();
	Word(std::string _word, int _popularity);

	bool operator<(const Word& obj2)
	{
		if (this->popularity == obj2.popularity)
		{
			if (this->word.length() <= obj2.word.length())
			{
				for (size_t i{ 0 }; i < obj2.word.length(); i++)
				{
					if (tolower(this->word[i]) > tolower(obj2.word[i]))
						return true;
					else if (tolower(this->word[i]) != tolower(obj2.word[i]))
						return false;
				}
			}
			else if (this->word.length() > obj2.word.length())
			{
				for (size_t i{ 0 }; i < this->word.length(); i++)
				{
					if (tolower(this->word[i]) > tolower(obj2.word[i]))
						return true;
					else if (tolower(this->word[i]) != tolower(obj2.word[i]))
						return false;
				}
			}
		}

		return (this->popularity < obj2.popularity);
	}
};

class T9
{
	RwayTrie<Word, 10, std::vector<int>> library;

	std::vector<int> get_key(std::string value);
	std::vector<int> recreate_key(std::string key);
public:

	void fill_lib(std::string filename = "words.txt");
	void save_lib(std::string filename = "words.txt");
	void add_word(Word val);
	void return_words(std::vector <Word> val, std::string key);
	std::vector<Word> get_words(std::string key);
};