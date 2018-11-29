#ifdef _WIN32
#ifdef _DEBUG
#define malloc(s) _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define free(p) _free_dbg(p, _NORMAL_BLOCK)
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif /*_DEBUG*/
#endif

#include "PA_EWallet.h"

#ifdef _WIN32
#pragma comment(lib, "EWallet.lib")
#endif //_WIN32

#include <stdio.h>  //for printf
#include <string.h> //for strlen
#include <stdlib.h> //for malloc

#if defined(_WIN32)
#include <windows.h>

void test_sleep(long lMilliSecond)
{
	Sleep(lMilliSecond);
	return;
}

long test_get_tick_count()
{
	return GetTickCount();
}

#elif ((defined(__linux__) || defined(__APPLE__)) && !defined(__ANDROID__))
#include <sys/time.h>
#include <unistd.h>

void test_sleep(long lMilliSecond)
{
	usleep(1000 * lMilliSecond);
}

long test_get_tick_count()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

#else

void test_sleep(long lMilliSecond)
{
	return;
}

long test_get_tick_count()
{
	return 0;
}

#endif

#define PAEW_TEST_DEFAULT_PIN "12345678"

static const char *getReturnString(const int retValue)
{
	char *strResult = 0;

	switch (retValue)
	{
	case PAEW_RET_SUCCESS:
		strResult = "success";
		break;
	case PAEW_RET_UNKNOWN_FAIL:
		strResult = "unknown error";
		break;
	case PAEW_RET_ARGUMENTBAD:
		strResult = "argument bad";
		break;
	case PAEW_RET_HOST_MEMORY:
		strResult = "host memory error";
		break;
	case PAEW_RET_DEV_ENUM_FAIL:
		strResult = "device enum failed";
		break;
	case PAEW_RET_DEV_OPEN_FAIL:
		strResult = "device open failed";
		break;
	case PAEW_RET_DEV_COMMUNICATE_FAIL:
		strResult = "device communicate failed";
		break;
	case PAEW_RET_DEV_NEED_PIN:
		strResult = "need pin error";
		break;
	case PAEW_RET_DEV_OP_CANCEL:
		strResult = "device operation cancelled";
		break;
	case PAEW_RET_DEV_KEY_NOT_RESTORED:
		strResult = "device key not restored";
		break;
	case PAEW_RET_DEV_KEY_ALREADY_RESTORED:
		strResult = "device key already restored";
		break;
	case PAEW_RET_DEV_COUNT_BAD:
		strResult = "device count bad";
		break;
	case PAEW_RET_DEV_RETDATA_INVALID:
		strResult = "device returned data invalid";
		break;
	case PAEW_RET_DEV_AUTH_FAIL:
		strResult = "device authentication failed";
		break;
	case PAEW_RET_DEV_STATE_INVALID:
		strResult = "device state invalid";
		break;
	case PAEW_RET_DEV_WAITING:
		strResult = "device waiting";
		break;
	case PAEW_RET_DEV_COMMAND_INVALID:
		strResult = "command invalid";
		break;
	case PAEW_RET_DEV_RUN_COMMAND_FAIL:
		strResult = "run command failed";
		break;
	case PAEW_RET_DEV_HANDLE_INVALID:
		strResult = "device handle invalid";
		break;
	case PAEW_RET_COS_TYPE_INVALID:
		strResult = "FW type invalid";
		break;
	case PAEW_RET_COS_TYPE_NOT_MATCH:
		strResult = "FW type not match";
		break;
	case PAEW_RET_DEV_BAD_SHAMIR_SPLIT:
		strResult = "bad shamir split";
		break;
	case PAEW_RET_DEV_NOT_ONE_GROUP:
		strResult = "device not one group";
		break;
	case PAEW_RET_BUFFER_TOO_SAMLL:
		strResult = "buffer too small";
		break;
	case PAEW_RET_TX_PARSE_FAIL:
		strResult = "transaction parsed error";
		break;
	case PAEW_RET_TX_UTXO_NEQ:
		strResult = "UTXO not equal to INPUT count";
		break;
	case PAEW_RET_TX_INPUT_TOO_MANY:
		strResult = "transaction INPUT too many";
		break;
	case PAEW_RET_MUTEX_ERROR:
		strResult = "mutex error";
		break;
	case PAEW_RET_COIN_TYPE_INVALID:
		strResult = "coin type invalid";
		break;
	case PAEW_RET_COIN_TYPE_NOT_MATCH:
		strResult = "coin type not match";
		break;
	case PAEW_RET_DERIVE_PATH_INVALID:
		strResult = "derive path invalid";
		break;
	case PAEW_RET_NOT_SUPPORTED:
		strResult = "call not supported";
		break;
	case PAEW_RET_INTERNAL_ERROR:
		strResult = "internal error";
		break;
	case PAEW_RET_BAD_N_T:
		strResult = "invalid N or T";
		break;
	case PAEW_RET_TARGET_DEV_INVALID:
		strResult = "target device invalid";
		break;
	case PAEW_RET_CRYPTO_ERROR:
		strResult = "crypto error";
		break;
	case PAEW_RET_DEV_TIMEOUT:
		strResult = "timeout";
		break;
	case PAEW_RET_DEV_PIN_LOCKED:
		strResult = "PIN locked";
		break;
	case PAEW_RET_DEV_PIN_CONFIRM_FAIL:
		strResult = "PIN confirm failed";
		break;
	case PAEW_RET_DEV_PIN_VERIFY_FAIL:
		strResult = "PIN verify failed";
		break;
	case PAEW_RET_DEV_CHECKDATA_FAIL:
		strResult = "device check data failed";
		break;
	case PAEW_RET_DEV_DEV_OPERATING:
		strResult = "device is on operating";
		break;
	case PAEW_RET_DEV_PIN_UNINIT:
		strResult = "PIN not inited";
		break;
	case PAEW_RET_DEV_BUSY:
		strResult = "device busy";
		break;
	case PAEW_RET_DEV_ALREADY_AVAILABLE:
		strResult = "device already available, don't need to abort";
		break;
	case PAEW_RET_DEV_DATA_NOT_FOUND:
		strResult = "device data not found";
		break;
	case PAEW_RET_DEV_SENSOR_ERROR:
		strResult = "device sensor error";
		break;
	case PAEW_RET_DEV_STORAGE_ERROR:
		strResult = "device storage error";
		break;
	case PAEW_RET_DEV_STORAGE_FULL:
		strResult = "device storage full";
		break;
	case PAEW_RET_DEV_FP_COMMON_ERROR:
		strResult = "finger print command error";
		break;
	case PAEW_RET_DEV_FP_REDUNDANT:
		strResult = "redundant fingerprint";
		break;
	case PAEW_RET_DEV_FP_GOOG_FINGER:
		strResult = "good fingerprint";
		break;
	case PAEW_RET_DEV_FP_NO_FINGER:
		strResult = "not fingerprint";
		break;
	case PAEW_RET_DEV_FP_NOT_FULL_FINGER:
		strResult = "not full fingerprint";
		break;
	case PAEW_RET_DEV_FP_BAD_IMAGE:
		strResult = "bad fingerprint image";
		break;
	case PAEW_RET_DEV_LOW_POWER:
		strResult = "device low power";
		break;
	case PAEW_RET_DEV_TYPE_INVALID:
		strResult = "device type invalid";
		break;
	case PAEW_RET_NO_VERIFY_COUNT:
		strResult = "no verify count";
		break;
	case PAEW_RET_AUTH_CANCEL:
		strResult = "current auth cancel";
		break;
	default:
		strResult = "unknown error type";
		break;
	}

	return strResult;
}

