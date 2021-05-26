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
        Bucket() :number(0), next(nullptr), previous(nullptr) {};
        Bucket* next;
        Bucket* previous;
        string& operator [](int index) {
            return A[index];
        }
    };
    Bucket* head;
    Bucket* tail;
public:
    VectoredList() {
        size = 1;
        capacity = 0;
        head = new Bucket;
        tail = head;
    }
    VectoredList(const VectoredList& newvec) = default;
    VectoredList &operator=( VectoredList&& v) {
        
        if (this != &v) {
            delete this->head;
            this->head = v.head;
            this->tail = v.tail;
            size = v.size;
            capacity = v.capacity;
            v.head = nullptr;
            v.tail = nullptr;
            v.capacity = 0;
            v.size = 0;}
        return *this;
    }
    VectoredList(VectoredList&& v):head(nullptr),tail(nullptr),size(1),capacity(0) {
        this->head = v.head;
        this->tail = v.tail;
        size = v.size;
        capacity = v.capacity;
        v.head= nullptr;
        v.tail=nullptr;
        v.capacity=0;
        v.size=0;
    }

    ~VectoredList() {
        if (head != nullptr && tail != nullptr)
        {
            while (tail->previous) {
                tail = tail->previous;
                delete tail->next;
                tail->next = nullptr;
            }delete head;
        }
        
    };
    int getSize()const { return (size * Bucket::N) - (Bucket::N - capacity); };
    void push_back(string v) {
       
        if (capacity >= 10)
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
    }
    string& operator [](int index) const{
        Bucket* tmp = head;
        if (index >= 0 && index< VectoredList::getSize())
        {
            for (int i = 0; i <= index; i++) if (i % tmp->N == 0 && i != 0)tmp = tmp->next;
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
        VectoredListIterator( VectoredList* l, int nr_ele)
        {
            vec = l;
            index = nr_ele;
            cursor = nr_ele;
        }
        VectoredListIterator& operator*() {
            return *this;
        }
        VectoredListIterator operator++() { ++cursor; return *this; }
        VectoredListIterator operator--() { --cursor; return *this; }

        bool operator !=(const VectoredListIterator& v2)const
        {
            if (this->cursor != v2.cursor) return true;
            return false;
        }
        string& get()const {
            Bucket* tmp = vec->head;
            int i = 0;
            if (i == cursor) return tmp->A[cursor % tmp->N];
            i += 1;
            while (i != cursor) {
                i++;
                if (i % 10 == 0) {
                    tmp = tmp->next;
                }

            }
            return tmp->A[cursor % tmp->N];
        }
        string& operator *()const { return  this->get(); }
        string& operator [](const int index) {
            Bucket* tmp = vec->head;
            if (index >= 0 && index < vec->capacity) {
                for (int i = 0; i <= index; i++) {
                    if (i % tmp->N == 0 && i != 0)tmp = tmp->next;
                }
            }
            return tmp->A[index % tmp->N];
        }
        int getCursor() { return cursor; }
        bool good()const {
            if (this->cursor >= 0 && this->cursor < vec->getSize()) return true; else { return false; }
        }


    };
    VectoredListIterator begin() { return VectoredListIterator(this, 0); }
    VectoredListIterator end() { return  VectoredListIterator(this, this->getSize()); }
    VectoredList& operator=(const VectoredList& other) {
        Bucket* tmp = head;
        if (this == &other) return *this;
        int i = 0;
        this->push_back(tmp->A[i]);
        while (i != VectoredList::getSize())
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
        put(VectoredList::getSize(), s);
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
            put(i, s);
        }
    }
    void put(int number, string value) {
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
        tmp->A[number % tmp->N] = value;
    }
    void erase(VectoredListIterator iterator) { erase(iterator, VectoredListIterator(this, iterator.getCursor() + 1)); }
    VectoredList operator+( VectoredList& rhs) const{
        VectoredList v(*this);
        for (int i = 0; i < rhs.size; i++) v.push_back(rhs[i]);

        return v;
    }
    bool assign(vector<string> v) {
        head = nullptr;
        tail = nullptr;
        capacity = 0;
        size = 0;
        VectoredList vec;
        for (int i = 0; i < v.size(); i++) vec.push_back(v[i]);
        *this = move(vec);
        return true;
    }
};




int main()
{
    cout << endl << "---------- 1 ----------" << endl;
     VectoredList v;
     string       t11("TEST 1.1");
     string       t12("TEST 1.2");
     v.push_back(t11);
     v.push_back(t12);

     VectoredList v1(move(v));

    for (int i = 0; i < v1.getSize(); ++i)
     {
         cout << v1[i] << endl;
    }

    cout << endl << "---------- 2 ----------" << endl;
     VectoredList v2;
     string t21("TEST 2.1");
     string t22("TEST 2.2");
     v2.push_back(t21);
     v2.push_back(t22);

     v1 = move(v2);

     for (int i = 0; i < v1.getSize(); ++i)
     {
         cout << v1[i] << endl;
     }

    cout << endl << "---------- 3 ----------" << endl;
     VectoredList v3, v4;
     string  t31("TEST 3.1");
     v3.push_back(t31);

     v4 = v1 + v3;
     for (int i = 0; i < v4.getSize(); ++i) cout << v4[i] << endl;

    cout << endl << "---------- 4 ----------" << endl;
     vector<string> V{"TEST 4.1", "TEST 4.2"};
     v3.assign(V);
     for (int i = 0; i < v3.getSize(); ++i)
         cout << v3[i] << endl;

}