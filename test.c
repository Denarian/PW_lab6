#include<stdio.h>
#include<omp.h>

#define N 50

void z3()
{
    double start, end;
    int i,a = 7;
    start = omp_get_wtime();
    #pragma omp parallel for firstprivate(a) num_threads(7) schedule(static, 3)

    for(i = 0 ; i < N ; i++)
    {
        a++;
    }
    end = omp_get_wtime();
    printf("result: %d static 3: %lf\n",a,end - start);

    start = omp_get_wtime();
    #pragma omp parallel for firstprivate(a) num_threads(7) schedule(static)

    for(i = 0 ; i < N ; i++)
    {
       
        a++;
    }
    end = omp_get_wtime();
    printf("result: %d static: %lf\n",a,end - start);

    start = omp_get_wtime();
    #pragma omp parallel for firstprivate(a) num_threads(7) schedule(dynamic, 3)

    for(i = 0 ; i < N ; i++)
    {
       
        a++;
    }
    end = omp_get_wtime();
    printf("result: %d dynamic 3: %lf\n",a,end - start);

        start = omp_get_wtime();
    #pragma omp parallel for firstprivate(a) num_threads(7) schedule(dynamic)

    for(i = 0 ; i < N ; i++)
    {
       
        a++;
    }
    end = omp_get_wtime();
    printf("result: %d dynamic 3: %lf\n",a,end - start);



   return;
}

void z5(int a)
{
    int w = 0;
    #pragma omp parallel for num_threads(4)
    for(int i = 0; i<500; i++)
    {
        w+= a*a;
    }
    printf("result: %d\n",w);
}

void z6(int a)
{
    int w = 0;
    double start, end;
    start = omp_get_wtime();
    #pragma omp parallel for num_threads(4) schedule(static, 3)
    for(int i = 0; i < 500; i++)
    {
        #pragma omp critical
        {
            w+= a*a;
        }
    }
    end = omp_get_wtime();
    printf("critical\n");
    printf("wynik: %d,czas: %f\n", w, end - start);

    w = 0;
    start = omp_get_wtime();
    #pragma omp parallel for num_threads(4) schedule(static, 3)  reduction( + : w)
    for(int i = 0; i < 500; i++)
    {
        w+= a*a;
    }
    end = omp_get_wtime();
    printf("reduction\n");
    printf("wynik: %d,czas: %f\n", w, end - start);

    w = 0;
    start = omp_get_wtime();
    
    omp_lock_t lock;
    omp_init_lock(&lock);

    #pragma omp parallel for num_threads(4) schedule(static, 3)  reduction( + : w)
    for(int i = 0; i < 500; i++)
    {
        omp_set_lock(&lock);
        w += a * a;
        omp_unset_lock(&lock);
    }
    end = omp_get_wtime();
    printf("lock\n");
    printf("wynik: %d,czas: %f\n", w, end - start);
    omp_destroy_lock(&lock);

    #pragma omp parallel for num_threads(4) schedule(static, 3)
    for(int i = 0; i < 500; i++)
    {
        #pragma omp atomic
        w+= a*a;
    }
    printf("atomic\n");
    printf("wynik: %d,czas: %f\n", w, end - start);
}

int main()
{
    int i,a = 7;
//#pragma omp parallel for num_threads(7)
//#pragma omp parallel for private(a) num_threads(7)
//#pragma omp parallel for firstprivate(a) num_threads(7)
/*
#pragma omp parallel for shared(a) num_threads(7)

    for(i = 0 ; i < 10 ; i++)
    {
        printf("Thread %d a=%d\n",omp_get_thread_num(), a);
        a++;
    }
    printf("result: %d\n", a);
*/
//    z3();// zadanie 3 i 4
    //z5(2));//zadanie 5
    z6(2);
    
return 0;
}