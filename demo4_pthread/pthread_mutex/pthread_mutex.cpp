#include <pthread.h>
#include <unistd.h>
#include <iostream>

#define MAX 50

int number;            //全局变量充当临界区
pthread_mutex_t mutex; //互斥锁

//线程处理函数
void *FunA_num(void *arg)
{
    for (int i = 0; i < MAX; i++)
    {
        //临界区加锁
        pthread_mutex_lock(&mutex);
        int cur = number;
        cur++;
        usleep(10);
        number = cur;
        //临界区解锁
        pthread_mutex_unlock(&mutex);
        std::cout << "线程A:ID=" << pthread_self() << " "
                  << "number=" << number << std::endl;
    }
    return NULL;
}

void *FunB_num(void *arg)
{
    for (int i = 0; i < MAX; i++)
    {
        //临界区加锁
        pthread_mutex_lock(&mutex);
        int cur = number;
        cur++;
        number = cur;
        std::cout << "线程B:ID=" << pthread_self() << " "
                  << "number=" << number << std::endl;
        //临界区解锁
        pthread_mutex_unlock(&mutex);
        usleep(5);
    }
    return NULL;
}

int main()
{
    pthread_t p1, p2;
    pthread_mutex_init(&mutex, NULL); //初始化互斥锁

    //创建两个子线程
    pthread_create(&p1, NULL, FunA_num, NULL);
    pthread_create(&p2, NULL, FunB_num, NULL);

    //阻塞，资源回收
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    pthread_mutex_destroy(&mutex);

    return 0;
}
