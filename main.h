#ifndef MAIN_H
#define MAIN_H
#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>

#define BUFF_SIZE 1024 /* use local buffer of 1024 chars */

/* DEFINE FLAGS */
#define FLAG_MINUS 1
#define FLAG_PLUS 2
#define FLAG_ZERO 4
#define FLAG_HASH 8
#define FLAG_SPACE 16

/* DEFINE SIZES LENGTH MODIFIERS */
#define SIZE_SHORT 1
#define SIZE_LONG 2
