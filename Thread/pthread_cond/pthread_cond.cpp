#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>

pthread_cond_t cond;
pthread_mutex_t mutex;

//创建链表
struct Node
{
    int number;
    struct Node *next;
};
Node *head = NULL; //头节点为空

// 生产者模型
void *Producer(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&mutex);
        // struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
        Node *newNode = new Node();
        newNode->number = rand() % 1000;
        newNode->next = head;
        head = newNode;
        std::cout << "生产者:ID=" << pthread_self() << " "
                  << "number=" << newNode->number << std::endl;
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&cond); //当生产了，唤醒阻塞在条件变量上的线程
        sleep(rand() % 3);
    }
    return NULL;
}

// 消费者模型
void *Consumer(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&mutex);
        while (head == NULL) //条件变量
        {
            pthread_cond_wait(&cond, &mutex); //当没有生产了，阻塞消费者
        }
        Node *node = head;
        std::cout << "消费者:ID=" << pthread_self() << " "
                  << "number=" << node->number << std::endl;
        head = head->next;
        delete node;
        pthread_mutex_unlock(&mutex);
        sleep(rand() % 3);
    }
    return NULL;
}

int main()
{
    pthread_cond_init(&cond, NULL);
    pthread_mutex_init(&mutex, NULL);

    //创建生产者消费者线程
    pthread_t tid1[5], tid2[5];
    for (int i = 0; i < 5; ++i)
    {
        pthread_create(&tid1[i], NULL, Producer, NULL);
        pthread_create(&tid2[i], NULL, Consumer, NULL);
    }

    //销毁线程，回收资源
    for (int i = 0; i < 5; ++i)
    {
        pthread_join(tid1[i], NULL);
        pthread_join(tid2[i], NULL);
    }

    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&mutex);

    return 0;
}
