#ifndef LAB_02_BASELIST_H
#define LAB_02_BASELIST_H

class BaseList {
public:
    virtual ~BaseList() = default;

    virtual void clear() = 0;

    virtual bool empty() const noexcept = 0;

    virtual size_t size() const noexcept = 0;
};

#endif //LAB_02_BASELIST_H