int ewallet_print_buf(const unsigned char *const pbData, const size_t nDataLen)
{
	int iRtn = -1;
	size_t i = 0;

	if (!pbData || !nDataLen)
	{
		iRtn = -1;
		goto END;
	}

	for (i = 0; i < (nDataLen - 1); i++)
	{
		printf("%02X", pbData[i]);
	}
	printf("%02X", pbData[i]);

	iRtn = 0;
END:
	return iRtn;
}

const char *ewallet_lifecycle2string(const unsigned char ucLifeCycle)
{
	const char *szRet = 0;

	switch (ucLifeCycle)
	{
	case PAEW_DEV_INFO_LIFECYCLE_INVALID:
		szRet = "invalid";
		break;
	case PAEW_DEV_INFO_LIFECYCLE_AGREE:
		szRet = "agree";
		break;
	case PAEW_DEV_INFO_LIFECYCLE_PRODUCE:
		szRet = "produce";
		break;
	case PAEW_DEV_INFO_LIFECYCLE_USER:
		szRet = "user";
		break;
	default:
		szRet = "unknown";
		break;
	}

	return szRet;
}

const char *ewallet_costype2string(const unsigned char ucCOSType)
{
	const char *szRet = 0;

	switch (ucCOSType)
	{
	case PAEW_DEV_INFO_COS_TYPE_PERSONAL:
		szRet = "personal";
		break;
	default:
		szRet = "unknown";
		break;
	}

	return szRet;
}

const char *ewallet_chaintype2string(const unsigned char ucChainType)
{
	const char *szRet = 0;

	switch (ucChainType)
	{
	case PAEW_DEV_INFO_CHAIN_TYPE_FORMAL:
		szRet = "formal net";
		break;
	case PAEW_DEV_INFO_CHAIN_TYPE_TEST:
		szRet = "test net";
		break;
	default:
		szRet = "unknown";
		break;
	}

	return szRet;
}

const char *ewallet_pinstate2string(const unsigned char ucPINState)
{
	const char *szRet = 0;

	switch (ucPINState)
	{
	case PAEW_DEV_INFO_PIN_INVALID_STATE:
		szRet = "invalid";
		break;
	case PAEW_DEV_INFO_PIN_LOGOUT:
		szRet = "logout";
		break;
	case PAEW_DEV_INFO_PIN_LOGIN:
		szRet = "login";
		break;
	case PAEW_DEV_INFO_PIN_LOCKED:
		szRet = "locked";
		break;
	case PAEW_DEV_INFO_PIN_UNSET:
		szRet = "unset";
		break;
	default:
		szRet = "unknown";
		break;
	}

	return szRet;
}

const char *ewallet_lcdstate2string(const uint64_t nLcdState)
{
	const char *szRet = 0;

	switch (nLcdState)
	{
	case PAEW_DEV_INFO_LCD_NULL:
		szRet = "null";
		break;
	case PAEW_DEV_INFO_LCD_SHOWLOGO:
		szRet = "show logo";
		break;
	case PAEW_DEV_INFO_LCD_WAITTING:
		szRet = "waiting";
		break;
	case PAEW_DEV_INFO_LCD_SHOWOK:
		szRet = "show ok";
		break;
	case PAEW_DEV_INFO_LCD_SHOWCANCEL:
		szRet = "show cancel";
		break;
	case PAEW_DEV_INFO_LCD_SHOWSKEYHASH:
		szRet = "show key hash";
		break;
	case PAEW_DEV_INFO_LCD_SHOWADDRESS:
		szRet = "show address";
		break;
	case PAEW_DEV_INFO_LCD_SHOWBTCSIGN:
		szRet = "show btc sign";
		break;
	case PAEW_DEV_INFO_LCD_SHOWETHSIGN:
		szRet = "show eth sign";
		break;
	case PAEW_DEV_INFO_LCD_SETNEWPIN:
		szRet = "set new pin";
		break;
	case PAEW_DEV_INFO_LCD_CHANGEPIN:
		szRet = "change pin";
		break;
	case PAEW_DEV_INFO_LCD_VERIFYPIN:
		szRet = "verify pin";
		break;
	case PAEW_DEV_INFO_LCD_PINLOCKED:
		szRet = "pin locked";
		break;
	case PAEW_DEV_INFO_LCD_FORMAT:
		szRet = "format";
		break;
	case PAEW_DEV_INFO_LCD_REBOOT:
		szRet = "reboot";
		break;
	case PAEW_DEV_INFO_LCD_SHOWBIP39:
		szRet = "show bip39";
		break;
	case PAEW_DEV_INFO_LCD_CHECKBIP39:
		szRet = "check bip39";
		break;
	case PAEW_DEV_INFO_LCD_SHOWBTSSIGN:
		szRet = "show bts sign";
		break;
	case PAEW_DEV_INFO_LCD_PINERROR:
		szRet = "show pin error";
		break;
	case PAEW_DEV_INFO_LCD_SELECT_MNENUM:
		szRet = "select mnemonic number";
		break;
	case PAEW_DEV_INFO_LCD_SHOWM:
		szRet = "show m";
		break;
	case PAEW_DEV_INFO_LCD_SHOWTIMEOUT:
		szRet = "show timeout";
		break;
	case PAEW_DEV_INFO_LCD_SHOWEOSSIGN:
		szRet = "show eos sign";
		break;
	case PAEW_DEV_INFO_LCD_SHOWFAIL:
		szRet = "show fail";
		break;
	case PAEW_DEV_INFO_LCD_SHOWNEOSIGN:
		szRet = "show neo sign";
		break;
	case PAEW_DEV_INFO_LCD_WAITING_TIMEOUT:
		szRet = "show waiting timeout";
		break;
	case PAEW_DEV_INFO_LCD_GET_MNENUM:
		szRet = "show get mnemonic number";
		break;
	case PAEW_DEV_INFO_LCD_GETMNE_BYDEV:
		szRet = "getting mnemonic by device";
		break;
	default:
		szRet = "unknown";
		break;
	}

	return szRet;
}

