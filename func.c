#include "header.h"

void draw(Field arr[][FEILD_WIDTH], Data goal, Data start, int end_of_searching, Data current_data, Node *list)
{
    draw_field(arr, goal, start, current_data);
    if (end_of_searching)
    {
        draw_path(arr, goal);
    }
    else if (!list_is_empty(list))
    {
        draw_path(arr, current_data);
    }
    else
    {
        printf("\n\nPath is not found!!!\n\n");
    }

    highlight_cell(start.y, start.x);
    highlight_cell(goal.y, goal.x);
    highlight_cell(current_data.y, current_data.x);
}

void draw_field(Field arr[][FEILD_WIDTH], Data goal, Data start, Data current_data)
{
    for (int i = 0; i < FEILD_WIDTH; i++)
    {
        for (int j = 0; j < FEILD_HEIGHT; j++)
        {
            if (arr[j][i].checked)
            {
                _draw_checked(j, i);
            }
            else
            {
                DrawRectangle(i * FIELD_CELL_SIZE, j * FIELD_CELL_SIZE, FIELD_CELL_SIZE, FIELD_CELL_SIZE, RED);
                DrawRectangle(i * FIELD_CELL_SIZE + 1, j * FIELD_CELL_SIZE + 1, FIELD_CELL_SIZE - 2, FIELD_CELL_SIZE - 2, GREEN);
            }

            _draw_landscape(j, i, arr);
        }
    }
}

void _draw_landscape(int j, int i, Field arr[][FEILD_WIDTH])
{
    if (arr[j][i].cell_type == WATER)
    {
        DrawRectangle(i * FIELD_CELL_SIZE, j * FIELD_CELL_SIZE, FIELD_CELL_SIZE, FIELD_CELL_SIZE, BLUE);
    }
    // else if (arr[j][i].cell_type == TREE)
    // {
    //     DrawRectangle(i * FIELD_CELL_SIZE, j * FIELD_CELL_SIZE, FIELD_CELL_SIZE, FIELD_CELL_SIZE, BROWN);
    // }
    // else if (arr[j][i].cell_type == BUSH)
    // {
    //     DrawRectangle(i * FIELD_CELL_SIZE, j * FIELD_CELL_SIZE, FIELD_CELL_SIZE, FIELD_CELL_SIZE, DARKGREEN);
    // }
    //  else if (arr[j][i].cell_type == GROUND)
    // {
    //     DrawRectangle(i * FIELD_CELL_SIZE, j * FIELD_CELL_SIZE, FIELD_CELL_SIZE, FIELD_CELL_SIZE, DARKBROWN);
    // }
    // else if (arr[j][i].cell_type == ROAD)
    // {
    //     DrawRectangle(i * FIELD_CELL_SIZE, j * FIELD_CELL_SIZE, FIELD_CELL_SIZE, FIELD_CELL_SIZE, DARKGRAY);
    // }
}

void highlight_cell(int j, int i)
{
    DrawRectangle(i * FIELD_CELL_SIZE, j * FIELD_CELL_SIZE, FIELD_CELL_SIZE, FIELD_CELL_SIZE, RED);
    DrawRectangle(i * FIELD_CELL_SIZE + 1, j * FIELD_CELL_SIZE + 1, FIELD_CELL_SIZE - 2, FIELD_CELL_SIZE - 2, PINK);
}

void _draw_checked(int j, int i)
{
    DrawRectangle(i * FIELD_CELL_SIZE, j * FIELD_CELL_SIZE, FIELD_CELL_SIZE, FIELD_CELL_SIZE, RED);
    DrawRectangle(i * FIELD_CELL_SIZE + 1, j * FIELD_CELL_SIZE + 1, FIELD_CELL_SIZE - 2, FIELD_CELL_SIZE - 2, GRAY);
}

void draw_path(Field arr[][FEILD_WIDTH], Data goal)
{
    if (arr[goal.y][goal.x].prev.x == 999999)
    {
        DrawRectangle(goal.x * FIELD_CELL_SIZE, goal.y * FIELD_CELL_SIZE, FIELD_CELL_SIZE, FIELD_CELL_SIZE, WHITE);
        return;
    }
    DrawRectangle(goal.x * FIELD_CELL_SIZE, goal.y * FIELD_CELL_SIZE, FIELD_CELL_SIZE, FIELD_CELL_SIZE, WHITE);

    draw_path(arr, arr[goal.y][goal.x].prev);
}

void set_walls(Field arr[][FEILD_WIDTH])
{
    for (int i = 0; i < FEILD_HEIGHT; i++)
    {
        for (int j = 0; j < FEILD_WIDTH; j++)
        {
            arr[i][j].cell_type = rand() % AMOUNT;
        }
    }
    arr[0][0].cell_type = 0;
}

void init_field(Field arr[][FEILD_WIDTH])
{
    for (int i = 0; i < FEILD_HEIGHT; i++)
    {
        for (int j = 0; j < FEILD_WIDTH; j++)
        {
            arr[i][j].cell_type = 0;
            arr[i][j].checked = 0;
            arr[i][j].pushed = 0;
            arr[i][j].prev.x = 999999;
            arr[i][j].prev.y = 999999;
        }
    }
    // arr[5][6].checked = 1;
    // arr[5][7].cell_type = 3;
}

Node *init_node(void)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->next = node;
    node->prev = node;
    return node;
}

void push_to_queue(int x, int y, Node *list)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data.x = x;
    node->data.y = y;

    node->prev = list;
    node->next = list->next;
    list->next->prev = node;
    list->next = node;
}

