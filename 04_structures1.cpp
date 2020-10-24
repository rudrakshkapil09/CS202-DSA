//Question 1 - set g to 7

#include <iostream>
using namespace std;

//union definitions
union u1 {
    int x;
    char y;
    float z;
};

union u2 {
    float f;
    int g;
    union u2 *h;
};

//structure definitions
struct s1 {
    int a;
    union u1 b;         //w/o pointer not working if s1 defined below s1
    struct s2 *c;
};

struct s2 {
    struct s2 *d;
    union u2 *e;
};


//[MAIN]
int main()
{
    struct s1 *T;
    T = new(s1);
    T->c = new(s2);
    T->c->e = new(u2);
    T->c->e->g = 7;
    
    cout << "The value of g is " << T->c->e->g << endl;
    return 0;
}



