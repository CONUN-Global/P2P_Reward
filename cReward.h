#pragma once

#include "cJSON.h"
#include "cURL.h"
#include "Common.h"

class cReward
{
public:
    cReward();
    ~cReward();

    std::string convertDouble(double value);

    std::string GetWalletInfoPath();
    std::string GetResultInfoPath();
    std::string GetRewardResultInfoPath(std::string ResultFileName);

    bool WalletInfoRead(const std::string _WalletInfoJson, std::string& _MasterWalletAddr, std::string& _MasterWalletPrivateKey);
    bool ResultInfoRead(const std::string _ResultInfoJson, const std::string _Master_Wallet_Addr, const std::string _Master_Wallet_PrivateKey, long double& _nTotalRewardCoin);
    bool RewardResultInfoRead(const std::string _RewardResultInfoJson);

    bool GetRewardInfo(std::string RewardFileName);
    bool GetReRewardInfo(std::string ResultFileName);

    bool SetContentHeader();
    bool SetUrl();

    long double TokenBalance();
    __int64 GetGasFee();
    __int64 GetGasLimit();

    bool Token_Transfer(std::string ResultFileName);

    bool Token_ReTransfer(std::string ResultFileName);

	std::vector<std::string> Get_Files_inDirectory(const std::string& _path, const std::string& _filter)
	{
		std::vector<std::string> return_;

		_finddata_t fd;
		long handle = _findfirst(_filter.c_str(), &fd);  //현재 폴더 내 모든 파일을 찾는다.

		if (handle == -1)    
            return return_;

        if (0 < strlen(fd.name))
        {            
			int result = 0;
			do
			{
                int nCompRet = strncmp(fd.name, _filter.c_str(), 11);
                int nCompRet2 = 0;

                for (int nLoop = 0; nLoop < static_cast<int>(strlen(fd.name)); nLoop++)
                {
                    nCompRet2 = isspace(fd.name[nLoop]); 
                    if (nCompRet2 != 0)
                        break;
                }

                int nLen = strlen(fd.name);
				if (0 == nCompRet && 0 == nCompRet2 && 26 >= nLen)
				{
					return_.push_back(fd.name);
					std::cout << "ResultInfo JSON File : [ " << fd.name << " ]" << std::endl;
				}
				result = _findnext(handle, &fd);
			} while (result != -1);
        }
		_findclose(handle);

		return return_;
	}

public:
    cJSON* m_pJson;

    std::map<int, StReward_Result>									m_Reward_Result;
    std::map<std::string, StReward_Info>							m_SumReward;
    std::multimap<std::string, StReward_Info>::iterator				m_it;
    std::multimap<std::string, StRewardList>::iterator				m_it2;

    std::pair<std::map<std::string, StReward_Info>::iterator, bool> m_Ret;

    StReward* m_pRewardInfo;
    StReReward* m_pReRewardInfo;

    cURL* m_pUrl;

    std::string m_strContentType;
    std::string m_strContentHeader;
    std::string m_strURL;

    std::string m_strParam, m_strParam2, m_strParam3, m_strParam4, m_strParam5, m_strParam6, m_strParam7, m_strParam8, m_strParam9, m_strParam10;

    __int64 nGas_Price, nGas_Limit;

    bool bTransfer_State;
    long double m_nTotalRewardCoin;
    int m_nReCount;
};

