#pragma once
#include "Heap.h"
#include <string>
#include <vector>
#include <iostream>
#include <memory>

template <typename T, size_t R = 256, typename Container = std::vector<char>>
class RwayTrie
{
	struct Node;

	std::shared_ptr<Node> root = std::shared_ptr<Node>(new Node());

	int get_node(int index, Container key);

	template<typename N>
	void put(Node* &node, Container key, N&& value, int d = 0);

	void save_trie(Node* &node, std::ostream& stream);

	std::vector<T> get_value(Node* node, Container key, int d = 0);

	void return_value(Node* &node, std::vector<T> values, Container key, int d = 0);

public:
	void save_trie(std::ostream& stream);
	void put(Container key, T&& value);
	void put(Container key, T& value);
	void return_value(std::vector<T> values, Container key);

	std::vector<T> get_value(Container key);
};




template <typename T, size_t R, typename Container>
struct RwayTrie<T, R, Container>::Node
{
	Heap<T> value;
	Node* next[R] = { nullptr }; //Array of pointers to next nodes

	~Node();
};

template <typename T, size_t R, typename Container>
RwayTrie<T, R, Container>::Node::~Node()
{
	for (Node* &p : next)
		delete p;
}


template <typename T, size_t R, typename Container>
int RwayTrie<T, R, Container>::get_node(int index, Container key)
{
	return static_cast<int>(key[index]);
}

template <typename T, size_t R, typename Container>
template<typename N>
void RwayTrie<T, R, Container>::put(Node* &node, Container key, N&& value, int d)
{
	if (!node) node = new Node;
	if (d == key.size())
	{
		node->value.insert(value);
		return;
	}
	int c = get_node(d, key);
	put(node->next[c], key, std::forward<N>(value), d + 1);
}

template<typename T, size_t R, typename Container>
void RwayTrie<T, R, Container>::save_trie(Node *& node, std::ostream& stream)
{
	if (!node) return;
	
	if (!node->value.is_empty())
	{
		std::vector<T> temp_vec = node->value.return_heap();
		for (auto t : temp_vec)
			stream << t << std::endl;
	}

	for (int i = 1; i < 10; i++)
	{
		save_trie(node->next[i], stream);
	}
}

template <typename T, size_t R, typename Container>
std::vector<T> RwayTrie<T, R, Container>::get_value(Node* node, Container key, int d)
{
	if (d == key.size())
	{
		if (!(node && !node->value.is_empty()))
		{
			return {};
		}
		else
		{
			std::vector<T> temp_v = node->value.return_sorted_heap();
			return temp_v;
		}
	}

	if (!node)
	{
		return {};
	}

	int c = get_node(d, key);
	return get_value(node->next[c], key, d + 1);
}

template <typename T, size_t R, typename Container>
void RwayTrie<T, R, Container>::return_value(Node* &node, std::vector<T> values, Container key, int d)
{
	if (!node) node = new Node;
	if (d == key.size())
	{
		node->value.remove_elements();
		node->value.fill<std::vector<T>>(values);
		return;
	}
	int c = get_node(d, key);
	return_value(node->next[c], values, key, d + 1);
}

template<typename T, size_t R, typename Container>
void RwayTrie<T, R, Container>::save_trie(std::ostream& stream)
{
	Node* temp_tpr = this->root.get();
	save_trie(temp_tpr, stream);
}

template <typename T, size_t R, typename Container>
void RwayTrie<T, R, Container>::put(Container key, T&& value)	//User call function (rvalue)
{
	Node* temp_ptr = this->root.get();
	put(temp_ptr, key, std::forward<T>(value));
}

template <typename T, size_t R, typename Container>
void RwayTrie<T, R, Container>::put(Container key, T& value)	//User call function (lvalue)
{
	Node* temp_ptr = this->root.get();
	put(temp_ptr, key, std::forward<T>(value));
}

template <typename T, size_t R, typename Container>
void RwayTrie<T, R, Container>::return_value(std::vector<T> values, Container key)	//User call function
{
	Node* temp_ptr = this->root.get();
	return_value(temp_ptr, values, key);
}

template <typename T, size_t R, typename Container>
std::vector<T> RwayTrie<T, R, Container>::get_value(Container key)
{
	Node* temp_ptr = this->root.get();
	return get_value(temp_ptr, key);
}