const char *ewallet_step2string(process_step pstep)
{
	const char *szRet = 0;

	switch (pstep)
	{
	case pstep_invalid:
		szRet = "invalid";
		break;
	case pstep_comm_enum_dev:
		szRet = "comm_enum_dev";
		break;
	case pstep_comm_open_dev:
		szRet = "comm_open_dev";
		break;
	case pstep_comm_close_dev:
		szRet = "comm_close_dev";
		break;
	case pstep_comm_get_devinfo:
		szRet = "comm_get_devinfo";
		break;
	case pstep_comm_dev_select:
		szRet = "comm_dev_select";
		break;
	case pstep_init_seed_gen:
		szRet = "init_seed_gen";
		break;
	case pstep_init_mne_show:
		szRet = "init_mne_show";
		break;
	case pstep_init_mne_confirm:
		szRet = "init_mne_confirm";
		break;
	case pstep_init_seed_import:
		szRet = "init_seed_import";
		break;
	case pstep_init_seed_import_comfirm:
		szRet = "init_seed_import_confirm";
		break;
	case pstep_init_keypair_gen:
		szRet = "init_keypair_gen";
		break;
	case pstep_init_key_agree_init:
		szRet = "init_key_agree_init";
		break;
	case pstep_init_key_agree_update:
		szRet = "init_key_agree_update";
		break;
	case pstep_init_key_agree_final:
		szRet = "init_key_agree_final";
		break;
	case pstep_init_key_agree_show:
		szRet = "init_key_agree_show";
		break;
	case pstep_init_key_agree_confirm:
		szRet = "init_key_agree_confirm";
		break;
	case pstep_init_shamir_transmit_init:
		szRet = "init_shamir_transmit_init";
		break;
	case pstep_init_shamir_export:
		szRet = "init_shamir_export";
		break;
	case pstep_init_shamir_import:
		szRet = "init_shamir_import";
		break;
	case pstep_init_shamir_confirm:
		szRet = "init_shamir_confirm";
		break;
	case pstep_comm_addr_gen:
		szRet = "comm_addr_gen";
		break;
	case pstep_comm_shamir_transmit_init:
		szRet = "comm_shamir_transmit_init";
		break;
	case pstep_comm_shamir_export:
		szRet = "comm_shamir_export";
		break;
	case pstep_comm_shamir_import:
		szRet = "comm_shamir_import";
		break;
	case pstep_comm_addr_get:
		szRet = "comm_addr_get";
		break;
	case pstep_comm_addr_confirm:
		szRet = "comm_addr_confirm";
		break;
	case pstep_comm_format:
		szRet = "comm_format";
		break;
	case pstep_comm_format_confirm:
		szRet = "comm_format_confirm";
		break;
	case pstep_sig_output_data:
		szRet = "sig_output_data";
		break;
	case pstep_sig_confirm:
		szRet = "sig_confirm";
		break;
	case pstep_comm_clearcos:
		szRet = "comm_clearcos";
		break;
	case pstep_comm_clearcos_confirm:
		szRet = "comm_clearcos_confirm";
		break;
	case pstep_comm_updatecos:
		szRet = "comm_updatecos";
		break;
	case pstep_comm_changepin:
		szRet = "comm_changepin";
		break;
	case pstep_comm_changepin_confirm:
		szRet = "comm_changepin_confirm";
		break;
	default:
		szRet = "unknown";
		break;
	}

	return szRet;
}

const char *ewallet_status2string(process_status pstatus)
{
	const char *szRet = 0;

	switch (pstatus)
	{
	case pstatus_invalid:
		szRet = "invalid";
		break;
	case pstatus_start:
		szRet = "start";
		break;
	case pstatus_finish:
		szRet = "finish";
		break;
	default:
		szRet = "unknown";
		break;
	}

	return szRet;
}

const char *ewallet_cointype2string(const unsigned char ucCoinType)
{
	const char *szRet = 0;

	switch (ucCoinType)
	{
	case PAEW_COIN_TYPE_BTC:
		szRet = "BTC";
		break;
	case PAEW_COIN_TYPE_ETH:
		szRet = "ETH";
		break;
	case PAEW_COIN_TYPE_EOS:
		szRet = "EOS";
		break;
	default:
		szRet = "unknown";
		break;
	}

	return szRet;
}

int test_ewallet_callback(callback_param *const pCallbackParam)
{
	int iRtn = -1;

	callback_data_addr_get *pCallbackData_AddrGet = 0;

	if (!pCallbackParam)
	{
		iRtn = -1;
		goto END;
	}

	if (pCallbackParam->pstep != pstep_comm_enum_dev)
	{
		printf("dev(%zd/%zd):\t", pCallbackParam->dev_index + 1, pCallbackParam->dev_count);
	}
	else
	{
		printf("dev(?/?):\t");
	}

	printf("%s\t", ewallet_step2string(pCallbackParam->pstep));
	printf("%s\t", ewallet_status2string(pCallbackParam->pstatus));
	if (pCallbackParam->pstatus == pstatus_finish)
	{
		printf("ret_value=0x%x\t", pCallbackParam->ret_value);
		if ((pCallbackParam->pstep == pstep_comm_addr_get) && (pCallbackParam->ret_value == PAEW_RET_SUCCESS))
		{
			pCallbackData_AddrGet = (callback_data_addr_get *)(pCallbackParam->data);
			if (pCallbackData_AddrGet->nCoinType == PAEW_COIN_TYPE_BTC)
			{
				printf("coin type: %s\t", ewallet_cointype2string(pCallbackData_AddrGet->nCoinType));
				printf("address: %s", (char *)pCallbackData_AddrGet->pbAddressData);
			}
			else if (pCallbackData_AddrGet->nCoinType == PAEW_COIN_TYPE_ETH)
			{
				printf("coin type: %s\t", ewallet_cointype2string(pCallbackData_AddrGet->nCoinType));
				printf("address: %s", (char *)pCallbackData_AddrGet->pbAddressData);
			}
			else if (pCallbackData_AddrGet->nCoinType == PAEW_COIN_TYPE_CYB)
			{
				printf("coin type: %s\t", ewallet_cointype2string(pCallbackData_AddrGet->nCoinType));
				printf("address: %s", (char *)pCallbackData_AddrGet->pbAddressData);
			}
			else if (pCallbackData_AddrGet->nCoinType == PAEW_COIN_TYPE_EOS)
			{
				printf("coin type: %s\t", ewallet_cointype2string(pCallbackData_AddrGet->nCoinType));
				printf("address: %s", (char *)pCallbackData_AddrGet->pbAddressData);
			}
			else if (pCallbackData_AddrGet->nCoinType == PAEW_COIN_TYPE_LTC)
			{
				printf("coin type: %s\t", ewallet_cointype2string(pCallbackData_AddrGet->nCoinType));
				printf("address: %s", (char *)pCallbackData_AddrGet->pbAddressData);
			}
			else if (pCallbackData_AddrGet->nCoinType == PAEW_COIN_TYPE_NEO)
			{
				printf("coin type: %s\t", ewallet_cointype2string(pCallbackData_AddrGet->nCoinType));
				printf("address: %s", (char *)pCallbackData_AddrGet->pbAddressData);
			}
		}
	}
	printf("\n");

	iRtn = 0;
END:
	return iRtn;
}

int test_ewallet_default()
{
	int iRtn = -1;

	void *pPAEWContext = 0;
	callback_param callbackParam;
	size_t nDevCount;

	iRtn = PAEW_InitContext(&pPAEWContext, &nDevCount, test_ewallet_callback, &callbackParam);
	if (iRtn != PAEW_RET_SUCCESS)
	{
		iRtn = -1;
		goto END;
	}

	iRtn = 0;
END:
	PAEW_FreeContext(pPAEWContext);
	return iRtn;
}

