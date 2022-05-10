#ifndef LAB_02_REVERSEITERATOR_H
#define LAB_02_REVERSEITERATOR_H

#include <iterator>

#include "ListIterator.hpp"

template <typename Iter>
class ReverseListIterator : public std::reverse_iterator<Iter> {
public:
    ReverseListIterator(Iter it) : std::reverse_iterator<Iter>(it) {}
    constexpr auto &operator*() {
        return *(std::reverse_iterator<Iter>::current);
    }
};

#endif //LAB_02_REVERSEITERATOR_H
