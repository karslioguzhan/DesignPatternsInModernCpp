#include <iostream>

struct Document;

//struct IMachine
//{
//    virtual void print(Document& doc) = 0;
//    virtual void scan(Document& doc) = 0;
//    virtual void fax(Document& doc) = 0;
//};
//
//struct MultifunctionPrinter :IMachine
//{
//    virtual void print(Document& doc) override
//    {
//
//    }
//    virtual void scan(Document& doc)
//    {
//
//    }
//
//    virtual void fac(Document& doc)
//    {
//
//    }
//};
//
//struct Scanner : IMachine
//{
//    virtual void print(Document& doc) override
//    {
//
//    }
//    virtual void scan(Document& doc)
//    {
//
//    }
//
//    virtual void fac(Document& doc)
//    {
//
//    }
//};

struct IPrinter
{
    virtual void print(Document& doc) = 0;
};

struct IScanner
{
    virtual void scan(Document& doc) = 0;
};

struct IFax
{
    virtual void fax(Document& doc) = 0;
};

struct Scanner :IScanner
{
    void scan(Document& doc) override
    {

    }
};

struct Printer : IPrinter
{
    void print(Document& doc) override
    {

    }
};

struct IMachine : IPrinter, IScanner
{

};
struct Machine :IMachine
{
    IPrinter& printer;
    IScanner& scanner;
    
    Machine(IPrinter& printer, IScanner& scanner) :
        printer(printer), scanner(scanner)
    {

    }

    void print(Document& doc) override
    {
        printer.print(doc);
    }

    void scan(Document& doc) override
    {
        scanner.scan(doc);
    }
};

int main()
{
    std::cout << "Break up interface to smaller Interfaces\n";
    std::cout << "Create more cohearance!\n";
}
