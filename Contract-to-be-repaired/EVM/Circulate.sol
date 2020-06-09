pragma solidity ^0.5.5;


contract Circulate {

    struct S { bool f; }
    S s;
    uint v;
    
    function h() internal view returns (S c) {
        if(true) {
	  c=s;
        }
    }
    
    function g() public view returns(bool){
        S storage st = h();
        return st.f;
    }

    function c(uint x) public {
        //无限循环
        while(true) {
             v = x;
	     if (s.f)
	     {
	       break;
	     }
        }
    }
}