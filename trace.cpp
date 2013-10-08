/*
 * ConsolTrace.cpp
 *
 *  Created on: 01 Eki 2013
 *      Author: ramazan.arikan
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <errno.h>
#include <malloc.h>
#include <ctype.h>
#include "syssrv.h"
#include "Host/Trace.h"


std::string trace_printf(const char *format, ...)
{
   char buffer[2048];
   va_list args;
   va_start (args, format);
   vsnprintf (buffer, 2048,format, args);
   va_end (args);
   return std::string(buffer);
}

namespace HOST
{

FIX::Mutex ConsolTrace::s_mutex;
FIX::UtcTimeStamp ConsolTrace::m_time;
bool ConsolTrace::m_millisecondsInTimeStamp = true;

void ConsolTrace::print(const std::string& type, const std::string& value)
{
   FIX::Locker l(s_mutex);
   //std::cout << value << std::endl;
   m_time.setCurrent();

   const char *ptime = (FIX::UtcTimeStampConvertor::convert(m_time,
         m_millisecondsInTimeStamp)).c_str();
   while (*ptime) {
      if (*ptime == '-') {
         ptime++;
         break;
      }
      ptime++;
   }
   std::cout << "TRC(" << type << "::" << ptime << ") => " << value
         << std::endl;
}
void ConsolTrace::printLog(const char* file, const char* func, int line,
      std::string type, std::string what)
{
#define WITDH 18

   char str[(WITDH * 3)/*file + func + line*/+ 32 /*extra*/];

   const char *fileName = (file);

   while (*file) {
      if (*file == '/')
         fileName = file + 1;
      file++;
   }

   int index = sprintf(str, " [ ");
   int i = 0;

   while (i < WITDH && fileName[i]) {
      str[index] = fileName[i];
      i++;
      index++;
   }

   while (i < WITDH) {
      str[index++] = ' ';
      i++;
   }

   str[index++] = ':';
   i = 0;
   while (i < WITDH && func[i]) {
      str[index] = func[i];
      i++;
      index++;
   }
   while (i < WITDH) {
      str[index++] = ' ';
      i++;
   }

   sprintf(str + index, ":line:%4d ] = ", line);
   std::string stdstr = str;
   stdstr += what;
   print(type, stdstr);
}


} /* namespace HOST */

