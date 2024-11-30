#include <stdio.h>
#include <stdlib.h> // malloc

// 定义二叉树节点结构
typedef struct TreeNode {
    char value;              // 节点值
    struct TreeNode* left;   // 左子树指针
    struct TreeNode* right;  // 右子树指针
} TreeNode;

// 创建新节点的函数
TreeNode* createNode(char val) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->value = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 定义栈结构，用于存储树节点
typedef struct Stack {
    TreeNode** arr;  // 指针数组，每个元素是指向二叉树节点的指针
    int top;         // 栈顶指针
    int capacity;    // 栈容量
} Stack;

// 初始化栈
void initStack(Stack* S, int capacity) {
    S->top = -1;
    S->capacity = capacity;
    S->arr = (TreeNode**)malloc(sizeof(TreeNode*) * capacity);
}

// 栈的压入操作
void push(Stack* S, TreeNode* node) {
    S->arr[++(S->top)] = node;
}

// 栈的弹出操作
TreeNode* pop(Stack* S) {
    return S->arr[(S->top)--];
}

// 获取栈顶元素
TreeNode* top(Stack* S) {
    return S->arr[S->top];
}

// 判断栈是否为空
int isEmpty(Stack* S) {
    return S->top == -1;
}

// 根据先序遍历构建二叉树（非递归实现）
TreeNode* buildTree(const char* preorder) {
    if (preorder[0] == '\0') return NULL;  // 空输入直接返回空树

    Stack stack;
    initStack(&stack, 100);  // 初始化栈

    TreeNode* root = createNode(preorder[0]);  // 创建根节点
    push(&stack, root);  // 根节点入栈

    TreeNode* current = root;  // 当前节点
    int expectRight = 0;       // 标志当前是否期待右子节点

    for (int i = 1; preorder[i] != '\0'; i++) {
        char val = preorder[i];  // 当前字符

        if (val == '#') {
            // 如果是空节点
            if (expectRight) {
                pop(&stack);  // 如果当前节点的右子节点也为null，出栈
                if (!isEmpty(&stack)) {
                current = top(&stack);
                }
            }
            expectRight = 1;  // 下一个节点应为右子节点
            continue;
        }

        TreeNode* newNode = createNode(val);  // 创建新节点
        if (!expectRight) {
            // 如果当前节点未设置左子节点，则设置为左子节点
            current->left = newNode;
        } else {
            // 否则，设置为右子节点
            current->right = newNode;
            pop(&stack);  // 当前节点的左右子节点已完成处理
        }

        push(&stack, newNode);  // 新节点入栈
        current = newNode;      // 更新当前节点
        expectRight = 0;        // 下一个节点默认期待左子节点
    }

    return root;  // 返回构建完成的树的根节点
}

// 层序遍历二叉树
void levelOrderTraversal(TreeNode* root) {
    if (root == NULL) {
        printf("二叉树为空。\n");
        return;
    }

    TreeNode* queue[100];  // 创建队列
    int front = 0, rear = 0;  // 队列头尾指针
    queue[rear++] = root;     // 根节点入队

    while (front < rear) {  // 当队列非空时继续遍历
        TreeNode* node = queue[front++];  // 获取队头节点
        printf("%c ", node->value);       // 输出节点值

        if (node->left) queue[rear++] = node->left;  // 左子节点入队
        if (node->right) queue[rear++] = node->right;  // 右子节点入队
    }
}

// 计算二叉树的深度
int treeDepth(TreeNode* root) {
    if (root == NULL) return 0;  // 空树深度为0

    TreeNode* queue[100];  // 创建队列
    int front = 0, rear = 0;  // 队列头尾指针
    queue[rear++] = root;  // 根节点入队
    int depth = 0;  // 初始化深度为0

    while (front < rear) {  // 当队列非空时继续遍历
        int levelSize = rear - front;  // 当前层节点数
        depth++;  // 深度加1

        for (int i = 0; i < levelSize; i++) {
            TreeNode* node = queue[front++];  // 获取队头节点
            if (node->left) queue[rear++] = node->left;  // 左子节点入队
            if (node->right) queue[rear++] = node->right;  // 右子节点入队
        }
    }

    return depth;  // 返回树深度
}

int main() {
    const char* preorder = "AB#D##C##";  // 先序遍历序列，#表示空节点
    TreeNode* root = buildTree(preorder);  // 构建二叉树

    printf("层序遍历结果：");
    levelOrderTraversal(root);  // 层序遍历二叉树
    printf("\n");

    printf("二叉树的深度为：%d\n", treeDepth(root));  // 计算并输出深度

    return 0;
}