#include <platon/platon.hpp>
#include <string>
#include <vector>
using namespace platon;

CONTRACT Donate : public platon::Contract{
	
	 private:
		platon::StorageType<"owner"_n,Address> owner;
		platon::StorageType<"charity"_n,Address> charity;
		platon::StorageType<"openingTime"_n, u128> openingTime;
		platon::StorageType<"closingTime"_n, u128> closingTime;
		platon::StorageType<"minVonAmount"_n, u128> minVonAmount;
		platon::StorageType<"maxVonAmount"_n, u128> maxVonAmount;
		platon::StorageType<"maxNumDonors"_n, u128> maxNumDonors;
		platon::StorageType<"donors"_n,std::vector<Address>> donors;
		platon::StorageType<"whitelist"_n, std::map<Address, bool>> whitelist;
		platon::StorageType<"paused"_n, bool> paused;
		
	 public:

		
		ACTION void init(const Address& _charity, u128 _openingTime, u128 _closingTime, u128 _minVonAmount, u128 _maxVonAmount, u128 _maxNumDonors) {
		    platon_assert(_charity != Address(0));
		    platon_assert(_closingTime > _openingTime);
		    platon_assert(_minVonAmount > 0);
            platon_assert(_maxVonAmount > _minVonAmount);
            platon_assert(_maxNumDonors > 0);
			owner.self() = caller();
			charity.self() = _charity;
			openingTime.self() = _openingTime;
			closingTime.self() = _closingTime;
			minVonAmount.self() = _minVonAmount;
			maxVonAmount.self() = _maxVonAmount;
			maxNumDonors.self() = _maxNumDonors;
		}
		
		ACTION void donate(const Address& _donor) {
			u128 val = platon_call_value();
			preValidateDonate(_donor, val);
		  
			donors.self().push_back(_donor);
		}
        	 
		ACTION void setOpeningClosingTimes(u128 _openingTime, u128 _closingTime) {
			onlyOwner();
			platon_assert(_closingTime > _openingTime);
			
			openingTime.self() = _openingTime;
		}
	  
		ACTION void addToWhitelist(const Address& _donor) {
			onlyOwner();
			
			whitelist.self()[_donor] = true;
		}
	  
	
		ACTION void addManyToWhitelist(const std::vector<Address>& _donors) {
			onlyOwner();
			
			for (uint64_t i = 0; i < _donors.size(); i++) {
		       whitelist.self()[_donors[i]] = true;
			}
		}
	  
		ACTION void removeFromWhitelist(const Address& _donor) {
			onlyOwner();
			
			whitelist.self()[_donor] = false;
		}

		ACTION void pause() {
			onlyOwner();
			platon_assert(paused.self() == false);
			
			paused.self() = true;
		}
	 
		ACTION void unpause() {
			onlyOwner();
			platon_assert(paused.self() == true);
			
			paused.self() = false;
		}
	  
		ACTION void transferOwnership(const Address& newOwner) {
			onlyOwner();
			platon_assert(newOwner != Address(0));
			owner.self() = newOwner;
		}
		
		CONST Address getCharity() {
			return charity.self();
		}
		
		
		CONST std::vector<Address> getDonors() {
			return donors.self();
		}
		
		CONST std::map<Address, bool> getWhitelist() {
			return whitelist.self();
		}
			  
	  private:
		void preValidateDonate(const Address& _donor ,u128 _vonAmount) {
			platon_assert(u128(platon_timestamp()) >= openingTime.self() && u128(platon_timestamp()) <= closingTime.self());
			platon_assert(!paused.self());
			platon_assert(donors.self().size() <= maxNumDonors.self());
			platon_assert(whitelist.self()[_donor]);
			platon_assert(_donor != Address(0));
			platon_assert(minVonAmount.self() <= _vonAmount && _vonAmount <= maxVonAmount.self());
		}
	
		void onlyOwner() {
			platon_assert(caller() == owner.self());
		}
};

PLATON_DISPATCH(Donate, (init)(donate)(setOpeningClosingTimes)(addToWhitelist)(addManyToWhitelist)(removeFromWhitelist)(pause)(unpause)(transferOwnership)(getOwner)(getCharity)(getDonors)(getWhitelist))