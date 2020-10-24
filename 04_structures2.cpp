//Question 2 - make m = 9

#include <iostream>
using namespace std;

//union definitions
union u1 {
    int x;
    float y;
    struct s2 *z;
};

union u2 {
    int p;
    char q;
};

//structure definitions
struct s1 {
    int a;
    union u1 b;
    int c;
    int d;
};

struct s2 {
    struct s2 *e;
    struct s3 *f;
};

struct s3 {
    int g;
    struct s4 *h;
    struct s3 *i;
};

struct s5 {
    int m;
    char n;
};

struct s4 {
    union u2 j;
    struct s5 k;
    struct s4 *l;
};


//[MAIN]
int main()
{
    struct s1 *S;
    S = new(s1);
    //S->b = new(u1);
    (S->b).z = new(s2);
    ((S->b).z)->f = new(s3);
    ((S->b).z)->f->h = new(s4);
    //((S->b).z)->f->h->k = new(s5);
    ((S->b).z)->f->h->k.m = 9;
    //no need to create new as the union/structure already declared above

    
    cout << "The value of m is " << ((S->b).z)->f->h->k.m << endl;
    return 0;
}





