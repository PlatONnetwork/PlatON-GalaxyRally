#include <platon/platon.hpp>
#include <string>
using namespace std;
using namespace platon;

CONTRACT ArrayFunc: public platon::Contract{

    private:
       platon::StorageType<"arr"_n,std::array<std::string,5>> storage_array_string;

    public:
        ACTION void init(){}
        
	
		ACTION void setInitArrayDate(){
			storage_array_string.self()[0] = "p";
			storage_array_string.self()[1] = "l";
			storage_array_string.self()[2] = "a";
			storage_array_string.self()[3] = "t";
			storage_array_string.self()[4] = "o";
			storage_array_string.self()[5] = "n";
        }
		
		
        CONST uint8_t getArraySize(){
             return storage_array_string.self().size();
        }

        CONST bool getArrayIsEmpty(){
            return storage_array_string.self().empty();
        }
     
        CONST std::string getArrayValueIndex(const uint32_t &index){
           return storage_array_string.self().at(index);
         }
       
        CONST std::string getArrayFirstValue(){
           return storage_array_string.self().front();
        }
    
        ACTION void setArrayFill(std::string str){
            storage_array_string.self().fill(str);
        }
};


PLATON_DISPATCH(ArrayFuncContract,(init)(setInitArrayDate)(getArraySize)(getArrayIsEmpty)(getArrayValueIndex)(getArrayFirstValue)(getArrayLength)(setArrayFill))

