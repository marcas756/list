/*! \copyright
 
   https://opensource.org/license/mit/

   Copyright 2013-2023 Marco Bacchi <marco@bacchi.at>
   
   Permission is hereby granted, free of charge, to any person
   obtaining a copy of this software and associated documentation
   files (the "Software"), to deal in the Software without
   restriction, including without limitation the rights to use,
   copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the
   Software is furnished to do so, subject to the following
   conditions:
   
   The above copyright notice and this permission notice shall be
   included in all copies or substantial portions of the Software.
   
   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
   OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
   NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
   HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
   WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/


/*!
    \file       unittest.h

    \brief      Provides preprocessor macros to write unit tests

    \details
*/

#ifndef UNITTEST_H_
#define UNITTEST_H_
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define UNITTEST_VERBOSE 1
#define UNITTEST_TALKATIVE 1

static int uttcerrcnt;
static int uttserrcnt;

#define UNITTEST_PROGRESS(var,start,stop) \
    unittest_printf_progress(var,start,stop)

#define UNITTEST_NEW_LOGFILE(filename) \
      FILE *fp = freopen(filename, "w" ,stdout); \
      fclose(fp);

#define UNITTEST_LOG2FILE(filename,...) \
      freopen(filename, "a" ,stdout); \
      UNITTEST_PRINTF(__VA_ARGS__); \
      fclose(fp);

#if UNITTEST_VERBOSE

    static char *uttsname;
    static char *uttcname;

    extern void unittest_printf_function ( const char * format, ... );
    #define UNITTEST_PRINTF(...) unittest_printf_function(__VA_ARGS__)

    #define uttcf  "<UTTCF>"
    #define uttcb  "<UTTCB>"
    #define uttsb  "<UTTSB>"
    #define uttce  "<UTTCE>"
    #define uttse  "<UTTSE>"

    void unittest_printf_progress(float var, float start, float stop)
    {
        static clock_t prev_clock = 0;

        if ( (clock() - prev_clock) <  CLOCKS_PER_SEC )
        {
            return;
        }

        prev_clock = clock();

        var = var-start;
        var /= stop-start;
        var = var*100;



        UNITTEST_PRINTF ("Progress %d %%\n",(int)var);
    }


    void unittest_printf_sss(const char *s1, const char *s2, const char *s3)
    {
        UNITTEST_PRINTF("%s %s %s\n",s1,s2,s3);
    }

    void unittest_printf_sssd(const char *s1, const char *s2, const char *s3, int d)
    {
        UNITTEST_PRINTF("%s %s %s %d\n",s1,s2,s3,d);
    }

    #if UNITTEST_TALKATIVE
        void unittest_printf_sssds(const char *s1, const char *s2, const char *s3, int d, char *s4)
        {
            UNITTEST_PRINTF("%s %s %s %d \"%s\"\n",s1,s2,s3,d,s4);
        }
    #endif

#else /* UNITTEST_VERBOSE */

    #define UNITTEST_PRINTF(...)

#endif /* UNITTEST_VERBOSE */

#if UNITTEST_VERBOSE

    #define UNITTEST_TESTCASE(name) \
        static void unittest_##name()

    #define UNITTEST_EXEC_TESTCASE(name)                                \
        do{                                                             \
            uttcerrcnt  = 0;                                            \
            uttcname = #name;                                           \
            unittest_printf_sss(uttcb,uttsname,uttcname);               \
            unittest_##name();                                          \
            unittest_printf_sssd(uttce,uttsname,uttcname,uttcerrcnt);   \
            uttserrcnt+=uttcerrcnt;                                     \
        }while(0)

        /* message is not compiled into code, thus it can be used as "in code" information (like remarks) */

        #if UNITTEST_TALKATIVE
            #define UNITTEST_ASSERT(message,test) \
                    do{if(!(test)){unittest_printf_sssds(uttcf,uttsname,uttcname,__LINE__,message);uttcerrcnt++;}}while(0)
        #else
            #define UNITTEST_ASSERT(message,test) \
                    do{if(!(test)){unittest_printf_sssd(uttcf,uttsname,uttcname,__LINE__);uttcerrcnt++;}}while(0)
        #endif


#else /* !UNITTEST_VERBOSE */
    #define UNITTEST_TESTCASE(name) \
        static void unittest_##name()

    #define UNITTEST_EXEC_TESTCASE(name)    \
        do{                                 \
            uttcerrcnt = 0;                 \
            unittest_##name();              \
            uttserrcnt+=uttcerrcnt;         \
        }while(0)

#define UNITTEST_ASSERT(message,test) \
        do{if(!(test)){uttcerrcnt++;}}while(0)
#endif /* UNITTEST_VERBOSE */


#if UNITTEST_VERBOSE

    #define UNITTEST_TESTSUITE(name)                 \
        static const char *const_uttsname = #name;   \
        int main()


    #define UNITTEST_TESTSUITE_BEGIN()                           \
        {                                                        \
            uttsname = (char*)const_uttsname;                    \
            uttserrcnt = 0;                                      \
            UNITTEST_PRINTF("%s %s \"%s\" \"%s\" \"%s\"\n",     \
            uttsb,uttsname,__FILE__,__DATE__,__TIME__);


    #define UNITTEST_TESTSUITE_END()                                      \
            UNITTEST_PRINTF("%s %s %d\n",uttse,uttsname,uttserrcnt);    \
        }                                                                 \
        return (uttserrcnt != 0)?EXIT_FAILURE:EXIT_SUCCESS;

#else /* UNITTEST_VERBOSE */

    #define UNITTEST_TESTSUITE(name)    \
            int main()

    #define UNITTEST_TESTSUITE_BEGIN()  { uttserrcnt = 0;
    #define UNITTEST_TESTSUITE_END()    } return (uttserrcnt != 0)?EXIT_FAILURE:EXIT_SUCCESS;

#endif /* UNITTEST_VERBOSE */

#endif /* UNITTEST_H_ */
