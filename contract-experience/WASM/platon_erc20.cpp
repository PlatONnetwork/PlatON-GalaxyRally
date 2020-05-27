#include <platon/platon.hpp>
#include <string>

using namespace platon;

class ierc20 {

public:

    // @return total issuance of tokens
    virtual uint64_t getTotalSupply() = 0;

    // @param _owner The address from which the balance will be retrieved
    // @return The balance.
    virtual uint64_t balanceOf(Address _owner) = 0;

    // @param _owner The address of the account owning tokens
    // @param _spender The address of the account able to transfer the tokens
    // @return Amount of remaining tokens allowed to spent.
    virtual uint64_t allowance(Address _owner, Address _spender) = 0;

    // @notice send '_value' token to `_to` from `msg.sender`
    // @param _to THe address of the recipient.
    // @param _value The amount of token to be transferred.
    // @return Whether the transfer was successful or not.
    virtual bool transfer(Address _to, uint64_t _value) = 0;

    // @notice send `_value` token to `_to` from `_from` on the condition it is approved by `_from`
    // @param _from The address of the sender.
    // @param _to The address of the recepient.
    // @param _value The amount of token to be transferred.
    // @return Whether the transfer was successful or not.
    virtual bool transferFrom(Address _from, Address _to, uint64_t _value) = 0;

    // @notice `msg.sender` approves `_spender` to spend `_value` tokens
    // @param _spender The address of the account able to transfer the tokens
    // @param _value The amount of tokens to be approved for transfer
    // @return Whether thee approval was successful or not.
    virtual bool approve(Address _spender, uint64_t _value) = 0;

protected:

    // define: _from, _to, _value
    PLATON_EVENT2(Transfer, Address, Address, uint64_t);
    // define: _owner, _spender, _value
    PLATON_EVENT2(Approval, Address, Address, uint64_t);

};

class platon_erc20: public ierc20, public platon::Contract {


public:

    ACTION void init(const std::string& _tokenName,
            const std::string& _tokenSymbol,
            uint64_t _initialAmount,
            uint8_t _decimalUnits)
    {

        Address sender = platon_caller();               // the owner of cantract and the issued tokens
        platon::set_owner(sender.toString());
      

        name.self() = _tokenName;						// Set the name for display purposes
        symbol.self() = _tokenSymbol;					// Set the symbol for display purposes.

        balances.self()[sender] = _initialAmount;		// Give the creator all initial tokens.
        total_supply.self() = _initialAmount;			// Update total supply.
        decimals.self() = _decimalUnits;				// Amount of decimals for display purposes

    }

    CONST std::string getName(){
      
        return name.self();
    }

    CONST std::string getSymbol(){
      
        return symbol.self();
    }

    CONST uint64_t getTotalSupply(){
      
        return total_supply.self();
    }

    CONST uint8_t getDecimals(){
        return decimals.self();
    }


    CONST uint64_t balanceOf(Address _owner) {
      
        return balances.self()[_owner];
    }

    CONST uint64_t allowance(Address _owner, Address _spender){
       
        return allowed.self()[_owner][_spender];
    }

public:

    ACTION bool transfer(Address _to, uint64_t _value){
        // Default assumes totalSupply can't be over max(2^64 - 1)
        // If your token leaves out totalSupply and can issue more tokens as time goes on,
        // you need to check if it doesn't wrap.
        // Replace the if with this on instead.
        Address sender = platon_caller();
        if (balances.self()[sender] >= _value && _value > 0) {
            balances.self()[sender] -= _value;
            balances.self()[_to] += _value;
            PLATON_EMIT_EVENT2(Transfer, sender, _to, _value);
          
            return true;
        }
        return false;
    }

    ACTION bool transferFrom(Address _from, Address _to, uint64_t _value) {
        // same as above. Replace this line with the following if you want to protect against
        // wrapping uints.
        Address sender = platon_caller();
        if(balances.self()[_from] >= _value && allowed.self()[_from][sender] >= _value && _value > 0){

            balances.self()[_to] += _value;
            balances.self()[_from] -= _value;
            allowed.self()[_from][sender] -= _value;

            PLATON_EMIT_EVENT2(Transfer, _from, _to, _value);
          
            return true;
        }
        return false;
    }

    ACTION bool approve(Address _spender, uint64_t _value){

        Address sender = platon_caller();
        if (balances.self()[sender] >= _value && _value > 0) {
            allowed.self()[sender][_spender] = _value;
            PLATON_EMIT_EVENT2(Approval, sender, _spender, _value);
           
            return true;
        }
        return false;
    }

    ACTION bool increaseApprove(Address _spender, uint64_t _value){

        Address sender = platon_caller();
        uint64_t old = allowed.self()[sender][_spender];
        platon_assert(balances.self()[sender] >= _value && _value > 0, "PlatON ERC20: can't increase approval");

        uint64_t new_val = old + _value;
        allowed.self()[sender][_spender] = new_val;

        PLATON_EMIT_EVENT2(Approval, sender, _spender, allowed.self()[sender][_spender]);
      
        return true;
    }


    ACTION bool decreaseApprove(Address _spender, uint64_t _value){

        Address sender = platon_caller();
        uint64_t old = allowed.self()[sender][_spender];
        platon_assert(old > 0 && old >= _value, "PlatON ERC20: can't decrease approval");

        uint64_t new_val = old - _value;
        allowed.self()[sender][_spender] = new_val;

        PLATON_EMIT_EVENT2(Approval, sender, _spender, allowed.self()[sender][_spender]);
      
        return true;
    }

    ACTION bool mint(Address _account, uint64_t _value) {
        platon_assert(platon::is_owner(), "PlatON ERC20: Only owner can do mint");
        platon_assert(_account != Address(0), "PlatON ERC20: mint to the zero address");
        if (_value > 0) {
            total_supply.self() += _value;
            balances.self()[_account] += _value;
            PLATON_EMIT_EVENT1(Mint, _account, _value);
         
            return true;
        }
        return false;
    }


    ACTION bool burn(Address _account, uint64_t _value) {
        platon_assert(platon::is_owner(), "PlatON ERC20: Only owner can do burn");
        platon_assert(_account != Address(0), "PlatON ERC20: burn from the zero address");
        if (balances.self()[_account] >= _value) {
            total_supply.self() -= _value;
            balances.self()[_account] -= _value;
            PLATON_EMIT_EVENT1(Burn, _account, _value);
          
            return true;
        }
        return false;
    }

    ACTION bool suicide(Address reciever) {
        if (platon::is_owner()) {
            platon_destroy(reciever);
          
            return true;
        }
        return false;
    }

protected:

    // define:  _to, _value
    PLATON_EVENT1(Mint, Address, uint64_t);
    // define: _from, _value
    PLATON_EVENT1(Burn, Address, uint64_t);

private:


    platon::StorageType<"name"_n, std::string> name;
    platon::StorageType<"symbol"_n, std::string> symbol;
    platon::StorageType<"total_supply"_n, uint64_t> total_supply;
    platon::StorageType<"decimals"_n, uint32_t> decimals;

private:

    platon::StorageType<"balances"_n, std::map<Address, uint64_t>> balances;
    platon::StorageType<"allowed"_n, std::map<Address, std::map<Address, uint64_t>>> allowed;


};

PLATON_DISPATCH(platon_erc20,(init)(getName)(getSymbol)(getTotalSupply)(getDecimals)(balanceOf)(allowance)
(transfer)(transferFrom)(approve)(increaseApprove)(decreaseApprove)(mint)(burn)(suicide))
