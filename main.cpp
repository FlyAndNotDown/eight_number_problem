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

        // 如果搜索深度超过了 50，则跳出并判断失败
        for (Node *node : open) {
            if (node->getDepth() > 20) break;
        }

        // 将其移入closed表
        closed.push_back(move);

        // 如果其与结束节点相同，则查找成功并结束
        if (move->equal(endNode)) {
            success = true;
            break;
        }

        // 将节点扩展并且加入open表
        if (move->topExtendable()) open.push_back(move->topExtend());
        if (move->bottomExtendable()) open.push_back(move->bottomExtend());
        if (move->leftExtendable()) open.push_back(move->leftExtend());
        if (move->rightExtendable()) open.push_back(move->rightExtend());

        // 将open表排序
        open.sort([=](Node *a, Node *b) -> bool {
            return a->evaluation(endNode) < b->evaluation(endNode);
        });
    }

    if (success) {
        int count = -1;
        Node *result = closed.back();
        while (result) {
            count++;
            result = result->getParent();
        }
        cout << "搜索成功!" << endl << "步骤数: " << count << endl;
    } else {
        cout << "搜索失败!" << endl;
    }

    return 0;

}