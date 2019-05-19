#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <errno.h>

#include "queue.h"
#include "cstr.h"

#undef DEBUG
//#define DEBUG

#ifdef DEBUG
#define dprintf(...) printf( __VA_ARGS__ )
#else
#define dprintf(...) do{}while(0)
#endif

typedef void* q_entry;
typedef q_entry* q_buffer;
typedef int32_t q_index ;

#define _q_alloc() _alloc_or_die( sizeof(q_handle) ) 
#define _q_buf_alloc(size) _alloc_or_die(size * sizeof(q_entry))

struct q_handle {
    q_buffer buffer;
    q_index r;
    q_index w;
    pthread_mutex_t lock;
    pthread_cond_t data;
    const q_config *config;
};

static void q_get( q_handle* q )
{
    pthread_mutex_lock( &q->lock ); 
}

static void q_put( q_handle* q )
{
    pthread_mutex_unlock( &q->lock ); 
}


static q_index q_inc( q_handle* q, q_index x )
{
    q_index ret = x;

    ret++;

    if (ret >= (int32_t)q->config->size)
        ret = 0;

    return ret;
}



static q_index _q_entries( q_handle* q )
{
    q_index ret;
    
    ret = q->w - q->r;
    
    if (ret < 0)
        ret += q->config->size;

    return ret;
}

static void q_timeout( int32_t secs, struct timespec *ts )
{
    clock_gettime( CLOCK_REALTIME, ts );
    ts->tv_sec += secs;
}

static int32_t _q_wait( q_handle* q, int32_t secs )
{
    struct timespec ts;
    int32_t rc = 0;
            
    q_timeout( secs, &ts );

    while( !_q_entries(q) && rc == 0 )
    {
        rc = pthread_cond_timedwait( &q->data, &q->lock, &ts );
    }

    return rc;
}

void* q_pop( q_handle *q )
{
    q_entry ret = NULL;
    
    q_get( q );
    dprintf("QPOP[ %d:%d ][%zd]\n", q->w, q->r, q->config->size );

    if ( !_q_entries(q) )
    {
        if ( !q->config->timeout || _q_wait(q,q->config->timeout) )
        {
            q_put( q );
            return NULL;
        }
    }

    ret = q->buffer[ q->r ];
    q->buffer[ q->r ] = NULL;

    q->r = q_inc( q, q->r );

    q_put( q );

    return ret;
}

void* q_push( q_handle *q, void* data )
{
    q_get( q );
    dprintf("QPUSH[ %d:%d ][%zd]\n", q->w, q->r, q->config->size );

    q->buffer[ q->w ] = data;

    q->w = q_inc( q, q->w );


    if ( q->w == q->r )
    {
        printf("**** WARNING:Lost data\n");

        if(q->config->lfn)
            q->config->lfn( q->buffer[ q->r ] );

        q->r = q_inc( q, q->r );
    }

    pthread_cond_broadcast( &q->data );
        
    q_put( q );

    return data;
}

size_t q_waiting( q_handle *q )
{
    size_t ret;

    q_get (q );
    ret = _q_entries(q);
    q_put (q);

    return ret;
} 

void q_map( q_handle *q, q_map_fn *qfn )
{
    q_get (q );

    for_each( data, q->buffer, q->config->size )
    {
        if (data)
            qfn( q, data );
    }
    end_for;

    q_put (q);
} 

q_handle* q_new( const q_config *config )
{
    q_handle* q = _q_alloc();
    q->buffer = _q_buf_alloc( config->size );
    
    pthread_mutex_init( &q->lock, NULL );
    pthread_cond_init( &q->data, NULL );
    q->config = config;
    dprintf("Q SIZE: %zd\n", q->config->size );
    dprintf("Q TIMO: %d\n", q->config->timeout );

    return q;
}



