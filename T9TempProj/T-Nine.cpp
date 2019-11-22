#include <iostream>
#include <fstream>
#include <vector>
#include "T9.h"

void print_interface()
{
	std::cout << "1: -" << std::endl;
	std::cout << "2: a, b, c" << std::endl;
	std::cout << "3: d, e, f" << std::endl;
	std::cout << "4: g, h, i" << std::endl;
	std::cout << "5: j, k, l" << std::endl;
	std::cout << "6: m, n, o" << std::endl;
	std::cout << "7: p, q, r, s" << std::endl;
	std::cout << "8: t, u, v" << std::endl;
	std::cout << "9: w, x, y, z" << std::endl;
	std::cout << "0: another word" << std::endl;
	std::cout << "B: remove word" << std::endl;
	std::cout << "Z: exit" << std::endl;
}

void remove_previous_popl(std::vector<Word> &words, int counter)
{
	if (counter > 0)
		words[counter - 1].popularity--;
}

int main()
{
	T9 t9;
	t9.fill_lib("words.txt");
	std::vector <std::string> line;
	std::string key;
	std::string key2;
	while (true)
	{
		system("CLS");
		for (auto t : line)
			std::cout << t << " ";

		std::cout << std::endl << std::endl;
		print_interface();

		std::cout << "Enter key: " << std::endl;
		if (key2 == "0" || key2 == std::string())
			if (key2 == "z" || key2 == "Z")
				key = "z";
			else if (key2 == "b" || key2 == "B")
			{
				line.pop_back();
				std::cin >> key;
			}
			else
				std::cin >> key;
		else
			key = key2;

		if (key == "z")
		{
			system("CLS");
			break;
		}

		int counter{};
		std::vector<Word> words;
		if (!(key == "b" || key == "B"))
			words = t9.get_words(key);
		do
		{
			if ((key == "b" || key == "B") && line.size() > 0)
				line.pop_back();
			else if (key == "b" || key == "B")
				break;
			else if (line.size() > 0)
			{
				if (counter < words.size())
				{
					line.push_back(words[counter].word);
					words[counter].popularity++;
					remove_previous_popl(words, counter);
				}
				else if (counter == words.size())
				{
					line.push_back(key);
					remove_previous_popl(words, counter);
				}
				else
				{
					while (counter > words.size())
						counter -= (words.size() + 1);
					if (counter < words.size())
					{
						line.push_back(words[counter].word);
						words[counter].popularity++;
						remove_previous_popl(words, counter);
					}
					else if (counter == words.size())
					{
						line.push_back(key);
						remove_previous_popl(words, counter);
					}
				}
			}
			else
			{
				std::string temp;
				if (counter < words.size())
				{
					temp = words[counter].word;
					words[counter].popularity++;
					remove_previous_popl(words, counter);
				}
				else if (counter == words.size())
				{
					temp = key;
					remove_previous_popl(words, counter);
				}
				else
				{
					while (counter > words.size())
						counter -= (words.size() + 1);
					if (counter < words.size())
					{
						temp = words[counter].word;
						words[counter].popularity++;
						remove_previous_popl(words, counter);
					}
					else if (counter == words.size())
					{
						temp = key;
						remove_previous_popl(words, counter);
					}
				}
				temp[0] = toupper(temp[0]);
				line.push_back(temp);
			}

			system("CLS");
			for (auto t : line)
				std::cout << t << " ";
			std::cout << std::endl << std::endl;

			print_interface();

			std::cout << "Enter key: " << std::endl;
			std::cin >> key2;

			if (key2 == "Z" || key2 != "0")
				break;
			else
			{
				line.pop_back();
				counter++;
			}
		} while (key2 != "Z" && key2 != "z" && key2 == "0");

		t9.return_words(words, key);
	}
	for (auto t : line)
		std::cout << t << " ";

	t9.save_lib("words.txt");
}
