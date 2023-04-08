// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_
template<typename type>
class TStack {
 private:
    static constexpr int kSize = 100;
    type arr[kSize];
    int top = -1;

 public:
    TStack() = default;
    type get() const {
        return arr[top];
    }
    bool isEmpty() const {
        return top == -1;
    }
    bool isFull() const {
        return top == kSize - 1;
    }
    void pop() {
        if (!isEmpty()) {
            --top;
        }
    }
    void push(type item) {
        if (!isFull()) {
            arr[++top] = item;
        }
    }
};


#endif  // INCLUDE_TSTACK_H_
