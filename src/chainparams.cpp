// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds array into usable address objects.
static void convertSeeds(std::vector<CAddress> &vSeedsOut, const unsigned int *data, unsigned int count, int port)
{
     // It'll only connect to one or two seed nodes because once it connects,
     // it'll get a pile of addresses with newer timestamps.
     // Seed nodes are given a random 'last seen time' of between one and two
     // weeks ago.
     const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int k = 0; k < count; ++k)
    {
        struct in_addr ip;
        unsigned int i = data[k], t;
        
        // -- convert to big endian
        t =   (i & 0x000000ff) << 24u
            | (i & 0x0000ff00) << 8u
            | (i & 0x00ff0000) >> 8u
            | (i & 0xff000000) >> 24u;
        
        memcpy(&ip, &t, sizeof(ip));
        
        CAddress addr(CService(ip, port));
        addr.nTime = GetTime()-GetRand(nOneWeek)-nOneWeek;
        vSeedsOut.push_back(addr);
    }
}



class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x6b;
        pchMessageStart[1] = 0xfa;
        pchMessageStart[2] = 0xe4;
        pchMessageStart[3] = 0x7d;
        vAlertPubKey = ParseHex("048167a6bd00e404c64e5d9465f9c1a90f56a30933c74f479011047b3ca1c27127fb3d1260832aaabde7b87d85c3935f7a623f3163fc6dd7601e311033941e3014");
        nDefaultPort = 19053;
        nRPCPort = 19054;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);

        const char* pszTimestamp = "How Trump could respond to the Syria chemical attack?";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1523373135, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1523373135;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 98392856;

        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0x966b7f93e3aab77dd3784f49e9929f05f0d423f771a54f7722c2beb673be5ede"));
        assert(genesis.hashMerkleRoot == uint256("0xc989f4b3005b7df9588223756d41cf7f413e1f20111b78b3d4219687178e281c"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,138);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,138);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,128);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,138);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        vSeeds.push_back(CDNSSeedData("0","213.91.190.58"));
        vSeeds.push_back(CDNSSeedData("1","45.76.35.38"));
        vSeeds.push_back(CDNSSeedData("2","45.77.89.133"));
        vSeeds.push_back(CDNSSeedData("3","207.246.97.85"));

        convertSeeds(vFixedSeeds, pnSeed, ARRAYLEN(pnSeed), nDefaultPort);

        nPoolMaxTransactions = 3;
        // strSporkKey = "044641223ef068e61bee2f836eaf65a0f364cbd9d634c0b3c4211db1911d885e2cf3836ae2eb9c002827b67de999c71920a33f01ff75161f0ddbea63916d879ae7"
        // strMasternodePaymentsPubKey = "048598d4a1db6a25ae5916d3ceea0144ba9bc6442f7f96e07f49ca224b8e643f54d18d3c78d7dbd04644b55871eab1137d34ac14d2422aaae74ca816bcd470169c"
        strDarksendPoolDummyAddress = "9frEPbxv2ANZzrViEqTCWaBL8S63FQHz9s";
        nLastPOWBlock = 2690000; // 5 years
        nPOSStartBlock = 3000;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x1c;
        pchMessageStart[1] = 0x2f;
        pchMessageStart[2] = 0xd5;
        pchMessageStart[3] = 0x3d;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("0435f00b1f5a9e23c46acfee0218f7c33d9a60767f2fed00d0b95c727ba1b2ffd364d9be88428e195e64f069e15303d51a857ee660b1a7ddbc8c38e71c5f7f1205");
        nDefaultPort = 19153;
        nRPCPort = 19154;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 8);
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nTime    = 1523373135+120;
        genesis.nNonce = 483;

       if (false && (genesis.GetHash() != hashGenesisBlock))
        {
            uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
            while (genesis.GetHash() > hashTarget)
            {
                ++genesis.nNonce;
                if (genesis.nNonce == 0)
                {
                    printf("NONCE WRAPPED, incrementing time");
                    ++genesis.nTime;
                }
            }
            cout << "testnet.genesis : \n" << genesis.ToString() << endl;
            cout << "testnet.genesis.GetHash(): " << genesis.GetHash().ToString() << endl;
            cout << "testnet.genesis.hashMerkleRoot: " << genesis.hashMerkleRoot.ToString() << endl;
            cout << "testnet.genesis.nTime: " << genesis.nTime << endl;
            cout << "testnet.genesis.nNonce: " << genesis.nNonce << endl;
        }
        //assert(hashGenesisBlock == uint256("6a7cb13f9c1bdd73bc0a76b7a5034e80716fdf6a13d64b7cd5ccba790c8441e7"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,123);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,123);
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1,125);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,123);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        convertSeeds(vFixedSeeds, pnTestnetSeed, ARRAYLEN(pnTestnetSeed), nDefaultPort);
        // strSporkKey = "04a5afa83fc1d05b02cc191cb4b27a12ec61811650d200173f5fa712b78e4221f236cb3e6f56d46ff8ee7597cadbb54ae37380c78d348dd2995292c6cffbebc3bf"
        // strMasternodePaymentsPubKey = "045608ba481008f7ca6700e56b43b610b4fc660b0d5dddfc62c23dad0107f5dde3a04bf48e28791afe6642ef68b8f12f70eb083a94b4036704120eb6db6b59a533"
        nLastPOWBlock = 0x7fffffff;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    
    bool fTestNet = GetBoolArg("-testnet", false);
    
    if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
