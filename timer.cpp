/*
 * it.c
 *
 *  Created on: 08 Eki 2013
 *      Author: ramazan.arikan
 */

#include <stdio.h>
#include <iostream>
#include <ia64/sys/inline.h>
#include <sys/_inttypes.h>
#include <machine/sys/inline.h>
#include <time.h>
#include <unistd.h>
#include <sys/param.h>
#include <sys/pstat.h>
#include <sys/pset.h>
#include <sys/unistd.h>

#define TRACEF printf

class IntervalCounter {
public:
   IntervalCounter()
   {

#if defined(_INCLUDE_HPUX_SOURCE) && !defined(__STDC_32_MODE__)
      m_start = getHRCurrNanosec();
#else
      m_start = getTimeOfDayCurrMicrosec() * 1000L;
#endif

#if defined(_INCLUDE_HPUX_SOURCE) && defined(__ia64) && \
   (defined(__HP_aCC) || defined(__GNUC__))

      m_start_CPU_ITC = getNanosecByCPU_ITC();

#endif

   }

   virtual ~IntervalCounter()
   {
      TRACEF("TimeDiff.delay: %lld nsec\n", getNanosecDiff());

#if defined(_INCLUDE_HPUX_SOURCE) && defined(__ia64) && \
   (defined(__HP_aCC) || defined(__GNUC__))
      if(s_initialized)
      TRACEF("TimeDiff.delay(ITC): %lld nsec\n", getNanosecByCPU_ITC() - m_start_CPU_ITC);
#endif
   }

   uint64_t getNanosecDiff()
   {
      uint64_t now;
#if defined(_INCLUDE_HPUX_SOURCE) && !defined(__STDC_32_MODE__)
      now = getHRCurrNanosec();
#else
      now = getTimeOfDayCurrMicrosec() * 1000L;
#endif

      return (now - m_start);
   }

public:
   static uint64_t getHRCurrNanosec()
   {
      uint64_t now = 0L;

#if defined(_INCLUDE_HPUX_SOURCE) && !defined(__STDC_32_MODE__)
      now = gethrtime();
#endif

      return now;
   }
   static uint64_t getTimeOfDayCurrMicrosec()
   {
      uint64_t now = 0L;

      struct timeval tmval;
      struct timezone tmzone;
      gettimeofday(&tmval, &tmzone);
      now = tmval.tv_sec * 1000000L + tmval.tv_usec;

      return now;
   }
   static uint64_t getTimeOfDayCurrMilisec()
   {
      return getTimeOfDayCurrMicrosec() / 1000L;
   }
   static uint64_t getHRCurrMicrosec()
   {
      return getHRCurrNanosec() / 1000L;
   }
   static uint64_t getHRCurrMilisec()
   {
      return getHRCurrNanosec() / 1000000L;
   }
   static uint64_t getCPUIntervalCounter()
   {
      uint64_t counter = 0L;

#if defined(_INCLUDE_HPUX_SOURCE) && defined(__ia64) && defined(__HP_aCC)
      counter = ((uint64_t) (_Asm_mov_from_ar(_AREG_ITC,_DFLT_FENCE)));
#elif defined(_INCLUDE_HPUX_SOURCE) && defined(__ia64) && defined(__GNUC__)
      __asm__ __volatile__("mov %0=ar.itc;;" : "=r" (counter)::"memory");
#endif

      return counter;
   }

   static uint64_t getNanosecByCPU_ITC()
   {
      uint64_t counter = getCPUIntervalCounter();

#if defined(_INCLUDE_HPUX_SOURCE) && defined(__ia64) && \
   (defined(__HP_aCC) || defined(__GNUC__))
      counter = counter / s_tick_cnt_pernsec;
#endif

      return (counter);
   }
   static void nanosleep(uint64_t nsec)
   {
      timespec time, remainder;
      time.tv_nsec = nsec; // % 1000000000L;
      time.tv_sec = 0; // nsec / 1000000000L;
      while (::nanosleep(&time, &remainder) == -1)
         time = remainder;
   }
public:
   static void init()
   {
      if (s_initialized)
         return;

#ifdef _INCLUDE_HPUX_SOURCE
#ifdef __ia64
      TRACEF("__ia64\n");
#if __HP_aCC
      TRACEF("__HP_aCC\n");
#elif __GNUC__
      TRACEF("__GNUC__\n");
#endif
#endif
#endif

#if defined(_INCLUDE_HPUX_SOURCE) && defined(__ia64) && \
   (defined(__HP_aCC) || defined(__GNUC__))

      TRACEF("_CPU_ITC_\n");
//
#if 1
      if (pset_create(&s_newpset) < 0) {
         TRACEF("Error: pset_create");
         //exit(EXIT_FAILURE);
         return;
      }
      if (pset_assign(s_newpset,(spu_t)0,NULL) < 0) {
         TRACEF("Error: pset_assign");
         //exit(EXIT_FAILURE);
         return;
      }
      if (pset_bind(s_newpset,P_PID,getpid(),NULL) < 0) {
         TRACEF("Error: pset_bind");
         //exit(EXIT_FAILURE);
         return;
      }
#endif

//

      s_clk_ticks = sysconf(_SC_CLK_TCK);

      if (pstat_getdynamic(&s_psd, sizeof(s_psd), (size_t) 1, 0) != -1) {

         s_number_of_processor = s_psd.psd_proc_cnt;

         s_psp = (struct pst_processor *) malloc(
               s_number_of_processor * sizeof(struct pst_processor));

         if (pstat_getprocessor(s_psp, sizeof(struct pst_processor),
                     s_number_of_processor, 0) != -1) {
            int i;
            int total_execs = 0;
            for (i = 0; i < s_number_of_processor; i++) {

               int execs = s_psp[i].psp_sysexec;

               total_execs += execs;

               s_tick_cnt_persec = s_psp[i].psp_iticksperclktick * s_clk_ticks;
               s_tick_cnt_pernsec = s_tick_cnt_persec / 1000000000.0;
               s_tick_cnt_perusec = s_tick_cnt_persec / 10000000.0;
               s_tick_cnt_permsec = s_tick_cnt_persec / 1000.0;

               TRACEF("s_tick_cnt_persec: %lld\n",s_tick_cnt_persec);
            }
         } else {
            TRACEF("Error: pstat_getprocessor\n");
            return;
         }
      } else {
         TRACEF("Error: pstat_getdynamic\n");
         return;
      }

#endif

      s_initialized = true;
   }
public:
   uint64_t m_start;

