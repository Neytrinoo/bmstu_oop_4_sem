#ifndef LAB_02_MYLIST_HPP
#define LAB_02_MYLIST_HPP

#include <memory>
#include <iostream>
#include <initializer_list>
#include <ctime>
#include <iterator>

#include "BaseList.h"
#include "ListNode.hpp"
#include "ListIterator.hpp"
#include "ConstListIterator.hpp"
#include "ReverseIterator.h"
#include "Exceptions.h"

template<typename T>
std::ostream &operator<<(std::ostream &out, const MyList<T> &list) {
    out << "List: {";
    for (auto it = list.begin(); it != list.end(); ++it) {
        auto it_cpy = it;
        if (++it_cpy == list.end()) {
            out << *it;
        } else {
            out << *it << ", ";
        }

    }
    out << "}";

    return out;
}


template<typename T, typename Allocator>
class MyList : public BaseList {
public:
    using traits = std::allocator_traits<Allocator>;
    using reference = T &;
    using const_reference = const T &;

    MyList() noexcept;

    explicit MyList(const MyList<T> &other);

    MyList(MyList<T> &&other) noexcept;

    MyList(std::initializer_list<T> in_list);

    MyList(ConstListIterator<T> begin, ConstListIterator<T> end);

    explicit MyList(const std::vector<T> &other);

    MyList(T *arr, size_t size);

    MyList<T, Allocator> &operator=(const MyList<T> &other);

    MyList<T, Allocator> &operator=(MyList<T> &&other) noexcept;

    MyList<T, Allocator> &operator=(const std::initializer_list<T> &in_list);


    MyList<T, Allocator> &extend(const MyList<T> &other);

    MyList<T> sum_lists(const MyList<T> &other);

    MyList<T> operator+(const MyList<T> &other) const;

    MyList<T, Allocator> &operator+=(const MyList<T> &to_add);

    MyList<T, Allocator> &insert(ListIterator<T> &after, const T &value);

    MyList<T, Allocator> &remove(ListIterator<T> &elem_to_remove);

    void push_back(const_reference value);

    void push_front(const_reference value);

    T pop_back();

    T pop_front();

    void clear() noexcept override;

    bool empty() const noexcept override;

    size_t size() const noexcept override;

    ListIterator<T> begin() noexcept;

    ListIterator<T> end() noexcept;

    ConstListIterator<T> begin() const noexcept;

    ConstListIterator<T> end() const noexcept;

    ConstListIterator<T> cbegin() const noexcept;

    ConstListIterator<T> cend() const noexcept;

    ReverseListIterator<ListIterator<T>> rbegin() noexcept;

    ReverseListIterator<ListIterator<T>> rend() noexcept;

    ReverseListIterator<ConstListIterator<T>> rbegin() const noexcept;

    ReverseListIterator<ConstListIterator<T>> rend() const noexcept;

    ReverseListIterator<ConstListIterator<T>> crbegin() const noexcept;

    ReverseListIterator<ConstListIterator<T>> crend() const noexcept;

    T &front();

    T &back();

    bool isEqual(const MyList<T> &other) const noexcept;

    bool operator==(const MyList<T> &other) const noexcept;

    bool isNotEqual(const MyList<T> &other) const noexcept;

    bool operator!=(const MyList<T> &other) const noexcept;

    friend std::ostream &operator<< <T>(std::ostream &out, const MyList &list);

private:
    std::shared_ptr<ListNode<T>> head_;
    std::shared_ptr<ListNode<T>> tail_;
    size_t size_{};
    Allocator allocator_;

    void copyConstructor(const MyList<T> &other);

    void transferConstructor(MyList<T> &&other) noexcept;

    void initializerConstructor(const std::initializer_list<T> &in_list);

};

template<typename T, typename Allocator>
bool MyList<T, Allocator>::empty() const noexcept {
    return size_ == 0;
}

template<typename T, typename Allocator>
MyList<T, Allocator> &MyList<T, Allocator>::insert(ListIterator<T> &after, const T &value) {
    if (!after) {
        time_t t_time = time(nullptr);
        throw ListIteratorError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
    }

    auto new_node = std::allocate_shared<ListNode<T>>(allocator_, value);
    if (!new_node) {
        time_t t_time = time(nullptr);
        throw ListMemoryError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
    }

    auto after_node = after.getListNode();
    if (after_node != tail_) {
        new_node->setNext(after_node->getNext());
        new_node->setPrev(after_node);
        after_node->getNext()->setPrev(new_node);
        after_node->setNext(new_node);
    } else {
        new_node->setPrev(tail_);
        tail_->setNext(new_node);
        tail_ = new_node;
    }

    return *this;
}

template<typename T, typename Allocator>
MyList<T> MyList<T, Allocator>::operator+(const MyList<T> &other) const {
    return sum_lists(other);
}

template<typename T, typename Allocator>
MyList<T, Allocator> &MyList<T, Allocator>::extend(const MyList<T> &other) {
    for (auto &it: other) {
        push_back(it);
    }

    return *this;
}

