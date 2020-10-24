//C-Trie - inserting and searching not done
//the tag checking /skipping is not being done so problematic
//use skip field to remember which [i] position to compare with
#include <iostream>
using namespace std;
const int d = 3;

union u {
    char key[20];                           //tag = 0;
    struct trienode *ptr[d+1] = {NULL};  //tag = 1;
};

typedef
struct trienode {
    int tag;
    union u data;
} *TRIEPTR;

/*Insertion function*/
int getSize(char key[])
{
    int i = 0;
    while (key[i] != '\0') i++;
    return i;
}

int isSubString(char key[], char check[])   //returns 1 if key is a substring of check
{
    int i = 0;
    while (key[i] != '\0') {
        if (key[i] != check[i]) return 0;
        i++;
    }
    return 1;
}

void printKey(TRIEPTR T, char key[])
{
    if (!T)
        for (int i = 0; key[i] != '\0'; i++)
            cout << key[i];
    else
        for (int i = 0; T->data.key[i] != '\0'; i++)
            cout << T->data.key[i];
}

int getIndex(char ch)
{
    return int(ch) - 65;
}

TRIEPTR newPtrNode(int n)
{
    TRIEPTR T = new(trienode);
    T->tag = n;
    for (int i = 0; i <= d+1; i++)
        T->data.ptr[i] = NULL;
    return T;
}

TRIEPTR newKeyNode(char key[])
{
    TRIEPTR T = new(trienode);
    T->tag = 0;
    strcpy(T->data.key, key);
    return T;
}

int findDifference(char first[], char second[])
{
    int n = (strlen(first) < strlen(second)) ? strlen(first) : strlen(second);
    for (int i = 0; i < n; i++)
        if (first[i] != second[i]) return i;
    return n-1;
}

void insertKey(TRIEPTR &T, char key[], int i, int flag, TRIEPTR T1)
{
    if (!T && !flag)
        T = newKeyNode(key);
    else if ((T && flag) || (T && T->tag == 0)) {
        int pos = (T->tag == 0) ? findDifference(key, T->data.key) : i;
        if (pos == strlen(key)-1 || pos == strlen(T->data.key)-1) {
            TRIEPTR T2 = newPtrNode(pos+1);
            T2->data.ptr[d] = T;
            //insertKey(T1->data.ptr[getIndex(key[pos+1])], key, 0, 0, NULL);
            T2->data.ptr[getIndex(key[pos+1])] = newKeyNode(key);
            T = T2;
        }
        if (pos < T->tag) {
            TRIEPTR N = NULL;
            insertKey(N, key, pos, 0, NULL);
        }
        
        
        TRIEPTR L = T1 ? T1 : T;      //temp to store original value
        T = newPtrNode(pos);
        flag = (L && key[T->tag] == L->data.key[pos]) ? 1 : 0;
        
        if (isSubString(L->data.key, key) && L->data.key[pos] == '\0')
            T->data.ptr[d] = L;
        if (isSubString(key, L->data.key) && key[pos] == '\0')    //only for second entry
            T->data.ptr[d] = newKeyNode(key);
        
        if (L && !flag) {
            insertKey(T->data.ptr[getIndex(key[pos])], key, T->tag, flag, NULL);
            insertKey(T->data.ptr[getIndex(L->data.key[pos])], L->data.key, T->tag, flag, NULL);
        }
        else
            insertKey(T->data.ptr[getIndex(key[i])], key, T->tag, flag, L);
    }
    else if (T->tag > 0 && key[i] == '\0')
        T->data.ptr[d] = newKeyNode(key);
    else if (T->tag > 0)
        insertKey(T->data.ptr[getIndex(key[T->tag])], key, T->tag+1, flag, NULL);
}

/*Printing sorted function*/
int findKey(TRIEPTR T, char key[], int i)
{
    if (T == NULL) return 0;
    if (T->tag > 0 && key[T->tag] != '\0')
        return findKey(T->data.ptr[getIndex(key[T->tag])], key, T->tag+1);
    else {
        if (!strcmp(key, T->data.key))
            return 1;
        for (int j = 0; j <= i; j++)
            if (key[j] != T->data.key[j]) return 0;
        if (getSize(key) > getSize(T->data.key))
            return 0;
        return 2;
    }
}

void printFound(TRIEPTR T, char key[])
{
    printKey(NULL, key);
    int f = findKey(T, key, 0);
    if (f == 1)
        cout << "\t\t => found.\n";
    else if (f == 2)
        cout << "\t\t => found (prefix).\n";
    else cout << "\t\t => not found.\n";
}

