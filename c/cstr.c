#include <stdarg.h>
#include <string.h>

#include "cstr.h"

#undef DEBUG
//#define DEBUG

#ifdef DEBUG
#define dprintf(...) printf( __VA_ARGS__ )
#else
#define dprintf(...) do{}while(0)
#endif

cstr cstrf( void* fmt, ... )
{
    size_t len;
    va_list args;
    va_start ( args, fmt);
    len = vsnprintf( NULL, 0, fmt, args );
    va_end( args );
   
    cstr_alloc( str, len );
    
    va_start ( args, fmt);
    vsprintf( str, fmt, args );
    va_end( args );

    return str;
}

void cstr_free( const cstr str )
{
    free(str);
}

void _tokenize( const cstr _str, const cstr toks, cstr** arr )
{
    cstr str = strdup(_str);
    cstr ctx;
    cstr **c = arr;
    for( 
            cstr tok = strtok_r( str, toks, &ctx ); 
            tok && *c; 
            c++, tok = strtok_r( NULL,  toks, &ctx )
            )
    {
        dprintf("TOK[%p][%s] \t ARR[%p][%p]\n", tok, tok, *c, **c);
        **c = strdup(tok);
    }
    cstr_free(str);
}

/*
 * Use relative index and return that
 * part of the string.
 * Such as "-2" - returns the second-to-last 
 * address of the string
 */
cstr cstridx( cstr str, int32_t idx )
{
    if ( idx < 0 )
        idx += strlen( str );

    return str + idx;
}

/*
 * Read a line at a time from the file pointer.
 */
cstr fgetline_r( FILE* fp, size_t* len, void* linebuf, size_t linesz )
{
    size_t sz = 0;

    dprintf("**GETLINE Start..\n");

    cstr ret = fgets( linebuf, linesz, fp );

    if(ret)
    {
        cstr lch = cstridx( ret, -1 );
        if ( *lch == '\n' )
            *lch = 0;

        sz = strlen( ret );
    }

    dprintf("fgetline: %d bytes at %p\n", sz, ret );
    
    *len = sz;
    return (const cstr)ret;
}

/*
 * Run a "grep" on the input string. Will return NULL if no match.
 * Takes a pre-compiled regex 
 */
const cstr cgrep( const cstr str, const regex_t* regex )
{
    return regexec(regex, str, 0, NULL, 0 ) ? (const cstr)NULL : str;
}

/*
 * Same as cgrep but compiles the regex for you on-the-fly
 */
const cstr grep( const cstr str, const cstr restr )
{
    regex_t regex;
    cstr ret;
    regcomp( &regex, restr, 0 );
    ret = cgrep( str, &regex );
    regfree( &regex );
    return ret;
}







