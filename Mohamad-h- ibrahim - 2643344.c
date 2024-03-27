// Mohamad.h/Ibrahim 2643344
#include <stdio.h>
#include <string.h>
#include "stdlib.h"

struct Signature {
    char Name[50];
    int x_initial;
    int x_final;
    int y_initial;
    int y_final;
    int height;
    int width;
};
typedef struct Signature sign;

sign * Load_SignaturesTable(char *input_file, int *sign_num);
void Display(sign * arr, int size);
int Search (sign * arr, int size, char *str_to_search);
void Sort(sign * arr, int size);
int main(int argc, char * argv[]) {
    FILE *in_stream;
    sign *Signature_arr;
    char input_file_name[30];
    int sign_num = 0;
    int choice = 0;
    char name_tosearch[30];

    // check whether we have the argument right or no
    if (argc != 2){
        printf("you need to pass the name of the file ");
        exit(1);
    }
    // copy the argument to a string for easier handling
    strcpy(input_file_name,argv[1]);
    printf(" the arg v is %s and copied to %s\n",argv[1],input_file_name);
    do {


        in_stream = fopen(input_file_name, "r");
        if (in_stream == NULL) {
            // start using the string directly if the argv isn't given, better for safety purposes!!
            printf("This file does not exist. Please enter again:");
            scanf("%s",input_file_name);
        }
    } while (in_stream == NULL);
    fclose(in_stream); // closes the testing stream
    Signature_arr = Load_SignaturesTable(input_file_name, &sign_num); // assign the pointer of the table to a string
    printf("\n");
    printf("The signature records file %s has been successfully loaded!\n"
           "The following records have been loaded:\n",input_file_name);
    Display(Signature_arr,sign_num);
    printf("\n\n");
    do {
        printf("\nTo search for a signature, please press 1\n"
               "To sort signatures based on width or height, please press 2\n"
               "To exit, please press 3\n"
               "Your choice:");
        scanf("%d",&choice);
        if (choice == 1){// first choice handling
            do {

                printf("Enter the name of the signature owner:");
                fflush(stdin);
                gets(name_tosearch);
                if (Search(Signature_arr,sign_num,name_tosearch) < 0){
                    printf("That owner does not exist! Please try again!");};
            } while (Search(Signature_arr,sign_num,name_tosearch) < 0  );
        } else if (choice == 2){// sort and display
            Sort(Signature_arr,sign_num);
            Display(Signature_arr,sign_num);
        } // no need for handling the choice 3 as it'll terminate by itself
    } while (choice != 3);
    return 0;
}


sign * Load_SignaturesTable(char *input_file, int *sign_num) {
    FILE *input;
    char c;
    int num_lines = 1;
    sign *SignatursTable;
    input = fopen(input_file, "r");
// count num of lines or specifically how many signatures do we have
    do {
        c = fgetc(input);
        if (c == '\n') num_lines++;
    } while (c != EOF);
    *sign_num = num_lines - 1;
    SignatursTable = (sign *) malloc(sizeof(sign) * (num_lines - 1));

    fseek(input, 52, SEEK_SET);
    int i = 0;
    do {// get the daya
        fscanf(input, "%50[^;];%d;%d;%d;%d;\n",
               SignatursTable[i].Name,
               &SignatursTable[i].x_initial,
               &SignatursTable[i].x_final,
               &SignatursTable[i].y_initial,
               &SignatursTable[i].y_final);
        SignatursTable[i].height = SignatursTable[i].y_final - SignatursTable[i].y_initial;
        SignatursTable[i].width = SignatursTable[i].x_final - SignatursTable[i].x_initial;
        i++;
    } while (!feof(input));


    fclose(input);
    return SignatursTable; // return the array
}
void Display(sign * arr, int size){ // print the data
    printf("%-20s%-10s%-10s%-10s%-10s%-10s%-10s\n\n","full_name","x_initial","x_final","y_initial","y_final","width","height");
    for (int j = 0; j < size; ++j) {
        printf("%-20s%-10d%-10d%-10d%-10d%-10d%-10d \n",
               arr[j].Name,
               arr[j].x_initial,
               arr[j].x_final,
               arr[j].y_initial,
               arr[j].y_final,
               arr[j].width,
               arr[j].height);
    }
}

int Search (sign * arr, int size, char *str_to_search){
    int found = 0;
    char arr_cp[size][50]; // initialize a copy string as strtok() null all the data
    char *token1, *token2;

    for (int i = 0; i < size; ++i) { // I have take the first name as a token and the last as another token
        strcpy(arr_cp[i],arr[i].Name);
        token1 = strtok(arr_cp[i]," ");
        token2 = strtok(NULL," ");
        if (strcmp(str_to_search,token1) == 0 || strcmp(str_to_search,token2) == 0){ // if first name or last name is given
            found = 1;
            printf("\n\n %s start signing at x=%d and y=%d and finalized at x=%d and\n"
                   "y=%d. Hence, %s has a signature of width %d and height %d.\n\n",
                   arr[i].Name,
                   arr[i].x_initial,
                   arr[i].y_initial,
                   arr[i].x_final,
                   arr[i].y_final,
                   arr[i].Name,
                   arr[i].width,
                   arr[i].height);
        }
    }
    if (found) return 1;
    else return -1;
}
void Sort(sign * arr, int size){
    char c;
    printf("\n\nSort by (w: width, h: height): ");
    scanf(" %c",&c);
    if (c == 'w'){ // normal bubble sorting for width
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < (size -1); ++j) {
                if (arr[j].width < arr[j+1].width){
                    sign temp = arr[j];
                    arr[j] = arr[j+1];
                    arr[j+1] = temp;
                }
            }
        }
    } else if(c == 'h'){// normal bubble sorting for height
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < (size -1); ++j) {
                if (arr[j].height < arr[j+1].height){
                    sign temp = arr[j];
                    arr[j] = arr[j+1];
                    arr[j+1] = temp;
                }
            }
        }
    }
}


