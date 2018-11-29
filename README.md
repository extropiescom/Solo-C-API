# Solo-C-API
C level API for WOOKONG Solo

Supported OS list:

macOS Mavericks (10.9) and above

Windows 7/8/8.1/10 x64

for macOS, use the following commands to compile and run:
```
gcc -o EWalletTest -L. -lEWallet EWalletTest.c
cp libEWallet.dylib /usr/local/lib
./EWalletTest
```

for Windows, use the following commands to compile and run:
```
cl EWalletTest.cpp
EWalletTest
```

All the APIs are defined in [PAEWallet.h](https://github.com/extropiescom/Solo-C-API/blob/master/PA_EWallet.h)


## 1. How to connect and disconnect:
   - Use `PAEW_InitContext` to connect device
   - User `PAEW_FreeContext` to disconnect device.
## 2. How to get EOS address:
   - Invoke `PAEW_DeriveTradeAddress`, with
   `derivePath = {0, 0x8000002C, 0x800000c2, 0x80000000, 0x00000000, 0x00000000}` according to [slip-44](https://github.com/satoshilabs/slips/blob/master/slip-0044.md).
   - Invoke `PAEW_GetTradeAddress` to get EOS address.
## 3. How to sign EOS transaction:
   Please refer to `test_ewallet_eos_sig ` in [EWalletTest.c](https://github.com/extropiescom/Solo-C-API/blob/master/EWalletTest.c)
   - Invoke `PAEW_DeriveTradeAddress`, with
   `derivePath = {0, 0x8000002C, 0x800000c2, 0x80000000, 0x00000000, 0x00000000};` according to [slip-44](https://github.com/satoshilabs/slips/blob/master/slip-0044.md).
   - (Optional) Invoke `PAEW_EOS_TX_Serialize` to serialize json string to binary.
   
   _NOTE1: ref_block_prefix field of json object MUST be wrapped by quotation marks ("") if you pass it to `PAEW_EOS_TX_Serialize`, such as \"2642943355\" in the following._
   
   _NOTE2: serializeData is the binary form of transaction, you should prefix it with 32 bytes of chain_id, and padding with 32 bytes of zeros, then pass it to `PAEW_EOS_TXSign` to sign._
   
   ```c
   const char* jsonTxString = "{\"expiration\":\"2018-05-16T02:49:35\",\"ref_block_num\":4105,\"ref_block_prefix\":\"2642943355\",\"max_net_usage_words\":0,\"max_cpu_usage_ms\":0,\"delay_sec\":0,\"context_free_actions\":[],\"actions\":[{\"account\":\"eosio\",\"name\":\"newaccount\",\"authorization\":[{\"actor\":\"eosio\",\"permission\":\"active\"}],\"data\":\"0000000000ea30550000000000000e3d01000000010003224c02ca019e9c0c969d2c8006b89275abeeb5b05af68f2cf5f497bd6e1aff6d01000000010000000100038d424cbe81564f1e4338d342a4dc2b70d848d8b026d3f783bc7c8e6c3c6733cf01000000\"}],\"transaction_extensions\":[],\"signatures\":[],\"context_free_data\":[]}";
   unsigned char *pSerializeData = NULL;
   int serializeDataLen = 0;
   //get buffer size using serializeData = null
   iRtn = PAEW_EOS_TX_Serialize(jsonTxString, pSerializeData, &serializeDataLen);
   if (iRtn == PAEW_RET_SUCCESS) {
      //malloc buffer, remember to free it after use
      pSerializeData = (unsigned char *)malloc(serializeDataLen);
      //serialize transaction
      iRtn = PAEW_EOS_TX_Serialize(jsonTxString, pSerializeData, &serializeDataLen);
   }
   ```   
   - Invoke `PAEW_EOS_TXSign(void * const pPAEWContext, const size_t nDevIndex, const unsigned char * const pbCurrentTX, const size_t nCurrentTXLen, unsigned char * const pbTXSig, size_t * const pnTXSigLen)`, 
   _this transaction is serialized result of a json transaction string, prefixed with chain_id (32 bytes) and tailed with zeros (32 bytes)_
   ```c
   unsigned char transaction[] = {0x74, 0x09, 0x70, 0xd9, 0xff, 0x01, 0xb5, 0x04, 0x63, 0x2f, 0xed, 0xe1, 0xad, 0xc3, 0xdf, 0xe5, 0x59, 0x90, 0x41, 0x5e, 0x4f, 0xde, 0x01, 0xe1, 0xb8, 0xf3, 0x15, 0xf8, 0x13, 0x6f, 0x47, 0x6c, 0x14, 0xc2, 0x67, 0x5b, 0x01, 0x24, 0x5f, 0x70, 0x5d, 0xd7, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0xa6, 0x82, 0x34, 0x03, 0xea, 0x30, 0x55, 0x00, 0x00, 0x00, 0x57, 0x2d, 0x3c, 0xcd, 0xcd, 0x01, 0x20, 0x29, 0xc2, 0xca, 0x55, 0x7a, 0x73, 0x57, 0x00, 0x00, 0x00, 0x00, 0xa8, 0xed, 0x32, 0x32, 0x21, 0x20, 0x29, 0xc2, 0xca, 0x55, 0x7a, 0x73, 0x57, 0x90, 0x55, 0x8c, 0x86, 0x77, 0x95, 0x4c, 0x3c, 0x10, 0x27, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x45, 0x4f, 0x53, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
   unsigned char signature[PAEW_EOS_SIG_MAX_LEN]= {0};
   int sigLen = PAEW_ETH_SIG_MAX_LEN;
   iRtn = PAEW_EOS_TXSign(pPAEWContext, 0, transaction, sizeof(transaction), signature, &sigLen);
   ```
 ## 4. How to sign BTC and ETH transaction: 
 Please refer to `test_ewallet_btc_sig` and `test_ewallet_eth_sig` in [EWalletTest.c](https://github.com/extropiescom/Solo-C-API/blob/master/EWalletTest.c)
 Similar to EOS, Invoke `PAEW_DeriveTradeAddress` first, then call `PAEW_BTC_TXSign` or `PAEW_ETH_TXSign` to get sign result


