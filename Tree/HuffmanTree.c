#include <stdio.h>
#include <stdlib.h>
#include  <string.h>

#define MAX_NODES 100  // maximum numbers of nodes
#define MAX_CODE_LEN 100   // maximum code length

typedef struct {
    char symbol;
    int weight;
    int parent;  // parent node index, initial value is -1
    int left;  // left child node index
    int right;  // right child node index
} HuffmanNode;

typedef struct {
    char symbol;
    char code[MAX_CODE_LEN];  // corresponding HUffman code
} HuffmanCode;

// construct Huffman tree
void buildHuffmanTree(HuffmanNode nodes[], int n) {
    int totalNodes = 2 * n -1;  // total numbers of nodes
    for (int i = n; i < totalNodes; i++) {
        // find the two nodes with smallest weight
        int min1 = -1, min2 = -1;  // min1 and min2 are used to store the indexes of the two nodes with the smallest weights, and the initial value -1 means that no node is currently selected
        for (int j = 0; j < i; j++) {
            if (nodes[j].parent == -1) {  // nodes thst haven't been merged 
                if (min1 == -1 || nodes[j].weight < nodes[min1].weight) {
                    min2 = min1;
                    min1 = j;
                } else if (min2 == -1 || nodes[j].weight < nodes[min2].weight) {
                    min2 = j;
                }
            }//if
        }//for(j)
        // merge the two nodes with smallest weight
        nodes[i].weight = nodes[min1].weight + nodes[min2].weight;
        nodes[i].left = min1;
        nodes[i].right = min2;
        nodes[min1].parent = i;
        nodes[min2].parent = i;
    }//for(i)
}//buildHuffmanTree

// generate Huffman code
void generateHuffmanCodes(HuffmanNode nodes[], int n, HuffmanCode codes[]) {

}