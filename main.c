#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdlib.h>
#include <direct.h>
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#include <windows.h>
#define MAX_SIZE 1000
#define FILENAME_SIZE 1024
#define MAX_LINE 2048

//https://www.tutorialkart.com/c-programming/c-read-text-file/(for Cat function)
//https://codeforwin.org/c-programming/c-program-to-list-all-files-in-a-directory-recursively(for tree function)

char command[MAX_SIZE];

int error_flag = 0;

void createfolder(const char directory[]);
void createfile(char directory[]);
void cat(FILE *fp , char fileaddress[]);
void copy(FILE *fp , int line_number , int char_pos ,int number_of_chars , char b_f[] , char fille_addres[]);
void removestr(FILE *fp , int line_number , int char_pos ,int number_of_chars , char b_f[] , char fille_addres[]);
void insertstr(FILE *fp , int line_number , int char_pos , char fileaddress[] , char string_to_be_inserted[]);


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
        else if(!(strcmp(command , "copy")))
        {
            FILE *for_function;
            char FILLE_ADDRESS[MAX_SIZE];
            char buffer[50];
            getchar();
            scanf("%s" , buffer);
            if(!(strcmp(buffer , "--file")))
            {
                char file_address[200];
                char directory[200];
                getchar();
                scanf("%s" , file_address);
                int address_length = strlen(file_address);
                if(file_address[0] != '/' && file_address[0] != '"') {
                    char chert[MAX_SIZE];
                    scanf("%[^\n]s" , chert);
                    printf("invalid command\nfor more information type <help>!\n");
                }
                else if(file_address[0] == '"' && file_address[address_length - 1] == '"') {
                    for(int i = 0; i < address_length - 2; i++) {
                    directory[i] = file_address[i + 1];
                    strcpy(FILLE_ADDRESS , directory + 1);
                    }
                    FILE *for_read = fopen(directory + 1 , "r");
                    fclose(for_read);
                    if(!for_read) {
                        printf("The file doesnt exist!\n");
                    }
                    else
                    {
                        for_function = for_read;
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
                        for_function = forread;
                        strcpy(FILLE_ADDRESS , file_address + 1);
                    }
                    
                }
                
                char position[50];
                getchar();
                scanf("%s" , position);
                if(!(strcmp(position , "--pos")))
                {
                    int line_number = 0;
                    char Two_dat;
                    int char_pos = 0;
                    scanf("%d%c%d" , &line_number , &Two_dat , &char_pos);
                    char size[50];
                    getchar();
                    scanf("%s" , size);
                    if(!(strcmp(size , "-size")))
                    {
                        int number_of_chars = 0;
                        scanf("%d" , &number_of_chars);
                        getchar();
                        char back_or_forward[3];
                        gets(back_or_forward);
                        
                        if(!(strcmp(back_or_forward , "-b")))
                        {
                            copy(for_function , line_number , char_pos , number_of_chars , back_or_forward , FILLE_ADDRESS);
                        }
                        else if (!(strcmp(back_or_forward , "-f")))
                        {
                            copy(for_function , line_number , char_pos , number_of_chars ,back_or_forward , FILLE_ADDRESS);
                        }
                        else
                        {
                            char chert[MAX_SIZE];
                            scanf("%[^\n]s" , chert);
                            printf("invalid command\nfor more information type <help>!\n");
                        }
                    }
                    else
                    {
                        char chert[MAX_SIZE];
                        scanf("%[^\n]s" , chert);
                        printf("invalid command\nfor more information type <help>!\n");
                    }
                }
                else
                {
                    char chert[MAX_SIZE];
                    scanf("%[^\n]s" , chert);
                    printf("invalid command\nfor more information type <help>!\n");
                }
            }
            else
            {
                char chert[MAX_SIZE];
                scanf("%[^\n]s" , chert);
                printf("invalid command\nfor more information type <help>!\n");
            }
        }
        else if(!(strcmp(command , "removestr")))
        {
            FILE *for_function;
            char FILLE_ADDRESS[MAX_SIZE];
            char buffer[50];
            getchar();
            scanf("%s" , buffer);
            if(!(strcmp(buffer , "--file")))
            {
                char file_address[200];
                char directory[200];
                getchar();
                scanf("%s" , file_address);
                int address_length = strlen(file_address);
                if(file_address[0] != '/' && file_address[0] != '"') {
                    char chert[MAX_SIZE];
                    scanf("%[^\n]s" , chert);
                    printf("invalid command\nfor more information type <help>!\n");
                }
                else if(file_address[0] == '"' && file_address[address_length - 1] == '"') {
                    for(int i = 0; i < address_length - 2; i++) {
                    directory[i] = file_address[i + 1];
                    strcpy(FILLE_ADDRESS , directory + 1);
                    }
                    FILE *for_read = fopen(directory + 1 , "r");
                    fclose(for_read);
                    if(!for_read) {
                        printf("The file doesnt exist!\n");
                    }
                    else
                    {
                        for_function = for_read;
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
                        for_function = forread;
                        strcpy(FILLE_ADDRESS , file_address + 1);
                    }
                    
                }
                
                char position[50];
                getchar();
                scanf("%s" , position);
                if(!(strcmp(position , "--pos")))
                {
                    int line_number = 0;
                    char Two_dat;
                    int char_pos = 0;
                    scanf("%d%c%d" , &line_number , &Two_dat , &char_pos);
                    char size[50];
                    getchar();
                    scanf("%s" , size);
                    if(!(strcmp(size , "-size")))
                    {
                        int number_of_chars = 0;
                        scanf("%d" , &number_of_chars);
                        getchar();
                        char back_or_forward[3];
                        gets(back_or_forward);
                        
                        if(!(strcmp(back_or_forward , "-b")))
                        {
                            removestr(for_function , line_number , char_pos , number_of_chars , back_or_forward , FILLE_ADDRESS);
                        }
                        else if (!(strcmp(back_or_forward , "-f")))
                        {
                            removestr(for_function , line_number , char_pos , number_of_chars ,back_or_forward , FILLE_ADDRESS);
                        }
                        else
                        {
                            char chert[MAX_SIZE];
                            scanf("%[^\n]s" , chert);
                            printf("invalid command\nfor more information type <help>!\n");
                        }
                    }
                    else
                    {
                        char chert[MAX_SIZE];
                        scanf("%[^\n]s" , chert);
                        printf("invalid command\nfor more information type <help>!\n");
                    }
                }
                else
                {
                    char chert[MAX_SIZE];
                    scanf("%[^\n]s" , chert);
                    printf("invalid command\nfor more information type <help>!\n");
                }
            }
            else
            {
                char chert[MAX_SIZE];
                scanf("%[^\n]s" , chert);
                printf("invalid command\nfor more information type <help>!\n");
            }
        }
        else if(!(strcmp(command , "cutstr")))
        {
            FILE *for_function;
            char FILLE_ADDRESS[MAX_SIZE];
            char buffer[50];
            getchar();
            scanf("%s" , buffer);
            if(!(strcmp(buffer , "--file")))
            {
                char file_address[200];
                char directory[200];
                getchar();
                scanf("%s" , file_address);
                int address_length = strlen(file_address);
                if(file_address[0] != '/' && file_address[0] != '"') {
                    char chert[MAX_SIZE];
                    scanf("%[^\n]s" , chert);
                    printf("invalid command\nfor more information type <help>!\n");
                }
                else if(file_address[0] == '"' && file_address[address_length - 1] == '"') {
                    for(int i = 0; i < address_length - 2; i++) {
                        directory[i] = file_address[i + 1];
                        strcpy(FILLE_ADDRESS , directory + 1);
                    }
                    FILE *for_read = fopen(directory + 1 , "r");
                    fclose(for_read);
                    if(!for_read) {
                        printf("The file doesnt exist!\n");
                    }
                    else
                    {
                        for_function = for_read;
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
                        for_function = forread;
                        strcpy(FILLE_ADDRESS , file_address + 1);
                    }

                }

                char position[50];
                getchar();
                scanf("%s" , position);
                if(!(strcmp(position , "--pos")))
                {
                    int line_number = 0;
                    char Two_dat;
                    int char_pos = 0;
                    scanf("%d%c%d" , &line_number , &Two_dat , &char_pos);
                    char size[50];
                    getchar();
                    scanf("%s" , size);
                    if(!(strcmp(size , "-size")))
                    {
                        int number_of_chars = 0;
                        scanf("%d" , &number_of_chars);
                        getchar();
                        char back_or_forward[3];
                        gets(back_or_forward);

                        if(!(strcmp(back_or_forward , "-b")))
                        {
                            copy(for_function , line_number , char_pos , number_of_chars , back_or_forward , FILLE_ADDRESS);
                            removestr(for_function , line_number , char_pos , number_of_chars , back_or_forward , FILLE_ADDRESS);
                        }
                        else if (!(strcmp(back_or_forward , "-f")))
                        {
                            copy(for_function , line_number , char_pos , number_of_chars , back_or_forward , FILLE_ADDRESS);
                            removestr(for_function , line_number , char_pos , number_of_chars ,back_or_forward , FILLE_ADDRESS);
                        }
                        else
                        {
                            char chert[MAX_SIZE];
                            scanf("%[^\n]s" , chert);
                            printf("invalid command\nfor more information type <help>!\n");
                        }
                    }
                    else
                    {
                        char chert[MAX_SIZE];
                        scanf("%[^\n]s" , chert);
                        printf("invalid command\nfor more information type <help>!\n");
                    }
                }
                else
                {
                    char chert[MAX_SIZE];
                    scanf("%[^\n]s" , chert);
                    printf("invalid command\nfor more information type <help>!\n");
                }
            }
            else
            {
                char chert[MAX_SIZE];
                scanf("%[^\n]s" , chert);
                printf("invalid command\nfor more information type <help>!\n");
            }
        }
        else if(!(strcmp(command , "insertstr")))
        {
            char string_to_be_inserted[MAX_SIZE];
            FILE *for_function;
            char FILLE_ADDRESS[MAX_SIZE];
            char buffer[50];
            getchar();
            scanf("%s" , buffer);
            if(!(strcmp(buffer , "--file")))
            {
                char file_address[200];
                char directory[200];
                getchar();
                scanf("%s" , file_address);
                int address_length = strlen(file_address);
                if(file_address[0] != '/' && file_address[0] != '"') {
                    char chert[MAX_SIZE];
                    scanf("%[^\n]s" , chert);
                    printf("invalid command\nfor more information type <help>!\n");
                }
                else if(file_address[0] == '"' && file_address[address_length - 1] == '"') {
                    for(int i = 0; i < address_length - 2; i++) {
                        directory[i] = file_address[i + 1];
                        strcpy(FILLE_ADDRESS , directory + 1);
                    }
                    FILE *for_read = fopen(directory + 1 , "r");
                    fclose(for_read);
                    if(!for_read) {
                        printf("The file doesnt exist!\n");
                    }
                    else
                    {
                        for_function = for_read;
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
                        for_function = forread;
                        strcpy(FILLE_ADDRESS , file_address + 1);
                    }

                }
                char str[50];
                getchar();
                scanf("%s" , str);
                if(!(strcmp(str , "--str"))) {
                    getchar();
                    scanf("%s" , string_to_be_inserted);
                    char position[50];
                    getchar();
                    scanf("%s", position);
                    if (!(strcmp(position, "--pos"))) {
                        getchar();
                        int line_number = 0;
                        char Two_dat;
                        int char_pos = 0;
                        scanf("%d%c%d", &line_number, &Two_dat, &char_pos);
                        insertstr(for_function , line_number , char_pos , FILLE_ADDRESS , string_to_be_inserted);
                    } else {
                        char chert[MAX_SIZE];
                        scanf("%[^\n]s", chert);
                        printf("invalid command\nfor more information type <help>!\n");
                    }
                }
                else
                {
                    char chert[MAX_SIZE];
                    scanf("%[^\n]s" , chert);
                    printf("invalid command\nfor more information type <help>!\n");
                }
            }
            else
            {
                char chert[MAX_SIZE];
                scanf("%[^\n]s" , chert);
                printf("invalid command\nfor more information type <help>!\n");
            }
        }
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

