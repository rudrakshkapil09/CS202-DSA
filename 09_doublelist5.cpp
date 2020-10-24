//Radix sort - array of queues
#include <iostream>
using namespace std;

//queue defintion
struct Queue {
    int size = 50;
    int f = -1;
    int r = -1;
    int elements[50];
};

//queue functions
void enqueue(Queue &q1, int x)
{
    if ((q1.r+1) % q1.size == q1.f)
        cout << "Queue full.\n";
    else {
        if (q1.f == -1)      //queue empty
            q1.f = 0;
        q1.r = (q1.r+1) % q1.size;
        q1.elements[q1.r] = x;
    }
}

int dequeue(Queue &q1) {
    if (q1.f == -1)
        cout <<"Queue empty";
    else {
        int t = q1.elements[q1.f];
        if (q1.f == q1.r)
            q1.f = q1.r = -1;
        else
            q1.f = (q1.f+1) % q1.size;
        return t;
    }
    return -1;
}

int queueIsEmpty(Queue q1) {
    if (q1.f == -1)
        return 1;
    else return 0;
}

//other functions:
void inputArrayFromBuckets(Queue bucket[], int input[])
{
    int j = 0;                      //input array counter
    for (int i = 0; i < 10; i++)  //bucket counter
        while (bucket[i].f != -1)
            input[j++] = dequeue(bucket[i]);
}

//radix function
void radixSort(Queue bucket[], int input[], int input_size)
{
    int i = 0, j = 0, digit = 1;
    while (digit < 1001) {
        j = 0;
        while (j < input_size) {
            i = (input[j]/digit)%10;
            enqueue(bucket[i], input[j]);
            j++;
        }
        inputArrayFromBuckets(bucket, input);
        digit *= 10;
    }
}

//[MAIN]
int main()
{
    Queue bucket[10];
    int size, input[20];
    //int input[10] = {786, 181, 202, 645, 193, 329, 864, 7, 148, 272};
    cout << "Enter number of integers: ";
    cin >> size;
    cout << "Enter list: ";
    for (int k = 0; k < size; k++)
        cin >> input[k];
    radixSort(bucket, input, size);
    for (int k = 0; k < 10; k++)
        cout << input[k] << " ";
    cout << endl;
}
