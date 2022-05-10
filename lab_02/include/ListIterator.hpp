#ifndef LAB_02_LISTITERATOR_HPP
#define LAB_02_LISTITERATOR_HPP

#include "Exceptions.h"

template<typename T>
class ListNode;

template <typename T, typename Allocator = std::allocator<T>>
class MyList;

template<typename T>
class ListIterator : public std::iterator<std::bidirectional_iterator_tag, T> {
public:
    using difference_type = ptrdiff_t;

    using pointer = T *;

    using const_pointer = const T *;

    using const_reference = const T &;

    using reference = T &;

    using iterator_category = std::bidirectional_iterator_tag;

    using value_type = T;


    ListIterator() = default;

    ListIterator(const ListIterator<T> &other) = default;

    explicit ListIterator(std::shared_ptr<ListNode<T>> node);

    ~ListIterator() = default;

    ListIterator<T> &operator=(const ListIterator<T> &other) = default;

    ListIterator<T> &next();
    ListIterator<T> &operator++();

    ListIterator<T> &prev();
    ListIterator<T> &operator--();

    ListIterator<T> operator++(int);
    ListIterator<T> operator--(int);

    reference get() const;

    reference operator*() const;

    pointer operator->() const;

    bool isEqual(const ListIterator<T> &other) const noexcept;

    bool operator==(const ListIterator<T> &other) const noexcept;

    bool isNotEqual(const ListIterator<T> &other) const noexcept;

    bool operator!=(const ListIterator<T> &other) const noexcept;

    bool moreThan(const ListIterator<T> &other) const noexcept;

    bool operator>(const ListIterator<T> &other) const noexcept;

    bool lessThan(const ListIterator<T> &other) const noexcept;

    bool operator<(const ListIterator<T> &other) const noexcept;

    bool moreOrEqualThan(const ListIterator<T> &other) const noexcept;

    bool operator>=(const ListIterator<T> &other) const noexcept;

    bool lessOrEqualThan(const ListIterator<T> &other) const noexcept;

    bool operator<=(const ListIterator<T> &other) const noexcept;

    explicit operator bool() const;

    friend class MyList<T>;

private:
    std::weak_ptr<ListNode<T>> node_;

    std::shared_ptr<ListNode<T>> getListNode();

    int compare(const ListIterator<T> &other) const noexcept;
};

template<typename T>
ListIterator<T>::ListIterator(std::shared_ptr<ListNode<T>> node) : node_(node) {

}

template<typename T>
T &ListIterator<T>::get() const {
    if (!(*this)) {
        time_t t_time = time(nullptr);
        throw ListIteratorError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time),
                                "The iterator points to nullptr");
    }

    return this->node_.lock()->getValueRef();
}

template<typename T>
T &ListIterator<T>::operator*() const {
    return get();
}

template<typename T>
T *ListIterator<T>::operator->() const {
    return &(get());
}

template<typename T>
ListIterator<T> &ListIterator<T>::next()  {
    if (!(*this)) {
        return *this;
    }
    node_ = node_.lock()->next_;

    return *this;
}

template<typename T>
ListIterator<T> &ListIterator<T>::prev() {
    if (!(*this)) {
        return *this;
    }

    node_ = node_.lock()->prev_;

    return *this;
}

template<typename T>
ListIterator<T> &ListIterator<T>::operator++() {
    return next();
}

template<typename T>
ListIterator<T> &ListIterator<T>::operator--() {
    return prev();
}

template<typename T>
ListIterator<T> ListIterator<T>::operator++(int) {
    if (!(*this)) {
        *this;
    }

    auto now_iter = *this;

    node_ = node_.lock()->next_;

    return now_iter;
}

template<typename T>
ListIterator<T> ListIterator<T>::operator--(int) {
    if (!(*this)) {
        *this;
    }

    auto now_iter = *this;

    node_ = node_.lock()->prev_;

    return now_iter;
}

template<typename T>
bool ListIterator<T>::isEqual(const ListIterator<T> &other) const noexcept {
    return compare(other) == 0;
}

template<typename T>
bool ListIterator<T>::operator==(const ListIterator<T> &other) const noexcept {
    return isEqual(other);
}

template<typename T>
bool ListIterator<T>::isNotEqual(const ListIterator<T> &other) const noexcept {
    return compare(other) != 0;
}

template<typename T>
bool ListIterator<T>::operator!=(const ListIterator<T> &other) const noexcept {
    return isNotEqual(other);
}

template<typename T>
bool ListIterator<T>::moreThan(const ListIterator<T> &other) const noexcept {
    return compare(other) > 0;
}

template<typename T>
bool ListIterator<T>::operator>(const ListIterator<T> &other) const noexcept {
    return moreThan(other);
}

template<typename T>
bool ListIterator<T>::lessThan(const ListIterator<T> &other) const noexcept  {
    return compare(other) < 0;
}

template<typename T>
bool ListIterator<T>::operator<(const ListIterator<T> &other) const noexcept {
    return lessThan(other);
}

template<typename T>
bool ListIterator<T>::moreOrEqualThan(const ListIterator<T> &other) const noexcept {
    return compare(other) >= 0;
}

template<typename T>
bool ListIterator<T>::operator>=(const ListIterator<T> &other) const noexcept{
    return moreOrEqualThan(other);
}

template<typename T>
bool ListIterator<T>::lessOrEqualThan(const ListIterator<T> &other) const noexcept {
    return compare(other) <= 0;
}

template<typename T>
bool ListIterator<T>::operator<=(const ListIterator<T> &other) const noexcept {
    return lessOrEqualThan(other);
}

template<typename T>
ListIterator<T>::operator bool() const {
    return node_.lock() != nullptr;
}

template<typename T>
std::shared_ptr<ListNode<T>> ListIterator<T>::getListNode() {
    return node_.lock();
}

template<typename T>
int ListIterator<T>::compare(const ListIterator<T> &other) const noexcept {
    int result = 0;
    if (other.node_.lock() == node_.lock()) {
        return result;
    }

    result = 1;
    for (auto now_node = node_; result == 1 && now_node.lock() != nullptr; now_node = now_node.lock()->next_) {
        if (now_node.lock() == other.node_.lock()) {
            result = -1;
        }
    }

    return result;
}

#endif //LAB_02_LISTITERATOR_HPP
