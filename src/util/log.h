#ifndef LOG_HPP
#define LOG_HPP

int log( char const * format, ... );
int log_open( char const * suffix );
int log_close();

#define LOG_DUMP_VECTOR( _v ) \
  char *_v##_str = new char[ _v.size() + 1 ]; \
  for ( unsigned int i = 0; i < _v.size(); ++i ) { \
    _v##_str[ i ] = _v[ i ]; \
  } \
  _v##_str[ _v.size() ] = 0

#endif