void print_list(Node *list)
{
    if (list_is_empty(list))
    {
        printf("\n\nList is empty\n\n");
        return;
    }
    for (Node *i = list->prev; i != list; i = i->prev)
    {
        printf("%d %d\n", i->data.x, i->data.y);
    }
}

Data pull_from_queue(Node *list)
{
    Data data;
    Node *node = list->prev;
    data = node->data;
    node->prev->next = list;
    list->prev = node->prev;
    free(node);
    return data;
}

int list_is_empty(Node *list)
{
    return list->next == list->prev && list->next == list;
}

int set_graph(int x, int y, int goal_x, int goal_y, Field arr[][FEILD_WIDTH], Node *list)
{
    if (x == goal_x && y == goal_y)
    {
        printf("%s", "\n\nYou've got it!!\n\n");
        arr[y][x].checked = 2;
        return 1;
    }

    arr[y][x].checked++;
    check_neighbors(x, y, arr, list);

    return 0;
}

void check_neighbors(int x, int y, Field arr[][FEILD_WIDTH], Node *list)
{
    _check_right(x, y, arr, list);
    _check_left(x, y, arr, list);
    _check_down(x, y, arr, list);
    _check_up(x, y, arr, list);

    // _check_diagonal(x, y, arr, list);

    return;
}

void _check_right(int x, int y, Field arr[][FEILD_WIDTH], Node *list)
{
    if (x + 1 < FEILD_WIDTH && arr[y][x + 1].cell_type < WATER && !arr[y][x + 1].checked && !arr[y][x + 1].pushed)
    {
        push_to_queue(x + 1, y, list);
        arr[y][x + 1].pushed = 1;
        arr[y][x + 1].prev.x = x;
        arr[y][x + 1].prev.y = y;
    }
}

void _check_left(int x, int y, Field arr[][FEILD_WIDTH], Node *list)
{
    if (x - 1 >= 0 && arr[y][x - 1].cell_type < WATER && !arr[y][x - 1].checked && !arr[y][x - 1].pushed)
    {
        push_to_queue(x - 1, y, list);
        arr[y][x - 1].pushed = 1;
        arr[y][x - 1].prev.x = x;
        arr[y][x - 1].prev.y = y;
    }
}

void _check_down(int x, int y, Field arr[][FEILD_WIDTH], Node *list)
{
    if (y + 1 < FEILD_HEIGHT && arr[y + 1][x].cell_type < WATER && !arr[y + 1][x].checked && !arr[y + 1][x].pushed)
    {
        push_to_queue(x, y + 1, list);
        arr[y + 1][x].pushed = 1;
        arr[y + 1][x].prev.x = x;
        arr[y + 1][x].prev.y = y;
    }
}

void _check_up(int x, int y, Field arr[][FEILD_WIDTH], Node *list)
{
    if (y - 1 >= 0 && arr[y - 1][x].cell_type < WATER && !arr[y - 1][x].checked && !arr[y - 1][x].pushed)
    {
        push_to_queue(x, y - 1, list);
        arr[y - 1][x].pushed = 1;
        arr[y - 1][x].prev.x = x;
        arr[y - 1][x].prev.y = y;
    }
}

void _check_diagonal(int x, int y, Field arr[][FEILD_WIDTH], Node *list)
{
    _check_diagonal_right_up(x, y, arr, list);
    _check_diagonal_right_down(x, y, arr, list);
    _check_diagonal_left_up(x, y, arr, list);
    _check_diagonal_left_down(x, y, arr, list);
}

void _check_diagonal_right_up(int x, int y, Field arr[][FEILD_WIDTH], Node *list)
{
    if (x + 1 < FEILD_WIDTH && y - 1 >= 0 && arr[y - 1][x + 1].cell_type < WATER && !arr[y - 1][x + 1].checked && !arr[y - 1][x + 1].pushed)
    {
        push_to_queue(x + 1, y - 1, list);
        arr[y - 1][x + 1].pushed = 1;
        arr[y - 1][x + 1].prev.x = x;
        arr[y - 1][x + 1].prev.y = y;
    }
}

void _check_diagonal_right_down(int x, int y, Field arr[][FEILD_WIDTH], Node *list)
{
    if (x + 1 < FEILD_WIDTH && y + 1 < FEILD_HEIGHT && arr[y + 1][x + 1].cell_type < WATER && !arr[y + 1][x + 1].checked && !arr[y + 1][x + 1].pushed)
    {
        push_to_queue(x + 1, y + 1, list);
        arr[y + 1][x + 1].pushed = 1;
        arr[y + 1][x + 1].prev.x = x;
        arr[y + 1][x + 1].prev.y = y;
    }
}

void _check_diagonal_left_down(int x, int y, Field arr[][FEILD_WIDTH], Node *list)
{
    if (x - 1 >= 0 && y + 1 < FEILD_HEIGHT && arr[y + 1][x - 1].cell_type < WATER && !arr[y + 1][x - 1].checked && !arr[y + 1][x - 1].pushed)
    {
        push_to_queue(x - 1, y + 1, list);
        arr[y + 1][x - 1].pushed = 1;
        arr[y + 1][x - 1].prev.x = x;
        arr[y + 1][x - 1].prev.y = y;
    }
}

void _check_diagonal_left_up(int x, int y, Field arr[][FEILD_WIDTH], Node *list)
{
    if (x - 1 >= 0 && y - 1 >= 0 && arr[y - 1][x - 1].cell_type < WATER && !arr[y - 1][x - 1].checked && !arr[y - 1][x - 1].pushed)
    {
        push_to_queue(x - 1, y - 1, list);
        arr[y - 1][x - 1].pushed = 1;
        arr[y - 1][x - 1].prev.x = x;
        arr[y - 1][x - 1].prev.y = y;
    }
}