int test_ewallet_getdevinfo()
{
	int iRtn = -1;

	void *pPAEWContext = 0;
	callback_param callbackParam;
	size_t nDevCount;

	size_t i = 0;
	PAEW_DevInfo devInfo;
	uint32_t nDevInfoType = 0;

	iRtn = PAEW_InitContext(&pPAEWContext, &nDevCount, test_ewallet_callback, &callbackParam);
	if (iRtn != PAEW_RET_SUCCESS)
	{
		iRtn = -1;
		goto END;
	}

	for (i = 0; i < nDevCount; i++)
	{
		iRtn = PAEW_GetDevInfo(pPAEWContext, i, PAEW_DEV_INFOTYPE_LCD_STATE, &devInfo);
		if ((iRtn != PAEW_RET_SUCCESS) && (iRtn != PAEW_RET_NOT_SUPPORTED))
		{
			iRtn = -1;
			goto END;
		}
		if (iRtn == PAEW_RET_SUCCESS)
		{
			printf("Device[%zd] LCD State: %s\n", i, ewallet_lcdstate2string(devInfo.nLcdState));
		}

		iRtn = PAEW_GetDevInfo(pPAEWContext, i, PAEW_DEV_INFOTYPE_COS_TYPE, &devInfo);
		if (iRtn != PAEW_RET_SUCCESS)
		{
			iRtn = -1;
			goto END;
		}
		printf("Device[%zd] COS Type: %s\n", i, ewallet_costype2string(devInfo.ucCOSType));

		nDevInfoType = PAEW_DEV_INFOTYPE_COS_TYPE | PAEW_DEV_INFOTYPE_COS_VERSION | PAEW_DEV_INFOTYPE_SN | PAEW_DEV_INFOTYPE_CHAIN_TYPE | PAEW_DEV_INFOTYPE_PIN_STATE | PAEW_DEV_INFOTYPE_LIFECYCLE;
		if (devInfo.ucCOSType == PAEW_DEV_INFO_COS_TYPE_DRAGONBALL)
		{
			nDevInfoType |= (PAEW_DEV_INFOTYPE_N_T | PAEW_DEV_INFOTYPE_SESSKEY_HASH);
		}
		iRtn = PAEW_GetDevInfo(pPAEWContext, i, nDevInfoType, &devInfo);
		if (iRtn != PAEW_RET_SUCCESS)
		{
			iRtn = -1;
			goto END;
		}
		printf("Device[%zd] COS Version: ", i);
		ewallet_print_buf(devInfo.pbCOSVersion, sizeof(devInfo.pbCOSVersion));
		printf("\n");
		printf("Device[%zd] Serial Number: ", i);
		ewallet_print_buf(devInfo.pbSerialNumber, sizeof(devInfo.pbSerialNumber));
		printf("\n");
		printf("Device[%zd] Chain Type: %s\n", i, ewallet_chaintype2string(devInfo.ucChainType));
		printf("Device[%zd] PIN State: %s\n", i, ewallet_pinstate2string(devInfo.ucPINState));
		printf("Device[%zd] Life Cycle: %s\n", i, ewallet_lifecycle2string(devInfo.ucLifeCycle));

		if (devInfo.ucCOSType == PAEW_DEV_INFO_COS_TYPE_DRAGONBALL)
		{
			printf("Device[%zd] N=%d, T=%d\n", i, devInfo.nN, devInfo.nT);
			printf("Device[%zd] SessKey Hash: ", i);
			ewallet_print_buf(devInfo.pbSessKeyHash, sizeof(devInfo.pbSessKeyHash));
			printf("\n");
		}
	}

	iRtn = 0;
END:
	PAEW_FreeContext(pPAEWContext);
	return iRtn;
}

int test_ewallet_check_dev_state()
{
	int iRtn = -1;
	const int pin_invalid = 1;
	const int lcd_invalid = 2;

	void *pPAEWContext = 0;
	callback_param callbackParam;
	size_t nDevCount;

	PAEW_DevInfo devInfo;
	uint32_t nDevInfoType = 0;

	int lastState = 0;

	printf("waiting for device state ready, press Ctrl+C to exit\n");
	while (1)
	{
		if (pPAEWContext)
		{
			iRtn = PAEW_FreeContext(pPAEWContext);
			pPAEWContext = NULL;
		}

		iRtn = PAEW_InitContext(&pPAEWContext, &nDevCount, NULL, NULL);
		if (iRtn != PAEW_RET_SUCCESS)
		{
			test_sleep(500);
			continue;
		}

		iRtn = PAEW_GetDevInfo(pPAEWContext, 0, PAEW_DEV_INFOTYPE_LCD_STATE | PAEW_DEV_INFOTYPE_PIN_STATE, &devInfo);
		if (iRtn != PAEW_RET_SUCCESS)
		{
			test_sleep(500);
			continue;
		}

		if (devInfo.ucPINState != PAEW_DEV_INFO_PIN_LOGIN)
		{
			if (pin_invalid != lastState)
			{
				lastState = pin_invalid;
				printf("Device Pin state: %s, you should unlock it first\n", ewallet_pinstate2string(devInfo.ucPINState));
			}
			test_sleep(500);
			continue;
		}

		if (devInfo.nLcdState != PAEW_DEV_INFO_LCD_SHOWLOGO && devInfo.nLcdState != PAEW_DEV_INFO_LCD_NULL)
		{
			if (pin_invalid != lastState)
			{
				lastState = pin_invalid;
				printf("Device LCD state: %s, you should clear it first\n", ewallet_lcdstate2string(devInfo.nLcdState));
			}
			test_sleep(500);
			continue;
		}
		break;
	}
END:
	PAEW_FreeContext(pPAEWContext);
	return iRtn;
}