template<typename T, typename Allocator>
MyList<T, Allocator> &MyList<T, Allocator>::operator=(const std::initializer_list<T> &in_list) {
    initializerConstructor(in_list);

    return *this;
}

template<typename T, typename Allocator>
void MyList<T, Allocator>::copyConstructor(const MyList<T> &other) {
    for (auto &it: other) {
        push_back(it);
    }
}

template<typename T, typename Allocator>
void MyList<T, Allocator>::transferConstructor(MyList<T> &&other) noexcept {
    head_ = other.head_;
    tail_ = other.tail_;
    size_ = other.size_;

    other.head_ = other.tail_ = nullptr;
    other.size_ = 0;

}

template<typename T, typename Allocator>
void MyList<T, Allocator>::initializerConstructor(const std::initializer_list<T> &in_list) {
    for (auto &elem: in_list) {
        push_back(elem);
    }
}

template<typename T, typename Allocator>
MyList<T, Allocator>::MyList() noexcept : size_(0), head_(nullptr), tail_(nullptr) {

}

template<typename T, typename Allocator>
MyList<T, Allocator>::MyList(const MyList<T> &other) : MyList() {
    copyConstructor(other);
}

template<typename T, typename Allocator>
MyList<T, Allocator>::MyList(MyList<T> &&other) noexcept {
    transferConstructor(std::move(other));
}

template<typename T, typename Allocator>
MyList<T, Allocator>::MyList(std::initializer_list<T> in_list) {
    initializerConstructor(in_list);
}

template<typename T, typename Allocator>
MyList<T, Allocator> &MyList<T, Allocator>::operator=(const MyList<T> &other) {
    copyConstructor(other);

    return *this;
}

template<typename T, typename Allocator>
MyList<T, Allocator> &MyList<T, Allocator>::operator=(MyList<T> &&other) noexcept {
    transferConstructor(std::move(other));

    return *this;
}

template<typename T, typename Allocator>
MyList<T> MyList<T, Allocator>::sum_lists(const MyList<T> &other) {
    auto this_copy = MyList(*this);

    for (auto &it: other) {
        this_copy.push_back(it);
    }

    return this_copy;
}

template<typename T, typename Allocator>
MyList<T, Allocator> &MyList<T, Allocator>::operator+=(const MyList<T> &to_add) {
    return extend(to_add);
}

template<typename T, typename Allocator>
void MyList<T, Allocator>::push_back(const_reference value) {
    auto new_node = std::allocate_shared<ListNode<T>>(allocator_, value);
    if (!new_node) {
        time_t t_time = time(nullptr);
        throw ListMemoryError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
    }

    if (size_ == 0) {
        head_ = tail_ = new_node;
    } else {
        tail_->setNext(new_node);
        new_node->setPrev(tail_);
        tail_ = new_node;
    }

    ++size_;
}

template<typename T, typename Allocator>
T MyList<T, Allocator>::pop_back() {
    if (empty()) {
        time_t t_time = time(NULL);
        throw ListEmptyError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
    }

    T node_data = tail_->getValue();
    if (tail_->getPrev()) {
        tail_ = tail_->getPrev();
        tail_->setNext(nullptr);
    } else {
        head_ = tail_ = nullptr;
    }
    --size_;

    return node_data;
}

template<typename T, typename Allocator>
void MyList<T, Allocator>::clear() noexcept {
    head_ = tail_ = nullptr;
    size_ = 0;
}

template<typename T, typename Allocator>
size_t MyList<T, Allocator>::size() const noexcept {
    return size_;
}

template<typename T, typename Allocator>
ListIterator<T> MyList<T, Allocator>::begin() noexcept {
    return ListIterator<T>(head_);
}

template<typename T, typename Allocator>
ListIterator<T> MyList<T, Allocator>::end() noexcept {
    if (tail_) {
        return ListIterator<T>(tail_->getNext());
    }
    return ListIterator<T>(head_);
}

template<typename T, typename Allocator>
ConstListIterator<T> MyList<T, Allocator>::begin() const noexcept {
    return ConstListIterator<T>(head_);
}

template<typename T, typename Allocator>
ConstListIterator<T> MyList<T, Allocator>::end() const noexcept {
    if (tail_) {
        return ConstListIterator<T>(tail_->getNext());
    }
    return ConstListIterator<T>(head_);
}

template<typename T, typename Allocator>
ConstListIterator<T> MyList<T, Allocator>::cbegin() const noexcept {
    return ConstListIterator<T>(head_);
}

template<typename T, typename Allocator>
ConstListIterator<T> MyList<T, Allocator>::cend() const noexcept {
    if (tail_) {
        return ConstListIterator<T>(tail_->getNext());
    }
    return ConstListIterator<T>(head_);
}

template<typename T, typename Allocator>
T & MyList<T, Allocator>::front() {
    return head_->getValueRef();
}

template<typename T, typename Allocator>
T & MyList<T, Allocator>::back() {
    return head_->getValueRef();
}


