#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>

/* Project Desc in README.txt
 */

typedef struct Node {
  struct Node *left;
  struct Node *right;
  struct Node *parent;
  int value;
  int radius;
  Vector2 pos;
  Color colour;
} Node;

int main() {
  int const window_width = 1152;
  int const window_height = 864;
  InitWindow(window_width, window_height, "ProjectName");
  SetTargetFPS(60);
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    EndDrawing();
  }
  CloseWindow();
  return 0;
}