void copy(FILE *fp , int line_number , int char_pos , int number_of_chars,char b_f[] , char fileaddress[])
{
    int flag = 0;
    char copied[MAX_SIZE];
    fp = fopen(fileaddress , "r");
    char *content_of_file;
    long numbytes;
    fseek(fp , 0L , SEEK_END);
    numbytes = ftell(fp);
    fseek(fp , 0L , SEEK_SET);
    content_of_file = (char *)calloc(numbytes, sizeof(char));
    fread(content_of_file , sizeof(char) , numbytes , fp);
    fclose(fp);
    int line_counter_with_enter = 0;
    for(int i = 0; i < strlen(content_of_file); i++)
    {
        if(content_of_file[i] == '\n')
        {
            line_counter_with_enter++;
        }
    }
    if(line_number > line_counter_with_enter)
    {
        flag = 1;
        printf("This Line doesnt exist in file!\n");
        printf("This file have %d lines\n" , line_counter_with_enter);
    }
    int keepline = 1;
    int first_index = 0;
    int second_index = 0;
    if(flag == 0)
    {
        for(int j = 0 ; j < strlen(content_of_file); j++)
        {
            if(content_of_file[j] == '\n')
            {
                keepline++;
                if(keepline == line_number)
                {
                    first_index = j + 1;
                    break;
                }
            }
        }
        char_pos += first_index;
        if(char_pos >= strlen(content_of_file))
        {
            printf("This character doesn't exist in file!\n");
        }
        else if(!(strcmp(b_f , "-b")))
        {
            if(char_pos - number_of_chars + 1 < 0)
            {
                printf("The size you specified does not exist in the file!\n");
            } else
            {
                for(int i = char_pos - number_of_chars + 1; i <= char_pos; i++)
                {
                    copied[i - char_pos + number_of_chars - 1] = content_of_file[i];
                }
            }
        }
        else if(!(strcmp(b_f , "-f")))
        {
            if((char_pos + number_of_chars - 1) >= strlen(content_of_file))
            {
                printf("The size you specified does not exist in the file!\n");
            } else
            {
                for(int i = char_pos ; i < char_pos + number_of_chars ; i++)
                {
                    copied[i - char_pos] = content_of_file[i];
                }
            }
        }
    }
    fclose(fp);
    FILE *clipboard;
    clipboard = fopen("clipboard.txt" , "w");
    fputs(copied , clipboard);
    fclose(clipboard);
//    wchar_t *fileLPCWSTR = "clipboard.txt";
//    int attr = GetFileAttributes(fileLPCWSTR);
//    if((attr && FILE_ATTRIBUTE_HIDDEN) == 0)
//    {
//        SetFileAttributes(fileLPCWSTR , attr | FILE_ATTRIBUTE_HIDDEN);
//    }
}

