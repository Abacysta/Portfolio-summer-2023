#include <iostream>
#include <functional>
#include <initializer_list>
#include <memory>

template <typename T>
class LinkedList {
    struct Node {
        T data;
        std::unique_ptr<Node> next;

        Node(T value) : data(std::move(value)), next(nullptr) {}
    };

    std::unique_ptr<Node> head;
    size_t count = 0;

public:

    LinkedList() = default;

    LinkedList(LinkedList&& other) noexcept : head(std::move(other.head)), count(other.count) {
        other.count = 0;
    }

    LinkedList& operator=(LinkedList&& other) noexcept {
        if (this != &other) {
            head = std::move(other.head);
            count = other.count;
            other.count = 0;
        }
        return *this;
    }

    LinkedList(std::initializer_list<T> init) {
        for (auto it = init.begin(); it != init.end(); ++it) {
            push_front(*it);
        }
    }

    void push_front(const T& value) {
        auto newNode = std::make_unique<Node>(value);
        newNode->next = std::move(head);
        head = std::move(newNode);
        ++count;
    }

    void push_front(T&& value) {
        auto newNode = std::make_unique<Node>(std::move(value));
        newNode->next = std::move(head);
        head = std::move(newNode);
        ++count;
    }

    void pop_front() {
        if (head) {
            head = std::move(head->next);
            --count;
        }
    }

    size_t size() const {
        return count;
    }

    template <typename Func>
    void for_each(Func func) const {
        Node* current = head.get();
        while (current) {
            func(current->data);
            current = current->next.get();
        }
    }

    LinkedList<T> split_when(const std::function<bool(const T&)>& condition) {
        LinkedList<T> tail;

        Node* current = head.get();
        Node* prev = nullptr;
        while (current) {
            if (condition(current->data)) {
                if (prev) {
                    tail.head = std::move(prev->next);
                    tail.count = count - (prev - head.get()) - 1;
                    count = prev - head.get() + 1;
                }
                else {
                    tail = std::move(*this);
                }
                break;
            }
            prev = current;
            current = current->next.get();
        }

        return tail;
    }
};

int main() {
    LinkedList<int> original = { 1, 42, 3 };
    auto tail = original.split_when([](const int& value) { return value == 42; });

    std::cout << "Original: ";
    original.for_each([](int v) { std::cout << v << " "; });
    std::cout << "\n";

    std::cout << "Tail: ";
    tail.for_each([](int v) { std::cout << v << " "; });
    std::cout << "\n";

    return 0;
}
