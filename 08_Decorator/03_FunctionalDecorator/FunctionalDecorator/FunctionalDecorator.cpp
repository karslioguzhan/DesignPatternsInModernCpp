#include <iostream>
#include <string>
#include <functional>

struct Logger
{
    std::function<void()> func;
    std::string name;

    Logger(const std::function<void()>& func, const std::string& name) :
        func(func), name(name)
    {
    }

    void operator()() const
    {
        std::cout << "Entering " << name << std::endl;
        func();
        std::cout << "Exiting " << name << std::endl;
    }
};

template <typename Func>
struct Logger2
{
    Func func;
    std::string name;

    Logger2(const Func &func, const std::string& name) :
        func(func), name(name)
    {
    }

    void operator()() const
    {
        std::cout << "Entering " << name << std::endl;
        func();
        std::cout << "Exiting " << name << std::endl;
    }
};

template <typename Func> auto make_logger2(Func func, const std::string& name)
{
    return Logger2<Func>{func, name};
}

double add(double a, double b)
{
    std::cout << a << " + " << b << " = " << (a + b) << std::endl;
    return a + b;
}

template<typename> struct Logger3;

template<typename R, typename... Args>
struct Logger3<R(Args...)>
{
    std::function<R(Args...)> func;
    std::string name;


    Logger3(const std::function<R(Args...)>& func, const std::string& name)
        : func(func), name(name)
    {
    }

    R operator() (Args ...args)
    {
        std::cout << "Entering " << name << std::endl;
        R result = func(args...);
        std::cout << "Exiting " << name << std::endl;
        return result;
    }
};

template <typename R, typename... Args>
auto make_logger3(R(*func)(Args...), const std::string& name)
{
    return Logger3<R(Args...)>(std::function<R(Args...)>(func), name);
}

int main()
{
    Logger([]() {std::cout << "Hello" << std::endl; }, "HelloFunction")();

    std::cout << std::endl;

    auto log = make_logger2([]() {std::cout << "Hello" << std::endl; }, "HelloFunction");
    log();
    std::cout << std::endl;

    auto logged_add = make_logger3(add, "Add");
    auto result = logged_add(2, 3);
    std::cout << "result = " << result << std::endl;
}
