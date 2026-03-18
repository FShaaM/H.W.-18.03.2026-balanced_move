#include <iostream>
#include <exception>

template< class T >
struct List
{
	T val;
	List< T >* next;
};

template< class T >
struct Vec
{
	T* data;
	size_t s;
	size_t cap;
};

template< class T >
Vec< List< T >* > balanced_move(Vec< List< T >* > v, size_t k)
{
	if (k == 0 || v.s == 0)
		return v;

	size_t total = 0;
	for (size_t i = 0; i < v.s; ++i)
	{
		List<T>* node = v.data[i];
		while (node)
		{
			++total;
			node = node->next;
		}
	}

	size_t col = (total + k - 1) / k;

	List< T >** heads = nullptr;
	List< T >** tails = nullptr;
	try
	{
		List< T >** heads = new List< T >[col];
		List< T >** tails = new List< T >[col];

		for (size_t i = 0; i < col; ++i)
			heads[i] = tails[i] = nullptr;
	}
	catch (std::bad_alloc&)
	{
		delete[] heads;
		throw;
	}

	size_t processed = 0;
	for (size_t i = 0; i < v.s; ++i)
	{
		List<T>* node = v.data[i];
		v.data[i] = nullptr;

		while (node)
		{
			List<T>* next = node->next;
			node->next = nullptr;

			size_t idx = processed / k;

			if (heads[idx] == nullptr)
			{
				heads[idx] = tails[idx] = node;
			}
			else
			{
				tails[idx]->next = node;
				tails[idx] = node;
			}
			++processed;
			node = next;
		}
	}

	Vec<List<T>*> result;
	result.data = heads;
	result.s = col;
	result.cap = col;

	delete[] tails;

	return result;
}

int main()
{}