/*Printing sorted function*/
void printSorted(TRIEPTR T, int i, int flag)
{
    if (T && i < d) {
        if (T->data.ptr[d] && flag)
            printSorted(T->data.ptr[d], 0, 0);
        if (T->tag == 0) {
            printKey(T, "");
            cout << ", ";
        }
        else if (T->tag > 0) {
            printSorted(T->data.ptr[i], 0, 1);
            printSorted(T, i+1, 0);
        }
    }
}

/*Deletion functions*/
int hasSomePointer(TRIEPTR T)
{
    for (int i = 0; i <= d; i++)
        if (T->data.ptr[i]) return 1;
    return 0;
}

int hasOnePointer(TRIEPTR T, TRIEPTR &P)
{
    if (!T) return 0;
    if (T->tag == 0) return 0;
    
    int flag = 0;
    for (int i = 0; i <= d; i++) {
        if (!flag && T->data.ptr[i]) {
            P = T->data.ptr[i];
            flag = 1;
            continue;
        }
        if (flag && T->data.ptr[i])
            return 0;
    }
    return flag;
}

void deleteKey(TRIEPTR &T, char key[], int i)
{
    if (T) {
        if (T->tag > 0 && key[i] != '\0') {
            deleteKey(T->data.ptr[getIndex(key[i])], key, i+1);
            
            TRIEPTR P = NULL;
            if (!hasSomePointer(T))
                T = NULL;
            else {
                int checkT = hasOnePointer(T, P);
                if (checkT != 0) {
                    TRIEPTR P2 = NULL;
                    while (hasOnePointer(P, P2)) {
                        //increase value of tag here
                        P = P2;
                    }
                    T = P;
                }
            }
        }
        else if (T->tag > 0 && key[i] == '\0') {
            if (T->data.ptr[d])
                T->data.ptr[d] = NULL;
        }
        else if (T->tag == 0)
            T = NULL;
    }
}

/*helper functions for main*/
char *getWord(string input)
{
    char *out = new char[20];
    for (int i = 0; input[i] != '\0'; i++)
        out[i] = input[i];
    return out;
}

void createTRIE(TRIEPTR &T, string input[], int n)
{
    cout << "Insertion...\n";
    for (int i = 1; i < n; i++) {
        cout << input[i] << " inserted.\n";
        insertKey(T, getWord(input[i]), 0, 0, NULL);
    }
    cout << endl << endl;
}

void checkTRIE(TRIEPTR &T, string input[], int n)
{
    cout << "Searching...\n";
    for (int i = 1; i < n; i++)
        printFound(T, getWord(input[i]));
}

void deleteTRIE(TRIEPTR &T, string input[], int n)
{
    cout << "\n\n\nDeletion...\n";
    for (int i = 0; i < n; i++) {
        cout << "\nDeletion of " << input[i] << ":\n";
        printFound(T, getWord(input[i]));
        deleteKey(T, getWord(input[i]), 0);
        printSorted(T, 0, 0);
        cout << "\n";
        printFound(T, getWord(input[i]));
        if (!T) {
            cout << "\nTrie no longer exists.\n";
            return;
        }
    }
}

//MAIN
int main()
{
    TRIEPTR T = NULL;
    char input[20] = {'A', 'A', 'B', 'B', 'C'};
    string insert_input[] = {"A", "AAB", "AAC", "AAA", "AABB"};
    string delete_input[] = {"A", "AAB", "CAB", "CAA", "AABBC", "ABBA", "ABBBC", "CBA", "BAAB", "BBC", "BBCC"};
    int num = sizeof(insert_input)/sizeof(insert_input[0]);
    
    //inserting and searching
    createTRIE(T, insert_input, num);
    checkTRIE(T, insert_input, num);
    
    //printing in order
    cout << "\n\nLexographical order:\n";
    printSorted(T, 0, 0);
    
    //deleting:
    //deleteTRIE(T, delete_input, num);
    return 0;
}

/*––––––––––––––––––––*/

//Trie template
#include <iostream>
using namespace std;
const int d = 3;

union u {
    char key[20];                           //tag = 0;
    struct trienode *ptr[d+1] = {NULL};  //tag = 1;
};

typedef
struct trienode {
    int tag;
    union u data;
} *TRIEPTR;

/*Insertion function*/
int getSize(char key[])
{
    int i = 0;
    while (key[i] != '\0') i++;
    return i;
}

int isSubString(char key[], char check[])   //returns 1 if key is a substring of check
{
    int i = 0;
    while (key[i] != '\0') {
        if (key[i] != check[i]) return 0;
        i++;
    }
    return 1;
}

void printKey(TRIEPTR T, char key[])
{
    if (!T)
        for (int i = 0; key[i] != '\0'; i++)
            cout << key[i];
    else
        for (int i = 0; T->data.key[i] != '\0'; i++)
            cout << T->data.key[i];
}

