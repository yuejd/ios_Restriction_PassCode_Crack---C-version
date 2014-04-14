/*
 * =====================================================================================
 *
 *       Filename:  mythread.h
 *
 *    Description:  the thread func help to speed up crack
 *
 *        Version:  1.0
 *        Created:  04/01/2014 17:28:37
 *       Compiler:  gcc
 *
 *         Author:  JiaDi Yue (Brady), jdyue19@gmail.com
 * =====================================================================================
 */
#include <openssl/evp.h>
#include <string.h>
#include <pthread.h>
#include "header.h"

#define KEK_KEY_LEN  20
#define ITERATION    1000 

void * crack_thread(void *arg) {
    unsigned char out[41];
    char pass[5];
    t_arg *k_s_args = (t_arg *)arg;
    printf("get into thread nu: %d\n", k_s_args->thread_nu);
    int i;
    for(i = k_s_args->thread_nu; i < 10000; i = i + 2) {
        if( *k_s_args->p ) {
            printf("thread %d exit\n", k_s_args->thread_nu);
            goto thread_end;
        }
        sprintf(pass, "%04d", i);
        PKCS5_PBKDF2_HMAC_SHA1(pass, strlen(pass), k_s_args->salt, strlen((char *)k_s_args->salt), ITERATION, KEK_KEY_LEN, out);

        //printf("%04d | ", i);
        //int j;
        //for(j = 0; j < KEK_KEY_LEN; j++) { 
        //    printf("%02x", out[j]); 
        //} 
        //printf("\n");

        if(memcmp((const void *)k_s_args->key, (const void *)out, 20))
            continue;
        else {
            strcpy(k_s_args->pass_code, pass);
            printf("thread %d work out\n", k_s_args->thread_nu);
            *k_s_args->p = 1;
            goto thread_end;
        }
    }
    printf("thread %d run over from loop\n", k_s_args->thread_nu);
thread_end:
    pthread_exit(NULL);
}
