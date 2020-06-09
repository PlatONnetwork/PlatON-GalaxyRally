#include <platon/platon.hpp>
#include <string>

using namespace platon;

CONTRACT Itermap : public platon::Contract{
   public:

      ACTION void init(){}

      ACTION uint8_t info (){
            
           for (uint8_t i = 0; i < 5; i++) {
                platonmap.self()[i] = i;
           }
          return 0;
      }

      CONST uint8_t get_value(const uint8_t key){
		  auto iter = platonmap.self()[key];   
		  if(iter != platonmap.self().end())
			  return iter->second;
		  else
			  return 0;
      }

   private:
      platon::StorageType<"uintmap"_n,std::map<uint8_t, uint8_t>> platonmap;
};

PLATON_DISPATCH(Iter, (init)(info)(get_value))
