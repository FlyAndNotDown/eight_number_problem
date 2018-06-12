//
// Created by John Kindem on 2018/6/12.
//

#ifndef EIGHT_NUMBER_PROBLEM_NODE_H
#define EIGHT_NUMBER_PROBLEM_NODE_H


class Node {
private:
    // 节点内区块信息
    int area[9];
    // 该节点位于的搜索深度
    int depth;
    // 该节点的父节点
    Node* parent;

    // 获取节点区块内 0 的位置
    int getZeroLocation();
public:
    // 构造
    Node(int *area);
    Node(int *area, int depth, Node *parent);

    // getter
    int* getArea();
    int getDepth();
    Node* getParent();

    // 比较两个节点的区块信息是否相同
    bool equal(Node*);

    // 某个方向是否可扩展
    bool topExtendable();
    bool bottomExtendable();
    bool leftExtendable();
    bool rightExtendable();

    // 获取向某个方向扩展而得到的子节点
    Node* topExtend();
    Node* bottomExtend();
    Node* leftExtend();
    Node* rightExtend();

    // 估价函数
    int evaluation(Node*);
};


#endif //EIGHT_NUMBER_PROBLEM_NODE_H
