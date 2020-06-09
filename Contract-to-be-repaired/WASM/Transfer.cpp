#include <platon/platon.hpp>
#include <string>
using namespace platon;

CONTRACT Transfer : public platon::Contract{
	public:
		ACTION void init() {}
		
		
		ACTION void transfer(const string& addr, uint64_t amount) {
			if(amount == 0){
				return;
			}
			platon_transfer(addr, amount);
		}

        CONST uint64_t getBalance(Address addr) {
			uint64_t e = platon_balance(addr);
            return e;
    }
	
};

PLATON_DISPATCH(Transfer, (init)(transfer)(getBalance))