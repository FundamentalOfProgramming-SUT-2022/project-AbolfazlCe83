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

char command[MAX_SIZE];

void createfolder(char directory[]);
void createfile(char directory[]);


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
                gets(file_address);
                int address_length = strlen(file_address);
                if(file_address[0] != '/' && file_address[0] != '"') {
                printf("1invalid command\nfor more information type <help>!\n");
                }
                else if(file_address[0] == '"' && file_address[address_length - 1] == '"') {
                    for(int i = 0; i < address_length - 2; i++) {
                    directory[i] = file_address[i + 1];
                    }
                    createfolder(directory);
                    createfile(directory);
                }
                else
                {
                    createfolder(file_address);
                    createfile(file_address);
                }
                
            }
            else
            {
                printf("2invalid command\nfor more information type <help>!\n");
            }
            
        }
        else
        {
            printf("3invalid command\nfor more information type <help>!\n");
        }
        
    }
}

int myflag = 0;

void createfolder(char directory[]){
    int slash_counter = 0;
    int directory_length = strlen(directory);
    for(int i = 0; i < directory_length; i++) {
        if(directory[i] == '/') {
            slash_counter++;
        }
        if(slash_counter >= 3) 
            break;
    }
    int index = 0;
    if(slash_counter >= 3) {
        for(int i = directory_length - 1; i > 0; i--) {
            if(directory[i] == '/') {
                index = i;
                break;
            }
        }
    }
    char newdirectory[200];
    if(index != 0) {
        for(int i = 0; i < index; i++) {
            newdirectory[i] = directory[i];
        }
        printf("%s" , newdirectory);
        DIR *checkdir = opendir(newdirectory + 1);
        if(checkdir && myflag == 0) {
            
        }
        else
        {
            mkdir(newdirectory + 1);
        }
        
    }
}

void createfile(char directory[]) {
    FILE *fptr = fopen(directory + 1 , "r");
    if(fptr) {
        printf("The File is already exist!\n");
        fclose(fptr);
    }
    else
    {
        myflag = 1;
        fptr = fopen(directory + 1 , "w");
        fclose(fptr);
    }
    
}