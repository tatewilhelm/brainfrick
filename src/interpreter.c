#include "interpreter.h"


int interpret(struct arguments_t arguments)
{


    // Load file
    FILE* file = fopen(arguments.filepath, "r");
    if (ferror(file))
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

    bool exit = false;
    switch (arguments.interpret_mode)
    {
    case CHAR_FILE:
        // Main loop of interpretation
        fpos_t* cf_loop_stack = calloc(loop_stack_size, sizeof(fpos_t));
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
                            free(cf_loop_stack);
                            free(cells);
                            return ENOMEM;
                        }
                    } else {
                        printf("brainfrick: A Fatal Error has occured. Attempting to move cell pointer right when pointer is at maximum.\n");
                        free(cf_loop_stack);
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
                    free(cf_loop_stack);
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
                    cf_loop_stack = realloc(cf_loop_stack, loop_stack_size * sizeof(fpos_t));
                    if (cf_loop_stack == NULL)
                    {
                        printf("brainfrick: A Fatal Error has occured. Ran out of memory.\n");
                        free(cf_loop_stack);
                        free(cells);
                        return ENOMEM;
                    }            
                    fgetpos(file, &cf_loop_stack[loop_stack_size]);
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
                    fsetpos(file, &cf_loop_stack[loop_stack_size]);
                } else {
                    loop_stack_size--;
                    cf_loop_stack = realloc(cf_loop_stack, loop_stack_size * sizeof(fpos_t));
                    if (cf_loop_stack == NULL)
                    {
                        printf("brainfrick: A Fatal Error has occured. Ran out of memory.\n");
                        free(cf_loop_stack);
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
        free(cf_loop_stack);

        break; 
    
    case READ_ONCE:

        printf("brainfrick: A Fatal Error has occured. Read mode has been removed due to unstabillity.\n");
        // char *file_content;
        // int program_ptr;

        // // Get file size
        // fseek(file, 0, SEEK_END);
        // int file_size = ftell(file);

        // // Read file into file_content
        // file_content = calloc(file_size, sizeof(char));
        // fseek(file, 0, SEEK_SET);
        // fread(file_content, sizeof(char), file_size, file);

        // // Main loop of interpretation
        // int* ro_loop_stack = calloc(loop_stack_size, sizeof(int));
        // while (!exit)
        // {
        //     program = file_content[program_ptr];

        //     switch (program)
        //     {

        //     case '+':
        //         // Increment
        //         cells[cell_pointer]++;
        //         break;

        //     case '-':
        //         // Decrement
        //         cells[cell_pointer]--;
        //         break;

        //     case '>':
        //         // Move Right

        //         // Underflow / overflow regulation
        //         if (cell_pointer == cells_size - 1)
        //         {
        //             if (arguments.infinite_cells)
        //             {
        //                 cells_size++;
        //                 cells = realloc(cells, cells_size * sizeof(uint8_t));
        //                 if (cells == NULL)
        //                 {
        //                     printf("brainfrick: A Fatal Error has occured. Ran out of memory.\n");
        //                     free(ro_loop_stack);
        //                     free(cells);
        //                     return ENOMEM;
        //                 }
        //             } else {
        //                 printf("brainfrick: A Fatal Error has occured. Attempting to move cell pointer right when pointer is at maximum.\n");
        //                 free(ro_loop_stack);
        //                 free(cells);
        //                 return -1;
        //             }
        //         }
        //         cell_pointer++;
        //         break;

        //     case '<':
        //         // Move Left

        //         // Check for over flow / underflow
        //         if (cell_pointer == 0)
        //         {
        //             printf("brainfrick: A Fatal Error has occured. Attempting to move cell pointer left when pointer is 0.\n");
        //             free(ro_loop_stack);
        //             free(cells);
        //             return -1;
        //         }
        //         cell_pointer--;
        //         break;

        //     case '.':
        //         // Output
        //         printf("%c", cells[cell_pointer]);
        //         break;

        //     case ',':
        //         // Input
        //         scanf("%c", &cells[cell_pointer]);
        //         break;

        //     case '[':   
        //         // Beginning of loop

        //         if (cells[cell_pointer] != 0)
        //         {
        //             // Push position to the stack
        //             loop_stack_size++;
        //             ro_loop_stack = realloc(ro_loop_stack, loop_stack_size * sizeof(fpos_t));
        //             if (cf_loop_stack == NULL)
        //             {
        //                 printf("brainfrick: A Fatal Error has occured. Ran out of memory.\n");
        //                 free(ro_loop_stack);
        //                 free(cells);
        //                 return ENOMEM;
        //             }            
        //             ro_loop_stack[loop_stack_size] = program_ptr;
        //         } else {
        //             // Keep going till we reach a ] of the same level

        //             bool end_found = false;
        //             int loop_level = 0;
        //             while (!end_found)
        //             {
        //                 switch (fgetc(file)) 
        //                 {
        //                     case '[':
        //                         loop_level++;
        //                     break;
        //                     case ']':
        //                         if (loop_level == 0)
        //                         {
        //                             end_found = true;
                            
        //                         } else {
        //                             loop_level--;
        //                         }
        //                     break;
        //                     case EOF:
        //                         printf("brainfrick: A Fatal Error has occured. Unexpected end of file.\n");
        //                         return -1;
        //                     break;

        //                 }
        //             }
        //         }
        //         break;

        //     case ']':
        //         // End of loop
        //         if (cells[cell_pointer] != 0)
        //         {
        //             program_ptr = ro_loop_stack[loop_stack_size];
        //         } else {
        //             loop_stack_size--;
        //             ro_loop_stack = realloc(ro_loop_stack, loop_stack_size * sizeof(fpos_t));
        //             if (cf_loop_stack == NULL)
        //             {
        //                 printf("brainfrick: A Fatal Error has occured. Ran out of memory.\n");
        //                 free(ro_loop_stack);
        //                 free(cells);
        //                 return ENOMEM;
        //             }
        //         }
        //         break;

        //     case '#':
        //         // The # actually does nothing, its just to catch breakpoints when debugging brainfrick.
        //         break;

        //     case EOF:
        //         exit = true;
        //         break;

        //     default:
        //         // A comment
        //         break;
        //     }

        //     program_ptr++;
        // }

        // free(cf_loop_stack);

        // break;

    }

    // Code for the end of both modes
    if (arguments.return_ending_cell)
    {
        int ending_cell = cells[cell_pointer];
        free(cells);
        return ending_cell;
    }

    free(cells);

    return 0;
}