int getIndex(char ch)
{
    return int(ch) - 65;
}

TRIEPTR newPtrNode(int n)
{
    TRIEPTR T = new(trienode);
    T->tag = n;
    for (int i = 0; i <= d+1; i++)
        T->data.ptr[i] = NULL;
    return T;
}

TRIEPTR newKeyNode(char key[])
{
    TRIEPTR T = new(trienode);
    T->tag = -1;
    strcpy(T->data.key, key);
    return T;
}

//change
int findKey(TRIEPTR T, char key[], int i)
{
    if (T == NULL) return 0;
    if (T->tag > -1 && key[i] != '\0')
        return findKey(T->data.ptr[getIndex(key[i])], key, i+1);        //change
    else if (T->tag > -1 || key[i] == '\0') {
        if (findKey(T->data.ptr[d], key, i-1))
            return 1;
        if (!strcmp(key, T->data.key))
            return 1;
        return 2;
    }
    else {
        if (!strcmp(key, T->data.key))
            return 1;
        for (int j = 0; j <= i; j++)
            if (key[j] != T->data.key[j]) return 0;
        if (getSize(key) > getSize(T->data.key))
            return 0;
        return 2;
    }
}

void printFound(TRIEPTR T, char key[])
{
    printKey(NULL, key);
    int f = findKey(T, key, 0);
    if (f == 1)
        cout << "\t\t => found.\n";
    else if (f == 2)
        cout << "\t\t => found (prefix).\n";
    else cout << "\t\t => not found.\n";
}

//change
void insertKey(TRIEPTR &T, char key[], int i, int flag, TRIEPTR T1)
{
    if (!T && !flag)
        T = newKeyNode(key);
    else if ((!T && flag) || T->tag == -1) {
        TRIEPTR L = T1 ? T1 : T;      //temp to store original value
        T = newPtrNode(0);  //change
        flag = (L && key[i] == L->data.key[i]) ? 1 : 0;
        if (isSubString(L->data.key, key) && L->data.key[i] == '\0')
            T->data.ptr[d] = L;
        if (isSubString(key, L->data.key) && key[i] == '\0')    //only for second entry
            T->data.ptr[d] = newKeyNode(key);
        if (L && !flag) {
            insertKey(T->data.ptr[getIndex(key[i])], key, i+1, flag, NULL);
            insertKey(T->data.ptr[getIndex(L->data.key[i])], L->data.key, i+1, flag, NULL);
        }
        else
            insertKey(T->data.ptr[getIndex(key[i])], key, i+1, flag, L);
    }
    else if (T->tag > -1 && key[i] == '\0')
        T->data.ptr[d] = newKeyNode(key);
    else if (T->tag > -1)
        insertKey(T->data.ptr[getIndex(key[i])], key, i+1, flag, NULL);
}

/*Printing sorted function*/
//change
void printSorted(TRIEPTR T, int i, int flag)
{
    if (T && i < d) {
        if (T->data.ptr[d] && flag)
            printSorted(T->data.ptr[d], 0, 0);
        
        if (T->tag == -1) {
            printKey(T, "");
            cout << ", ";
        }
        else if (T->tag > -1) {
            printSorted(T->data.ptr[i], 0, 1);
            printSorted(T, i+1, 0);
        }
    }
}

/*Deletion functions*/
int hasSomePointer(TRIEPTR T)
{
    for (int i = 0; i <= d; i++)
        if (T->data.ptr[i]) return 1;
    return 0;
}

//change
void deleteKey(TRIEPTR &T, char key[], int i)
{
    if (T) {
        if (T->tag > -1 && key[i] != '\0') {
            deleteKey(T->data.ptr[getIndex(key[i])], key, i+1);
            if (!hasSomePointer(T))
                T = NULL;
        }
        else if (T->tag > -1 && key[i] == '\0') {
            if (T->data.ptr[d])
                T->data.ptr[d] = NULL;
        }
        else if (T->tag == -1)
            T = NULL;
    }
}


