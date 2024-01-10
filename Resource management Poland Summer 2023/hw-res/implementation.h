#pragma once
#include <algorithm>
template<typename Resource>
class ControlBlock {
public:
    Resource* resource;
    long sharedCount;
    long weakCount;

    ControlBlock(Resource* res) : resource(res), sharedCount(1), weakCount(0) {}

    ~ControlBlock() {
        delete resource;
    }
};

template <typename Resource>
class WeakPtr;

template <typename Resource>
class SharedPtr {
private:
    Resource* resource;
    ControlBlock<Resource>* ctrlBlock;

public:
    SharedPtr() : resource(nullptr), ctrlBlock(nullptr) {}

    explicit SharedPtr(Resource* res) : resource(res), ctrlBlock(new ControlBlock<Resource>(res)) {}

    SharedPtr(const SharedPtr<Resource>& rhs) : resource(rhs.resource), ctrlBlock(rhs.ctrlBlock) {
        if (ctrlBlock) {
            ctrlBlock->sharedCount++;
        }
    }

    SharedPtr(const WeakPtr<Resource>& rhs);

    ~SharedPtr() {
        if (ctrlBlock && --ctrlBlock->sharedCount == 0) {
            delete ctrlBlock;
            ctrlBlock = nullptr;
        }
    }

    void Reset() {
        *this = SharedPtr();
    }

    void Reset(Resource* res) {
        *this = SharedPtr(res);
    }

    void Swap(SharedPtr<Resource>& rhs) {
        std::swap(resource, rhs.resource);
        std::swap(ctrlBlock, rhs.ctrlBlock);
    }

    Resource* Get() const { return resource; }
    Resource& operator*() const { return *resource; }
    Resource* operator->() const { return resource; }
    long UseCount() const { return ctrlBlock ? ctrlBlock->sharedCount : 0; }
    ControlBlock<Resource>* getCtrlBlock() const { return ctrlBlock; }
};

template <typename Resource>
class WeakPtr {
private:
    Resource* resource;
    ControlBlock<Resource>* ctrlBlock;

public:
    WeakPtr() : resource(nullptr), ctrlBlock(nullptr) {}

    WeakPtr(const WeakPtr<Resource>& rhs) : resource(rhs.resource), ctrlBlock(rhs.ctrlBlock) {
        if (ctrlBlock) {
            ctrlBlock->weakCount++;
        }
    }

    WeakPtr(const SharedPtr<Resource>& rhs) : resource(rhs.Get()), ctrlBlock(rhs.getCtrlBlock()) {
        if (ctrlBlock) {
            ctrlBlock->weakCount++;
        }
    }

    ~WeakPtr() {
        if (ctrlBlock && --ctrlBlock->weakCount == 0 && ctrlBlock->sharedCount == 0) {
            delete ctrlBlock;
        }
    }

    void Reset() {
        *this = WeakPtr();
    }

    void Swap(WeakPtr<Resource>& rhs) {
        std::swap(resource, rhs.resource);
        std::swap(ctrlBlock, rhs.ctrlBlock);
    }

    long UseCount() const { return ctrlBlock ? ctrlBlock->sharedCount : 0; }
    bool Expired() const { return UseCount() == 0; }

    SharedPtr<Resource> Lock() const {
        if (Expired()) {
            return SharedPtr<Resource>();
        }
        return SharedPtr<Resource>(*this);
    }
};

template <typename Resource>
SharedPtr<Resource>::SharedPtr(const WeakPtr<Resource>& rhs) : resource(rhs.resource), ctrlBlock(rhs.ctrlBlock) {
    if (ctrlBlock && ctrlBlock->sharedCount != 0) {
        ctrlBlock->sharedCount++;
    }
    else {
        resource = nullptr;
        ctrlBlock = nullptr;
    }
}
