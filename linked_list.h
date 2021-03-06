#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H

#include <iostream>
#include <stdexcept>

template <typename T>
class Node {
public:
    T data;
    Node<T>* next;

    // Constructors 
    Node<T>(T d, Node<T>* n) {
        data = d;
        next = n;
    }

    Node<T>(T d) {
        data = d;
        next = NULL;
    }

    Node<T>(Node<T>* n) {
        data = T();
        next = n;
    }

    Node<T>() {
        data = T();
        next = NULL;
    }
};

template <typename T>
class LinkedList {
public:
    Node<T>* head;
    unsigned length;

    LinkedList<T>(Node<T>* h) {
        head = h;
        length = 1;
    }

    LinkedList<T>() { 
        head = NULL;
        length = 0;
    }

    ~LinkedList<T>() {
        Node<T>* current = head;
        Node<T>* next = current->next;
        while (next != NULL) {
            delete current;
            current = next;
            next = next->next;
        }
        delete current;
    }

    Node<T>* tail() {
        if (head == NULL)
            return head;
        Node<T>* tail = head;
        while (tail->next != NULL)
            tail = tail->next;
        return tail;
    }

    void append_node(Node<T>* n) {
        if (length == 0)
            head = n;
        else
            tail()->next = n;
        ++length;
    }

   void append(T item) {
        Node<T>* node = new Node<T>(item);
        // std::cout << "ADD: node->data is " << node->data << std::endl; // debug
        append_node(node);
    }

    void remove(int index) {
        if (index < 0 || index > (length - 1) || length == 0)
            throw std::out_of_range("linked_list.h: remove(): index of out bounds.");
        if (index == 0) {
            Node<T>* old_head = head;
            head = head->next;
            delete old_head;
        } else {
            Node<T>* prev = node_at(index - 1);
            Node<T>* current = prev->next;
            prev->next = current->next;
            delete current;
        }

        --length;
    }

    Node<T>* node_at(int index) {
        if (index < 0 || index > (length - 1) || length == 0)
            throw std::out_of_range("linked_list.h: node_at(): index of out bounds.");

        Node<T>* current = head;
        while (index > 0) {
            current = current->next;
            --index;
        }

        return current;
    }

    T at(int index) {
        return node_at(index)->data;
    }

    LinkedList<T> slice(int start, int end) {
        if (start < 0 || start > (length - 1) ||
            end < 0 || end > (length - 1) || start > end)
            throw std::out_of_range("linked_list.h: slice(): index out of bounds.");

        LinkedList<T> sliced_list = LinkedList<T>();
        int i = end - start;
        Node<T>* current = this->node_at(start);
        while (i > 0) {
            sliced_list.append(current->data);
            current = current->next;
            --i;
        }

        return sliced_list;
    }

    friend std::ostream& operator<<(std::ostream& output, const LinkedList<T>& ll) {
        ll.print();
        return output;
    }

private:
    void print() const {
        Node<T>* current = head;
        std::cout << "[";
        while (current->next != NULL) {
            std::cout << current->data << ", ";
            current = current->next;
        }
        std::cout << current->data << "]";
    }
};

#endif // _LINKED_LIST_H
