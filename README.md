# ios Restriction PassCode Crack -C version



## Overview 

**ios Restriction PassCode Cracker**, this version of the application is written with C programming language,which is used to crack the Restriction PassCode of iphone/ipad.
(iphone/ipad 访问限制密码破解)

### Method
**bruce crack**

>1 .get the Base64 key and salt from the backup file in Computer.

>2 .decode the Base64 key and salt.

>3 .try from 1 to 9999 to with the pbkdf2-hmac-sha1 hash with openssl


### How to Use
1.Make sure to use Itunes to back up the ios device to Computer

2.change dir to the code.

```
./crack
```


### Source Code
```
  base64_cd.c : for base64 encoding and decoding
  header.h : header file
  iosPCCrack.c : main
  Makefile
  mythread.c : crack method thread
  parsefile.c : file parse
```


*jdyue19@gmail.com*
