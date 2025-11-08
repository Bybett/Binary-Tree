#include "raylib.h"
#include "../include/globals.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define RADIUS 12
#define Y_OFFSET 20
#define X_OFFSET 20

typedef struct Node {
  struct Node *left; // Left will point to the child with the lower value.
  struct Node *right;
  int value; // Raylib will display nodes as cirlces. Each node will display their value.
  int depth;
} Node;

typedef struct Circle {
  int pos_x;
  int pos_y;
  int radius;
  Color colour;
} Circle;

typedef struct VisualNode {
  Circle circle;
  Node *node;
} VisualNode;


void printTree(Node *node) {
  if (node->left != NULL) printTree(node->left);
  printf("val:%i || dep:%i\n", node->value, node->depth);
  if (node->right != NULL) printTree(node->right);
}


void bInsert(Node *node, int value) {
  if (node->value == value) {
    return;
  }
  // If the value to insert is smaller than the node's value, check the child and make it if needed
  // and then insert the value or traverse the tree.
  if (node->value > value) {
    if (!node->left) {
      node->left = (Node *)malloc(sizeof(Node));
      node->left->value = value;
      node->left->left = NULL;
      node->left->right = NULL;
      node->left->depth = node->depth + 1;
    } else {
      bInsert(node->left, value);
    }
  // If the value to insert is bigger than the node's value, check the child and make if needed
  // and insert the value or traverse the tree.
  } else if (node->value < value) {
    if (!node->right) {
      node->right = (Node *)malloc(sizeof(Node));
      node->right->value = value;
      node->right->left = NULL;
      node->right->right = NULL;
      node->right->depth = node->depth + 1;
    } else {
      bInsert(node->right, value);
    }
  }
}


// TODO: Finish this function. Seg fault &|| free() error in here
void generateTree(Node *node, VisualNode **tree, int *tree_size) {
  // No left node? We've found a leaf to add to the visual tree.
  if (!node->left) {
    printf("Leaf found...\n");
    *tree_size = *tree_size + 1;
    printf("====size:%i====\n", *tree_size);
    VisualNode *temp = realloc(*tree, *tree_size * sizeof(VisualNode)); // Make the tree list + 1 longer
    printf("Test 1\n");
    if (!temp) {
      printf("Error re-allocating tree... exiting\n"); 
      exit(1);
    }

    printf("Test 2\n");
    printf("====Size:%i\n", *tree_size);
    *tree = temp;
    printf("Test 3\n");
    VisualNode prev_node = (*tree)[*tree_size - 2]; // We will need some data from the node in tree[tree_size - 2]
    // Current working node, the most recently added one. The reason for the &(*tree) is to get the address of the item at the desried index. tree, is a ptr to a ptr.
    VisualNode *current_node = &(*tree)[*tree_size - 1];
    printf("VisualNodes prev_node and current_node made...\n");
    current_node->node = node;
    current_node->circle.radius = RADIUS;
    printf("Checking if current_node is Right...\n");

    if (prev_node.node->right) {
      printf("Is Right child...\n");
      current_node->circle.pos_x = prev_node.circle.pos_x - X_OFFSET;
      current_node->circle.pos_y = prev_node.circle.pos_y;
    } else {
      printf("Not Right child...\n");
      current_node->circle.pos_x = prev_node.circle.pos_x + X_OFFSET;
      current_node->circle.pos_y = prev_node.circle.pos_y + RADIUS + Y_OFFSET;
    }

  }
  printf("====SIZE:%i====\n", *tree_size);
  printf("Exited !node->left...\n");

  // If there is a left node, we till have further to traverse until we find a leaf
  if (node->left) {generateTree(node->left, tree, tree_size);}

  if (node->right) {generateTree(node->right, tree, tree_size);}
}


void renderTree(VisualNode *tree, int *tree_size) {
  for (int i = 0; i < *tree_size; i++) {
    VisualNode current_node = tree[i];
    DrawCircle(current_node.circle.pos_x, current_node.circle.pos_y, RADIUS, BLACK);
  }
}


int main() {
  Node *root = (Node *)malloc(sizeof(Node));
  root->value = 7;
  root->depth = 0;

  int size = 1;
  int *tree_size = &size;
  VisualNode *tree = (VisualNode *)malloc(sizeof(VisualNode));
  tree[0].circle.pos_x = WINDOW_WIDTH / 2;
  tree[0].circle.pos_y = RADIUS + (Y_OFFSET * 2);
  tree[0].node = root;

  bInsert(root, 8);
  bInsert(root, 3);
  bInsert(root, 11);
  bInsert(root, 22);
  bInsert(root, 8);
  bInsert(root, 4);

  //printTree(root);
  generateTree(root, &tree, tree_size);

  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Unsorted Binary Search Tree");
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(WHITE);
    renderTree(tree, tree_size);
    DrawCircle(tree[0].circle.pos_x, tree[0].circle.pos_y, RADIUS, BLACK);
    EndDrawing();
  }
  CloseWindow();
  return 0;
}

