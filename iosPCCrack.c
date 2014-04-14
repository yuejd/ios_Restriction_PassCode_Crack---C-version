/*
 * =====================================================================================
 *
 *       Filename:  iosPCCrack.c
 *
 *    Description:  ios Restrictions Passcode cracker
 *
 *        Version:  1.0
 *        Created:  03/30/2014 22:31:27
 *       Compiler:  gcc
 *
 *         Author:  JiaDi Yue (Brady), jdyue19@gmail.com
 * =====================================================================================
 */
#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include "header.h"

#define HOMEDIR "/Users/yuejiadi/Library/Application Support/MobileSync/Backup/"
#define PSFILE "398bc9c2aeeab4cb0c12ada0f52eea12cf14f40b"

    int
main ( int argc, char *argv[] )
{
    char * bk_dir_name_array[10] = {NULL};
    DIR *directory_pointer;
    struct dirent *entry;
    int i = 0;
   
    if((directory_pointer = opendir( HOMEDIR )) == NULL)
        printf( "Error dir opening \n ");
    else
    {
        i = 0;
        while((entry = readdir(directory_pointer)) != NULL && i < 10)
        {
            if(entry->d_name[0] == '.')
                continue;
            bk_dir_name_array[i] = entry->d_name;
//            printf("%s\n", bk_dir_name_array[i]);
            i++;
        }
        closedir(directory_pointer);
    }

    i = 0;
    while(bk_dir_name_array[i]) {
        printf("backup file:%d\n", i+1);
        char pscode_file_name[256];
        char key64[30];
        char salt64[10];
        char pass_code[5];
        unsigned char key[42];
        unsigned char salt[10];
        strcpy(pscode_file_name, HOMEDIR);
        strcat(pscode_file_name, bk_dir_name_array[i]);
        strcat(pscode_file_name, "/");
        strcat(pscode_file_name, PSFILE);
        i++;
//        printf("%s\n", pscode_file_name);
        if( !parse_psfile(key64, salt64, pscode_file_name) )
            continue;
//        printf("%s\n", key64);
//        printf("%s\n", salt64);

        int key_bytes = 0;
        int salt_bytes = 0;
        key_bytes = base64_decode((unsigned char *)key64, key);
        salt_bytes = base64_decode((unsigned char *)salt64, salt);

        printf("key: ");
        int j = 0;
        for(j = 0; j < key_bytes; j++) { 
            printf("%02x", key[j]); 
        }
        printf("\n");
        printf("salt: ");
        for(j = 0; j < salt_bytes; j++) { 
            printf("%02x", salt[j]); 
        }
        printf("\n");

        clock_t start_time, finish_time;
        double duration;
        start_time = clock();

        pthread_t my_threads[2];
        t_arg my_t_arg[2];
        int p = 0;
        for(j = 0; j < 2; j++) {
            my_t_arg[j].key = key;
            my_t_arg[j].salt = salt;
            my_t_arg[j].pass_code = pass_code;
            my_t_arg[j].thread_nu = j;
            my_t_arg[j].p = &p;
            if((pthread_create(&my_threads[j], NULL, crack_thread, &my_t_arg[j])) != 0) {
                printf("thread created failed\n");
                exit(0);
            }
        }

        for(j = 0; j < 2; j++) {
            if(my_threads[j] != 0) {
                pthread_join(my_threads[j], NULL);
                //printf("thread %d over\n", j);
            }
        }

        printf("passcode: %s\n", pass_code);
        finish_time = clock();
        duration = (double)(finish_time - start_time) / CLOCKS_PER_SEC;
        printf("%f seconds\n", duration);
    }
    return EXIT_SUCCESS;
}
