#include <iostream>
#include <vector>

#include "MyList.hpp"

int main() {

    MyList<int> my_list;
    my_list.push_back(1);
    my_list.push_back(2);
    my_list.push_back(3);
    my_list.push_back(4);

    auto new_list(my_list);
    new_list.push_back(5);
    std::cout << my_list.pop_back() << std::endl;
    std::cout << my_list.pop_back() << std::endl;
    std::cout << my_list.pop_back() << std::endl;
    std::cout << my_list.pop_back() << std::endl;
    my_list.push_back(1);
    my_list.push_back(2);
    my_list.push_back(3);
    my_list.push_back(4);
    std::cout << my_list << std::endl;
    std::cout << std::endl;
    std::cout << new_list << std::endl;
    auto new_list_move(std::move(my_list));
    std::cout << std::endl;
    std::cout << new_list_move << std::endl;
    std::cout << std::endl;

    for (auto iter = new_list_move.begin(); iter != new_list_move.end(); iter++) {
        std::cout << *iter << std::endl;
    }

    std::cout << std::endl;
    for (auto it : new_list_move) {
        std::cout << it << std::endl;
    }

    for (auto it = new_list_move.begin(); it != new_list_move.end(); ++it) {
        std::cout << *it << std::endl;

    }

    std::cout << std::endl;
    MyList<int> initializer_list_list{1, 2, 3, 4};
    std::cout <<initializer_list_list << std::endl;

    auto insert_it1 = initializer_list_list.begin();
    initializer_list_list.insert(insert_it1, 0);
    std::cout << std::endl;
    std::cout << "insert test:" << std::endl;
    std::cout << initializer_list_list << std::endl;

    auto insert_it2 = initializer_list_list.begin();
    insert_it2++;
    initializer_list_list.insert(insert_it2, 5);
    std::cout << std::endl;
    std::cout << "insert test:" << std::endl;
    std::cout << initializer_list_list << std::endl;

    MyList<int> add_test{};

    initializer_list_list += add_test;
    add_test.push_back(2);
    initializer_list_list += add_test;

    std::cout << std::endl;
    std::cout << initializer_list_list << std::endl;

    std::cout << "reverse test:" << std::endl;
    MyList<int> test_reverse{1, 2, 3, 4};
    for(auto reverse_it = test_reverse.rbegin(); reverse_it != test_reverse.rend(); reverse_it++) {
        std::cout << *reverse_it << std::endl;
    }

    std::cout << (initializer_list_list == add_test) << std::endl;

    initializer_list_list.push_front(5);

    return 0;
}