int test_ewallet_get_address()
{
	int iRtn = -1;

	void *pPAEWContext = 0;
	callback_param callbackParam;
	size_t nDevCount;

	PAEW_DevInfo devInfo;
	size_t i = 0;

	unsigned char pbAddressData[PAEW_COIN_ADDRESS_MAX_LEN] = {0};
	size_t nAddressDataLen = 0;

	const uint32_t puiBTCPath[] = {0, 0x8000002c, 0x80000000, 0x80000000, 0x00000000, 0x00000000};
	const uint32_t puiETHPath[] = {0, 0x8000002c, 0x8000003c, 0x80000000, 0x00000000, 0x00000000};
	const uint32_t puiEOSPath[] = {0, 0x8000002C, 0x800000c2, 0x80000000, 0x00000000, 0x00000000};

	iRtn = PAEW_InitContext(&pPAEWContext, &nDevCount, test_ewallet_callback, &callbackParam);
	if (iRtn != PAEW_RET_SUCCESS)
	{
		iRtn = -1;
		goto END;
	}

	iRtn = PAEW_GetDevInfo(pPAEWContext, 0, PAEW_DEV_INFOTYPE_COS_TYPE, &devInfo);
	if (iRtn != PAEW_RET_SUCCESS)
	{
		iRtn = -1;
		goto END;
	}
	printf("Device[%zd] COS Type: %s\n", (size_t)0, ewallet_costype2string(devInfo.ucCOSType));

	if (devInfo.ucCOSType == PAEW_DEV_INFO_COS_TYPE_PERSONAL)
	{
		for (i = 0; i < nDevCount; i++)
		{
			iRtn = PAEW_DeriveTradeAddress(pPAEWContext, i, PAEW_COIN_TYPE_BTC, puiBTCPath, sizeof(puiBTCPath) / sizeof(puiBTCPath[0]));
			if (iRtn != PAEW_RET_SUCCESS)
			{
				iRtn = -1;
				goto END;
			}

			nAddressDataLen = sizeof(pbAddressData);
			iRtn = PAEW_GetTradeAddress(pPAEWContext, i, PAEW_COIN_TYPE_BTC, 1, pbAddressData, &nAddressDataLen);
			if (iRtn != PAEW_RET_SUCCESS)
			{
				iRtn = -1;
				goto END;
			}

			iRtn = PAEW_DeriveTradeAddress(pPAEWContext, i, PAEW_COIN_TYPE_ETH, puiETHPath, sizeof(puiETHPath) / sizeof(puiETHPath[0]));
			if (iRtn != PAEW_RET_SUCCESS)
			{
				iRtn = -1;
				goto END;
			}

			nAddressDataLen = sizeof(pbAddressData);
			iRtn = PAEW_GetTradeAddress(pPAEWContext, i, PAEW_COIN_TYPE_ETH, 1, pbAddressData, &nAddressDataLen);
			if (iRtn != PAEW_RET_SUCCESS)
			{
				iRtn = -1;
				goto END;
			}			

			iRtn = PAEW_DeriveTradeAddress(pPAEWContext, i, PAEW_COIN_TYPE_EOS, puiEOSPath, sizeof(puiEOSPath) / sizeof(puiEOSPath[0]));
			if (iRtn != PAEW_RET_SUCCESS)
			{
				iRtn = -1;
				goto END;
			}

			nAddressDataLen = sizeof(pbAddressData);
			iRtn = PAEW_GetTradeAddress(pPAEWContext, i, PAEW_COIN_TYPE_EOS, 1, pbAddressData, &nAddressDataLen);
			if (iRtn != PAEW_RET_SUCCESS)
			{
				iRtn = -1;
				goto END;
			}
		}
	}
	else
	{
		iRtn = -1;
		goto END;
	}

	iRtn = 0;
END:
	PAEW_FreeContext(pPAEWContext);
	return iRtn;
}

