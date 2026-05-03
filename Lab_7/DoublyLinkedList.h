#pragma once
#include <iostream>
#include <memory>
#include <stdexcept>
#include "Node.h"

template <typename T>
class DoublyLinkedList {
private:
    std::shared_ptr<Node<T>> head;
    std::shared_ptr<Node<T>> tail;
    size_t listSize;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), listSize(0) {}

    bool empty() const {
        return listSize == 0;
    }

    size_t size() const {
        return listSize;
    }

    void push_front(const T& value) {
        auto newNode = std::make_shared<Node<T>>(value);

        if (empty()) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }

        listSize++;
    }

    void push_back(const T& value) {
        auto newNode = std::make_shared<Node<T>>(value);

        if (empty()) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }

        listSize++;
    }

    void pop_front() {
        if (empty()) {
            throw std::runtime_error("List is empty");
        }

        if (listSize == 1) {
            head = tail = nullptr;
        } else {
            head = head->next;
            head->prev.reset();
        }

        listSize--;
    }

    void pop_back() {
        if (empty()) {
            throw std::runtime_error("List is empty");
        }

        if (listSize == 1) {
            head = tail = nullptr;
        } else {
            tail = tail->prev.lock();
            tail->next = nullptr;
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

        if (index == listSize) {
            push_back(value);
            return;
        }

        auto newNode = std::make_shared<Node<T>>(value);
        auto current = head;

        for (size_t i = 0; i < index; i++) {
            current = current->next;
        }

        auto previous = current->prev.lock();

        previous->next = newNode;
        newNode->prev = previous;
        newNode->next = current;
        current->prev = newNode;

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

        if (index == listSize - 1) {
            pop_back();
            return;
        }

        auto current = head;

        for (size_t i = 0; i < index; i++) {
            current = current->next;
        }

        auto previous = current->prev.lock();
        auto nextNode = current->next;

        previous->next = nextNode;
        nextNode->prev = previous;

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

    friend std::ostream& operator<<(std::ostream& os, const DoublyLinkedList<T>& list) {
        auto current = list.head;

        while (current) {
            os << current->data << " ";
            current = current->next;
        }

        return os;
    }
};