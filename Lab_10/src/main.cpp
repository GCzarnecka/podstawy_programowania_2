#include <array>
#include <iostream>
#include<string>
#include<vector>
using namespace std;

class VectoredList {
    int size;
    int capacity;
    class Bucket {
    public:
        static const int N = 10;
        array<string, N> A;
        int number;
        Bucket() :number(0),next(nullptr), previous(nullptr){};
        Bucket(Bucket* p, string value) :previous(p), number(1), next(0) {A[0] = value; };
        Bucket* next;
        Bucket* previous;
        string& operator [](int index) {
            return A[index];
        }
    };
    Bucket* head;
    Bucket* tail;
public:
    VectoredList(){
            size=1;
            capacity = 0;
            head = new Bucket;
            tail = head;
        }
    ~VectoredList() {
        while (tail->previous) {
            tail = tail->previous;
            delete tail->next;
            tail->next = nullptr;
        }delete head;
    };
    int getSize()const { return (size * Bucket::N) - (Bucket::N-capacity); };
    bool push_back(string v) {
        if(capacity>=10)
        {
            auto* b = new Bucket;
            tail->next = b;
            b->previous = tail;
            tail = b;
            ++size;
            capacity = 0;
        }
        tail->A[tail->number] = v;
        tail->number++;
        capacity++;
        return true;

    }
    string& operator [](int index) {
        Bucket* tmp = head;
        if (index >= 0)
        { for (int i = 0; i <= index; i++) if (i % tmp->N == 0 && i != 0)tmp = tmp->next;
        }
        return tmp->A[index % tmp->N];
    }
    
    class VectoredListIterator {
        Bucket* b;
        int index;
        int cursor;
        string v;
        VectoredList* vec;
    public:
        VectoredListIterator(VectoredList* l, int nr_ele)
        {
            vec = l;
            index = nr_ele;
            cursor = nr_ele;
        }
        VectoredListIterator& operator*() {
            return *this;
        }
        VectoredListIterator operator++() {++ cursor; return *this; }
        VectoredListIterator operator--() { --cursor; return *this; }
       
         bool operator !=(const VectoredListIterator& v2)const
         {
             if (this->cursor != v2.cursor) return true;
                 return false;
         }
         string& get()const {
             Bucket* tmp = vec->head;
             int i = 0;
             if(i==cursor) return tmp->A[cursor % tmp->N];
             i += 1;
             while (i != cursor) {
                 i++;
                 if (i % 10 == 0 ) {
                     tmp = tmp->next;
                 }
                
             }
             return tmp->A[cursor % tmp->N];
         }
        string& operator *()const { return  this->get(); }
        string& operator [](int index) {
            Bucket* tmp = vec->head;
            if (index >= 0 && index < vec->capacity) {
                for (int i = 0; i <= index; i++) {
                    if (i % tmp->N == 0 && i != 0)tmp = tmp->next;
                }
            }
            return tmp->A[index % tmp->N];
        }
        int getCursor() { return cursor; }
        bool good()const { return this->cursor >= 0; }
    

    };
    Bucket *element(int cursor){
        int idx = cursor / 10;
    }
    VectoredListIterator begin() { return VectoredListIterator(this, 0); }
    VectoredListIterator end() { return  VectoredListIterator(this, this->getSize()); }
    VectoredList &operator=(const VectoredList& other) {
        Bucket* tmp = head;
        if (this == &other) return *this;
        int i = 0;
        this->push_back(tmp->A[i]);
        while(i!= VectoredList::getSize())
        {
            i++;
            if (i % 10 == 0) {
                tmp = tmp->next;
            }
            this->push_back(tmp->A[i % tmp->N]);
        }
        return *this;
    }
    void pop_back() {
        string s = "";
        put(  VectoredList::getSize(),s);
        capacity--;
        --tail->number;
        if (!tail->number) {
            tail = tail->previous;
            delete tail->next;
            tail->next = nullptr;
        }
    }
    void erase(VectoredList::VectoredListIterator iterator1, VectoredList::VectoredListIterator iterator2) {
        string s = "";
        int i, j;
        for (i = iterator1.getCursor(), j = iterator2.getCursor(); j < VectoredList::getSize(); i++, j++) {
            put(i, (VectoredListIterator(this, j).get()));
        } 
        int sub = iterator2.getCursor() - iterator1.getCursor();
        i = getSize();
        int tmp = getSize() - sub;
        while (i > tmp) {
            i--;
            if (tail->number > 0)
                --tail->number;
            else {
                size--;
                capacity = 10;
                delete tail->next;
                tail = tail->previous;
                tail->next = nullptr;
            }
            put(i,s);
        }
    }
    void put(int number,string value) {
        Bucket* tmp = head;
        int i = 0;
        if (i == number)  tmp->A[number % tmp->N] = value;
        i += 1;
        while (i != number) {
            i++;
            if (i % 10 == 0) {
                tmp = tmp->next;
            }
        }
         tmp->A[number % tmp->N]= value;
    }
    void erase(VectoredListIterator iterator) { erase(iterator, VectoredListIterator(this, iterator.getCursor() + 1)); }
};


int main()
{
    cout << endl << "---------- 1,2 ----------" << endl;
    VectoredList v;
    for (int i = 0; i < 101; ++i)
    {
        v.push_back("s" + to_string(i));
        cout << v[i] <<endl;
    }
    cout << v.getSize() << endl;
    for (VectoredList::VectoredListIterator ita(&v, 101); ita.good(); --ita)
    {
        cout <<ita.get() << " ";
       if (ita.getCursor() % 10 == 0)
           cout <<  endl;
    }
    

    cout << endl << "---------- 3 ----------" << endl;;
    for (const auto &element : v)
     cout <<*( element)<< "AAA" << endl;

    cout << endl << "---------- 4 ----------" << endl;
     VectoredList::VectoredListIterator it3(&v, 3);
     VectoredList::VectoredListIterator it33(&v, 33);
     VectoredList::VectoredListIterator it45(&v, 45);
     v.erase(it3);
     v.pop_back();
     cout << endl;
     v.pop_back();
     v.erase(it33, it45);
     for (int i = 0; i <v.getSize(); ++i)
     {
         cout << v[i] << " ";
         if (i % 10 == 0)
             cout << endl;
     }
    cout << endl << "---------- 5 ----------" << endl;
     VectoredList v2 = v;
     for (int i = 0; i < v2.getSize(); ++i)
    {
         cout << v2[i] << " ";
         if (i % 10 == 0)
             cout << endl;
     }
}
