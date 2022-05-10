#ifndef LAB_02_CONSTLISTITERATOR_HPP
#define LAB_02_CONSTLISTITERATOR_HPP

#include "ListIterator.hpp"

template<typename T>
class ListNode;

template<typename T, std::bidirectional_iterator Iter = ListIterator<T>>
class ConstListIterator : public std::iterator<std::bidirectional_iterator_tag, T> {
public:
    ConstListIterator() = default;

    ConstListIterator(const ConstListIterator<T, Iter> &other) = default;

    explicit ConstListIterator(std::shared_ptr<ListNode<T>> node);

    ~ConstListIterator() = default;

    ConstListIterator<T, Iter> &operator=(const ConstListIterator<T> &other);

    ConstListIterator<T, Iter> &next();

    ConstListIterator<T, Iter> &operator++();

    ConstListIterator<T, Iter> &prev();

    ConstListIterator<T, Iter> &operator--();

    ConstListIterator<T, Iter> operator++(int);

    ConstListIterator<T, Iter> operator--(int);

    const T &get() const;

    const T &operator*() const;

    const T *operator->() const;

    bool isEqual(const ConstListIterator<T, Iter> &other) const noexcept;

    bool operator==(const ConstListIterator<T, Iter> &other) const noexcept;

    bool isNotEqual(const ConstListIterator<T, Iter> &other) const noexcept;

    bool operator!=(const ConstListIterator<T, Iter> &other) const noexcept;

    bool moreThan(const ConstListIterator<T, Iter> &other) const noexcept;

    bool operator>(const ConstListIterator<T, Iter> &other) const noexcept;

    bool lessThan(const ConstListIterator<T, Iter> &other) const noexcept;

    bool operator<(const ConstListIterator<T, Iter> &other) const noexcept;

    bool moreOrEqualThan(const ConstListIterator<T, Iter> &other) const noexcept;

    bool operator>=(const ConstListIterator<T, Iter> &other) const noexcept;

    bool lessOrEqualThan(const ConstListIterator<T, Iter> &other) const noexcept;

    bool operator<=(const ConstListIterator<T, Iter> &other) const noexcept;

    explicit operator bool() const;

private:
    Iter iterator_;


};

template<typename T, std::bidirectional_iterator Iter>
ConstListIterator<T, Iter>::ConstListIterator(std::shared_ptr<ListNode<T>> node) : iterator_(node) {

}

template<typename T, std::bidirectional_iterator Iter>
ConstListIterator<T, Iter> &ConstListIterator<T, Iter>::next() {
    if (!(*this)) {
        return *this;
    }

    ++iterator_;
    return *this;
}

template<typename T, std::bidirectional_iterator Iter>
ConstListIterator<T, Iter> &ConstListIterator<T, Iter>::operator++() {
    return next();
}

template<typename T, std::bidirectional_iterator Iter>
ConstListIterator<T, Iter> &ConstListIterator<T, Iter>::prev() {
    if (!(*this)) {
        return *this;
    }

    --iterator_;

    return *this;
}

template<typename T, std::bidirectional_iterator Iter>
ConstListIterator<T, Iter> &ConstListIterator<T, Iter>::operator--() {
    return prev();
}

template<typename T, std::bidirectional_iterator Iter>
ConstListIterator<T, Iter> ConstListIterator<T, Iter>::operator++(int) {
    if (!(*this)) {
        return *this;
    }

    auto now_iter = *this;

    iterator_++;

    return now_iter;
}

template<typename T, std::bidirectional_iterator Iter>
ConstListIterator<T, Iter> ConstListIterator<T, Iter>::operator--(int) {
    if (!(*this)) {
        return *this;
    }

    auto now_iter = *this;

    iterator_--;

    return now_iter;
}

template<typename T, std::bidirectional_iterator Iter>
const T &ConstListIterator<T, Iter>::get() const {
    return *iterator_;
}

template<typename T, std::bidirectional_iterator Iter>
const T &ConstListIterator<T, Iter>::operator*() const {
    return get();
}

template<typename T, std::bidirectional_iterator Iter>
const T *ConstListIterator<T, Iter>::operator->() const {
    return &(get());
}

template<typename T, std::bidirectional_iterator Iter>
bool ConstListIterator<T, Iter>::isEqual(const ConstListIterator<T, Iter> &other) const noexcept {
    return iterator_ == other.iterator_;
}

template<typename T, std::bidirectional_iterator Iter>
bool ConstListIterator<T, Iter>::operator==(const ConstListIterator<T, Iter> &other) const noexcept {
    return isEqual(other);
}

template<typename T, std::bidirectional_iterator Iter>
bool ConstListIterator<T, Iter>::isNotEqual(const ConstListIterator<T, Iter> &other) const noexcept {
    return iterator_ != other.iterator_;
}

template<typename T, std::bidirectional_iterator Iter>
bool ConstListIterator<T, Iter>::operator!=(const ConstListIterator<T, Iter> &other) const noexcept {
    return isNotEqual(other);
}

template<typename T, std::bidirectional_iterator Iter>
bool ConstListIterator<T, Iter>::moreThan(const ConstListIterator<T, Iter> &other) const noexcept {
    return iterator_ > other.iterator_;
}

template<typename T, std::bidirectional_iterator Iter>
bool ConstListIterator<T, Iter>::operator>(const ConstListIterator<T, Iter> &other) const noexcept {
    return moreThan(other);
}

template<typename T, std::bidirectional_iterator Iter>
bool ConstListIterator<T, Iter>::lessThan(const ConstListIterator<T, Iter> &other) const noexcept {
    return iterator_ < other.iterator_;
}

template<typename T, std::bidirectional_iterator Iter>
bool ConstListIterator<T, Iter>::operator<(const ConstListIterator<T, Iter> &other) const noexcept {
    return lessThan(other);
}

template<typename T, std::bidirectional_iterator Iter>
bool ConstListIterator<T, Iter>::moreOrEqualThan(const ConstListIterator<T, Iter> &other) const noexcept {
    return iterator_ >= other.iterator_;
}

template<typename T, std::bidirectional_iterator Iter>
bool ConstListIterator<T, Iter>::operator>=(const ConstListIterator<T, Iter> &other) const noexcept {
    return moreOrEqualThan(other);
}

template<typename T, std::bidirectional_iterator Iter>
bool ConstListIterator<T, Iter>::lessOrEqualThan(const ConstListIterator<T, Iter> &other) const noexcept {
    return iterator_ <= other.iterator_;
}

template<typename T, std::bidirectional_iterator Iter>
bool ConstListIterator<T, Iter>::operator<=(const ConstListIterator<T, Iter> &other) const noexcept {
    return lessOrEqualThan(other);
}

template<typename T, std::bidirectional_iterator Iter>
ConstListIterator<T, Iter>::operator bool() const {
    return (bool) iterator_;
}

template<typename T, std::bidirectional_iterator Iter>
ConstListIterator<T, Iter> &ConstListIterator<T, Iter>::operator=(const ConstListIterator<T> &other) {
    iterator_ = other.iterator_;
};

#endif //LAB_02_CONSTLISTITERATOR_HPP
