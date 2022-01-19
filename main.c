#include "header.h"

int main(void)
{
    // Resizable window
    //-----------------------------------------------------------------------------------
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(CANVAS_WIDTH, CANVAS_HEIGHT, "Snake");

    // Declarations
    //-----------------------------------------------------------------------------------
    srand(time(NULL));
    int end_of_searching = 0;
    Field field[FEILD_HEIGHT][FEILD_WIDTH] = {0};
    Data goal = {
        .x = FEILD_WIDTH - 1,
        .y = FEILD_HEIGHT - 1,
    };
    Data start = {
        .x = 0,
        .y = 0,
    };
    Data current_data;
    init_field(field);
    set_walls(field);

    Node *list = init_node();
    push_to_queue(start.x, start.y, list);
    // print_list(list);

    // Main loop
    //====================================================================================
    // SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        if (!(list_is_empty(list)) && !end_of_searching)
        {
            current_data = pull_from_queue(list);
            end_of_searching = set_graph(current_data.x, current_data.y, goal.x, goal.y, field, list);
        }
        // -------------------------------------------------------------------------------
        // Draw
        // -------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(GREEN);
        draw(field, goal, start, end_of_searching, current_data, list);

        EndTextureMode();
        EndDrawing();
    }
    //====================================================================================
    CloseWindow();
    return 0;
}