int test_ewallet_btc_sig()
{
	int iRtn = -1;

	void *pPAEWContext = 0;
	callback_param callbackParam;
	size_t nDevCount;

	PAEW_DevInfo devInfo;
	size_t i = 0;

	unsigned char pbAddressData[PAEW_COIN_ADDRESS_MAX_LEN] = {0};
	size_t nAddressDataLen = 0;

	//m/44'/0'/0'/0/0
	const uint32_t puiBTCPath[] = {0, 0x8000002C, 0x80000000, 0x80000000, 0x00000000, 0x00000000};

	const size_t nUTXOCount = 2;
	const unsigned char pbUTXO1[] = {0x01, 0x00, 0x00, 0x00, 0x03, 0xe0, 0xb1, 0x1a, 0x95, 0x15, 0xee, 0x6d, 0x6b, 0x54, 0x08, 0xaf, 0x88, 0x1d, 0x6e, 0x44, 0x75, 0xdd, 0xbd, 0x4f, 0x4c, 0xab, 0xcf, 0xfa, 0x73, 0x00, 0xfc, 0x95, 0x36, 0x7f, 0xe5, 0x3f, 0xd0, 0x01, 0x00, 0x00, 0x00, 0x6b, 0x48, 0x30, 0x45, 0x02, 0x21, 0x00, 0xd7, 0xe8, 0x36, 0x51, 0x9e, 0x2b, 0x08, 0x5c, 0xae, 0x1c, 0xe9, 0xc4, 0xee, 0x45, 0x66, 0xe1, 0x4c, 0x31, 0xcf, 0x27, 0x6e, 0xbc, 0x78, 0xd4, 0x5b, 0x86, 0x55, 0xf8, 0x4f, 0x76, 0x3e, 0x5c, 0x02, 0x20, 0x4f, 0xb4, 0x83, 0xa7, 0xa4, 0xe5, 0xf1, 0x00, 0xcb, 0xcd, 0xd2, 0x23, 0xf3, 0xc2, 0x18, 0x20, 0xd9, 0xe8, 0xc9, 0xf6, 0xa6, 0x7f, 0x2b, 0x06, 0xbd, 0x52, 0xde, 0xf4, 0x66, 0x34, 0xba, 0xd9, 0x01, 0x21, 0x03, 0x95, 0xe0, 0x57, 0x1b, 0x44, 0x1e, 0x0f, 0x2f, 0xd9, 0x32, 0x90, 0x6a, 0x3f, 0xd6, 0x8a, 0x57, 0x09, 0x8a, 0x55, 0x52, 0xdd, 0x62, 0xe2, 0x23, 0x87, 0x13, 0x9b, 0x1f, 0x60, 0x78, 0x22, 0x3d, 0xff, 0xff, 0xff, 0xff, 0xe0, 0xb1, 0x1a, 0x95, 0x15, 0xee, 0x6d, 0x6b, 0x54, 0x08, 0xaf, 0x88, 0x1d, 0x6e, 0x44, 0x75, 0xdd, 0xbd, 0x4f, 0x4c, 0xab, 0xcf, 0xfa, 0x73, 0x00, 0xfc, 0x95, 0x36, 0x7f, 0xe5, 0x3f, 0xd0, 0x00, 0x00, 0x00, 0x00, 0x6a, 0x47, 0x30, 0x44, 0x02, 0x20, 0x5e, 0xfa, 0x77, 0x19, 0xce, 0x8d, 0xb5, 0x45, 0x4c, 0x55, 0xc2, 0x1a, 0x97, 0xe8, 0x9e, 0xce, 0xe2, 0x0e, 0x16, 0x7b, 0x84, 0x81, 0x63, 0x22, 0x5a, 0x30, 0xb6, 0x30, 0xb2, 0xab, 0xb8, 0x70, 0x02, 0x20, 0x12, 0xa2, 0x4d, 0xf9, 0xf0, 0xc7, 0x64, 0x84, 0x3b, 0x8e, 0xe5, 0x8a, 0x56, 0x63, 0x2f, 0xc8, 0x4b, 0xda, 0x23, 0xcc, 0xf7, 0xa7, 0x4c, 0xad, 0xe9, 0x45, 0xe7, 0xc1, 0x67, 0x96, 0xa4, 0x27, 0x01, 0x21, 0x03, 0x95, 0xe0, 0x57, 0x1b, 0x44, 0x1e, 0x0f, 0x2f, 0xd9, 0x32, 0x90, 0x6a, 0x3f, 0xd6, 0x8a, 0x57, 0x09, 0x8a, 0x55, 0x52, 0xdd, 0x62, 0xe2, 0x23, 0x87, 0x13, 0x9b, 0x1f, 0x60, 0x78, 0x22, 0x3d, 0xff, 0xff, 0xff, 0xff, 0x09, 0xfb, 0x2c, 0xc0, 0xa8, 0x73, 0x80, 0x0b, 0x67, 0xfb, 0x14, 0x39, 0x83, 0xf6, 0x6d, 0x7a, 0x02, 0xa6, 0xfb, 0x74, 0x02, 0x35, 0x6c, 0x64, 0x24, 0x67, 0x20, 0xf3, 0x1f, 0xb9, 0xee, 0xaf, 0x01, 0x00, 0x00, 0x00, 0x6a, 0x47, 0x30, 0x44, 0x02, 0x20, 0x25, 0xdd, 0xa0, 0xab, 0x18, 0x22, 0xb2, 0x87, 0x84, 0x96, 0x11, 0x6b, 0x36, 0xdb, 0x23, 0x9a, 0xeb, 0x98, 0x27, 0x60, 0xa8, 0x60, 0x39, 0xfd, 0xd5, 0xc3, 0x71, 0x34, 0x13, 0x78, 0x76, 0x38, 0x02, 0x20, 0x64, 0x60, 0xf3, 0x5b, 0x32, 0xa2, 0x92, 0xd2, 0x04, 0x73, 0xa8, 0x67, 0x73, 0x50, 0x68, 0xc1, 0xcf, 0xf3, 0xf0, 0x06, 0xeb, 0x27, 0xa1, 0x59, 0x22, 0xd3, 0xb7, 0x23, 0xce, 0x92, 0xfb, 0x54, 0x01, 0x21, 0x03, 0x95, 0xe0, 0x57, 0x1b, 0x44, 0x1e, 0x0f, 0x2f, 0xd9, 0x32, 0x90, 0x6a, 0x3f, 0xd6, 0x8a, 0x57, 0x09, 0x8a, 0x55, 0x52, 0xdd, 0x62, 0xe2, 0x23, 0x87, 0x13, 0x9b, 0x1f, 0x60, 0x78, 0x22, 0x3d, 0xff, 0xff, 0xff, 0xff, 0x02, 0x00, 0x46, 0xc3, 0x23, 0x00, 0x00, 0x00, 0x00, 0x19, 0x76, 0xa9, 0x14, 0xcd, 0x55, 0x7a, 0x2e, 0x83, 0xfb, 0x75, 0x18, 0x50, 0x73, 0xa3, 0x01, 0xda, 0x77, 0x28, 0x85, 0x18, 0x3b, 0x58, 0x0c, 0x88, 0xac, 0x11, 0x39, 0xc0, 0x05, 0x00, 0x00, 0x00, 0x00, 0x19, 0x76, 0xa9, 0x14, 0xcd, 0x55, 0x7a, 0x2e, 0x83, 0xfb, 0x75, 0x18, 0x50, 0x73, 0xa3, 0x01, 0xda, 0x77, 0x28, 0x85, 0x18, 0x3b, 0x58, 0x0c, 0x88, 0xac, 0x00, 0x00, 0x00, 0x00};
	const unsigned char pbUTXO2[] = {0x01, 0x00, 0x00, 0x00, 0x01, 0xde, 0xe0, 0x79, 0x35, 0x92, 0x48, 0x29, 0x9e, 0x3f, 0x24, 0xe7, 0x87, 0x7c, 0x6b, 0x1c, 0x2f, 0x36, 0x1b, 0x54, 0x74, 0x1f, 0x00, 0xb8, 0x05, 0x6f, 0xc5, 0x00, 0x1c, 0xdc, 0x75, 0x07, 0x94, 0x00, 0x00, 0x00, 0x00, 0x6a, 0x47, 0x30, 0x44, 0x02, 0x20, 0x0d, 0xbb, 0xca, 0x48, 0x74, 0xb8, 0x36, 0x23, 0xea, 0x6c, 0x31, 0x97, 0x0d, 0xf4, 0x9e, 0xfb, 0xc3, 0x71, 0xc1, 0x20, 0xa9, 0x33, 0xea, 0x7f, 0x5a, 0xd7, 0x07, 0xf7, 0xa0, 0xbc, 0x57, 0xab, 0x02, 0x20, 0x7c, 0xd3, 0x14, 0x05, 0xcb, 0xcb, 0x55, 0x20, 0xe6, 0x35, 0x07, 0x9f, 0x1b, 0x8a, 0x8b, 0xde, 0xc9, 0xe7, 0xea, 0x6c, 0x5a, 0xa5, 0x99, 0x7e, 0xa1, 0xee, 0x65, 0x9e, 0xe4, 0xef, 0xdd, 0x77, 0x01, 0x21, 0x03, 0x95, 0xe0, 0x57, 0x1b, 0x44, 0x1e, 0x0f, 0x2f, 0xd9, 0x32, 0x90, 0x6a, 0x3f, 0xd6, 0x8a, 0x57, 0x09, 0x8a, 0x55, 0x52, 0xdd, 0x62, 0xe2, 0x23, 0x87, 0x13, 0x9b, 0x1f, 0x60, 0x78, 0x22, 0x3d, 0xff, 0xff, 0xff, 0xff, 0x02, 0x00, 0x46, 0xc3, 0x23, 0x00, 0x00, 0x00, 0x00, 0x19, 0x76, 0xa9, 0x14, 0xcd, 0x55, 0x7a, 0x2e, 0x83, 0xfb, 0x75, 0x18, 0x50, 0x73, 0xa3, 0x01, 0xda, 0x77, 0x28, 0x85, 0x18, 0x3b, 0x58, 0x0c, 0x88, 0xac, 0x60, 0xb9, 0xeb, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x19, 0x76, 0xa9, 0x14, 0xcd, 0x55, 0x7a, 0x2e, 0x83, 0xfb, 0x75, 0x18, 0x50, 0x73, 0xa3, 0x01, 0xda, 0x77, 0x28, 0x85, 0x18, 0x3b, 0x58, 0x0c, 0x88, 0xac, 0x00, 0x00, 0x00, 0x00};
	const unsigned char *ppbUTXO[] = {pbUTXO1, pbUTXO2};
	const size_t pnUTXOLen[] = {sizeof(pbUTXO1), sizeof(pbUTXO2)};

	const unsigned char pbCurrentTX[] = {0x01, 0x00, 0x00, 0x00, 0x02, 0xbf, 0x69, 0x08, 0x9d, 0x98, 0xb9, 0x3c, 0xd3, 0xe5, 0x4f, 0xb2, 0xcc, 0x45, 0x75, 0xde, 0x55, 0x0f, 0xa4, 0x6b, 0x49, 0x01, 0xc8, 0xd3, 0xf5, 0x9c, 0xa3, 0x18, 0xfc, 0x63, 0xe0, 0x02, 0x77, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xcd, 0x6e, 0x85, 0xa4, 0xe5, 0x33, 0xf5, 0x6f, 0x65, 0x8b, 0x80, 0xb1, 0x9d, 0xee, 0x11, 0x4f, 0x0b, 0xc4, 0xb0, 0xc7, 0x80, 0xeb, 0x68, 0x3b, 0x59, 0x22, 0x1c, 0x6f, 0xe1, 0x81, 0xd3, 0x57, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x02, 0x00, 0xca, 0x9a, 0x3b, 0x00, 0x00, 0x00, 0x00, 0x19, 0x76, 0xa9, 0x14, 0xcd, 0x55, 0x7a, 0x2e, 0x83, 0xfb, 0x75, 0x18, 0x50, 0x73, 0xa3, 0x01, 0xda, 0x77, 0x28, 0x85, 0x18, 0x3b, 0x58, 0x0c, 0x88, 0xac, 0xbb, 0xb3, 0xeb, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x19, 0x76, 0xa9, 0x14, 0xcd, 0x55, 0x7a, 0x2e, 0x83, 0xfb, 0x75, 0x18, 0x50, 0x73, 0xa3, 0x01, 0xda, 0x77, 0x28, 0x85, 0x18, 0x3b, 0x58, 0x0c, 0x88, 0xac, 0x00, 0x00, 0x00, 0x00};

	unsigned char pbTXSig1[PAEW_BTC_SIG_MAX_LEN] = {0};
	unsigned char pbTXSig2[PAEW_BTC_SIG_MAX_LEN] = {0};
	unsigned char *ppbTXSig[] = {pbTXSig1, pbTXSig2};
	size_t pnTXSigLen[] = {sizeof(pbTXSig1), sizeof(pbTXSig2)};

	iRtn = PAEW_InitContext(&pPAEWContext, &nDevCount, test_ewallet_callback, &callbackParam);
	if (iRtn != PAEW_RET_SUCCESS)
	{
		iRtn = -1;
		goto END;
	}

	iRtn = PAEW_GetDevInfo(pPAEWContext, 0, PAEW_DEV_INFOTYPE_COS_TYPE, &devInfo);
	if (iRtn != PAEW_RET_SUCCESS)
	{
		iRtn = -1;
		goto END;
	}
	printf("Device[%zd] COS Type: %s\n", (size_t)0, ewallet_costype2string(devInfo.ucCOSType));

	if (devInfo.ucCOSType == PAEW_DEV_INFO_COS_TYPE_PERSONAL)
	{
		for (i = 0; i < nDevCount; i++)
		{
			iRtn = PAEW_DeriveTradeAddress(pPAEWContext, i, PAEW_COIN_TYPE_BTC, puiBTCPath, sizeof(puiBTCPath) / sizeof(puiBTCPath[0]));
			if (iRtn != PAEW_RET_SUCCESS)
			{
				iRtn = -1;
				goto END;
			}

			nAddressDataLen = sizeof(pbAddressData);
			iRtn = PAEW_GetTradeAddress(pPAEWContext, i, PAEW_COIN_TYPE_BTC, 0, pbAddressData, &nAddressDataLen);
			if (iRtn != PAEW_RET_SUCCESS)
			{
				iRtn = -1;
				goto END;
			}

			iRtn = PAEW_BTC_TXSign(pPAEWContext, i, nUTXOCount, ppbUTXO, pnUTXOLen, pbCurrentTX, sizeof(pbCurrentTX), ppbTXSig, pnTXSigLen);
			if (iRtn != PAEW_RET_SUCCESS)
			{
				iRtn = -1;
				goto END;
			}
		}
	}
	else
	{
		iRtn = -1;
		goto END;
	}

	iRtn = 0;
END:
	PAEW_FreeContext(pPAEWContext);
	return iRtn;
}

