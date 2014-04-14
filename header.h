/*
 * =====================================================================================
 *
 *       Filename:  header.h
 *
 *    Description:  header file of the APP
 *
 *        Version:  1.0
 *        Created:  04/01/2014 22:34:26
 *       Compiler:  gcc
 *
 *         Author:  JiaDi Yue (Brady), jdyue19@gmail.com
 *
 * =====================================================================================
 */


typedef struct thread_arg {
    unsigned char * key;
    unsigned char * salt;
    char * pass_code;
    int thread_nu;
    int *p;
} t_arg;

char * base64_encode( const unsigned char * bindata, char * base64, int binlength );
int base64_decode( unsigned char * base64, unsigned char * bindata );
void * crack_thread(void *arg);
int parse_psfile ( char *key, char *salt, char *pscode_file );
