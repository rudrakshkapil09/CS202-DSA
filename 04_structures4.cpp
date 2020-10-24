//Question 4 - i = 'a'

#include <iostream>
using namespace std;

//structure definition
struct s1 {
    struct s1 *a;
    int b;
    struct s2 *c;
};

struct s3 {
    int h;
    char i;
};

struct s2 {
    struct s2 *e;
    struct s3 f;
    struct s4 *g;
};

struct s4 {
    struct s4 *j;
    struct s4 *k;
};

//[MAIN]
int main()
{
    struct s1 *S;
    S = new (s1);
    S->c = new(s2);
    S->c->f.i = 'a';
    
    cout << "The value of i is " << S->c->f.i << endl;
    return 0;
}
