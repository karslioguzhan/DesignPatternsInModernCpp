#include <iostream>
#include <sstream>
#include <vector>


// Is just a utility class for modeling html element
struct HtmlElement
{
    std::string name, text;
    std::vector<HtmlElement> elements;
    const size_t indent_size = 2;

    HtmlElement() {}
    HtmlElement(const std::string& name,
        const std::string& text) :
        name(name), text(text) {};

    // API for printing
    std::string str(int indent = 0) const
    {
        std::ostringstream oss;
        std::string i(indent_size * indent, ' ');
        oss << i << "<" << name << ">" << std::endl;
        if (text.size() > 0)
        {
            oss << std::string(indent_size * (indent + 1), ' ') <<
                text << std::endl;
        }
        for (const auto& e : elements)
        {
            oss << e.str(indent + 1);
        }
        oss << i << "</" << name << ">" << std::endl;
        return oss.str();
    }
};

// Here is the builder for html element
struct HtmlBuilder
{
    HtmlElement root;
    HtmlBuilder(std::string root_name)
    {
        root.name = root_name;
    }

    void add_child(std::string child_name, std::string child_text)
    {
        HtmlElement e{ child_name, child_text };
        root.elements.emplace_back(e);
    }

    std::string str() const
    {
        return root.str();
    }
};

int main()
{
    // Example with an html element
    auto text{ "hello" };
    std::string output;
    output += "<p>";
    output += text;
    output += "</p>";
    std::cout << output << std::endl;

    // Example with an unordered list
    std::string words[] = { "hello", "world" };
    std::ostringstream oss;
    oss << "<ul>";
    for (auto w : words)
    {
        oss << " <li>" << w << "</li>";
    }
    oss << "</ul>";
    std::cout << oss.str() << std::endl;

    // Dedicated builder for creation a component with more lines
    HtmlBuilder builder{ "ul" };
    builder.add_child("li", "hello");
    builder.add_child("li", "world");
    
    std::cout << builder.str() << std::endl;

}
