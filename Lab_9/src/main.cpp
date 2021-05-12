#include <bitset>
#include <functional>
#include <iostream>
#define throw_line1(arg) throw nullPointerException(arg, __FILE__, __LINE__);
#define throw_line2(arg) throw divisionByZeroException(arg, __FILE__, __LINE__);
struct Base
{
    virtual ~Base()
    {
    }
};

struct Derived : Base
{
    virtual void name()
    {
        std::cout << "name()" << std::endl;
    }
};

class MyException : public std::exception {
    std::string msg;
public:
    virtual const char* what()const { return "Base"; }
    MyException() {};
    virtual void getMessage() = 0;
    virtual void getFile() = 0;
    virtual void getLine() = 0;
};

class nullPointerException :public MyException
{
    std::string msg;
    const char* file;
    int line;
public:
    const char* what()const { return "nullPointerException"; }
    nullPointerException(const std::string& arg, const char* file, int line) {
        this->msg = arg;
        this->file = file;
        this->line = line;
    }
    ~nullPointerException() {};
    void getMessage() { std::cout << msg <<  std::endl; };
    void getFile() { std::cout << *file << std::endl; }
    void getLine() { std::cout << line << std::endl; }
};

class divisionByZeroException :public MyException
{
    std::string msg;
    const char* file;
    int line;
public:
    const char* what()const { return "divisionByZeroException"; }
    divisionByZeroException(const std::string& arg, const char* file, int line) {
        this->msg = arg;
        this->file = file;
        this->line = line;
    }
    ~divisionByZeroException() {};
    void getMessage() { std::cout << msg<< std::endl; };
    void getFile() { std::cout << *file<<std::endl; }
    void getLine() { std::cout << line << std::endl; }
    
};

void division(int* num, int den)
{
    if (num == nullptr) throw_line1("null");
    if (den == 0)  throw_line2("zero");
    int var = *num / den;
    std::cout << "var" << var << std::endl;
}


int main()
{
    // 0. Solve the quiz
    // https: // www.geeksforgeeks.org/c-plus-plus-gq/exception-handling-gq/

    // 1. Handle standard exceptions
    try {
         int* myarray = new int[10000000000000L];
    }
    catch(  std::bad_alloc &e){
        std::cout << "Allocation failed: "<<e.what();
    }
  
    
    // 2. Handle standard exceptions
    Base b;
    try {
 
        Derived& f = dynamic_cast<Derived&>(b);
    }
    catch(std::bad_cast& e){
        std::cout << "cast failed " << e.what() <<std:: endl;
    }

    
    // 3. Handle standard exceptions
    std::function<int(int, int)> add = std::plus<int>();
    std::function<int(int, int)> add2;
    std::cout << add(10, 20) << '\n';
    try {
        std::cout << add2(10, 20) << '\n';
    }
    catch(std::bad_function_call& e){
        std::cout << e.what() << '\n';
    }

    // 4. Handle standard exceptions
    Base* base = 0;
    try {
        typeid(*base).name();
    }
    catch (const std::bad_typeid& e) {
        std::cout <<"typeid failed "<<e.what() <<std:: endl;
    }
    
    // 5. Handle standard exceptions
    std::bitset<128> x(1);
    
    std::cout << x.to_ulong() << std::endl;
   x.flip();
    
    try {
        std::cout << x.to_ulong() << std::endl;
   }
    catch (std::overflow_error &e) {
        std::cout << e.what() << std::endl;
    }

    // 6. Write a function: void division(int *num, int den)
    // write your own expection class(es) to handle two kinds of exceptions
    // throw when ptr is null or x == 0
    // provide and extra info about the exception (message, line, function name,
    // info) e.g throw myexception("msg", __FILE__, catch exceptions
    int a = 2;
    int var = 1;
    int* ptr = 0;
    try {
        division(ptr, var);
    }
    catch (nullPointerException &e) {
        std::cout << e.what() << std::endl;
        e.getMessage();
        e.getFile();
        e.getLine();
    }
    ptr = &a;
    var = 0;
    try {
        division(ptr, var);
    }
    catch (divisionByZeroException& e) {
        std::cout << e.what() << std::endl;
        e.getMessage();
        e.getFile();
        e.getLine();
    }
    
}