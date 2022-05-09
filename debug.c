
#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>
#include <stdarg.h>

#ifdef DEBUG
   void debug(char* format, ...) {
      va_list arglist;
      va_start(arglist, format);
      vprintf(format, arglist);
      va_end(arglist);
   }
#else
   void debug(char* text, ...) { /* do nothing */ }
#endif

#endif // DEBUG_H