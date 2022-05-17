#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>

#define MAX 50

int number;              //全局变量充当临界区
pthread_rwlock_t rwlock; //读写锁

//线程处理函数
void *FunRead(void *arg)
{
    for (int i = 0; i < MAX; ++i)
    {
        //临界区加锁
        pthread_rwlock_rdlock(&rwlock);
        std::cout << "读线程:ID=" << pthread_self() << " "
                  << "number=" << number << std::endl;
        pthread_rwlock_unlock(&rwlock); //临界区解锁
        usleep(rand() % 5);
    }
    return NULL;
}

void *FunWrite(void *arg)
{
    for (int j = 0; j < MAX; ++j)
    {
        //临界区加锁
        pthread_rwlock_wrlock(&rwlock);
        int cur = number;
        cur++;
        number = cur;
        std::cout << "写线程:ID=" << pthread_self() << " "
                  << "number=" << number << std::endl;
        //临界区解锁
        pthread_rwlock_unlock(&rwlock);
        usleep(5);
    }
    return NULL;
}

int main()
{
    pthread_t p1[5], p2[3];
    pthread_rwlock_init(&rwlock, NULL); //初始化互斥锁

    //创建5个读子线程，3个写子线程
    for (int i = 0; i < 5; ++i)
    {
        pthread_create(&p1[i], NULL, FunRead, NULL);
    }

    for (int j = 0; j < 3; ++j)
    {
        pthread_create(&p2[j], NULL, FunWrite, NULL);
    }

    //阻塞，资源回收
    for (int i = 0; i < 5; ++i)
    {
        pthread_join(p1[i], NULL);
    }

    for (int j = 0; j < 3; ++j)
    {
        pthread_join(p2[j], NULL);
    }

    pthread_rwlock_destroy(&rwlock);

    return 0;
}
