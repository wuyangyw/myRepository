#include <pthread.h>
#include <unistd.h>
#include <iostream>

void *Callback(void *arg)
{
    for (int i = 0; i < 5; i++)
    {
        std::cout << "子线程:i=" << i << std::endl;
    }
    std::cout << "子线程ID:" << pthread_self() << std::endl;
    return NULL;
}

int main()
{
    pthread_t tid;
    pthread_create(&tid, NULL, Callback, NULL);
    for (int i = 0; i < 5; i++)
    {
        std::cout << "主线程:i=" << i << std::endl;
    }
    std::cout << "主线程ID:" << pthread_self() << std::endl;
    sleep(3);
    return 0;
}
