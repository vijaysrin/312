// String ADT <Project3.cpp>
// EE 312 Project 3 submission by
// Vijay Srinivasan
// vks445
// Slip days used: <0>
// Spring 2018
// Copy and paste this file at the top of all your submitted source code files.

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "String.h"

#define SIGNATURE (~0xdeadbeef)

/*
 * Helper macro to find the signature of a UTString
 * Treat this like a function that takes a UTString*
 * Accesses a uint32_t from where the signature should be located
 */
#define CHECK(s) (*(uint32_t*) ((s)->string + (s)->length + 1))

 /*
 * Checks if a UTString is valid or not.
 */
bool isOurs(UTString* s) {
    if (CHECK(s) == SIGNATURE) { return true; } 
    else { return false; }
}

uint32_t getLength(const char* s){
    int32_t lengthOfString = 0;
    for(int i = 0; *(s + i) != '\0'; i++){
        lengthOfString++;
    }
    return lengthOfString;
}

void setCheck(UTString* s){
    *(s->string + s->length) = '\0';
    uint32_t* pointCheck = (uint32_t*) (s->string + s->length + 1);
    *pointCheck = SIGNATURE;
}



/* 
 * Allocate a utstring on the heap. 
 * Initialize the string correctly by copying sr c.
 * Return a pointer to the UTString.
 */
UTString* utstrdup(const char* src) {
    UTString* UT  = (UTString*) malloc(sizeof(UTString));
    if(UT == NULL)
        return UT;
    UT->length = getLength(src);
    UT->capacity = getLength(src);
    UT->string = (char*) malloc(sizeof(char) * UT->length + 5);
    setCheck(UT);
    for(int i = 0; i < UT->length; i++){
        *(UT->string + i) = *(src + i);
    }
    return UT;
}

/* 
 * Returns 1he length of s.
 *  s must be a valid UTString.
 */
uint32_t utstrlen(const UTString* s) {
    return s->length;
}

/*
 * Append The string suffix to the UTString s.
 *  s must be a valid UTString.
 * Do not allocate any additional storage: only append as many characters
 *  as will actually fit in s. 
 * Update the length of s.
 * Return s with the above changes.
 */
UTString* utstrcat(UTString* s, const char* suffix) {
    assert(isOurs(s));
    int full = 0;
    for(int i = s->length; i < s->capacity; i++){
      if(*(suffix + i - s->length) == '\0'){
	full = 1;
	break;
      }
      *(s->string + i) = *(suffix + i - s->length);
    }
    if(full)
      s->length = s->length + getLength(suffix);
    else
      s->length = s->capacity; 
    setCheck(s);
    assert(isOurs(s));
    return s;
}

/* 
 * Copy src into dst.
 * dst must be a valid UTString. 
 * src is an ordinary string.
 * Do not allocate any additional storage: only copy as many characters
 * as will actually fit in dst.
 * Update the length of dst. 
 * Return dst with the above changes.
 */
UTString* utstrcpy(UTString* dst, const char* src) {
    assert(isOurs(dst));
    int full = 0;
    for(int i = 0; i < dst->capacity; i++){
        *(dst->string + i) = *(src + i);
        if(*(src + i) == '\0'){
	  full = 1;
	  break;
        }
    }
    if(full)
      dst->length = getLength(src);
     else
      dst->length = dst->capacity; 
    setCheck(dst);
    return dst;
}

/*
 * Free all memory associated with the given UTString. 
 */
void utstrfree(UTString* self) {
    free(self->string);
    free(self);
}

/* 
 * Make s have at least as much capacity as new_capacity.
 * s must be a valid UTString.
 * If s has enough capacity already, do nothing.
 * If s does not have enough capacity, then allocate enough capacity, 
 * copy the old string and the null terminator, free the old string,
 * and update all relevant metadata. 
 * Return s with the above changes.
 */
UTString* utstrrealloc(UTString* s, uint32_t new_capacity) {
    assert(isOurs(s));
    if(new_capacity <= s->capacity)
        return s;
    s->string = (char*) realloc(s->string, (sizeof(char) * new_capacity + 5));
    s->capacity = new_capacity;
    setCheck(s);
    assert(isOurs(s));
    return s;
}

