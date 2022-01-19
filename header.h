#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "raylib.h"

#define SPRITE_EDGE_SIZE 64
#define FIELD_CELL_SIZE 100
#define CANVAS_WIDTH 800
#define CANVAS_HEIGHT 800

#define FEILD_WIDTH CANVAS_WIDTH / FIELD_CELL_SIZE
#define FEILD_HEIGHT CANVAS_HEIGHT / FIELD_CELL_SIZE

typedef enum Landscape
{
    ROAD = 0,
    GROUND,
    BUSH,
    TREE,
    WATER,
    AMOUNT
} Landscape;

typedef struct Data
{
    int x;
    int y;
} Data;

typedef struct Field
{
    int cell_type;
    int checked;
    int pushed;
    Data prev;
} Field;

typedef struct Node
{
    Data data;
    struct Node *next;
    struct Node *prev;
} Node;

//====================================================================================
// Function declaration
void draw(Field arr[][FEILD_WIDTH], Data goal, Data start, int end_of_searching, Data current_data, Node * list);
void draw_field(Field arr[][FEILD_WIDTH], Data goal, Data start, Data current_data);
void draw_path(Field arr[][FEILD_WIDTH], Data goal);
void _draw_checked(int j, int i);
void _draw_landscape(int j, int i, Field arr[][FEILD_WIDTH]);
void highlight_cell(int j, int i);
void init_field(Field arr[][FEILD_WIDTH]);
void set_walls(Field arr[][FEILD_WIDTH]);
Node *init_node(void);
Node *add_node(int x, int y);
void push_to_queue(int x, int y, Node *list);
Data pull_from_queue(Node *list);
void print_list(Node *list);
int set_graph(int start_x, int start_y, int end_x, int end_y, Field arr[][FEILD_WIDTH], Node *list);
int list_is_empty(Node *list);
void check_neighbors(int x, int y, Field arr[][FEILD_WIDTH], Node *list);
void _check_right(int x, int y, Field arr[][FEILD_WIDTH], Node *list);
void _check_left(int x, int y, Field arr[][FEILD_WIDTH], Node *list);
void _check_down(int x, int y, Field arr[][FEILD_WIDTH], Node *list);
void _check_up(int x, int y, Field arr[][FEILD_WIDTH], Node *list);
void _check_diagonal(int x, int y, Field arr[][FEILD_WIDTH], Node *list);
void _check_diagonal_left_up(int x, int y, Field arr[][FEILD_WIDTH], Node *list);
void _check_diagonal_left_down(int x, int y, Field arr[][FEILD_WIDTH], Node *list);
void _check_diagonal_right_up(int x, int y, Field arr[][FEILD_WIDTH], Node *list);
void _check_diagonal_right_down(int x, int y, Field arr[][FEILD_WIDTH], Node *list);

void chech_check(Field arr[][FEILD_WIDTH]);
//====================================================================================
