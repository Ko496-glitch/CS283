#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define BUFFER_SZ 50

//prototypes
void usage(char *);
void print_buff(char *, int);
int  setup_buff(char *, char *, int);

//prototypes for functions to handle required functionality
int  count_words(char *, int, int);
//add additional prototypes here


int setup_buff(char *buff, char *user_str, int len){
    if(strlen(user_str)>=len){
        return -1;
    }
    strcpy(buff,user_str);
    return strlen(buff);
    //TODO: #4:  Implement the setup buff as per the directions
}

void print_buff(char *buff, int len){
    printf("Buffer:  ");
    for (int i=0; i<len; i++){
        putchar(*(buff+i));
    }
    putchar('\n');
}

void usage(char *exename){
    printf("usage: %s [-h|c|r|w|x] \"string\" [other args]\n", exename);

}

int count_words(char *buff, int len, int str_len){
    //YOU MUST IMPLEMENT
    return 0;
}

//ADD OTHER HELPER FUNCTIONS HERE FOR OTHER REQUIRED PROGRAM OPTIONS

int main(int argc, char *argv[]){

    char *buff;             //placehoder for the internal buffer
    char *input_string;     //holds the string provided by the user on cmd line
    char opt;               //used to capture user option from cmd line
    int  rc;                //used for return codes
    int  user_str_len;      //length of user supplied string

    //TODO:  #1. WHY IS THIS SAFE, aka what if arv[1] does not exist?
    //We check (argc < 2) just to ensure that user atleast input two arguements.If argv does not exist we will go on to call the usage() fucnction and would exit.

    if ((argc < 2) || (*argv[1] != '-')){
        usage(argv[0]);
        exit(1); //We check (argc < 2) so if the user doesn't supply argv[1], we never access it.
                // Hence if argv[1] doesn't exist, we call usage() and exit, preventing an out-of-bounds read.
    }

    opt = (char)*(argv[1]+1);   //get the option flag

    //handle the help flag and then exit normally
    if (opt == 'h'){
        usage(argv[0]);
        exit(0);
    }

    //WE NOW WILL HANDLE THE REQUIRED OPERATIONS

    //TODO:  #2 Document the purpose of the if statement below
     // If statement here is just validating the fact that number of arguements are atleast 3 otherwise terminate the program.
    if (argc < 3){
        usage(argv[0]);
        exit(1);
    }

    input_string = argv[2]; //capture the user input string

    //TODO:  #3 Allocate space for the buffer using malloc and
    //          handle error if malloc fails by exiting with a 
    //          return code of 99
    // CODE GOES HERE FOR #3

    //Code for #3 starts here. We are dynamically allocating the memory.
    buffer = (char*)malloc(BUFFER_SIZE * sizeof(char));
    if (buffer == NULL) {
        fprintf(stderr, "Error");
        exit(99);
    }

    user_str_len = setup_buff(buff, input_string, BUFFER_SZ);     //see todos
    if (user_str_len < 0){
        printf("Error setting up buffer, error = %d", user_str_len);
        exit(2);
    }

    switch (opt){
        case 'c':
            rc = count_words(buff, BUFFER_SZ, user_str_len);  //you need to implement
            if (rc < 0){
                printf("Error counting words, rc = %d", rc);
                exit(2);
            }
            printf("Word Count: %d\n", rc);
            break;

        case 'r':
            for(int i =0;i<user_str_len/2;i++){
                char num = buff[i];
                buff[i] = buff[user_str_len -1 -i];
                buff[user_str_len - 1 -i] = num;
            }
            printf("Reversed Buffer: ");
            printf(buff,user_str_len);
            break;

        case 'w':
                rc = 0;
                for (int i = 0; i < user_str_len; i++) {
                 if (strchr("AEIOUaeiou", buff[i])) {
                rc++;
            }   
    }
                printf("Count of vowwel would be: %d\n", rc);
                break;

        //TODO:  #5 Implement the other cases for 'r' and 'w' by extending
        //       the case statement options
        default:
            usage(argv[0]);
            exit(1);
    }

    //TODO:  #6 Dont forget to free your buffer before exiting
    print_buff(buff,BUFFER_SZ);
    free(buff);
    exit(0);
}

//TODO:  #7  Notice all of the helper functions provided in the 
//          starter take both the buffer as well as the length.  Why
//          do you think providing both the pointer and the length
//          is a good practice, after all we know from main() that 
//          the buff variable will have exactly 50 bytes?
//  
//          So by providig the pointe and the length ensures safety, flexibility and clarity.
        //1) We know the function setup_biff() is making sure that if we passed the size more that what program can handle which is 50 bytes in this case it willl terminate/
        //2) Function like count_words takes both buffer_size len and str_len to clarify and enforce size imits during operations.