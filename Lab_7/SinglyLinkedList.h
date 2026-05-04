#pragma once
#include <iostream>
#include <memory>
#include <stdexcept>
#include "Node.h"

template <typename T>
class SinglyLinkedList {
private:
    std::shared_ptr<Node<T>> head;
    size_t listSize;

public:
    SinglyLinkedList() : head(nullptr), listSize(0) {}

    bool empty() const {
        return listSize == 0;
    }

    size_t size() const {
        return listSize;
    }

    void push_front(const T& value) {
        auto newNode = std::make_shared<Node<T>>(value);
        newNode->next = head;
        head = newNode;
        listSize++;
    }

    void push_back(const T& value) {
        auto newNode = std::make_shared<Node<T>>(value);

        if (empty()) {
            head = newNode;
        } else {
            auto current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }

        listSize++;
    }

    void pop_front() {
        if (empty()) {
            throw std::runtime_error("List is empty");
        }

        head = head->next;
        listSize--;
    }

    void pop_back() {
        if (empty()) {
            throw std::runtime_error("List is empty");
        }

        if (listSize == 1) {
            head = nullptr;
        } else {
            auto current = head;
            while (current->next->next) {
                current = current->next;
            }
            current->next = nullptr;
        }

        listSize--;
    }

    T& at(size_t index) {
        if (index >= listSize) {
            throw std::out_of_range("Index out of range");
        }

        auto current = head;
        for (size_t i = 0; i < index; i++) {
            current = current->next;
        }

        return current->data;
    }

        void insert(size_t index, const T& value) {
            if (index > listSize) {
                throw std::out_of_range("Index out of range");
            }

            if (index == 0) {
                push_front(value);
                return;
            }

            auto newNode = std::make_shared<Node<T>>(value);
            auto current = head;

            for (size_t i = 0; i < index - 1; i++) {
                current = current->next;
            }

            newNode->next = current->next;
            current->next = newNode;
            listSize++;
        }

    void remove(size_t index) {
        if (index >= listSize) {
            throw std::out_of_range("Index out of range");
        }

        if (index == 0) {
            pop_front();
            return;
        }

        auto current = head;

        for (size_t i = 0; i < index - 1; i++) {
            current = current->next;
        }

        current->next = current->next->next;
        listSize--;
    }

    int find(const T& value) const {
        auto current = head;
        int index = 0;

        while (current) {
            if (current->data == value) {
                return index;
            }

            current = current->next;
            index++;
        }

        return -1;
    }

    friend std::ostream& operator<<(std::ostream& os, const SinglyLinkedList<T>& list) {
        auto current = list.head;

        while (current) {
            os << current->data << " ";
            current = current->next;
        }

        return os;
    }
};