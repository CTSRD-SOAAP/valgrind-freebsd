
/* FIXME: this is basically a bad test as it is scheduling-
   sensitive.  Sometimes the output is:

   child: new value 6
   child: new value 10
   done, x = 10

   and sometimes

   child: new value 10
   done, x = 10
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Simple test program, no race.  Parent writes atomically to a counter
   whilst child reads it.  When counter reaches a prearranged value, 
   child joins back to parent.  Parent (writer) uses hardware bus lock;
   child is only reading and so does not need to use a bus lock. */

#undef PLAT_x86_darwin
#undef PLAT_amd64_darwin
#undef PLAT_x86_freebsd
#undef PLAT_amd64_freebsd
#undef PLAT_x86_linux
#undef PLAT_amd64_linux
#undef PLAT_ppc32_linux
#undef PLAT_ppc64_linux
#undef PLAT_arm_linux
#undef PLAT_s390x_linux
#undef PLAT_mips32_linux

#if defined(__APPLE__) && defined(__i386__)
#  define PLAT_x86_darwin 1
#elif defined(__APPLE__) && defined(__x86_64__)
#  define PLAT_amd64_darwin 1
#elif defined(__FreeBSD__) && defined(__i386__)
#  define PLAT_x86_freebsd 1
#elif defined(__FreeBSD__) && defined(__amd64__)
#  define PLAT_amd64_freebsd 1
#elif defined(__linux__) && defined(__i386__)
#  define PLAT_x86_linux 1
#elif defined(__linux__) && defined(__x86_64__)
#  define PLAT_amd64_linux 1
#elif defined(__linux__) && defined(__powerpc__) && !defined(__powerpc64__)
#  define PLAT_ppc32_linux 1
#elif defined(__linux__) && defined(__powerpc__) && defined(__powerpc64__)
#  define PLAT_ppc64_linux 1
#elif defined(__linux__) && defined(__arm__)
#  define PLAT_arm_linux 1
#elif defined(__linux__) && defined(__s390x__)
#  define PLAT_s390x_linux 1
#elif defined(__linux__) && defined(__mips__)
#  define PLAT_mips32_linux 1
#endif


#if defined(PLAT_amd64_linux) || defined(PLAT_x86_linux) \
    || defined(PLAT_amd64_darwin) || defined(PLAT_x86_darwin) \
    || defined(PLAT_amd64_freebsd) || defined(PLAT_x86_freebsd)
#  define INC(_lval,_lqual)	     \
      __asm__ __volatile__ ( \
      "lock ; incl (%0)" : /*out*/ : /*in*/"r"(&(_lval)) : "memory", "cc" )
#elif defined(PLAT_ppc32_linux) || defined(PLAT_ppc64_linux)
#  define INC(_lval,_lqual)		  \
   __asm__ __volatile__(                  \
      "1:\n"                              \
      "        lwarx 15,0,%0\n"           \
      "        addi 15,15,1\n"            \
      "        stwcx. 15,0,%0\n"          \
      "        bne- 1b\n"                 \
      : /*out*/ : /*in*/ "b"(&(_lval))    \
      : /*trash*/ "r15", "cr0", "memory"  \
   )
#elif defined(PLAT_arm_linux)
#  define INC(_lval,_lqual) \
  __asm__ __volatile__( \
      "1:\n"                                 \
      "        ldrex r8, [%0, #0]\n"         \
      "        add   r8, r8, #1\n"           \
      "        strex r9, r8, [%0, #0]\n"     \
      "        cmp   r9, #0\n"               \
      "        bne   1b\n"                   \
      : /*out*/ : /*in*/ "r"(&(_lval))       \
      : /*trash*/ "r8", "r9", "cc", "memory" \
  );
#elif defined(PLAT_s390x_linux)
#  define INC(_lval,_lqual) \
   __asm__ __volatile__( \
      "1: l     0,%0\n"                            \
      "   lr    1,0\n"                             \
      "   ahi   1,1\n"                             \
      "   cs    0,1,%0\n"                          \
      "   jl    1b\n"                              \
      : "+m" (_lval) :: "cc", "0","1" \
   )
#elif defined(PLAT_mips32_linux)
#  define INC(_lval,_lqual)                         \
     __asm__ __volatile__ (                         \
      "L1xyzzy1" _lqual":\n"                        \
      "        move $8, %0\n"                       \
      "        ll $9, 0($t0)\n"                     \
      "        addi $9, $9, 1\n"                    \
      "        sc $9, 0($t0)\n"                     \
      "        li $10, 1\n"                         \
      "        bne $9, $10, L1xyzzy1" _lqual        \
      : /*out*/ : /*in*/ "r"(&(_lval))              \
      : /*trash*/ "$8", "$9", "$10", "cc", "memory" \
        )
#else
#  error "Fix Me for this platform"
#endif



#define LIMIT 10

volatile int x = 0;

void* child_fn ( void* arg )
{
   int q = 0;
   int oldx = 0;
   struct timespec ts = { 0, 1000 * 1000 };

   while (1) {
      q = (x >= LIMIT);
      if (x != oldx) {
         oldx = x;
         printf("child: new value %d\n", oldx);
         fflush(stdout);
      }
      if (q) break;
      nanosleep(&ts, 0);
   }
   return NULL;
}

int main ( void )
{
   pthread_t child;
   int i;

   if (pthread_create(&child, NULL, child_fn, NULL)) {
      perror("pthread_create");
      exit(1);
   }

   for (i = 0; i < LIMIT; i++) {
      INC(x, "main");
      if (i == 5) sleep(1); /* make sure child doesn't starve */
   }

   if (pthread_join(child, NULL)) {
      perror("pthread join");
      exit(1);
   }

   printf("done, x = %d\n", x);

   return 0;
}
