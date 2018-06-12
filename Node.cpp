//
// Created by John Kindem on 2018/6/12.
//

#include "Node.h"

Node::Node(int *area) {
    for (int i = 0; i < 9; i++)
        this->area[i] = area[i];
    this->depth = 0;
    this->parent = nullptr;
}

Node::Node(int *area, int depth, Node *parent) {
    for (int i = 0; i < 9; i++)
        this->area[i] = area[i];
    this->depth = depth;
    this->parent = parent;
}

int* Node::getArea() {
    return this->area;
}

int Node::getDepth() {
    return this->depth;
}

Node* Node::getParent() {
    return this->parent;
}

bool Node::equal(Node *another) {
    for (int i = 0; i < 9; i++) {
        if (this->area[i] != another->area[i]) return false;
    }
    return true;
}

int Node::getZeroLocation() {
    for (int i = 0; i < 9; i++) {
        if (this->area[i] == 0) return i;
    }
    return -1;
}

bool Node::topExtendable() {
    return this->getZeroLocation() / 3 > 0;
}

bool Node::bottomExtendable() {
    return this->getZeroLocation() / 3 < 2;
}

bool Node::leftExtendable() {
    return this->getZeroLocation() % 3 > 0;
}

bool Node::rightExtendable() {
    return this->getZeroLocation() % 3 < 2;
}

Node* Node::topExtend() {
    int area[9];
    for (int i = 0; i < 9; i++) area[i] = this->area[i];

    int zero = this->getZeroLocation();
    int row = zero / 3;
    int col = zero % 3;

    int temp = area[zero];
    area[zero] = area[(row - 1) * 3 + col];
    area[(row - 1) * 3 + col] = temp;

    Node* node = new Node(area, this->depth + 1, this);

    return node;
}

Node* Node::bottomExtend() {
    int area[9];
    for (int i = 0; i < 9; i++) area[i] = this->area[i];

    int zero = this->getZeroLocation();
    int row = zero / 3;
    int col = zero % 3;

    int temp = area[zero];
    area[zero] = area[(row + 1) * 3 + col];
    area[(row + 1) * 3 + col] = temp;

    Node* node = new Node(area, this->depth + 1, this);

    return node;
}

Node* Node::leftExtend() {
    int area[9];
    for (int i = 0; i < 9; i++) area[i] = this->area[i];

    int zero = this->getZeroLocation();
    int row = zero / 3;
    int col = zero % 3;

    int temp = area[zero];
    area[zero] = area[row * 3 + (col - 1)];
    area[row * 3 + (col - 1)] = temp;

    Node* node = new Node(area, this->depth + 1, this);

    return node;
}

Node* Node::rightExtend() {
    int area[9];
    for (int i = 0; i < 9; i++) area[i] = this->area[i];

    int zero = this->getZeroLocation();
    int row = zero / 3;
    int col = zero % 3;

    int temp = area[zero];
    area[zero] = area[row * 3 + (col + 1)];
    area[row * 3 + (col + 1)] = temp;

    Node* node = new Node(area, this->depth + 1, this);

    return node;
}

int Node::evaluation(Node *endNode) {
    int n = 0;
    for (int i = 0; i < 9; i++) {
        if (this->area[i] != endNode->getArea()[i]) n++;
    }
    return this->depth + n;
}