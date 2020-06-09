#include <platon/platon.hpp>
#include <string>
using namespace platon;

CONTRACT Compute : public platon::Contract{
	
	private:
      platon::StorageType<"vecstorage"_n, std::vector<std::string>> storage_vector_string;
	  platon::StorageType<"ownaddr"_n, Address> contract_ower;

	public:
    ACTION void init(){}

    CONST int MonthsBetween2Date(const std::string& date1, const std::string& date2)
    {    
      int year1, month1;
      int year2, month2;
      year1 = atoi((date1.substr(0,4)).c_str());
    	month1 = atoi((date1.substr(5,2)).c_str());
    	year2 = atoi((date2.substr(0,4)).c_str());
    	month2 = atoi((date2.substr(5,2)).c_str());
      return 12*(year2-year1) + month2 - month1;
    }

    ACTION void insertVectorValue(const std::string &my_value)
    {
        storage_vector_string.self().push_back(my_value);
    }

    CONST uint64_t getVectorSize()
    {
       return storage_vector_string.self().size();
    }

    CONST std::string getPagingQuery(uint64_t CurrentPage, uint64_t PageMaxSize)
    {
        int vecSize = 0;
        int pages = 0;
		
        vecSize = storage_vector_string.self().size();
        pages = vecSize / PageMaxSize;
        if(0 != vecSize % PageMaxSize)
        {
            pages += 1;
        }

        if(CurrentPage <= 0)
        {
        	return "";
        }
        else if(CurrentPage > pages)
        {
            return "";
        }

        int nStartIndex = (CurrentPage - 1) * PageMaxSize;
        int nEndIndex = nStartIndex + PageMaxSize - 1;

        if(nEndIndex >= vecSize)
        {
        	nEndIndex = vecSize - 1;
        }

        std::string strVecInfo = "{";
        strVecInfo += "\"";
        strVecInfo += "PageTotal";
        strVecInfo += "\":";
        strVecInfo += to_string(pages);
        strVecInfo += ",";
        strVecInfo += "\"";
        strVecInfo += "Data";
        strVecInfo += "\":[";

        for(int i = nStartIndex; i <= nEndIndex; i++)
        {
            std::string strTmp = "";
            strTmp = storage_vector_string.self().at(i);
            strVecInfo += strTmp + ",";
        }

        strVecInfo.pop_back();
        strVecInfo += "]}";

        char* buf = (char*)malloc(strVecInfo.size() + 1);
        memset(buf, 0, strVecInfo.size()+1);
        strcpy(buf, strVecInfo.c_str());
        return buf;
    }

    ACTION bool destroy_contract()
    {
      Address platon_address = platon_origin();
      if (contract_ower.self() != platon_address.toString()){
          return false;
      }
      return platon_destroy(platon_address);
    }
};

PLATON_DISPATCH(Compute, (init)(MonthsBetween2Date)(insertVectorValue)(getVectorSize)(getPagingQuery)(destroy_contract))
