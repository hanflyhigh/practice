#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define N 2   // Ïû·ÑÕß»òÕßÉú²úÕßµÄÊýÄ¿
#define M 30 // »º³åÊýÄ¿

int in = 0;   // Éú²úÕß·ÅÖÃ²úÆ·µÄÎ»ÖÃ
int out = 0; // Ïû·ÑÕßÈ¡²úÆ·µÄÎ»ÖÃ

int buff[M] = {0}; // »º³å³õÊ¼»¯Îª0£¬ ¿ªÊ¼Ê±Ã»ÓÐ²úÆ·

sem_t empty_sem; // Í¬²½ÐÅºÅÁ¿£¬ µ±ÂúÁËÊ±×èÖ¹Éú²úÕß·Å²úÆ·
sem_t full_sem;   // Í¬²½ÐÅºÅÁ¿£¬ µ±Ã»²úÆ·Ê±×èÖ¹Ïû·ÑÕßÏû·Ñ
pthread_mutex_t mutex; // »¥³âÐÅºÅÁ¿£¬ Ò»´ÎÖ»ÓÐÒ»¸öÏß³Ì·ÃÎÊ»º³å

int product_id = 0;   //Éú²úÕßid
int prochase_id = 0; //Ïû·ÑÕßid

/* ´òÓ¡»º³åÇé¿ö */
void print()
{
    int i;
    for(i = 0; i < M; i++)
        printf("%d ", buff[i]);
    printf("\n");
}

/* Éú²úÕß·½·¨ */
void *product()
{
    int id = ++product_id;

    while(1)
    {
        // ÓÃsleepµÄÊýÁ¿¿ÉÒÔµ÷½ÚÉú²úºÍÏû·ÑµÄËÙ¶È£¬±ãÓÚ¹Û²ì
        sleep(4);
        //sleep(1);

        sem_wait(&empty_sem);
        pthread_mutex_lock(&mutex);

        in = in % M;
        printf("product%d in %d. like: \t", id, in);

        buff[in] = 1;  
        print();  
        ++in;

        pthread_mutex_unlock(&mutex);
        sem_post(&full_sem);  
    }
}

/* Ïû·ÑÕß·½·¨ */
void *prochase()
{
    int id = ++prochase_id;
    while(1)
    {
        // ÓÃsleepµÄÊýÁ¿¿ÉÒÔµ÷½ÚÉú²úºÍÏû·ÑµÄËÙ¶È£¬±ãÓÚ¹Û²ì
        sleep(5);
        //sleep(1);

        sem_wait(&full_sem);
        pthread_mutex_lock(&mutex);

        out = out % M;
        printf("prochase%d in %d. like: \t", id, out);

        buff[out] = 0;
        print();
        ++out;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty_sem);
    }
}

int main()
{
    pthread_t id1[N];
    pthread_t id2[N];
    int i;
    int ret[N];

    // ³õÊ¼»¯Í¬²½ÐÅºÅÁ¿
    int ini1 = sem_init(&empty_sem, 0, M);
    int ini2 = sem_init(&full_sem, 0, 0);  
    if(ini1 && ini2 != 0)
    {
        printf("sem init failed \n");
        exit(1);
    }
    //³õÊ¼»¯»¥³âÐÅºÅÁ¿
    int ini3 = pthread_mutex_init(&mutex, NULL);
    if(ini3 != 0)
    {
        printf("mutex init failed \n");
        exit(1);
    }
    // ´´½¨N¸öÉú²úÕßÏß³Ì
    for(i = 0; i < N; i++)
    {
        ret[i] = pthread_create(&id1[i], NULL, product, (void *)(&i));
        if(ret[i] != 0)
        {
            printf("product%d creation failed \n", i);
            exit(1);
        }
        sleep(1);
    }
    //´´½¨N¸öÏû·ÑÕßÏß³Ì
    for(i = 0; i < N; i++)
    {
        ret[i] = pthread_create(&id2[i], NULL, prochase, NULL);
        if(ret[i] != 0)
        {
            printf("prochase%d creation failed \n", i);
            exit(1);
        }
        sleep(1);
    }
    //Ïú»ÙÏß³Ì
    for(i = 0; i < N; i++)
    {
        pthread_join(id1[i],NULL);
        pthread_join(id2[i],NULL);
    }
    exit(0);
}
