#include <iostream>
#include <d3util/json.h>
using namespace std;


struct print_person
{
    template<class FieldData, class Annotations>
    auto operator()(FieldData f, Annotations a, int) noexcept -> std::enable_if_t<!std::is_convertible<typename FieldData::type, datetime>::value>
    {
        std::cout << std::endl << f.name() << "=" << f.get() ;
    }

    template<class FieldData, class Annotations>
    auto operator()(FieldData f, Annotations a, int) noexcept -> std::enable_if_t<std::is_convertible<typename FieldData::type, datetime>::value>
    {
        std::cout << std::endl << f.name() << "=" << to_string(f.get()) ;
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

int main()
{    
    Person p("Tom Petter", 82, "Rua de cima");
    p.now = chrono::system_clock::now();
    p.status = Person::Status::offline;

    Json::Value json = to_json<Person>(p);
    Person copy = from_json(json);

    reflector::visit_each(copy, print_person{});
}
