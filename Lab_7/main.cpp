#include <iostream>
#include "SinglyLinkedList.h"
#include "DoublyLinkedList.h"

int main() {
    try {
        SinglyLinkedList<int> singleList;

        singleList.push_back(10);
        singleList.push_back(20);
        singleList.push_front(5);
        singleList.insert(1, 7);

        std::cout << "Singly linked list: " << singleList << std::endl;
        std::cout << "Size: " << singleList.size() << std::endl;
        std::cout << "Element at index 2: " << singleList.at(2) << std::endl;
        std::cout << "Index of 20: " << singleList.find(20) << std::endl;

        singleList.remove(1);
        singleList.pop_back();

        std::cout << "After removing elements: " << singleList << std::endl;

        std::cout << "------------------------" << std::endl;

        DoublyLinkedList<std::string> doubleList;

        doubleList.push_back("One");
        doubleList.push_back("Two");
        doubleList.push_front("Zero");
        doubleList.insert(2, "Middle");

        std::cout << "Doubly linked list: " << doubleList << std::endl;
        std::cout << "Size: " << doubleList.size() << std::endl;
        std::cout << "Element at index 1: " << doubleList.at(1) << std::endl;
        std::cout << "Index of Two: " << doubleList.find("Two") << std::endl;

        doubleList.remove(2);
        doubleList.pop_front();

        std::cout << "After removing elements: " << doubleList << std::endl;

    } catch (const std::exception& error) {
        std::cout << "Error: " << error.what() << std::endl;
    }

    return 0;
}