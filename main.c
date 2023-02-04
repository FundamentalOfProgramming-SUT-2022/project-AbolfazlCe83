#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdlib.h>
#include <direct.h>
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#define MAX_SIZE 1000

//https://codeforwin.org/c-programming/c-program-to-list-all-files-in-a-directory-recursively(for tree function)

char command[MAX_SIZE];

int error_flag = 0;

void createfolder(const char directory[]);
void createfile(char directory[]);
void cat(FILE *fp , char fileaddress[]);
void copy(FILE *fp , int line_number , int char_pos , char b_f[] , char fille_addres[]);


int main() {
    int flag = 1;
    while (flag) {
        scanf("%s" , command);
        if (!(strcmp(command , "createfile")))
        {
            char buffer[50];
            getchar();
            scanf("%s" , buffer);
            if (!(strcmp(buffer , "--file"))) {
                char file_address[200];
                char directory[200];
                getchar();
                scanf("%[^\n]s" , file_address);
                int address_length = strlen(file_address);
                if(file_address[0] != '/' && file_address[0] != '"') {
                    char chert[MAX_SIZE];
                    scanf("%[^\n]s" , chert);
                    printf("invalid command\nfor more information type <help>!\n");
                }
                else if(file_address[0] == '"' && file_address[address_length - 1] == '"') {
                    for(int i = 0; i < address_length - 2; i++) {
                    directory[i] = file_address[i + 1];
                    }
                    createfolder(directory + 1);
                    createfile(directory + 1);
                }
                else
                {
                    createfolder(file_address + 1);
                    createfile(file_address + 1);
                }
                
            }
            else
            {
                char chert[MAX_SIZE];
                scanf("%[^\n]s" , chert);
                printf("invalid command\nfor more information type <help>!\n");
            }
            
        }
        else if(!(strcmp(command , "cat")))
        {
            char buffer[50];
            getchar();
            scanf("%s" , buffer);
            if(!(strcmp(buffer , "--file"))) {
                char file_address[200];
                char directory[200];
                getchar();
                gets(file_address);
                int address_length = strlen(file_address);
                if(file_address[0] != '/' && file_address[0] != '"') {
                    char chert[MAX_SIZE];
                    scanf("%[^\n]s" , chert);
                    printf("invalid command\nfor more information type <help>!\n");
                }
                else if(file_address[0] == '"' && file_address[address_length - 1] == '"') {
                    for(int i = 0; i < address_length - 2; i++) {
                    directory[i] = file_address[i + 1];
                    }
                    FILE *for_read = fopen(directory + 1 , "r");
                    fclose(for_read);
                    if(!for_read) {
                        printf("The file doesnt exist!\n");
                    }
                    else
                    {
                        cat(for_read , directory +1);
                    }
                }
                else 
                {
                    FILE *forread = fopen(file_address + 1 , "r");
                    fclose(forread);
                    if(!forread) {
                        printf("The file doesnt exist!\n");
                    }
                    else
                    {
                        cat(forread , file_address + 1);
                    }
                    
                }
            }
            else {
                char chert[MAX_SIZE];
                scanf("%[^\n]s" , chert);
                printf("invalid command\nfor more information type <help>!\n");
            }
        }
        // else if(!(strcmp(command , "copy")))
        // {
        //     FILE *for_function;
        //     char FILLE_ADDRESS[MAX_SIZE];
        //     char buffer[50];
        //     getchar();
        //     scanf("%s" , buffer);
        //     if(!(strcmp(buffer , "--file")))
        //     {
        //         char file_address[200];
        //         char directory[200];
        //         getchar();
        //         scanf("%s" , file_address);
        //         int address_length = strlen(file_address);
        //         if(file_address[0] != '/' && file_address[0] != '"') {
        //             char chert[MAX_SIZE];
        //             scanf("%[^\n]s" , chert);
        //             printf("invalid command\nfor more information type <help>!\n");
        //         }
        //         else if(file_address[0] == '"' && file_address[address_length - 1] == '"') {
        //             for(int i = 0; i < address_length - 2; i++) {
        //             directory[i] = file_address[i + 1];
        //             strcpy(FILLE_ADDRESS , directory + 1);
        //             }
        //             FILE *for_read = fopen(directory + 1 , "r");
        //             fclose(for_read);
        //             if(!for_read) {
        //                 printf("The file doesnt exist!\n");
        //             }
        //             else
        //             {
        //                 for_function = for_read;
        //             }
        //         }
        //         else 
        //         {
        //             FILE *forread = fopen(file_address + 1 , "r");
        //             fclose(forread);
        //             if(!forread) {
        //                 printf("The file doesnt exist!\n");
        //             }
        //             else
        //             {
        //                 for_function = forread;
        //                 strcpy(FILLE_ADDRESS , file_address + 1);
        //             }
                    
        //         }
                
        //         char position[50];
        //         getchar();
        //         scanf("%s" , position);
        //         if(!(strcmp(position , "--pos")))
        //         {
        //             int line_number = 0;
        //             char Two_dat;
        //             int char_pos = 0;
        //             scanf("%d%c%d" , &line_number , &Two_dat , &char_pos);
        //             char size[50];
        //             getchar();
        //             scanf("%s" , size);
        //             if(!(strcmp(size , "-size")))
        //             {
        //                 int number_of_chars = 0;
        //                 scanf("%d" , number_of_chars);
        //                 getchar();
        //                 char back_or_forward[3];
        //                 gets(back_or_forward);
        //                 if(!(strcmp(back_or_forward , "-b") || strcmp(back_or_forward , "-f")))
        //                     copy(for_function , line_number , char_pos , back_or_forward , FILLE_ADDRESS);
        //                 else
        //                 {
        //                     char chert[MAX_SIZE];
        //                     scanf("%[^\n]s" , chert);
        //                     printf("invalid command\nfor more information type <help>!\n");
        //                 }
        //             }
        //             else
        //             {
        //                 char chert[MAX_SIZE];
        //                 scanf("%[^\n]s" , chert);
        //                 printf("invalid command\nfor more information type <help>!\n");
        //             }
        //         }
        //         else
        //         {
        //             char chert[MAX_SIZE];
        //             scanf("%[^\n]s" , chert);
        //             printf("invalid command\nfor more information type <help>!\n");
        //         }
        //     }
        //     else
        //     {
        //         char chert[MAX_SIZE];
        //         scanf("%[^\n]s" , chert);
        //         printf("invalid command\nfor more information type <help>!\n");
        //     }
        // }
        else
        {
            char chert[MAX_SIZE];
            scanf("%[^\n]s" , chert);
            printf("invalid command\nfor more information type <help>!\n");
        }
        
    }
}

