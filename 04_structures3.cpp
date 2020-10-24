//Question 3 - make i = 7

#include <iostream>
using namespace std;

//structure & union definitions
union u1 {
    char x;
    int y;
};

struct s1 {
    int a;
    union u1 b;
    union u2 *c;
    union u1 *d;
    float e;
};

struct s2 {
    char g;
    int h;
};

union u3 {
    float j;
    int i;
};

union u2 {
    struct s2 m;
    union u3 n;
};

int main()
{
    struct s1 *T;
    T = new(s1);
    T->c = new(u2);
    (T->c->n).i = 7;
    
    cout << "The value of i is " << (T->c->n).i << endl;
    return 0;
}

