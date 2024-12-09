#include <stdio.h>
#include <stdlib.h>
#include  <string.h>

#define MAX_NODES 100  // 哈夫曼树中允许的最大节点数
#define MAX_CODE_LEN 100   // 哈夫曼编码的最大长度

// 哈夫曼树节点的结构体
typedef struct { // 符号和权重由用户输入，父节点和左右子节点在主函数中被初始化为-1
    char symbol; // 符号
    int weight; // 权重
    int parent;  // 父节点索引，初始化为-1
    int left;  // 左子节点索引
    int right;  // 右子节点索引
} HuffmanNode;

// 定义哈夫曼编码的结构体
typedef struct {
    char symbol; // 符号
    char code[MAX_CODE_LEN];  // 符号对应的哈夫曼编码
} HuffmanCode;

// 构建哈夫曼树
void buildHuffmanTree(HuffmanNode nodes[], int n) {
    int totalNodes = 2 * n -1;  // 哈夫曼树的总节点数=n个叶子节点+（n-1）个内部节点（一共n个叶子节点，每两个叶子节点合并一次后，生成一个内部节点，少一个叶子节点，合并n-1次后，只剩下了根节点，所以内部节点有n-1个）

    for (int i = n; i < totalNodes; i++) { // for循环的索引i从第一个内部节点开始遍历n-1个内部节点
        int min1 = -1, min2 = -1;  // 存储权值最小和次小节点的索引，初始值为-1表示未选中节点

        for (int j = 0; j < i; j++) {  // j从第一个叶子节点开始遍历，遍历到当前的内部节点
            if (nodes[j].parent == -1) {  // 只有未被合并的节点才参与选择（符号和权重由用户输入，父节点和左右子节点在主函数中被初始化为-1）                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
                if (min1 == -1 || nodes[j].weight < nodes[min1].weight) {
                    min2 = min1; // 如果当前的权值更小，则把原来的最小变为次小，接着把当前值赋给min1作为最小 。
                    min1 = j; // 刚开始默认第一个值是最小的，接着在进行比较，如果遇到权值更小的则更新
                } else if (min2 == -1 || nodes[j].weight < nodes[min2].weight) {
                    min2 = j; // 刚开始如果第二的值比第一个值大，则默认第二个值是次小的，接着进行比较，如果遇到权值更小的则更新
                }
            }//if
        }//for(j)

        // 合并这两个权重最小的节点，生成一个新节点
        nodes[i].weight = nodes[min1].weight + nodes[min2].weight; // 新节点的权重为两个子节点权重之和
        nodes[i].left = min1; // 新节点的左子节点
        nodes[i].right = min2; // 新节点的右子节点
        nodes[min1].parent = i; // 更新左子节点的父节点为新节点
        nodes[min2].parent = i; // 更新右子节点的父节点为新节点
    }//for(i)
}//buildHuffmanTree

// 生成哈夫曼编码
void generateHuffmanCodes(HuffmanNode nodes[], int n, HuffmanCode codes[]) {
    char tempCode[MAX_CODE_LEN];
    for (int i = 0; i < n; i++) {
        int current = i;
        int parent = nodes[current].parent;
        int codeLen = 0;

        // 遍历树以生成编码
        while (parent != -1) {
            if (nodes[parent].left == current) {
                tempCode[codeLen++] = '0';
            } else {
                tempCode[codeLen++] = '1';
            }
            current = parent;
            parent = nodes[current].parent;
        }

        tempCode[codeLen] = '\0';

        // 反转生成的代码
        for (int j = 0; j < codeLen; j++) {
            codes[i].code[j] = tempCode[codeLen - j - 1];
        }
        codes[i].code[codeLen] = '\0';
        codes[i].symbol = nodes[i].symbol;
    }
}

// 打印哈夫曼树的结构和编码
void printHuffmanTree(HuffmanNode nodes[], int n) {
    printf("哈夫曼树的结构：\n");
    for (int i =0; i < 2 * n - 1; i++) {
        printf("Node %d: Symbol=%s, Weight=%d, Parent=%d, Left=%d, Right=%d\n",
       i,
       nodes[i].symbol == '\0' ? "Internal" : &nodes[i].symbol,
       nodes[i].weight,
       nodes[i].parent,
       nodes[i].left,
       nodes[i].right);
    }
}

void printHuffmanCodes(HuffmanCode codes[], int n) {
    printf("\n哈夫曼编码：\n");
    for (int i = 0; i < n; i++) {
        printf("Symbol: %c, Code: %s\n", codes[i].symbol, codes[i].code);
    }
}

int main() {
    int n;
    printf("请输入符号的个数：");
    scanf("%d", &n);

    HuffmanNode nodes[MAX_NODES];
    HuffmanCode codes[MAX_NODES];

    printf("输入符号和他们的权重：\n");
    for (int i = 0; i < n; i++) {  // nodes[]前n个为叶子节点，接下来的n-1个为内部节点
        scanf(" %c %d", &nodes[i].symbol, &nodes[i].weight);// 在 %c 前加空格，跳过空白字符
        nodes[i].parent = -1;
        nodes[i].left = -1;
        nodes[i].right = -1;
    }

    // 初始化内部节点
    for  (int i = n; i < 2 * n - 1; i++) {
        nodes[i].symbol = '\0'; // 内部节点没有符号
        nodes[i].weight = 0;
        nodes[i].parent = -1;
        nodes[i].left = -1;
        nodes[i].right = -1;
    }

    buildHuffmanTree(nodes, n);
    generateHuffmanCodes(nodes, n, codes);

    printHuffmanTree(nodes, n);
    printHuffmanCodes(codes, n);

    return 0;
}