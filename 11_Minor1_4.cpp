//Minor question 4 - decoding an encoded string
#include <iostream>
using namespace std;

//structure definitions
typedef
struct lnode {
    char data;
    struct lnode *next;
} *LPTR;

struct LQueue {
    LPTR f;
    LPTR r;
};

//special functions - SLL
void LaddAfter(LPTR &L, char x)
{
    LPTR T = new(lnode);
    T->data = x;
    if (L == NULL)
        L = T;
    else {
        L->next = T;
        L = T;
    }
}

void Lenqueue(LQueue &LQ, char x)
{
    int was_empty = 0;
    if (LQ.r == NULL) was_empty = 1;
    LaddAfter(LQ.r, x);
    if (was_empty) LQ.f = LQ.r;
}

int LqueueIsEmpty(LQueue LQ)
{
    if (LQ.f == NULL)
        return 1;
    else return 0;
}

char LdeleteFirst(LPTR &L)
{
    char x = L->data;
    L = L->next;
    return x;
}

char Ldequeue(LQueue &LQ)
{
    if (LqueueIsEmpty(LQ)) {
        cout << "Queue empty.\n";
        return '0';
    }
    else {
        int is_one_element = 0;
        if (LQ.f == LQ.r)
            is_one_element = 1;
        char x = LdeleteFirst(LQ.f);
        if (is_one_element) LQ.f = LQ.r = NULL;
        return x;
    }
}

//special function
void decodeString(LQueue Q, char input[], char out[])
{
    static int index = 0, midindex = 0;
    static char ch;
    static int count;
    ch = input[index++];
    if (index > 20) return;
    if (isdigit(ch)) {
        count = ch - '0';
    }
    else if (ch == ']') {
        char x[10] = {}, y;
        while (!LqueueIsEmpty(Q)) {
            y = Ldequeue(Q);
            x[midindex++] = y;
        }
        for (int i = 0; i < count; i++)
            strcat(out, x);
        count = 0;
        midindex = 0;
    }
    else if(isalpha(ch)) {
        Lenqueue(Q, ch);
    }
    decodeString(Q, input, out);
    
}

int main()
{
    char a[50] = "3[a]2[bcd]5[d]", out[50] = {};
    LQueue Q;
    Q.f = Q.r = NULL;
    decodeString(Q, a, out);//, 9);
    for (int i = 0; i < 20; i++)
        cout << out[i] << " ";
}