int myflag = 0;

void createfolder(const char directory[]){
    int i = 0;
    int index_of_end = 0;
    while (1)
    {
        if(directory[i] == '/') {
            index_of_end = i;
        }
        char newdir[MAX_SIZE] = {0};
        if(index_of_end != 0) {
        for(int j = 0; j < index_of_end; j++) {
            newdir[j] = directory[j];
        }
        newdir[strlen(newdir)] = '\0';
        DIR *check = opendir(newdir);
        if(check) 
        {
            closedir(check);
        }
        else
        {
            mkdir(newdir);
        }
        }
        i++;
        if(i == strlen(directory))
            break;
        index_of_end = 0;
    }
    
    // int directory_length = strlen(directory);
    // int index_end = 0;
    // int slash_counter = 0;
    // char newdir[MAX_SIZE];
    // for(int i = 0; i < directory_length; i++) {
    //     if(directory[i] == '/') {
    //         slash_counter++;
    //     }
    // }
    // char diiiiiir[MAX_SIZE];
    // int first_slash = 0;
    // int second_slash = 1;
    // for(int j = 0 ; j < slash_counter ; j++) {
    //     for(int i = 0 ; i < directory_length ; i++) {
    //         if(directory[i] == '/') {
    //             second_slash++;
    //             if(second_slash > first_slash) {
    //                 index_end = i;
    //                 break;
    //             }
    //         }
    //         if(index_end != 0) {
    //         for(int k = 0; k < index_end; k++) {
    //             newdir[k] = directory[k];
    //         }
    //         }
    //     }
    //     first_slash = second_slash;
    //     second_slash = 0;
    //     printf("%s\n" , newdir);
    //     for(int i = 0; i < strlen(newdir) ; i++) {
    //         newdir[i] = 0;
    //     }
    // }
    }

void createfile(char directory[]) {
    FILE *fptr = fopen(directory , "r");
    if(fptr) {
        printf("The File is already exist!\n");
        fclose(fptr);
    }
    else
    {
        myflag = 1;
        fptr = fopen(directory , "w");
        fclose(fptr);
    }
}

void cat(FILE *fp , char fileaddress[]) {
    fp = fopen(fileaddress , "r");
    char *content_of_file;
    long numbytes;
    fseek(fp , 0L , SEEK_END);
    numbytes = ftell(fp);
    fseek(fp , 0L , SEEK_SET);
    content_of_file = (char *)calloc(numbytes, sizeof(char));
    fread(content_of_file , sizeof(char) , numbytes , fp);
    fclose(fp);
    printf(content_of_file);
    printf("\n");
}

// void copy(FILE *fp , int line_number , int char_pos , char b_f[] , char fileaddress[])
// {
//     fp = fopen(fileaddress , "r");
//     char *content_of_file;
//     long numbytes;
//     fseek(fp , 0L , SEEK_END);
//     numbytes = ftell(fp);
//     fseek(fp , 0L , SEEK_SET);
//     content_of_file = (char *)calloc(numbytes, sizeof(char));
//     fread(content_of_file , sizeof(char) , numbytes , fp);
//     fclose(fp);
// }