template<typename T, typename Allocator>
bool MyList<T, Allocator>::isEqual(const MyList<T> &other) const noexcept {
    if (size() != other.size()) {
        return false;
    }

    auto this_it = begin();
    auto other_it = other.begin();
    while (this_it != end() && other_it != other.end() && *this_it == *other_it) {
        this_it++;
        other_it++;
    }

    return this_it == end() && other_it == other.end();
}

template<typename T, typename Allocator>
bool MyList<T, Allocator>::operator==(const MyList<T> &other) const noexcept {
    return isEqual(other);
}

template<typename T, typename Allocator>
bool MyList<T, Allocator>::isNotEqual(const MyList<T> &other) const noexcept {
    return !isEqual(other);
}

template<typename T, typename Allocator>
bool MyList<T, Allocator>::operator!=(const MyList<T> &other) const noexcept {
    return isNotEqual(other);
}

template<typename T, typename Allocator>
ReverseListIterator<ListIterator<T>> MyList<T, Allocator>::rbegin() noexcept {
    return ReverseListIterator<ListIterator<T>>(ListIterator<T>(tail_));
}

template<typename T, typename Allocator>
ReverseListIterator<ListIterator<T>> MyList<T, Allocator>::rend() noexcept {
    if (head_) {
        return ReverseListIterator<ListIterator<T>>(ListIterator<T>(head_->getPrev()));
    } else {
        return ReverseListIterator<ListIterator<T>>(ListIterator<T>(head_));
    }
}

template<typename T, typename Allocator>
ReverseListIterator<ConstListIterator<T>> MyList<T, Allocator>::rbegin() const noexcept {
    return ReverseListIterator<ConstListIterator<T>>(ConstListIterator<T>(tail_));
}

template<typename T, typename Allocator>
ReverseListIterator<ConstListIterator<T>> MyList<T, Allocator>::rend() const noexcept {
    if (head_) {
        return ReverseListIterator<ConstListIterator<T>>(ConstListIterator<T>(head_->getPrev()));
    } else {
        return ReverseListIterator<ConstListIterator<T>>(ConstListIterator<T>(head_));
    }
}

template<typename T, typename Allocator>
ReverseListIterator<ConstListIterator<T>> MyList<T, Allocator>::crbegin() const noexcept {
    return ReverseListIterator<ConstListIterator<T>>(ConstListIterator<T>(tail_));
}

template<typename T, typename Allocator>
ReverseListIterator<ConstListIterator<T>> MyList<T, Allocator>::crend() const noexcept {
    if (head_) {
        return ReverseListIterator<ConstListIterator<T>>(ConstListIterator<T>(head_->getPrev()));
    } else {
        return ReverseListIterator<ConstListIterator<T>>(ConstListIterator<T>(head_));
    }
}

template<typename T, typename Allocator>
MyList<T, Allocator>::MyList(ConstListIterator<T> begin, ConstListIterator<T> end) {
    if (end < begin) {
        time_t t_time = time(NULL);
        throw ListIteratorError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
    }

    for (auto it = begin; it != end; ++it) {
        push_back(*it);
    }
}

template<typename T, typename Allocator>
MyList<T, Allocator>::MyList(const std::vector<T> &other) {
    for (auto &it: other) {
        push_back(it);
    }
}

template<typename T, typename Allocator>
MyList<T, Allocator>::MyList(T *arr, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        push_back(arr[i]);
    }
}

template<typename T, typename Allocator>
MyList<T, Allocator> &MyList<T, Allocator>::remove(ListIterator<T> &elem_to_remove) {
    if (!elem_to_remove) {
        time_t t_time = time(NULL);
        throw ListIteratorError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
    }

    if (empty()) {
        time_t t_time = time(NULL);
        throw ListEmptyError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
    }

    if (elem_to_remove == head_) {
        head_ = head_->getNext();
    } else if (elem_to_remove == tail_) {
        auto tail_prev = tail_->getPrev();
        if (tail_prev) {
            tail_prev->setNext(nullptr);
        }
        tail_ = tail_->getPrev();
    } else {
        auto node = elem_to_remove.getListNode();
        node->getNext()->setPrev(node->getPrev());
        node->getPrev()->setNext(node->getNext());
    }

    return *this;
}

template<typename T, typename Allocator>
void MyList<T, Allocator>::push_front(const_reference value) {
    auto new_node = std::allocate_shared<ListNode<T>>(allocator_, value);
    if (!new_node) {
        time_t t_time = time(nullptr);
        throw ListMemoryError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
    }

    if (size_ == 0) {
        head_ = tail_ = new_node;
    } else {
        new_node->setNext(head_);
        head_->setPrev(new_node);
        head_ = new_node;
    }

    ++size_;
}

template<typename T, typename Allocator>
T MyList<T, Allocator>::pop_front() {
    if (empty()) {
        time_t t_time = time(NULL);
        throw ListEmptyError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
    }

    T node_data = head_->getValue();
    if (head_->getNext()) {
        head_->getNext()->setPrev(nullptr);
        head_ = head_->getNext();
    } else {
        head_ = tail_ = nullptr;
    }

    --size_;

    return node_data;
}

#endif //LAB_02_MYLIST_HPP