   //
   static bool s_initialized;

#if defined(_INCLUDE_HPUX_SOURCE) && defined(__ia64) && \
   (defined(__HP_aCC) || defined(__GNUC__))

   uint64_t m_start_CPU_ITC;

   static struct pst_dynamic s_psd;
   static struct pst_processor *s_psp;
   static uint64_t s_number_of_processor;
   static uint64_t s_clk_ticks;
   static uint64_t s_tick_cnt_persec;
   static double s_tick_cnt_pernsec;
   static double s_tick_cnt_perusec;
   static double s_tick_cnt_permsec;

   static psetid_t s_newpset;

#endif

};

bool IntervalCounter::s_initialized = false;

#if defined(_INCLUDE_HPUX_SOURCE) && defined(__ia64) && \
   (defined(__HP_aCC) || defined(__GNUC__))
struct pst_dynamic IntervalCounter::s_psd;
struct pst_processor* IntervalCounter::s_psp = NULL;
uint64_t IntervalCounter::s_number_of_processor = 0;
uint64_t IntervalCounter::s_clk_ticks = 0;
uint64_t IntervalCounter::s_tick_cnt_persec = 0;
double IntervalCounter::s_tick_cnt_pernsec = 0;
double IntervalCounter::s_tick_cnt_perusec = 0;
double IntervalCounter::s_tick_cnt_permsec = 0;
psetid_t IntervalCounter::s_newpset;
#endif

void cpu_status()
{
   struct pst_dynamic psd;
   struct pst_processor *psp;
   uint64_t tick_cnt_persec = 0;
   uint64_t clk_ticks = sysconf(_SC_CLK_TCK);

   printf("Clock tick persec: %lld", clk_ticks);

   if (pstat_getdynamic(&psd, sizeof(psd), (size_t) 1, 0) != -1) {
      size_t nspu = psd.psd_proc_cnt;
      psp = (struct pst_processor *) malloc(
            nspu * sizeof(struct pst_processor));
      if (pstat_getprocessor(psp, sizeof(struct pst_processor), nspu, 0)
            != -1) {
         int i;
         int total_execs = 0;
         for (i = 0; i < nspu; i++) {

            int execs = psp[i].psp_sysexec;

            total_execs += execs;

            tick_cnt_persec = psp[i].psp_iticksperclktick * clk_ticks;

            printf("%d exec()s on processor #%d\n", execs, i);
            printf("cpu_speed: %lld\n",
                  psp[i].psp_iticksperclktick * clk_ticks);
            printf("cpu_frequency: %d\n", psp[i].psp_cpu_frequency);
         }
         printf("total execs for the system were %d\n", total_execs);

      } else
         perror("pstat_getdynamic");
   } else
      perror("pstat_getdynamic");
}

int main()
{
   IntervalCounter::init();

   printf("Interval timer started!\n");
   uint64_t start; // = GET_ITIMER;
   uint64_t now;
   uint64_t max = 0xffffffffffffffffLL;
   uint64_t frequency = 160000000000LL;

   start = IntervalCounter::getHRCurrNanosec();

   printf("max period: %lld\n", max / frequency);

#ifdef _INCLUDE_HPUX_SOURCE
   printf("_INCLUDE_HPUX_SOURCE\n");
#ifdef __ia64
   printf("  __ia64\n");
#if __HP_aCC
   printf("     __HP_aCC\n");
#elif __GNUC__
   printf("     __GNUC__\n");
#else
   printf("     !__HP_aCC && __GNUC__\n");
#endif
#else
   printf("  !__ia64\n");
#endif
#else
   printf("!_INCLUDE_HPUX_SOURCE\n");
#endif
   cpu_status();
   while (1) {
      {
         IntervalCounter ico;
         sleep(1);
      }
      {
         IntervalCounter ico;
         usleep(1);
      }
      {
         IntervalCounter ico;
         //IntervalCounter::nanosleep(10);
      }
      now = IntervalCounter::getHRCurrNanosec();

      printf("interval: %lld nsec\n", now - start);
      start = now;
   }
}

