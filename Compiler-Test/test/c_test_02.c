#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "iostream"
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <regex>
#include <Chalcedony\Chalcedony.h>
#include <CLexer.h>
#include <CParser.h>
//'l'
extern "C" {
       int catc\u0068( int a, int b );  // C 'catch()' function
}
inline int catch_func( int a, int b ) { return catc\u0068(a,b); }

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void *)1.09f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

class koko;
int main(void)
{
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (0 != err) {
        printf("can't create thread 1: %s\n", strerror(err));
        exit(-1);
    }
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (0 != err) {
        printf("can't create thread 2: %s\n", strerror(err));
        exit(-1);
    }

    err = pthread_join(tid1, &tret);
    if (0 != err) {
        printf("can't join with thread 1: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 1 exit code %d\n", (int)tret);

    err = pthread_join(tid2, &tret);
    if (0 != err) {
        printf("can't join with thread 2: %s\n", strerror(err));
        exit(-1);
    }
    printf("thread 2 exit code %d\n", (int)tret);

    return 0;
}
