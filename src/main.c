#include "raylib.h"
#include "../include/globals.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define RADIUS 16.0
#define X_OFFSET (RADIUS)
#define Y_OFFSET (RADIUS * 3)

typedef struct Circle {
  float pos_x;
  float pos_y;
  Color colour;
} Circle;

typedef struct Node {
  struct Node *left; // Left will point to the child with the lower value.
  struct Node *right;
  struct Node *parent;
  int value; // Raylib will display nodes as cirlces. Each node will display their value.
  int depth;
  Circle circle;
} Node;


void printTree(Node *node) {
  if (node->left != NULL) printTree(node->left);
  printf("val:%i || dep:%i pos_x: %f || pos_y:%f\n", node->value, node->depth, node->circle.pos_x, node->circle.pos_y);
  if (node->right != NULL) printTree(node->right);
}


void bInsert(Node *node, int value) {
  if (node->value == value) {
    return;
  }
  // If the value to insert is smaller than the node's value, check the child and make it if needed
  // and then insert the value, or traverse the tree if there is already a child.
  if (node->value > value) {
    if (!node->left) {
      node->left = (Node *)malloc(sizeof(Node));
      node->left->value = value;
      node->left->left = NULL;
      node->left->right = NULL;
      node->left->depth = node->depth + 1;
      node->left->circle.colour = RED;
      // This is to position the child node in the middle of its parent node and its grandparent
      node->left->circle.pos_x = (node->circle.pos_x - RADIUS) - (((float)WINDOW_WIDTH) / pow(2, node->depth + 2));
      node->left->circle.pos_y = Y_OFFSET + (Y_OFFSET * node->left->depth * 1.50);
    } else {
      bInsert(node->left, value);
    }

  // If the value to insert is bigger than the node's value, check the child and make if it needed
  // then insert the value, or traverse the tree if there is already a child.
  } else if (node->value < value) {
    if (!node->right) {
      node->right = (Node *)malloc(sizeof(Node));
      node->right->value = value;
      node->right->left = NULL;
      node->right->right = NULL;
      node->right->depth = node->depth + 1;
      node->right->circle.colour = BLUE;
      // This is to position the child node in the middle of its parent node and its grandparent
      node->right->circle.pos_x = (node->circle.pos_x + RADIUS) + (((float)WINDOW_WIDTH) / pow(2, node->depth + 2));
      node->right->circle.pos_y = Y_OFFSET + (Y_OFFSET * node->right->depth * 1.5);
    } else {
      bInsert(node->right, value);
    }
  }
}


void renderTree(Node *node) {
  // Drawing the circles that represent the nodes.
  DrawCircle(node->circle.pos_x, node->circle.pos_y, RADIUS, node->circle.colour);
  char str[8];
  sprintf(str, "%d", node->value);
  // Center the text on the circle
  Vector2 text_width = MeasureTextEx(GetFontDefault(), str, 20, 2);
  DrawText(str, node->circle.pos_x - text_width.x / 2, node->circle.pos_y - text_width.y / 2, 20, BLACK);

  if (node->left) {
    // For drawin the lines between parent and child.
    DrawLine(node->circle.pos_x, node->circle.pos_y + RADIUS,
             node->left->circle.pos_x, node->left->circle.pos_y - RADIUS, BLACK);
    renderTree(node->left);
  }

  if (node->right) {
    // For drawin the lines between parent and child.
    DrawLine(node->circle.pos_x, node->circle.pos_y + RADIUS,
             node->right->circle.pos_x, node->right->circle.pos_y - RADIUS, BLACK);
    renderTree(node->right);
  }
}


int main() {
  Node *root = (Node *)malloc(sizeof(Node));
  root->value = 7;
  root->depth = 0;
  root->circle.pos_x = (float)WINDOW_WIDTH / 2;
  root->circle.pos_y = Y_OFFSET;
  root->circle.colour = PURPLE;

  bInsert(root, 1);
  bInsert(root, 3);
  bInsert(root, 11);
  bInsert(root, 22);
  bInsert(root, 8);
  bInsert(root, 4);
  bInsert(root, 13);
  bInsert(root, 6);
  bInsert(root, 17);
  bInsert(root, 12);
  bInsert(root, 21);
  bInsert(root, 16);
  bInsert(root, 23);
  bInsert(root, 5);
  printTree(root);
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Binary Search Tree: Visualizer");
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(WHITE);
    renderTree(root);
    EndDrawing();
  }
  CloseWindow();
  return 0;
}

