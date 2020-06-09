#include <platon/platon.hpp>
#include <string>
using namespace platon;

class message {
   public:
      std::string head;
      PLATON_SERIALIZE(message, (head))
};

class my_message : public message {
   public:
      std::string body;
      std::string end;
      PLATON_SERIALIZE(my_message, message, (body)(end))
};

CONTRACT OneInherit : public platon::Contract{
   public:
      ACTION void init(){
      }

      ACTION void add_my_message(const my_message &one_message){
          info.self().push_back(one_message);
      }

      CONST uint8_t get_my_message_size(){
          return info.self().size();
      }

      CONST std::string get_my_message_head(const uint8_t index){
          return info.self()[index].head;
      }

      CONST std::string get_my_message_body(const uint8_t index){
          return info.self()[index].body;
      }


   private:
      platon::StorageType<"mymvector"_n, std::vector<my_message>> info;
};

PLATON_DISPATCH(OneInherit, (init)(add_my_message)(get_my_message_size)(get_my_message_head)(get_my_message_body))
