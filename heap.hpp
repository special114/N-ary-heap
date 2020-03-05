#ifndef HEAP_HPP
#define HEAP_HPP

/* N-ary heap implementation
 * authors: Rafał Surdej, Jakub Kowalczyk
 * 13.12.2019
 */

#include <iostream>
#include <utility>
#include <exception>
#include <vector>

using namespace std;

const int N = 3;

template<typename KeyType, typename ValueType>
class Heap3
{
public:
    using KeyValueType = std::pair<KeyType, ValueType>;

    bool empty() const noexcept
    {
        return !el_num;
    }

    void insert(KeyType const & key, ValueType const & value)
    {
        insert(pair<KeyType, ValueType>(key, value));
    }

    void insert(KeyValueType const & key_value)
    {
        h_vec.push_back(key_value);
        ++ el_num;
        int el_idx = el_num - 1;
        int par_idx = get_par_idx(N, el_idx);
        while (el_idx != par_idx && h_vec[el_idx].first < h_vec[par_idx].first)
        {
            swap(h_vec[el_idx], h_vec[par_idx]);
            el_idx = par_idx;
            par_idx = get_par_idx(N, el_idx);
        }
    }

    KeyValueType const & peek() const
    {
        if (size())
            return h_vec[0];
        else
            throw logic_error("No elements in the heap!");
    }

    int get_first_child_idx(const int N, int idx) const
    {
        return N * idx + 1;
    }

    int get_par_idx(const int N, int idx) const
    {
        if (idx == 0)
            return 0;
        else if (idx % N == 0)
            return idx / N - 1;
        else
            return idx / N;
    }

    int get_num_of_childr(const int N, int idx) const
    {
        int first_child_idx = N * idx + 1;
        int last_child_idx = first_child_idx + N;
        int num_of_childr;
        if (el_num > last_child_idx)
        {
            num_of_childr = N;
        }
        else if (el_num > first_child_idx)
            num_of_childr = el_num - first_child_idx;
        else
            num_of_childr = 0;
        return num_of_childr;
    }

    void swap_with_children(int idx)
    {
        int child_num = get_num_of_childr(N, idx);
        if (child_num)
        {
            int child_idx = get_first_child_idx(N, idx);
            int min_child_idx = child_idx;
            for (int i = 1; i < child_num; ++i)
            {
                if ( h_vec[child_idx + i].first < h_vec[min_child_idx].first )
                    min_child_idx = child_idx + i;
            }
            if (h_vec[min_child_idx] < h_vec[idx])
            {
                swap(h_vec[min_child_idx], h_vec[idx]);
                swap_with_children(min_child_idx);
            }
        }
    }

    KeyValueType pop()
    {
        if (size())
        {
            KeyValueType outcome = h_vec[0];
            swap(h_vec[0], h_vec[el_num - 1]);
            h_vec.pop_back();
            --el_num;
            swap_with_children(0);
            return outcome;
        }
        else
            throw runtime_error("The heap is empty");
    }

    size_t size() const
    {
        return el_num;
    }

    template<typename StreamType>
    void print_heap(StreamType& stream, int idx, int level) const
    {
        for (int i = 0; i < level; ++i)
            stream << "     ";
        stream << h_vec[idx].first << endl;
        int first_child_idx = get_first_child_idx(N, idx);
        int child_num = get_num_of_childr(N, idx);
        for (int i = 0; i < child_num; ++i)
        {
            print_heap(stream, first_child_idx + i, level + 1);
        }
    }

    template<typename StreamType>
    void print(StreamType& stream) const
    {
        if (size())
        {
            int idx = 0;
            print_heap(stream, idx, 0);
        }
        else
            stream << "The heap is empty!\n";
    }

private:
    vector<KeyValueType> h_vec;
    int el_num = 0;
};


#endif


