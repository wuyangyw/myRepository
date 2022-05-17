#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>

sem_t semProducer;                  //生产者信号量
sem_t semConsumer;                  //消费者信号量
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
        sem_wait(&semProducer);       //生产者信号量
        pthread_mutex_lock(&mutex);   //放在sem_wait内层，放外层会造成死锁

        // struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
        Node *newNode = new Node();
        newNode->number = rand() % 1000;
        newNode->next = head;
        head = newNode;
        std::cout << "生产者:ID=" << pthread_self() << " "
                  << "number=" << newNode->number << std::endl;

        pthread_mutex_unlock(&mutex); 
        sem_post(&semConsumer);        //消费者信号量，通知消费者消费
        sleep(rand() % 3);
    }
    return NULL;
}

// 消费者模型
void *Consumer(void *arg)
{
    while (1)
    {
        sem_wait(&semConsumer);       //消费者信号量
        pthread_mutex_lock(&mutex); 

        Node *node = head;
        std::cout << "消费者:ID=" << pthread_self() << " "
                  << "number=" << node->number << std::endl;
        head = head->next;
        delete node;
        
        pthread_mutex_unlock(&mutex);
        sem_post(&semProducer);       //生产者信号了，通知生产者生产
        sleep(rand() % 3);
    }
    return NULL;
}

int main()
{
    sem_init(&semProducer,0,1);      //初始化生产者信号量资源数为5
    sem_init(&semConsumer,0,0);      //初始化消费者信号量资源数为0,启动时自动阻塞

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

    pthread_mutex_destroy(&mutex);
    sem_destroy(&semProducer);
    sem_destroy(&semConsumer);

    return 0;
}