void removestr(FILE *fp , int line_number , int char_pos ,int number_of_chars , char b_f[] , char fileaddress[])
{
    int flag = 0;
    fp = fopen(fileaddress , "r");
    char *content_of_file;
    long numbytes;
    fseek(fp , 0L , SEEK_END);
    numbytes = ftell(fp);
    fseek(fp , 0L , SEEK_SET);
    content_of_file = (char *)calloc(numbytes, sizeof(char));
    fread(content_of_file , sizeof(char) , numbytes , fp);
    fclose(fp);
    int line_counter_with_enter = 0;
    for(int i = 0; i < strlen(content_of_file); i++)
    {
        if(content_of_file[i] == '\n')
        {
            line_counter_with_enter++;
        }
    }
    if(line_number > line_counter_with_enter)
    {
        flag = 1;
        printf("This Line doesnt exist in file!\n");
        printf("This file have %d lines\n" , line_counter_with_enter);
    }
    bool keep_reading = true;
    int keepline = 1;
    int first_index = 0;
    int second_index = 0;
    if(flag == 0)
    {
    for(int j = 0 ; j < strlen(content_of_file); j++)
    {
        if(content_of_file[j] == '\n')
        {
            keepline++;
            if(keepline == line_number)
            {
                first_index = j + 1;
            }
            if(keepline == line_number + 1)
            {
                second_index = j - 1;
                break;
            }
        }
    }
    int length_of_string = second_index - first_index;
    if(char_pos + first_index >= strlen(content_of_file))
    {
        printf("This charachter doesn't exist in file!\nthe number of charachters is : %d\n" , strlen(content_of_file));
        
    }
    else if(!(strcmp(b_f , "-b")))
    {
        char_pos += first_index;
        if(char_pos - number_of_chars + 1 < 0)
        {
            printf("The size you specified does not exist in the file!\n");
        }
        else
        {
            char newcontent[MAX_SIZE];
            int i = 0;
            for(;i <= char_pos - number_of_chars; i++)
            {
                newcontent[i] = content_of_file[i];
            }
            int j = i;
            i += number_of_chars;
            for(; j < strlen(content_of_file) - number_of_chars; j++)
            {
                newcontent[j] = content_of_file[i];
                i++;
            }
            fp = fopen(fileaddress , "w");
            fputs(newcontent , fp);
            fclose(fp);
        }
    }
    else if(!(strcmp(b_f , "-f")))
    {
        char_pos += first_index;
        if((char_pos + number_of_chars - 1) >= strlen(content_of_file))
        {
            printf("The size you specified does not exist in the file!\n");       
        }
        else
        {
            int i = 0;
            char new_content[MAX_SIZE];
            for (; i < char_pos; i++) {
                new_content[i] = content_of_file[i];
            }
            int j = i;
            i += number_of_chars;
            for(; j < strlen(content_of_file) - number_of_chars; j++)
            {
                new_content[j] = content_of_file[i];
                i++;
            }
            fp = fopen(fileaddress , "w");
            fputs(new_content , fp);
            fclose(fp);
        }
    }
    }

}

