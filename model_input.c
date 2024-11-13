#include "structs.h"
#include "model_input.h"
#include <stdio.h>
#include <stdlib.h>
#define MAX_STR_LEN 10000

void string_split(char* text, char** sub_str, char a);


int test_model_input(void) {

    FILE *input_file_pointer;
    char str[MAX_STR_LEN];
    int ch;
    int i = 0;

    input_file_pointer = fopen("model_data/trains.txt", "r");

    if (input_file_pointer != NULL){        /* File could be opened */
        while ((ch = fgetc(input_file_pointer)) != EOF){
            str[i] = ch;
            i++;
        }
        str[i] = '\0';

        printf("Read from file: %s\n", str);

        char* sub_str[1000];
        Train trains[1000];
        int i=0;

        string_split(str,sub_str,'\n');

        while (1)
        {
            trains[i] = read_train(sub_str[i]);
            i++;
            if(sub_str[i]==NULL)
            {
                break;
            }
        }

        print_train(trains[0]);
        printf("\n");
        print_train(trains[1]);

        fclose(input_file_pointer);
    }
    else{
        printf("Could not open input file. Bye.");
        exit(EXIT_FAILURE);
    }

    return 0;
}

void string_split(char* text, char** sub_str, char a)
{
    int i = 0;
    sub_str[0] = text;
    int sub_str_index = 1;

    while (1)
    {
        if (text[i] == '\0')
        {
            break;
        }
        if (text[i] == a)
        {
            text[i] = '\0';

            sub_str[sub_str_index] = text + i + 1;
            sub_str_index++;
        }
        i++;
    }
}

Train read_train(char* str)
{
    char* sub_str[100];
    string_split(str, sub_str,';');
    Train train;
    train.name=(sub_str[0]);
    train.max_speed=atof(sub_str[1]);
    train.acceleration=atof(sub_str[2]);
    train.deceleration=atof(sub_str[3]);


    return train;
}

void print_train(Train train)
{
    printf("the trains name: %s\n and the trains max speed: %f\n and the trains acceleration: %f\n and the trains deceleration: %f\n",
        train.name, train.max_speed, train.acceleration, train.deceleration);
}