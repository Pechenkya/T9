#include "T9.h"
#include <iostream>
#include <fstream>

std::vector<int> T9::get_key(std::string value)
{
	unsigned int size = value.length();
	std::vector <int> int_key(size);

	int counter{};

	for (auto v : value)
	{
		v = tolower(v);
		if (v == 'a' || v == 'b' || v == 'c')
			int_key[counter++] = 2;
		else if (v == 'd' || v == 'e' || v == 'f')
			int_key[counter++] = 3;
		else if (v == 'g' || v == 'h' || v == 'i')
			int_key[counter++] = 4;
		else if (v == 'j' || v == 'k' || v == 'l')
			int_key[counter++] = 5;
		else if (v == 'm' || v == 'n' || v == 'o')
			int_key[counter++] = 6;
		else if (v == 'p' || v == 'q' || v == 'r' || v == 's')
			int_key[counter++] = 7;
		else if (v == 't' || v == 'u' || v == 'v')
			int_key[counter++] = 8;
		else if (v == 'w' || v == 'x' || v == 'y' || v == 'z')
			int_key[counter++] = 9;
		else
			int_key[counter++] = 1;
	}

	return int_key;
}

std::vector<int> T9::recreate_key(std::string key)
{
	unsigned int size = key.length();
	std::vector <int> recreated_key(size);
	for (unsigned int i = 0; i < size; i++)
	{
		recreated_key[i] = static_cast<int>(key[i]) - 48;
	}
	return recreated_key;
}

void T9::fill_lib(std::string filename)
{
	std::ifstream inp(filename);
	std::string temp{};
	int popl{};
	do
	{
		inp >> temp;
		if (temp == "/0")
			break;
		inp >> popl;
		for (auto& c : temp)
			c = tolower(c);
		this->add_word(Word(temp, popl));
	} while (temp != "/0");
	inp.close();
}

void T9::add_word(Word val)
{
	std::vector<int> key = get_key(val.word);
	this->library.put(key, val);
}

void T9::return_words(std::vector<Word> val, std::string key)
{
	std::vector <int> _key = recreate_key(key);
	library.return_value(val, _key);
}

std::vector<Word> T9::get_words(std::string key)
{
	std::vector<int> _key = recreate_key(key);
	return this->library.get_value(_key);
}

Word::Word() : word{}, popularity{ 0 }{}
Word::Word(std::string _word, int _popularity) : word{ _word }, popularity{ _popularity } {}
