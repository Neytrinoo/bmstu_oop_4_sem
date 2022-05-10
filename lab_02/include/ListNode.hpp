#ifndef LAB_02_LISTNODE_HPP
#define LAB_02_LISTNODE_HPP

#include "ConstListIterator.hpp"

template<typename T>
class ListIterator;

//template<typename T, typename Iter>
//class ConstListIterator;

template<typename T>
class ListNode {
public:
    ListNode() = default;

    explicit ListNode(const T &data);

    ListNode(const T &data, const std::shared_ptr<ListNode<T>> next);

    ListNode(const T &data, const std::shared_ptr<ListNode<T>> next, const std::shared_ptr<ListNode<T>> prev);

    virtual ~ListNode() = default;

    T getValue() const noexcept;

    T &getValueRef();

    void setNext(const std::shared_ptr<ListNode<T>> new_next);

    void setPrev(const std::shared_ptr<ListNode<T>> new_prev);

    std::shared_ptr<ListNode<T>> getNext();

    std::shared_ptr<ListNode<T>> getPrev();

    friend class ListIterator<T>;

    friend class ConstListIterator<T>;

private:
    T data_;
    std::shared_ptr<ListNode<T>> next_;
    std::weak_ptr<ListNode<T>> prev_;
};

template<typename T>
ListNode<T>::ListNode(const T &data) : data_(data), next_(nullptr) {}

template<typename T>
ListNode<T>::ListNode(const T &data, const std::shared_ptr<ListNode<T>> next) : data_(data), next_(next),
                                                                                prev_(nullptr) {

}

template<typename T>
ListNode<T>::ListNode(const T &data, const std::shared_ptr<ListNode<T>> next, const std::shared_ptr<ListNode<T>> prev) : data_(
        data), next_(next), prev_(prev) {

}

template<typename T>
T ListNode<T>::getValue() const noexcept {
    return data_;
}

template<typename T>
T &ListNode<T>::getValueRef()  {
    return data_;
}

template<typename T>
void ListNode<T>::setNext(const std::shared_ptr<ListNode<T>> new_next) {
    next_ = new_next;
}

template<typename T>
void ListNode<T>::setPrev(const std::shared_ptr<ListNode<T>> new_prev) {
    prev_ = new_prev;
}

template<typename T>
std::shared_ptr<ListNode<T>> ListNode<T>::getNext() {
    return next_;
}

template<typename T>
std::shared_ptr<ListNode<T>> ListNode<T>::getPrev() {
    return prev_.lock();
}

#endif //LAB_02_LISTNODE_HPP
