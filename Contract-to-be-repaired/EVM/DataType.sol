pragma solidity ^0.5.5;


contract DataType {


    function getBalance(address addr) public view returns (uint) {
        return addr.balance;
    }

  
    function getAddress() public returns (uint) {
        address b = 0x00ca35b7d915458ef540ade6068dfe2f44e8fa733c;
        return getBalance(b);
    }


    function getHexLitera() public view returns (bytes2, bytes1, bytes1){
        bytes2 b = hex"01f4";
        return (b, b[1], b[2]);
    }


    enum Season{Spring, Summer, Autumn, Winter}


    function getSeason() public view returns(Season){
        Season s = Season(5);
        return s;
    }
    
}