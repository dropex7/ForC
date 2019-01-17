#include <iostream>
#include <libxml++/libxml++.h>

float ustoi(const Glib::ustring& str )
{
    float sum = 0;
    int t = 10;
    Glib::ustring::const_iterator it = str.begin();
    while (*it != ',')
    {
        sum = sum * 10 + *it - '0';
        it++;
    }
    it++;
    while (it != str.end())
    {
        sum += (*it - '0')/t;
        it++;
        t*=10;
    }
    return sum;
}

float findValute (const xmlpp::Node::NodeList &nodeList,const Glib::ustring& name)
{
    bool found = false;
    for (xmlpp::Node* a : nodeList)
    {
        xmlpp::Node::NodeList nodeList2 = a->get_children();
        for (xmlpp::Node* b : nodeList2)
        {
            if (b->get_name() == "CharCode")
            {
                auto elem = dynamic_cast<xmlpp::Element*>(b);
                Glib::ustring elemname = elem->get_first_child_text()->get_content();
                if(elemname == name)
                    found = true;
            }
            if (found && b->get_name() == "Value")
            {
                xmlpp::Element* elem = dynamic_cast<xmlpp::Element*>(b);
                return ustoi(elem->get_first_child_text()->get_content());
            }
        }

    }
}

int main(int argc , char* argv[])
{
    std::string datafile = "daily.xml" ;
    Glib::ustring valuteFrom = "USD";
    Glib::ustring valuteTo = "EUR";
    for (int i = 1; i < argc; ++i)
    {
        if (std::string(argv[i]).substr(0, 4) == "from")
            valuteFrom =  Glib::ustring(argv[i]).substr(std::string(argv[i]).find("=") + 1);
        if  (std::string(argv[i]).substr(0, 2)== "to")
            valuteTo =  Glib::ustring(argv[i]).substr(std::string(argv[i]).find("=") + 1);
        if (std::string(argv[i]).substr(0, 4) == "data")
            datafile = std::string(argv[i]).substr(std::string(argv[i]).find("=") + 1);
    }

    xmlpp::DomParser parser;
    try
    {
        parser.set_validate(false);
        parser.set_substitute_entities();
        parser.parse_file(datafile);
        if (!parser)
            throw std::runtime_error("Parsing error");
    }
    catch (const std::exception& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }
    xmlpp::Node* rootNode = parser.get_document()->get_root_node();
    xmlpp::Node::NodeList nodeList = rootNode->get_children();
    float ans = findValute(nodeList,valuteFrom) / findValute(nodeList,valuteTo);
    std::cout << "One " << valuteFrom << " is " << ans << " " << valuteTo << std::endl;
    return 0;
}
