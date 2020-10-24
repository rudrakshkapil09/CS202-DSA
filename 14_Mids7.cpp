//5.b) Special kd tree with union and searching function
#include <iostream>
using namespace std;
const int dim = 3;

//struct definition
union u {
    char ch;        //tag 1
    int num;        //tag 0
};

typedef
struct kdnode {
    struct kdnode *lchild;
    int first[dim/3];
    int tag[dim/3];
    union u mid[dim/3];
    string end[dim/3];
    struct kdnode *rchild;
} *KDPTR;

KDPTR newNode(kdnode data)
{
    KDPTR T = new(kdnode);
    T->lchild = T->rchild = NULL;
    for(int i = 0; i < dim/3; i++) {
        T->first[i] = data.first[i];
        T->end[i] = data.end[i];
        if (data.tag[i])
            T->mid[i].ch = data.mid[i].ch;
        else T->mid[i].num = data.mid[i].num;
    }
    return T;
}

void create(KDPTR &T, kdnode data, int i)
{
    if(!T)
        T = newNode(data);
    else {
        if (i < dim/3) {                //check first[]
            if (data.first[i] < T->first[i])
                return create(T->lchild, data, ((i+1)/3)%dim);
            else return create(T->rchild, data, ((i+1)/3)%dim);
        }
        if (i < 2*(dim/3)) {       //check mid depending on tag
            switch (data.tag[i]) {
                case 1:
                    if (data.mid[i].ch < T->mid[i].ch)
                        return create(T->lchild, data, ((i+1)/3)%dim);
                    else return create(T->rchild, data, ((i+1)/3)%dim);
                    break;
                case 0:
                    if (data.mid[i].num < T->mid[i].num)
                        return create(T->lchild, data, ((i+1)/3)%dim);
                    else return create(T->rchild, data, ((i+1)/3)%dim);
                    break;
            }
        }
        if (data.end[i].size() < T->end[i].size())      //check end
            return create(T->lchild, data, ((i+1)/3)%dim);
        else return create(T->rchild, data, ((i+1)/3)%dim);
    }
}

int checkFound(KDPTR T, kdnode data)
{
    int flag = 1;
    for(int j = 0; j < dim/3; j++) {
        if(T->first[j] != data.first[j] || T->end[j] != data.end[j] || ((data.tag[j]) && (T->mid[j]).ch != data.mid[j].ch) || ((!data.tag[j]) && (T->mid[j]).num != data.mid[j].num)) {
            flag = 0;
            break;
        }
    }
    if (flag) return 1;
    else return 0;
}

int search(KDPTR T, kdnode data, int i)
{
    if(T) {
        if (i < dim/3) {                //check first[]
            if(T->first[i] == data.first[i])
                return checkFound(T, data);
            else if (data.first[i] < T->first[i])
                return search(T->lchild, data, ((i+1)/3)%dim);
            else return search(T->rchild, data, ((i+1)/3)%dim);
        }
        else if (i < 2*(dim/3)) {       //check mid depending on tag
            switch (data.tag[i]) {
                case 1:
                    if(T->mid[i].ch == data.mid[i].ch)
                        return checkFound(T, data);
                    else if (data.mid[i].ch < T->mid[i].ch)
                        return search(T->lchild, data, ((i+1)/3)%dim);
                    else return search(T->rchild, data, ((i+1)/3)%dim);
                    break;
                case 0:
                    if(T->mid[i].num == data.mid[i].num)
                        return checkFound(T, data);
                    else if (data.mid[i].num < T->mid[i].num)
                        return search(T->lchild, data, ((i+1)/3)%dim);
                    else return search(T->rchild, data, ((i+1)/3)%dim);
                    break;
            }
        }
        else {                          //check end
            if(T->end[i] == data.end[i])
                return checkFound(T, data);
            else if (data.end[i].size() < T->end[i].size())
                return search(T->lchild, data, ((i+1)/3)%dim);
            else return search(T->rchild, data, ((i+1)/3)%dim);
        }
    }
    return 0;
}


//MAIN
int main()
{
    KDPTR T = NULL;
    kdnode k1, k2, k3, k4;
    k1.first[0] = 3;
    k1.end[0] = "hedj";
    k1.tag[0] = 0;
    k1.mid[0].num = 4;
    
    k2.first[0] = 4;
    k2.end[0] = "21";
    k2.tag[0] = 1;
    k2.mid[0].ch = '0';
    
    k3.first[0] = 2;
    k3.tag[0] = 0;
    k3.mid[0].num = 1;
    k3.end[0] = "third";
    
    k4.first[0] = 1;
    k4.tag[0] = 0;
    k4.mid[0].num = 3;
    k4.end[0] = "last";
    
    create(T, k1, 0);
    create(T, k2, 0);
    create(T, k3, 0);
    create(T, k4, 0);
    
    if (search(T, k1, 0) && search(T, k2, 0) && search(T, k3, 0) && search(T, k4, 0))
        cout << "All nodes present correctly.\n";
    
}
