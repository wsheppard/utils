#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <regex.h>

/*
 * MACRO helper - return "a" if "a" is NOT NULL.
 * Otherwise return "b"
 * Only evaluate "a" and "b" ONCE.
 */
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

/* Represent strings which need to be free'd with
 * the cstr type. */
typedef char* cstr;

/* Represent vector of cstrs */
typedef cstr* cstrv;

/* 
 * Don't continue applications which cannot allocate memory
 */
static inline void* _alloc_or_die( size_t size)
{
    return ifnull ( calloc(1, size ), ({abort();NULL;}) );
}

/*
 * Helper MACRO to create pointer-to-type with name "name"
 * and allocate or die ( abort )
 */
#define gen_alloc(name,type) type *name = _alloc_or_die( sizeof( type ) ) 

/*
 * strdup wrapper which aborts() on fail
 */
#define cstrdup(str) _alloc_or_die( strlen(str) + 1 )

/*
 * Create cstr with "name" and size "size". Abort on allocation failure 
 */
#define cstr_alloc(name, size) cstr name = _alloc_or_die( size + 1 )

/*
 * CSTR Wrapper for printf. This automatically allocates ( or aborts() )
 * a cstr and this must be free'd. This function is the same as "asprintf()" 
 * but doesn't require the additional libraries */
cstr cstrf( void* fmt, ... );

/*
 * Read a line at a time - must provide scratch buffer and size 
 */
cstr fgetline_r( FILE* fp, size_t* len, void* linebuf, size_t linesz );

/*
 * Grep(regex) helpers 
 */
const cstr cgrep( const cstr str, const regex_t* regex );
const cstr grep( const cstr str, const cstr restr );

/* Wrapper on free() */
void cstr_free( const cstr str );

/*
 * Takes an array of pointer-to-cstr and fills each successive
 * entry in that array with a pointer to a new cstr that is created
 * from tokens found in "_str" of the kinds specified by "toks"
 *
 * Quits on the first NULL pointer-to-cstr in the array - this acts
 * as a natural way to cut processing.
 *
 * TODO: Have max num as separate arg and use MACROs to derive the
 * array size automatically
 */
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