void insertstr(FILE *fp , int line_number , int char_pos , char fileaddress[] , char string_to_be_inserted[]) {
    int flag = 0;
    fp = fopen(fileaddress, "r");
    char *content_of_file;
    long numbytes;
    fseek(fp, 0L, SEEK_END);
    numbytes = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    content_of_file = (char *) calloc(numbytes, sizeof(char));
    fread(content_of_file, sizeof(char), numbytes, fp);
    fclose(fp);
    if(line_number == 1 && char_pos == 0 && strlen(content_of_file) == 0)
    {
        fp = fopen(fileaddress , "w");
        fputs(string_to_be_inserted , fp);
        fclose(fp);
        return;
    }
    int line_counter_with_enter = 1;
    for (int i = 0; i < strlen(content_of_file); i++) {
        if (content_of_file[i] == '\n') {
            line_counter_with_enter++;
        }
    }
    if (line_number > line_counter_with_enter) {
        flag = 1;
        printf("This Line doesnt exist in file!\n");
        printf("This file have %d lines\n", line_counter_with_enter - 1);
    }
    line_counter_with_enter--;
    bool keep_reading = true;
    int keepline = 1;
    int first_index = 0;
    int second_index = 0;
    if (flag == 0) {
        for (int j = 0; j < strlen(content_of_file); j++) {
            if (content_of_file[j] == '\n') {
                keepline++;
                if (keepline == line_number) {
                    first_index = j + 1;
                }
                if (keepline == line_number + 1) {
                    second_index = j - 1;
                    break;
                }
            }
        }
        int length_of_string = second_index - first_index;
        if (char_pos + first_index >= strlen(content_of_file)) {
            printf("This charachter doesn't exist in file!\nthe number of charachters is : %d\n",
                   strlen(content_of_file));
        }
        else
        {
//            if(line_number == 1 &&)
            char_pos += first_index - 1;
            char new_content_first_half[char_pos - 11];
            int i = 0;
            for(; i <= char_pos; i++)
            {
                new_content_first_half[i] = content_of_file[i];
            }
            char new_content_second_half[strlen(content_of_file) - char_pos];
            for(int j = 0; j < strlen(content_of_file) - char_pos; j++)
            {
                new_content_second_half[j] = content_of_file[i];
                i++;
            }
            fp = fopen(fileaddress, "w");
            fprintf(fp, "%s%s%s", new_content_first_half, string_to_be_inserted, new_content_second_half);
            fclose(fp);
            if(line_number == 1)
            {
                removestr(fp , 1 , char_pos + 1 , strlen(string_to_be_inserted) , "-f" , fileaddress);
            }

        }
    }
}