int test_ewallet_eth_sig()
{
	int iRtn = -1;

	void *pPAEWContext = 0;
	callback_param callbackParam;
	size_t nDevCount;

	PAEW_DevInfo devInfo;
	size_t i = 0;

	unsigned char pbAddressData[PAEW_COIN_ADDRESS_MAX_LEN] = {0};
	size_t nAddressDataLen = 0;

	const uint32_t puiETHPath[] = {0, 0x8000002c, 0x8000003c, 0x80000000, 0x00000000, 0x00000000};
	const unsigned char pbETHCurrentTX[] = {0xec, 0x09, 0x85, 0x04, 0xa8, 0x17, 0xc8, 0x00, 0x82, 0x52, 0x08, 0x94, 0x35, 0x35, 0x35, 0x35, 0x35, 0x35, 0x35, 0x35, 0x35, 0x35, 0x35, 0x35, 0x35, 0x35, 0x35, 0x35, 0x35, 0x35, 0x35, 0x35, 0x88, 0x0d, 0xe0, 0xb6, 0xb3, 0xa7, 0x64, 0x00, 0x00, 0x80, 0x01, 0x80, 0x80};
	unsigned char pbETHTXSig[PAEW_ETH_SIG_MAX_LEN] = {0};
	size_t nETHTXSigLen = PAEW_ETH_SIG_MAX_LEN;

	iRtn = PAEW_InitContext(&pPAEWContext, &nDevCount, test_ewallet_callback, &callbackParam);
	if (iRtn != PAEW_RET_SUCCESS)
	{
		iRtn = -1;
		goto END;
	}

	iRtn = PAEW_GetDevInfo(pPAEWContext, 0, PAEW_DEV_INFOTYPE_COS_TYPE, &devInfo);
	if (iRtn != PAEW_RET_SUCCESS)
	{
		iRtn = -1;
		goto END;
	}
	printf("Device[%zd] COS Type: %s\n", (size_t)0, ewallet_costype2string(devInfo.ucCOSType));

	if (devInfo.ucCOSType == PAEW_DEV_INFO_COS_TYPE_PERSONAL)
	{
		for (i = 0; i < nDevCount; i++)
		{
			iRtn = PAEW_DeriveTradeAddress(pPAEWContext, i, PAEW_COIN_TYPE_ETH, puiETHPath, sizeof(puiETHPath) / sizeof(puiETHPath[0]));
			if (iRtn != PAEW_RET_SUCCESS)
			{
				iRtn = -1;
				goto END;
			}

			nAddressDataLen = sizeof(pbAddressData);
			iRtn = PAEW_GetTradeAddress(pPAEWContext, i, PAEW_COIN_TYPE_ETH, 0, pbAddressData, &nAddressDataLen);
			if (iRtn != PAEW_RET_SUCCESS)
			{
				iRtn = -1;
				goto END;
			}

			nETHTXSigLen = sizeof(pbETHTXSig);
			iRtn = PAEW_ETH_TXSign(pPAEWContext, i, pbETHCurrentTX, sizeof(pbETHCurrentTX), pbETHTXSig, &nETHTXSigLen);
			if (iRtn != PAEW_RET_SUCCESS)
			{
				iRtn = -1;
				goto END;
			}
		}
	}
	else
	{
		iRtn = -1;
		goto END;
	}

	iRtn = 0;
END:
	PAEW_FreeContext(pPAEWContext);
	return iRtn;
}

