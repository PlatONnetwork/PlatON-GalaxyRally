#include <platon/platon.hpp>
#include <string>
using namespace std;
using namespace platon;

class person {
    public:
        person(){}
        person(const std::string &my_name):name(my_name){}
        std::string name;
        PLATON_SERIALIZE(person, (name))
};


CONTRACT Vector : public platon::Contract{
    public:
    ACTION void init(){}

    ACTION void init(const std::string  &init_name){
      input_vector.self().push_back(person(init_name));
    }

    ACTION void add_vector(const std::string  &one_name){
        input_vector.self().push_back(person(one_name));
    }

    CONST uint64_t get_vector_size(){
        return input_vector.self().size();
    }

    CONST std::string get_vector(uint8_t index){
        return input_vector.self()[index].name;
    }  

    private:
        platon::StorageType<"pvector"_n, std::vector<person>> input_vector;
};

PLATON_DISPATCH(Vector, (init)(add_vector)(get_vector_size)(get_vector))
