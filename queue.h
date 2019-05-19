#include <stdint.h>
#include <stddef.h>

typedef struct q_handle q_handle;

typedef void lostfn( void* );

typedef struct q_config {
    size_t size;
    int32_t timeout;
    lostfn *lfn; /* Function to call on LOST elements */ 
}q_config;

#define QLFN( func ) (lostfn*)func


#define QARGS(...) (q_config){ .size = 8, .timeout = 0, __VA_ARGS__ }

q_handle* q_new( const q_config *config );
void* q_push( q_handle *q, void* data );
void* q_pop( q_handle *q );

/*
 * Return the unread entries in the buffer
 */
size_t q_waiting( q_handle *q );

/* 
 * Enumerate with mapping function.
 * Go through each entry without pop() and apply
 * the map function
 */
typedef void q_map_fn( q_handle *q, void *data );
void q_map( q_handle *q, q_map_fn *qfn );
