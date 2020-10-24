//student table
#include <iostream>
#include <cstring>
using namespace std;

//STRUCT DEFINITIONS
typedef
struct hnode {
    char id[4];
    struct hnode *next;
    struct lnode *rlink;
} *HPTR;

union u1 {                  //ux
    struct hnode *idc;      //tag = 1
    struct lnode *xnext;    // tag = 0
};

union u2 {                  //ux
    struct hnode *ids;      //tag = 1
    struct lnode *ynext;    // tag = 0
};

typedef
struct lnode {
    int xtag;
    union u1 ux;
    int ytag;
    union u2 uy;
} *LPTR;

//FUNCTIONS
void setHead(HPTR &H, char id[])
{
    HPTR H2 = new(hnode);
    HPTR H3 = H;
    H2->rlink = NULL;
    H2->next = NULL;
    strcpy(H2->id, id);
    if (H == NULL)
        H = H2;
    else {
        while (H3->next != NULL)
            H3 = H3->next;
        H3->next = H2;
    }
}

void setStudentHeaders(HPTR &H)
{
    int n;
    char student_data[10][4] = {"S1", "S2", "S3", "S4", "S5", "S6", "S7", "S8", "S9", "S10"};
    cout << "Enter the number of students: ";
    cin >> n;
    for (int i = 0; i < n; i++)
        setHead(H, student_data[i]);
}

void setCourseHeaders(HPTR &H)
{
    int n;
    char student_data[10][4] = {"C1", "C2", "C3", "C4", "C5", "C6", "C7", "C8", "C9", "C10"};
    cout << "Enter the number of courses: ";
    cin >> n;
    for (int i = 0; i < n; i++)
        setHead(H, student_data[i]);
}

void addNode(HPTR S, HPTR C)
{
    LPTR L = new(lnode);
    if (S->rlink == NULL) {
        L->ytag = 1;
        (L->uy).ids = S;
        S->rlink = L;
    }
    else {              //add a while loop to find the last element
        LPTR T = S->rlink;
        while (T->ytag != 1)
            T = (T->uy).ynext;
        T->ytag = 0;
        (T->uy).ids = NULL;
        (T->uy).ynext = L;
        L->ytag = 1;
        (L->uy).ids = S;
    }
    if (C->rlink == NULL) {
        L->xtag = 1;
        (L->ux).idc = C;
        C->rlink = L;
    }
    else {
        LPTR T = C->rlink;
        while (T->xtag != 1)
            T = (T->ux).xnext;
        T->xtag = 0;
        (T->ux).idc = NULL;
        (T->ux).xnext = L;
        L->xtag = 1;
        (L->ux).idc = C;
    }
    
}

void inputData(HPTR &S, HPTR &C)
{
    char x[4], student[4], course[4];
    cin.getline(x,4);
    cout << "Enter student id: ";
    cin.getline(student, 4);
    cout << "Enter course id: ";
    cin.getline(course, 4);
    
    HPTR S2 = S, C2 = C;
    while (strcmp(S2->id, student) != 0)
        S2 = S2->next;
    while (strcmp(C2->id, course) != 0)
        C2 = C2->next;
    addNode(S2, C2);
}

void printStudentData(HPTR S)
{
    char student[4], x[4];
    cin.getline(x,4);
    cout << "Enter student id: ";
    cin.getline(student, 4);
    
    while (strcmp(S->id, student) != 0)
        S = S->next;
    
    cout << "Registered courses => ";
    LPTR T = S->rlink;
    LPTR T2 = S->rlink;
    while (T->ytag != 1) {
        while (T2->xtag != 1)
            T2 = (T2->ux).xnext;
        cout << (T2->ux).idc->id << " ";
        T = (T->uy).ynext;
        T2 = T;
    }
    if (T->ytag == 1)
        cout << (T->ux).idc->id << " ";
    cout << endl;
}

void printCourseData(HPTR C)
{
    char course[4], x[4];
    cin.getline(x,4);
    cout << "Enter course id: ";
    cin.getline(course, 4);
    
    while (strcmp(C->id, course) != 0)
        C = C->next;
    
    cout << "Registered students => ";
    LPTR T = C->rlink;
    LPTR T2 = C->rlink;
    while (T->xtag != 1) {
        while (T2->ytag != 1)
            T2 = (T2->uy).ynext;
        cout << (T2->uy).ids->id << " ";
        T = (T->ux).xnext;
        T2 = T;
    }
    if (T->xtag == 1)
        cout << (T->uy).ids->id << " ";
    cout << endl;
}

int main()
{
    char choice = '0';
    HPTR SPTR = NULL, CPTR = NULL;
    setStudentHeaders(SPTR);
    setCourseHeaders(CPTR);
    
    while (choice != 'Q' && choice != 'q') {
        cout << "\nA - Add registration data\nS - Print student data\nC - Print course data\nQ - Quit\nEnter choice => ";
        cin >> choice;
        switch (choice) {
            case 'Q': case 'q': break;
            case 'A': case 'a': inputData(SPTR, CPTR); break;
            case 'S': case 's': printStudentData(SPTR); break;
            case 'C': case 'c': printCourseData(CPTR); break;
            default: break;
        }
    }
    return 0;
}
