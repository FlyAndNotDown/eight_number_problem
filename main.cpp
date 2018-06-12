#include <iostream>
#include "Node.h"
#include <list>
using namespace std;

int main() {

    // 输入初始节点
    int inputs[9];
    cout << "请输入初始节点 (3x3 数组，0 表示该格为空)" << endl;
    for (int i = 0; i < 9; i++) cin >> inputs[i];

    // 定义初始节点和结束节点
    Node* startNode = new Node(inputs);
    Node* endNode = new Node(new int [9] {1, 2 ,3, 8, 0, 4, 7, 6, 5});

    // 输出一哈结束节点
    cout << endl << "结束节点: " << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) cout << endNode->getArea()[i * 3 + j] << " ";
        cout << endl;
    }
    cout << endl;

    // 定义open表和closed表
    list<Node*> open, closed;

    // 将初始节点推入open表
    open.push_back(startNode);

    // 定义成功状态
    bool success = false;

    // 开始查找
    while (!open.empty()) {
        // 取出open表第一个元素
        Node *move = open.front();
        open.pop_front();

        // 如果搜索深度超过了设定值，则跳出并判断失败
        bool jump = false;
        for (Node *node : open) {
            if (node->getDepth() > 18) {
                jump = true;
                break;
            }
        }
        if (jump) break;

        // 将其移入closed表
        closed.push_back(move);

        // 如果其与结束节点相同，则查找成功并结束
        if (move->equal(endNode)) {
            success = true;
            break;
        }

        // 将节点扩展并且加入open表
        if (move->topExtendable()) {
            Node *ex = move->topExtend();
            if (!ex->inList(&open) && !ex->inList(&closed)) open.push_back(ex);
        }
        if (move->bottomExtendable()) {
            Node *ex = move->bottomExtend();
            if (!ex->inList(&open) && !ex->inList(&closed)) open.push_back(ex);
        }
        if (move->leftExtendable()) {
            Node *ex = move->leftExtend();
            if (!ex->inList(&open) && !ex->inList(&closed)) open.push_back(ex);
        }
        if (move->rightExtendable()) {
            Node *ex = move->rightExtend();
            if (!ex->inList(&open) && !ex->inList(&closed)) open.push_back(ex);
        }

        // 将open表排序
        open.sort([=](Node *a, Node *b) -> bool {
            return a->evaluation(endNode) < b->evaluation(endNode);
        });
    }

    if (success) {
        // 统计步骤数量并输出结果
        int count = 0;
        Node* result = closed.back();
        list<Node *> l;
        while (result) {
            l.push_back(result);
            count++;
            result = result->getParent();
        }
        cout << "搜索成功!" << endl << "步骤数(加上起止): " << count << endl;
        cout << "详细步骤: " << endl;
        while (!l.empty()) {
            Node* front = l.back();
            l.pop_back();
            for (int i = 0; i < 9; i++) cout << front->getArea()[i] << " ";
            cout << endl;
        }
    } else {
        cout << "搜索失败!在指定搜索深度内没能完成搜索!" << endl;
    }

    return 0;

}