/*
 * =====================================================================================
 *
 *       Filename:  parsefile.c
 *
 *    Description:  get the passcode file and parse it
 *
 *        Version:  1.0
 *        Created:  03/28/2014 18:11:22
 *       Compiler:  gcc
 *
 *         Author:  JiaDi Yue (Brady), jdyue19@gmail.com
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <string.h>

int parse_psfile ( char *key, char *salt, char *pscode_file )
{
    FILE *ps_fd;
    ps_fd = fopen(pscode_file, "r");
    
    if(!ps_fd) {
        printf("ps_fd fopen error\n");
        return 0;
    }
    else {
        char file_line[128];
        int i = 0;
        while(i < 7){
            i++;
            fgets(file_line, 128, ps_fd);
        }
        strcpy(key, file_line + 1);
        key[28] = '\0';
//        printf("%s\n", key);
        while( i < 11 ) {
            i++;
            fgets(file_line, 128, ps_fd);
        }
        strcpy(salt, file_line + 1);
        salt[8] = '\0';
//        printf("%s\n", salt);

        fclose(ps_fd);
    }
    return 1;
}				/* ----------  end of function main  ---------- */

