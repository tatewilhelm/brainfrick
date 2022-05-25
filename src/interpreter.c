#include "interpreter.h"


int interpret(struct arguments_t arguments)
{


    // Load file
    FILE* file = fopen(arguments.filepath, "r");
    if (fopen(arguments.filepath, "r") == NULL)
    {
        printf("brainfrick: A fataal error has occured. File does not exist when attempting interpreted read.\n");
        return -1;
    }


    // The command itself being execute
    char program;


    // Cells
    size_t cells_size = 1; // Only used for infite cells mode
    uint8_t *cells;

    // Infinite cells dynamic array mode
    if (arguments.infinite_cells) {
        cells = calloc(cells_size, sizeof(uint8_t));
    } else {
        cells_size = STD_CELL_SIZE;
        cells = calloc(STD_CELL_SIZE, sizeof(u_int8_t));
    }

    // Points to current cell
    unsigned int cell_pointer = 0;

    // Initialize the stack
    size_t loop_stack_size = 1;
    fpos_t* loop_stack = calloc(loop_stack_size, sizeof(fpos_t));


    // Main loop of interpretation
    bool exit = false;
    while (!exit)
    {
    
        program = fgetc(file);
    

        switch (program)
        {

        case '+':
            // Increment
            cells[cell_pointer]++;
            break;

        case '-':
            // Decrement
            cells[cell_pointer]--;
            break;

        case '>':
            // Move Right

            // Underflow / overflow regulation
            if (cell_pointer == cells_size - 1)
            {
                if (arguments.infinite_cells)
                {
                    cells_size++;
                    cells = realloc(cells, cells_size * sizeof(uint8_t));
                    if (cells == NULL)
                    {
                        printf("brainfrick: A Fatal Error has occured. Ran out of memory.\n");
                        free(loop_stack);
                        free(cells);
                        return ENOMEM;
                    }
                } else {
                    printf("brainfrick: A Fatal Error has occured. Attempting to move cell pointer right when pointer is at maximum.\n");
                    free(loop_stack);
                    free(cells);
                    return -1;
                }
            }
            cell_pointer++;
            break;

        case '<':
            // Move Left

            // Check for over flow / underflow
            if (cell_pointer == 0)
            {
                printf("brainfrick: A Fatal Error has occured. Attempting to move cell pointer left when pointer is 0.\n");
                free(loop_stack);
                free(cells);
                return -1;
            }
            cell_pointer--;
            break;

        case '.':
            // Output
            printf("%c", cells[cell_pointer]);
            break;

        case ',':
            // Input
            scanf("%c", &cells[cell_pointer]);
            break;

        case '[':   
            // Beginning of loop

            if (cells[cell_pointer] != 0)
            {
                // Push position to the stack
                loop_stack_size++;
                loop_stack = realloc(loop_stack, loop_stack_size * sizeof(fpos_t));
                if (loop_stack == NULL)
                {
                    printf("brainfrick: A Fatal Error has occured. Ran out of memory.\n");
                    free(loop_stack);
                    free(cells);
                    return ENOMEM;
                }            
                fgetpos(file, &loop_stack[loop_stack_size]);
            } else {
                // Keep going till we reach a ] of the same level

                bool end_found = false;
                int loop_level = 0;
                while (!end_found)
                {
                    switch (fgetc(file)) 
                    {
                        case '[':
                            loop_level++;
                        break;
                        case ']':
                            if (loop_level == 0)
                            {
                                end_found = true;
                            } else {
                                loop_level--;
                            }
                        break;
                        case EOF:
                            printf("brainfrick: A Fatal Error has occured. Unexpected end of file.\n");
                            return -1;
                        break;

                    }
                }
            }
            break;

        case ']':
            // End of loop
            if (cells[cell_pointer] != 0)
            {
                fsetpos(file, &loop_stack[loop_stack_size]);
            } else {
                loop_stack_size--;
                loop_stack = realloc(loop_stack, loop_stack_size * sizeof(fpos_t));
                if (loop_stack == NULL)
                {
                    printf("brainfrick: A Fatal Error has occured. Ran out of memory.\n");
                    free(loop_stack);
                    free(cells);
                    return ENOMEM;
                }
            }
            break;

        case '#':
            // The # actually does nothing, its just to catch breakpoints when debugging brainfrick.
            break;

        case EOF:
            exit = true;
            break;

        default:
            // A comment
            break;
        }
    }

    free(loop_stack);

    if (arguments.return_ending_cell)
    {
        int ending_cell = cells[cell_pointer];
        free(cells);
        return ending_cell;
    }

    free(cells);

    return 0;
}