#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <memory>
using namespace std;

enum class OutputFormat
{
    markdown,
    html
};

struct ListStrategy
{
    virtual void start(ostringstream& oss)
    {

    }

    virtual void add_list_item(ostringstream& oss, const string& item) = 0;

    virtual void end(ostringstream& oss)
    {

    }
};

struct MarkDownListStrategy : ListStrategy {

    void add_list_item(ostringstream& oss, const string& item) override {
        oss << "* " << item << "\n";
    }

};
struct HTMLListStrategy : ListStrategy {

    virtual void start(ostringstream& oss)
    {
        oss << "<ul>\n";
    }

    void add_list_item(ostringstream& oss, const string& item) override {
        oss << "<li>" << item << "</li>\n"; 
    }

    virtual void end(ostringstream& oss)
    {
        oss << "</ul>\n";
    }
};



struct TextProcessor
{
private:
    ostringstream oss;
    unique_ptr<ListStrategy> list_strategy;

public:
    
    void clear() {
        oss.str("");
        oss.clear();
    }

    void append_list(const vector<string>& items)
    {
        list_strategy->start(oss);

        for (auto& item : items)
            list_strategy->add_list_item(oss, item);

        list_strategy->end(oss);
    }

    void set_output_format(const OutputFormat& format)
    {
        switch (format)
        {
        case OutputFormat::markdown:
            list_strategy = make_unique<MarkDownListStrategy>();
            break;
        
        case OutputFormat::html:
            list_strategy = make_unique<HTMLListStrategy>();
            break;
        }
    }

    string str() {
        return oss.str();
    }
};

/*
list in markdown 
*first item
*second item
*/

/*
list in htnk
<ul>
<li>first item<\li>
<li>second item<\li>
</ul>
*/

int main()
{
    vector<string> items{ "foo","bar","baz" };
    TextProcessor tp;

    tp.set_output_format(OutputFormat::markdown);
    tp.append_list(items);
    cout << tp.str() << "\n";
    tp.clear();

    tp.set_output_format(OutputFormat::html);
    tp.append_list(items);
    cout << tp.str() << "\n";
    tp.clear();

    
}
