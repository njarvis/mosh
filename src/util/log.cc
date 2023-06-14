#include <unistd.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <fcntl.h>
#include <time.h>

#include "log.h"

static int log_fd = 0;
static char const *log_name_prefix = "/tmp/";

int log( char const *format, ...)
{
  va_list ap;

  va_start( ap, format );
  if ( log_fd ) {
    time_t t;
    char timestamp[ 256 ];
    t = time(NULL);
    strftime( timestamp, sizeof( timestamp ), "%Y-%m-%dT%H:%M:%SZ ", gmtime( &t ) );
    dprintf( log_fd, "%s", timestamp );
    vdprintf( log_fd, format, ap );
  }
  va_end( ap );

  return 0;
}

int log_open( char const *suffix )
{
  char log_name[ 256 ];
  snprintf( log_name, sizeof( log_name ), "%s%s", log_name_prefix, suffix );
  if ( ( log_fd = open( log_name, O_WRONLY | O_CREAT | O_APPEND, 0644 ) ) == -1 ) {
    perror( "open" );
    return -1;
  }
  return 0;
}

int log_close()
{
  if ( log_fd ) {
    close( log_fd );
    log_fd = 0;
  }
  return 0;
}
