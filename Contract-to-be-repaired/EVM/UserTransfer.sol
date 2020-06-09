pragma solidity ^0.5.5;


contract UserTransfer {

    address owner;
    mapping(address => uint8) public balances; 

    constructor () public {
        owner = msg.sender;
        balances[msg.sender] = 200;
    }
    

    function transfer(address _to, uint8 _value) public returns (bool) {
		
	require(owner == msg.sender);
        balances[msg.sender] -= _value;
        balances[_to] += _value;
        return true;
   }
	
   function getBalance(address addr) view public returns (uint8){
	return balances[addr];
   }

}