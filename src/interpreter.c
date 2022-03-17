#include "interpreter.h"


int interpret(struct arguments_t arguments)
{


    // Load file
    FILE* file = fopen(arguments.filepath, "r");
    if (fopen(arguments.filepath, "r") == NULL)
    {
        printf("brainfrick: A fatal error has occured. File does not exist when attempting interpreted read.\n");
        return -1;
    }


    // The command itself being execute
    char program;


    // Cells
    uint8_t cells[30000];

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
            if (cell_pointer == sizeof(cells) - 1)
            {
                printf("brainfrick: A Fatal Error has occured. Attempting to move cell pointer right when pointer is at maximum.\n");
                return -1;
            }
            cell_pointer++;
            break;

        case '<':
            // Move Left

            // Check for over flow / underflow
            if (cell_pointer == 0)
            {
                printf("brainfrick: A Fatal Error has occured. Attempting to move cell pointer left when pointer is 0.\n");
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

            // Push position to the stack
            loop_stack_size++;
            loop_stack = realloc(loop_stack, loop_stack_size * sizeof(fpos_t));
            if (loop_stack == NULL)
            {
                return ENOMEM;
            }            
            fgetpos(file, &loop_stack[loop_stack_size]);
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
        return cells[cell_pointer];
    }

    return 0;
}