int test_ewallet_eos_sig()
{
	int iRtn = -1;

	void *pPAEWContext = 0;
	callback_param callbackParam;
	size_t nDevCount;

	PAEW_DevInfo devInfo;
	size_t i = 0;

	unsigned char pbAddressData[PAEW_COIN_ADDRESS_MAX_LEN] = {0};
	size_t nAddressDataLen = 0;

	const uint32_t puiEOSPath[] = {0, 0x8000002C, 0x800000c2, 0x80000000, 0x00000000, 0x00000000};

	const char *szEOSCurrentTX = "{ \"expiration\": \"2018-05-24T11:34:03\", \"ref_block_num\": 47172, \"ref_block_prefix\": \"3655466833\", \"max_net_usage_words\": 0, \"max_cpu_usage_ms\": 0, \"delay_sec\": 0, \"context_free_actions\": [], \"actions\": [ { \"account\": \"consale\", \"name\": \"getlist\", \"authorization\": [ { \"actor\": \"alice\", \"permission\": \"active\" } ], \"data\": \"\" } ], \"transaction_extensions\": []}";
	unsigned char pbEOSTXBin[512] = {0};
	size_t nEOSTXBinLen = 0;

	const unsigned char pbEOSCurrentTX[] = {0x74, 0x09, 0x70, 0xd9, 0xff, 0x01, 0xb5, 0x04, 0x63, 0x2f, 0xed, 0xe1, 0xad, 0xc3, 0xdf, 0xe5, 0x59, 0x90, 0x41, 0x5e, 0x4f, 0xde, 0x01, 0xe1, 0xb8, 0xf3, 0x15, 0xf8, 0x13, 0x6f, 0x47, 0x6c, 0x14, 0xc2, 0x67, 0x5b, 0x01, 0x24, 0x5f, 0x70, 0x5d, 0xd7, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0xa6, 0x82, 0x34, 0x03, 0xea, 0x30, 0x55, 0x00, 0x00, 0x00, 0x57, 0x2d, 0x3c, 0xcd, 0xcd, 0x01, 0x20, 0x29, 0xc2, 0xca, 0x55, 0x7a, 0x73, 0x57, 0x00, 0x00, 0x00, 0x00, 0xa8, 0xed, 0x32, 0x32, 0x21, 0x20, 0x29, 0xc2, 0xca, 0x55, 0x7a, 0x73, 0x57, 0x90, 0x55, 0x8c, 0x86, 0x77, 0x95, 0x4c, 0x3c, 0x10, 0x27, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x45, 0x4f, 0x53, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

	unsigned char pbEOSTXSig[PAEW_EOS_SIG_MAX_LEN] = {0};
	size_t nEOSTXSigLen = PAEW_EOS_SIG_MAX_LEN;

	iRtn = PAEW_EOS_TX_Serialize(szEOSCurrentTX, 0, &nEOSTXBinLen);
	if (iRtn != PAEW_RET_SUCCESS)
	{
		iRtn = -1;
		goto END;
	}
	nEOSTXBinLen = sizeof(pbEOSTXBin);
	iRtn = PAEW_EOS_TX_Serialize(szEOSCurrentTX, pbEOSTXBin, &nEOSTXBinLen);
	if (iRtn != PAEW_RET_SUCCESS)
	{
		iRtn = -1;
		goto END;
	}
	nEOSTXBinLen = sizeof(pbEOSTXBin);
	iRtn = PAEW_EOS_TX_Part_Serialize(PAEW_SIG_EOS_TX_HEADER, szEOSCurrentTX, pbEOSTXBin, &nEOSTXBinLen);
	if (iRtn != PAEW_RET_SUCCESS)
	{
		iRtn = -1;
		goto END;
	}
	nEOSTXBinLen = sizeof(pbEOSTXBin);
	iRtn = PAEW_EOS_TX_Part_Serialize(PAEW_SIG_EOS_TX_ACTION_COUNT, szEOSCurrentTX, pbEOSTXBin, &nEOSTXBinLen);
	if (iRtn != PAEW_RET_SUCCESS)
	{
		iRtn = -1;
		goto END;
	}
	nEOSTXBinLen = sizeof(pbEOSTXBin);
	iRtn = PAEW_EOS_TX_Part_Serialize(PAEW_SIG_EOS_TX_ACTION, szEOSCurrentTX, pbEOSTXBin, &nEOSTXBinLen);
	if (iRtn != PAEW_RET_SUCCESS)
	{
		iRtn = -1;
		goto END;
	}
	nEOSTXBinLen = sizeof(pbEOSTXBin);
	iRtn = PAEW_EOS_TX_Part_Serialize(PAEW_SIG_EOS_TX_CF_HASH, szEOSCurrentTX, pbEOSTXBin, &nEOSTXBinLen);
	if (iRtn != PAEW_RET_SUCCESS)
	{
		iRtn = -1;
		goto END;
	}

	iRtn = PAEW_InitContext(&pPAEWContext, &nDevCount, test_ewallet_callback, &callbackParam);
	if (iRtn != PAEW_RET_SUCCESS)
	{
		iRtn = -1;
		goto END;
	}

	iRtn = PAEW_GetDevInfo(pPAEWContext, 0, PAEW_DEV_INFOTYPE_COS_TYPE, &devInfo);
	if (iRtn != PAEW_RET_SUCCESS)
	{
		iRtn = -1;
		goto END;
	}
	printf("Device[%zd] COS Type: %s\n", (size_t)0, ewallet_costype2string(devInfo.ucCOSType));

	if (devInfo.ucCOSType == PAEW_DEV_INFO_COS_TYPE_PERSONAL)
	{
		for (i = 0; i < nDevCount; i++)
		{
			iRtn = PAEW_DeriveTradeAddress(pPAEWContext, i, PAEW_COIN_TYPE_EOS, puiEOSPath, sizeof(puiEOSPath) / sizeof(puiEOSPath[0]));
			if (iRtn != PAEW_RET_SUCCESS)
			{
				iRtn = -1;
				goto END;
			}

			nAddressDataLen = sizeof(pbAddressData);
			iRtn = PAEW_GetTradeAddress(pPAEWContext, i, PAEW_COIN_TYPE_EOS, 0, pbAddressData, &nAddressDataLen);
			if (iRtn != PAEW_RET_SUCCESS)
			{
				iRtn = -1;
				goto END;
			}

			nEOSTXSigLen = sizeof(pbEOSTXSig);
			iRtn = PAEW_EOS_TXSign(pPAEWContext, i, pbEOSCurrentTX, sizeof(pbEOSCurrentTX), pbEOSTXSig, &nEOSTXSigLen);
			if (iRtn != PAEW_RET_SUCCESS)
			{
				iRtn = -1;
				goto END;
			}
		}
	}
	else
	{
		iRtn = -1;
		goto END;
	}

	iRtn = 0;
END:
	PAEW_FreeContext(pPAEWContext);
	return iRtn;
}

int main()
{
	int iRtn = -1;

#if defined(_WIN32) && defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_CRT_DF);
	//_CrtSetBreakAlloc(1805);
#endif

	iRtn = test_ewallet_getdevinfo();
	printf("test_ewallet_getdevinfo return %d\n", iRtn);

	test_ewallet_check_dev_state();
	iRtn = test_ewallet_get_address();
	printf("test_ewallet_get_address return %d\n", iRtn);

	test_ewallet_check_dev_state();
	iRtn = test_ewallet_btc_sig();
	printf("test_ewallet_btc_sig return %d\n", iRtn);

	test_ewallet_check_dev_state();
	iRtn = test_ewallet_eth_sig();
	printf("test_ewallet_eth_sig return %d\n", iRtn);

	test_ewallet_check_dev_state();
	iRtn = test_ewallet_eos_sig();
	printf("test_ewallet_eos_sig return %d\n", iRtn);

	printf("all tests done, press any key to continue...");
	getchar();

	iRtn = 0;
	return iRtn;
}