//MAIN
int main()
{
    TRIEPTR T = NULL;
    char input[20] = {'A', 'A', 'B', 'B', 'C'};
    
    //insertions
    insertKey(T, input, 0, 0, NULL);
    strcpy(input, "AAB");
    insertKey(T, input, 0, 0, NULL);
    strcpy(input, "BBC");
    insertKey(T, input, 0, 0, NULL);
    strcpy(input, "ABBBC");
    insertKey(T, input, 0, 0, NULL);
    strcpy(input, "A");
    insertKey(T, input, 0, 0, NULL);
    strcpy(input, "ABBA");
    insertKey(T, input, 0, 0, NULL);
    strcpy(input, "BAAB");
    insertKey(T, input, 0, 0, NULL);
    strcpy(input, "BBCC");
    insertKey(T, input, 0, 0, NULL);
    strcpy(input, "CAA");
    insertKey(T, input, 0, 0, NULL);
    strcpy(input, "CBA");
    insertKey(T, input, 0, 0, NULL);
    strcpy(input, "CAB");
    insertKey(T, input, 0, 0, NULL);
    
    //searching for proper insertion
    strcpy(input, "AAB");
    printFound(T, input);
    strcpy(input, "AABBC");
    printFound(T, input);
    strcpy(input, "BBC");
    printFound(T, input);
    strcpy(input, "ABBBC");
    printFound(T, input);
    strcpy(input, "A");
    printFound(T, input);
    strcpy(input, "CAA");
    printFound(T, input);
    strcpy(input, "ABBA");
    printFound(T, input);
    strcpy(input, "BAAB");
    printFound(T, input);
    strcpy(input, "BBCC");
    printFound(T, input);
    strcpy(input, "CBA");
    printFound(T, input);
    strcpy(input, "CAB");
    printFound(T, input);
    
    cout << "\nExtras:\n";
    strcpy(input, "AA");
    printFound(T, input);
    strcpy(input, "ABBB");
    printFound(T, input);
    strcpy(input, "CAAAA");
    printFound(T, input);
    strcpy(input, "CA");
    printFound(T, input);
    
    //printing in order
    cout << "\nLexographical order:\n";
    printSorted(T, 0, 0);
    
    //Deletions:
    //case 1:
    cout << "\n\nDeletion of A:\n";
    strcpy(input, "A");
    printFound(T, input);
    deleteKey(T, input, 0);
    printSorted(T, 0, 0);
    cout << "\n";
    printFound(T, input);
    
    //case 2:
    cout << "\nDeletion of AAB:\n";
    strcpy(input, "AAB");
    printFound(T, input);
    deleteKey(T, input, 0);
    printSorted(T, 0, 0);
    cout << "\n";
    printFound(T, input);
    
    //case 3:
    cout << "\nDeletion of CAB:\n";
    strcpy(input, "CAB");
    printFound(T, input);
    deleteKey(T, input, 0);
    printSorted(T, 0, 0);
    cout << "\n";
    printFound(T, input);
    
    cout << "\nDeletion of CAA:\n";
    strcpy(input, "CAA");
    printFound(T, input);
    deleteKey(T, input, 0);
    printSorted(T, 0, 0);
    cout << "\n";
    printFound(T, input);
    
    cout << "\nDeletion of CA:\n";
    strcpy(input, "CA");
    printFound(T, input);
    deleteKey(T, input, 0);
    printSorted(T, 0, 0);
    cout << "\n";
    printFound(T, input);
    
    //case 4:
    cout << "\nDeletion of AABBC:\n";
    strcpy(input, "AABBC");
    printFound(T, input);
    deleteKey(T, input, 0);
    printSorted(T, 0, 0);
    cout << "\n";
    printFound(T, input);
    cout << "\nDeletion of AA:\n";
    strcpy(input, "AA");
    printFound(T, input);
    deleteKey(T, input, 0);
    printSorted(T, 0, 0);
    cout << "\n";
    printFound(T, input);
    
    //case 5:
    cout << "\nDeletion of ABBA:\n";
    strcpy(input, "ABBA");
    printFound(T, input);
    deleteKey(T, input, 0);
    printSorted(T, 0, 0);
    cout << "\n";
    printFound(T, input);
    cout << "\nDeletion of ABBBC:\n";
    strcpy(input, "ABBBC");
    printFound(T, input);
    deleteKey(T, input, 0);
    printSorted(T, 0, 0);
    cout << "\n";
    printFound(T, input);
    
    //all remaining elements:
    cout << "\nDeletion of CBA:\n";
    strcpy(input, "CBA");
    printFound(T, input);
    deleteKey(T, input, 0);
    printSorted(T, 0, 0);
    cout << "\n";
    printFound(T, input);
    cout << "\nDeletion of BAAB:\n";
    strcpy(input, "BAAB");
    printFound(T, input);
    deleteKey(T, input, 0);
    printSorted(T, 0, 0);
    cout << "\n";
    printFound(T, input);
    cout << "\nDeletion of BBC:\n";
    strcpy(input, "BBC");
    printFound(T, input);
    deleteKey(T, input, 0);
    printSorted(T, 0, 0);
    cout << "\n";
    printFound(T, input);
    cout << "\nDeletion of BBCC:\n";
    strcpy(input, "BBCC");
    printFound(T, input);
    deleteKey(T, input, 0);
    printSorted(T, 0, 0);
    cout << "\n";
    printFound(T, input);
    
    if (!T) cout << "\nThe tree no longer exists.\n";
}

