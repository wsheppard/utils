#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <regex.h>


#define ifnull( a, b ) ({\
    __auto_type _a = a;\
   _a ? _a : b; })

#define array_size(a) (sizeof a / sizeof *a)

#define for_each(a,b,c) \
       for ( uint32_t x = 0; x < c; x++ ) do\
    {\
               __auto_type a = b[x];

#define end_for }while(0) 

#define for_eacha(a,b) \
       for ( uint32_t x = 0; x < array_size(b); x++ ) do\
    {\
               __auto_type a = b[x];

#define for_eachn(a,b) \
           for ( uint32_t x = 0; b[x]; x++ ) do\
            {\
                       __auto_type a = b[x];

#define for_x(n) \
           for ( uint32_t x = 0; x < n; x++ ) do\
            {\

typedef char* cstr;
typedef cstr* cstrv;

/* 
 * Don't continue applications which cannot allocate memory
 */
static inline void* _alloc_or_die( size_t size)
{
    return ifnull ( calloc(1, size ), ({abort();NULL;}) );
}

#define gen_alloc(n,t) t *n = _alloc_or_die( sizeof( t ) ) 
#define cstr_alloc(n,len) cstr n = _alloc_or_die( len + 1 )

cstr cstrf( void* fmt, ... );

void _tokenize( const cstr _str, const cstr toks, cstr** arr );

/* 
 * Helper macro to allow you to specify your "array of pointer-to-cstr" as a simple
 * list of arguments such as - &cstr1, &cstr2 
 */
#define tokenize( pstr, toks, ... ) _tokenize( pstr, toks, (cstr*[]){ __VA_ARGS__ , NULL} )

/*
 * Standard tokenizer for whitespace
 */
#define wstoks( pstr, ... ) tokenize( pstr, "\t\n ", __VA_ARGS__ )

/*
 * Standard tokenizer for newlines 
 */
#define nltoks( pstr, ... ) tokenize( pstr, "\n", __VA_ARGS__ )

cstr fgetline( FILE* fp, size_t* len );
const cstr cgrep( const cstr str, const regex_t* regex );
const cstr grep( const cstr str, const cstr restr );
void cstr_free( const cstr str );

