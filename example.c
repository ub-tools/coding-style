/* Ethan Blanton <eblanton@buffalo.edu>
 * Example coding style for UB CSE.
 * 
 * Every file should begin with a block comment indicating the author
 * (with a contact point), and optionally a copyright statement,
 * followed by a single line description of what the file contains.  It
 * may include more information below that, if desired.
 *
 * All code should compile with -Wall -O2 and any warnings emitted
 * should be either eliminated or well-understood.  For example, this
 * file emits warnings for the inclusion of /* within comment blocks,
 * which is intentional, but all other warnings have been eliminated.
 */

/* Block comments should appear in /*-style blocks.  This helps
 * distinguish temporarily-commented code from documentation, as well as
 * a series of brief one-line comments from an extended block comment.
 *
 * The left margin of such comments should be set off by * characters,
 * and the opening /* and closing *-slash pairs can appear either on a
 * line by themselves or inline with the comment block, as circumstances
 * dictate; this block uses the inline notation at the open and the
 * dedicated line location for the close.
 *
 * Comments should generally precede that which they document, although
 * in some circumstances this may be altered.  End-of-line comments, for
 * example, or a loop description appearing immediately after the loop's
 * open bracket.
 *
 * Comments should be neatly formatted and use good grammar and
 * punctuation as much as possible.  Brevity may dictate a terse style
 * that is not entirely correct or aggressive abbreviation to fit, e.g.,
 * at the end of a line.
 */

/*
 * Basic formatting uses four-space indents, and tab characters are
 * never inserted for indentation.  Line continuations use a consistent
 * and readable formatting; e.g., continued argument lists may have an
 * indentation spacing them to the opening parenthesis of the argument
 * list, or may have a single additional basic indent inserted if the
 * line would otherwise be too long.
 *
 * Binary operators other than . and -> are surrounded by spaces, and
 * unary operators have no space between the operator and its argument.
 */

/*
 * Includes should appear at the top of a file unless absolutely
 * necessary that they appear otherwise.  In general, system-provided
 * includes should appear first, followed by library- or
 * dependency-provided includes, followed by local includes.  Unused
 * headers should be pruned.
 */
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

/* If we had a library include, it would be here. */
// #include <libwhatever.h>

#include "example.h"

/*
 * Constants should be declared as const variables wherever possible,
 * and preprocessor defines only when necessary.  All constants and
 * mutable global or file-static declarations should appear before any
 * other code in a source file.
 *
 * Constants should be IN_ALL_CAPS, and mutable variables in_snake_case
 * with an initial lowercase.
 */

/*
 * Magic values should be confined to constants.  You should never, for
 * example, declare a buffer of some integer size without defining a
 * constant that describes the size, with a comment explaining why it is
 * sized how it is.
 */

/* Maximum buffer size.  This must be a #define (and not a const int,
 * for example) due to restrictions in the C language.
 */
#define MAX_BUFSIZE 8192

/* Global mutable declared in myproject.h.  Indicates whether
 * initialization has been completed or not.  */
bool initialized = false;

/* Type definitions should appear after constants and global, unless a
 * type is required to define a constant or global, in which case it
 * should appear immediately before it is first required.
 *
 * Type names should use CamelCase, and opening braces for structs,
 * unions, etc. should appear on the first line of the declaration.
 */

/* I/O management buffer */
struct _IOBuffer {
    char buffer[MAX_BUFSIZE];
    int bufused;
};

/*
 * Function definitions should appear after all other types, constants,
 * globals, etc. have been declared.  Every function should be preceded
 * by a comment describing its utility and basic usage.  Function and
 * argument names should be descriptive.
 *
 * Opening braces for function definitions should appear on the same
 * line as the closing parenthesis for the argument list.
 *
 * Parenthesis for function arguments both at declaration and
 * application immediately follow the function name.
 */

/*
 * Allocates and returns an I/O buffer.  The buffer will be empty and
 * ready for use.
 *
 * It is good style to include (void) in the argument list of a function
 * that actually takes no arguments, due to unfortunate pre-ANSI
 * function prototype semantics.  (Basically, a prototype with no
 * arguments at all tells the compiler that the function exists, but
 * might take any set of arguments not defined here.)  The compiler will
 * accept either an empty argument list or (void).
 */
IOBuffer *iobuffer_create(void) {
    /* All variable declarations appear at the beginning of a block,
     * with the exception of loop variables, which may appear in the
     * loop condition.  Variables may be initialized at declaration
     * time. */
    IOBuffer *buf = malloc(sizeof(IOBuffer));

    buf->bufused = 0;

    return buf;
}

/*
 * Frees an I/O buffer allocated by iobuffer_create().
 *
 * The I/O buffer cannot be used after this call completes.
 */
void iobuffer_destroy(IOBuffer *buf) {
    /* Conditionals and loops have one space between the keyword and the
     * opening parenthesis, and ALWAYS use braces, even if the body is
     * only one line.
     *
     * Comparisons with NULL are explicit. */
    if (buf != NULL) {
        free(buf);
    }
}

/* Read a given number of bytes into a buffer from an open file descriptor.
 *
 * This function returns < 0 on error, 0 if the buffer is full, or the
 * number of bytes read on a successful read.  The number of bytes read
 * may be less than requested if there is not enough space in the buffer
 * or EOF is reached.
 *
 * buf:   the buffer to fill
 * fd:    the file descriptor from which to read
 * bytes: the number of bytes to read
 */
int iobuffer_read(IOBuffer *buf, int fd, size_t bytes) {
    size_t to_read; // may be < bytes if the buffer is full
    int result;     // will hold read result

    if (MAX_BUFSIZE - buf->bufused < bytes) {
        to_read = MAX_BUFSIZE - buf->bufused;
        if (to_read == 0) { // The buffer is completely full already
            return 0;
        }
    } else {
        to_read = bytes;
    }

    result = read(fd, buf->buffer + buf->bufused, to_read);

    if (result < 0) {
        return result;
    }

    buf->bufused += result;

    return result;
}

/* Return the status of a given IOBuffer.
 *
 * This function returns an IOBufferStatus enum containing the logical
 * status of the IOBuffer passed in.
 */
IOBufferStatus iobuffer_status(IOBuffer *buf) {
    /* Case statements have their labels flush with the case keyword,
     * and bodies indented.  Every label should end with a break,
     * return, or other statement that exits the conditional.  If a
     * fallthrough is actually desired, it should be indicated clearly
     * with a FALLTHROUGH comment.
     *
     * Every case statement should be complete when possible (that is,
     * it should handle every possible input value).  If a case switches
     * over an enum or user-defined type, it need not handle invalid
     * values.  Otherwise, it should have a default statement.
     */
    switch (buf->bufused) {
    case 0:
        return IOBUFFER_EMPTY;
    case MAX_BUFSIZE:
        return IOBUFFER_FULL;
    default:
        return IOBUFFER_DATA;            
    }
}
