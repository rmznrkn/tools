/*
 * ConsolTrace.h
 *
 *  Created on: 01 Eki 2013
 *      Author: ramazan.arikan
 */

#ifndef CONSOLTRACE_H_
#define CONSOLTRACE_H_

#include "quickfix/Mutex.h"
#include "quickfix/Message.h"
#include <map>
#include <vector>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>
#include <ia64/sys/inline.h>

#define GET_ITIMER ((uint64_t) (Asm_mov_from_ar(AREG_ITC,_DFLT_FENCE)))

#define TRACE_ENABLED 0
namespace HOST
{

class Trace {
public:
   virtual ~Trace()
   {
   }

   virtual void clear() = 0;
   virtual void backup() = 0;
   virtual void print(const std::string&) = 0;

};

class ConsolTrace {
public:

   static void print(const std::string& type, const std::string& value);
   static void printLog(const char* file, const char* func, int line,
         std::string type, std::string what);
   static std::string intToStr(int i)
   {
      char str[100];
      sprintf(str, "%d", i);
      return std::string(str);
   }
private:
   static FIX::Mutex s_mutex;
   static FIX::UtcTimeStamp m_time;
   static bool m_millisecondsInTimeStamp;
};
} /* namespace HOST */

//#ifdef __cplusplus
/*extern*/std::string trace_printf(const char *format, ...);
//#endif

#if TRACE_ENABLED
#define HTRACE(TYPE,WHAT) HOST::ConsolTrace::printLog(__FILE__,__FUNCTION__,__LINE__, TYPE, WHAT);
#define PTRACE(WHAT) HOST::ConsolTrace::printLog(__FILE__,__FUNCTION__,__LINE__, "INFO", WHAT);
#define TRACE_IN() HOST::ConsolTrace::printLog(__FILE__,__FUNCTION__,__LINE__, "INFO", "Top of function");
#define TRACE_SOUT() HOST::ConsolTrace::printLog(__FILE__,__FUNCTION__,__LINE__, "INFO", "return SUCCESS");
#define TRACE_FOUT() HOST::ConsolTrace::printLog(__FILE__,__FUNCTION__,__LINE__, "ERR ", "return FAILURE");
#define STRACE(WHAT) HOST::ConsolTrace::printLog(__FILE__,__FUNCTION__,__LINE__, "INFO", WHAT);
#define ETRACE(WHAT) HOST::ConsolTrace::printLog(__FILE__,__FUNCTION__,__LINE__, "ERR ", WHAT);
#define WTRACE(WHAT) HOST::ConsolTrace::printLog(__FILE__,__FUNCTION__,__LINE__, "WARN", WHAT);
#define INT2STR(INT) HOST::ConsolTrace::intToStr(INT)

#define TRACEF(FORMAT, args...) HOST::ConsolTrace::printLog(__FILE__,__FUNCTION__,__LINE__, "INFO", trace_printf(FORMAT,args))
#define ETRACEF(FORMAT, args...) HOST::ConsolTrace::printLog(__FILE__,__FUNCTION__,__LINE__, "ERR ", trace_printf(FORMAT,args))
#define WTRACEF(FORMAT, args...) HOST::ConsolTrace::printLog(__FILE__,__FUNCTION__,__LINE__, "WARN ", trace_printf(FORMAT,args))

#else
#define HTRACE(TYPE,WHAT) ;
#define PTRACE(WHAT)      ;
#define STRACE(WHAT)      ;
#define ETRACE(WHAT)      ;
#define WTRACE(WHAT)      ;
#define INT2STR(INT)      ;
#define TRACE_IN()        ;
#define TRACE_SOUT()      ;
#define TRACE_FOUT()      ;

#define TRACEF(FORMAT,args...);
#define ETRACEF(FORMAT,args...);
#define WTRACEF(FORMAT,args...);
#endif

namespace HOST
{

class IntervalCounter {
public:
   IntervalCounter()
   {
      m_start = GET_ITIMER;
   }
   virtual ~IntervalCounter()
   {
      TRACEF("TimeDiff.delay: %ld msec", getDifference());
   }
   uint64_t getDifference()
   {
      uint64_t now = GET_ITIMER;

      return (now - m_start);
   }
   //struct timeval m_start;
   uint64_t m_start;
};

}//namespace HOST

#endif /* CONSOLTRACE_H_ */
