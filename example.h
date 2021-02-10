/* Ethan Blanton <eblanton@buffalo.edu>
 * Example coding style for UB CSE.
 *
 * This file is the coding style example for C headers.  The opening
 * comment in a C header should indicate what the header contains.
 *
 * This file contains the type declarations and function prototypes for
 * the iobuffer functions in example.c.
 */

/* Header files should usually be wrapped in this preprocessor
 * construction.  It causes the header file to be compiled only once,
 * even if it is included multiple times. */
#ifndef EXAMPLE_H_
#define EXAMPLE_H_

/*
 * The order of sections is the same as C files.  In this example, there
 * are no public constants, and the only public type is a partial type
 * for a structure defined in example.c.
 */

/* I/O management buffer
 *
 * The internal fields of this structure are private.
 *
 * Hiding this implementation actually makes this API useless, but as
 * it's a coding style example, that's not critical here.
 */
typedef struct _IOBuffer IOBuffer;

/*
 * Enumerated values and other list-like types should be laid out with
 * one value to a line unless another format is logically desirable for
 * some reason (e.g., the data forms a matrix of some kind, or there are
 * many values with very short names, etc.).  The final entry may have a
 * trailing comma.
 */
typedef enum {
    IOBUFFER_EMPTY,        /* This IOBuffer has no data */
    IOBUFFER_DATA,         /* This IOBuffer has data, but is not full */
    IOBUFFER_FULL          /* This IOBuffer is full */
} IOBufferStatus;

/*
 * Note that the documentation for these function prototypes is present
 * in the file example.c.  It is not necessary (or desirable) to
 * duplicate documentation.  Whether to place documentation at the
 * function prototype in a header or at the function definition in an
 * implementation file is a judgement call.  In general, public,
 * exported functions should have their documentation in headers.
 */

IOBuffer *iobuffer_create(void);

void iobuffer_destroy(IOBuffer *buf);

int iobuffer_read(IOBuffer *buf, int fd, size_t bytes);

IOBufferStatus iobuffer_status(IOBuffer *buf);

/* Preprocessor directives for conditional compilation should include
 * comments linking them together, as it becomes very difficult to
 * follow structure otherwise.  In this case, this directive matches
 * with #if EXAMPLE_H_. */
#endif /* EXAMPLE_H_ */
