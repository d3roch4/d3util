#include <iostream>
#include <d3util/json.h>
#include <mor/mor.h>
using namespace std;

struct print_person
{
    /*template<class FieldData, class Annotations>
    auto operator()(FieldData f, Annotations a, int) noexcept -> std::enable_if_t<!std::is_convertible<typename FieldData::type, datetime>::value>
    {
        std::cout << std::endl << f.name() << "=" << f.get() ;
    }

    template<class FieldData, class Annotations>
    auto operator()(FieldData f, Annotations a, int) noexcept -> std::enable_if_t<std::is_convertible<typename FieldData::type, datetime>::value>
    {
        std::cout << std::endl << f.name() << "=" << to_string(f.get()) ;
    }*/

    template<class FieldData, class Annotations>
    void operator()(FieldData f, Annotations a, int qtd)
    {
        const char* name = f.name();
        std::cout << std::endl << f.name();// << "=" << f.get() ;
    }
};

class Person
{
public:
    enum Status {
        unknow,
        online,
        offline
    };

REFLECTABLE(
    (std::string) name,
    (int) age,
    (std::string) addres,
    (datetime) now,
    (Status) status
)

    Person(){}
    Person(string name, int age, string addr){
        this->name = name;
        this->age = age;
        this->addres = addr;
    }
};
ANNOTATIONS_ENTITY(Person) = {Entity("person")};

string to_string(Person::Status status){
    switch (status) {
        case Person::online: return "online";
        case Person::offline: return "offline";
        default: return "Unknow";
    }
}
istream& operator>>(istream& stream, Person::Status& status){
    int i;
    stream >> i;
    status = static_cast<Person::Status>(i);
    return stream;
}

int main()
{    
    Person p("Tom Petter", 82, "Rua de cima");
    p.now = chrono::system_clock::now();
    p.status = Person::Status::offline;

    Json::Value json = to_json<Person>(p);
//    Person copy = from_json(json);
    
    print_person pp{};
//    reflector::visit_each(copy, pp);
}
