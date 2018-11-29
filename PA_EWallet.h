/**
 *\file		PA_EWallet.h
 *\brief	Header File of EWallet Middleware
 */

#ifndef _PA_EWALLET_H_
#define _PA_EWALLET_H_

#include <stdint.h>

#ifndef _WIN32
#include <stddef.h> //for size_t
#endif              //_WIN32

/**
 * \defgroup group_retvalue Return values
 */
///@{
#define PAEW_RET_SUCCESS 0x00000000                  ///<success
#define PAEW_RET_UNKNOWN_FAIL 0x80000001             ///<unknown error
#define PAEW_RET_ARGUMENTBAD 0x80000002              ///<argument bad
#define PAEW_RET_HOST_MEMORY 0x80000003              ///<memory malloc failed, maybe insufficient memory on host
#define PAEW_RET_DEV_ENUM_FAIL 0x80000004            ///<device enumerate failed
#define PAEW_RET_DEV_OPEN_FAIL 0x80000005            ///<device open(connect) failed
#define PAEW_RET_DEV_COMMUNICATE_FAIL 0x80000006     ///<device communicate failed, usually caused by disconnect
#define PAEW_RET_DEV_NEED_PIN 0x80000007             ///<device not login, need PIN verification
#define PAEW_RET_DEV_OP_CANCEL 0x80000008            ///<current operation on device is cancelled
#define PAEW_RET_DEV_KEY_NOT_RESTORED 0x80000009     ///<current operation needs key restored
#define PAEW_RET_DEV_KEY_ALREADY_RESTORED 0x8000000A ///<current operation doesn’t need key restored
#define PAEW_RET_DEV_COUNT_BAD 0x8000000B            ///<errors such as no device, or device count must equal to N when initiating, device count must >= T and <= N when restore or sign
#define PAEW_RET_DEV_RETDATA_INVALID 0x8000000C      ///<received data length less than 2 or ret data structure invalid
#define PAEW_RET_DEV_AUTH_FAIL 0x8000000D            ///<current operation is failed because of device authentication error
#define PAEW_RET_DEV_STATE_INVALID 0x8000000E        ///<life cycle or other device state not matched to current operation
#define PAEW_RET_DEV_WAITING 0x8000000F              ///<waiting for user to operate on device
#define PAEW_RET_DEV_COMMAND_INVALID 0x80000010      ///<command cannot recognized by device
#define PAEW_RET_DEV_RUN_COMMAND_FAIL 0x80000011     ///<data returned by device indicates some common errors
#define PAEW_RET_DEV_HANDLE_INVALID 0x80000012       ///<invalid device handle
#define PAEW_RET_COS_TYPE_INVALID 0x80000013         ///<value of COS type must be PAEW_DEV_INFO_COS_TYPE_XXX
#define PAEW_RET_COS_TYPE_NOT_MATCH 0x80000014       ///<device cos type not matched to current operation, such as dragon ball spec function calls on personal e-wallet, or passed argument implies specific cos type while current cos type not match, or current inserted devices' types are not the same
#define PAEW_RET_DEV_BAD_SHAMIR_SPLIT 0x80000015     ///<errors when calculating shamir data
#define PAEW_RET_DEV_NOT_ONE_GROUP 0x80000016        ///<dragon ball devices not belong to one group
#define PAEW_RET_BUFFER_TOO_SAMLL 0x80000017         ///<size of input buffer not enough to store return data
#define PAEW_RET_TX_PARSE_FAIL 0x80000018            ///<input transaction parse failed
#define PAEW_RET_TX_UTXO_NEQ 0x80000019              ///<count of input and UTXO is not equal
#define PAEW_RET_TX_INPUT_TOO_MANY 0x8000001A        ///<input count shouldn't larger than 100
#define PAEW_RET_MUTEX_ERROR 0x8000001B              ///<mutex error, such as create / free / lock / unlock
#define PAEW_RET_COIN_TYPE_INVALID 0x8000001C        ///<value of coin type must be PAEW_COIN_TYPE_XXX
#define PAEW_RET_COIN_TYPE_NOT_MATCH 0x8000001D      ///<value of coin type must be equal to the value passed to PAEW_DeriveTradeAddress
#define PAEW_RET_DERIVE_PATH_INVALID 0x8000001E      ///<derive path must start by 0x00000000, indicates m
#define PAEW_RET_NOT_SUPPORTED 0x8000001F            ///<operation not supportted
#define PAEW_RET_INTERNAL_ERROR 0x80000020           ///<library internal errors, such as internal structure definition mistake
#define PAEW_RET_BAD_N_T 0x80000021                  ///<value of N or T is invalid
#define PAEW_RET_TARGET_DEV_INVALID 0x80000022       ///<when getting address or signing, dragon ball must select a target device by calling PAEW_DeriveTradeAddress successfully first
#define PAEW_RET_CRYPTO_ERROR 0x80000023             ///<errors of cryption
#define PAEW_RET_DEV_TIMEOUT 0x80000024              ///<operation time out
#define PAEW_RET_DEV_PIN_LOCKED 0x80000025           ///<PIN locked
#define PAEW_RET_DEV_PIN_CONFIRM_FAIL 0x80000026     ///<set new pin error when confirm
#define PAEW_RET_DEV_PIN_VERIFY_FAIL 0x80000027      ///<input pin error when change pin or do other operation
#define PAEW_RET_DEV_CHECKDATA_FAIL 0x80000028       ///<input data check failed in device, usually caused by invalid CRC check
#define PAEW_RET_DEV_DEV_OPERATING 0x80000029        ///<user is operating device, please wait
#define PAEW_RET_DEV_PIN_UNINIT 0x8000002A           ///<PIN not initialized
#define PAEW_RET_DEV_BUSY 0x8000002B                 ///<device is busy, such as when enroll or verify finger print, previous operation is not finished yet
#define PAEW_RET_DEV_ALREADY_AVAILABLE 0x8000002C    ///<device is available, not need to abort again
#define PAEW_RET_DEV_DATA_NOT_FOUND 0x8000002D       ///<required data is not found
#define PAEW_RET_DEV_SENSOR_ERROR 0x8000002E         ///<sensor (such as finger print sensor) error
#define PAEW_RET_DEV_STORAGE_ERROR 0x8000002F        ///<device storage error
#define PAEW_RET_DEV_STORAGE_FULL 0x80000030         ///<device storage full
#define PAEW_RET_DEV_FP_COMMON_ERROR 0x80000031      ///<finger print common error (such as finger print verify or enroll error)
#define PAEW_RET_DEV_FP_REDUNDANT 0x80000032         ///<finger print redundant error
#define PAEW_RET_DEV_FP_GOOG_FINGER 0x80000033       ///<finger print enroll step success
#define PAEW_RET_DEV_FP_NO_FINGER 0x80000034         ///<sensor haven't got any finger print
#define PAEW_RET_DEV_FP_NOT_FULL_FINGER 0x80000035   ///<sensor haven't got full finger print image
#define PAEW_RET_DEV_FP_BAD_IMAGE 0x80000036         ///<sensor haven't got valid image
#define PAEW_RET_DEV_LOW_POWER 0x80000037            ///<device power is too low
#define PAEW_RET_DEV_TYPE_INVALID 0x80000038         ///<invalid device type
#define PAEW_RET_NO_VERIFY_COUNT 0x80000039          ///<count of verification run out when doing signature
#define PAEW_RET_AUTH_CANCEL 0x8000003A              ///<not used yet
#define PAEW_RET_PIN_LEN_ERROR 0x8000003B            ///<PIN length error
#define PAEW_RET_AUTH_TYPE_INVALID 0x8000003C        ///<authenticate type invalid
///@}

#if (defined(_WIN32) && defined(_USRDLL))

#ifdef _EWALLET_DLL_
#define EWALLET_API __declspec(dllexport)
#else //_EWALLET_DLL_
#define EWALLET_API
#endif //_EWALLET_DLL_

#else //_WIN32

#define EWALLET_API

#endif //_WIN32

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * \defgroup group_callbacks Callbacks
 */
    ///@{

    typedef enum _process_step
    {
        pstep_invalid,

        pstep_comm_enum_dev,
        pstep_comm_open_dev,
        pstep_comm_close_dev,
        pstep_comm_get_devinfo,
        pstep_comm_dev_select,

        pstep_init_seed_gen,
        pstep_init_mne_show,
        pstep_init_mne_confirm,
        pstep_init_seed_import,
        pstep_init_seed_import_comfirm,

        pstep_init_keypair_gen,
        pstep_init_key_agree_init,
        pstep_init_key_agree_update,
        pstep_init_key_agree_final,
        pstep_init_key_agree_show,
        pstep_init_key_agree_confirm,

        pstep_init_shamir_transmit_init,
        pstep_init_shamir_export,
        pstep_init_shamir_import,
        pstep_init_shamir_confirm,

        pstep_sig_output_data,
        pstep_sig_confirm,

        pstep_comm_addr_gen,
        pstep_comm_shamir_transmit_init,
        pstep_comm_shamir_export,
        pstep_comm_shamir_import,

        pstep_comm_addr_get,
        pstep_comm_addr_confirm,

        pstep_comm_format,
        pstep_comm_format_confirm,

        pstep_comm_clearcos,
        pstep_comm_clearcos_confirm,

        pstep_comm_updatecos,

        pstep_comm_changepin,
        pstep_comm_changepin_confirm,

        pstep_comm_addr_info_get,
        pstep_comm_addr_info_set,

        pstep_comm_erc20_info_set,

        pstep_init_mne_check,
        pstep_init_pin_init,

        pstep_comm_pin_verify,

        pstep_comm_fp_getlist,
        pstep_comm_fp_enroll,
        pstep_comm_fp_verify,
        pstep_comm_fp_getstate,
        pstep_comm_fp_abort,
        pstep_comm_fp_delete,
        pstep_comm_fp_calibrate,
    } process_step;

    typedef enum _process_status
    {
        pstatus_invalid,
        pstatus_start,
        pstatus_finish,
    } process_status;

#define INVALID_DEV_INDEX ((size_t)(-1))
#define PAEW_CALLBACK_DATA_MAX_LEN (1024)

#pragma pack(1)
    typedef struct _callback_data_addr_get
    {
        unsigned char nCoinType;
        size_t nAddressLen;
        unsigned char pbAddressData[PAEW_CALLBACK_DATA_MAX_LEN - sizeof(size_t) - 1];
    } callback_data_addr_get;
#pragma pack()

    typedef struct _callback_param
    {
        process_step pstep;
        process_status pstatus;
        int ret_value; //when pstatus==pstatus_finish, check this value

        size_t dev_index; //current main device index, from 0 to dev_count-1, not valid in pstep_comm_enum_dev

        //user define data
        size_t dev_count; //valid in pstep_comm_enum_dev

        unsigned char data[PAEW_CALLBACK_DATA_MAX_LEN]; //store addr or other informations
    } callback_param;

    typedef int (*tFunc_Proc_Callback)(callback_param *const pCallbackParam);

    typedef int (*tFunc_Progress_Callback)(void *const pCallbackContext, const size_t nProgress); ///<Callback to indicate progress of a long-time function

    typedef int (*tFunc_PutState_Callback)(void *const pCallbackContext, const int nState); ///<Callback to indicate button or finge rprint loop state

    typedef int (*tFunc_GetAuthType)(void *const pCallbackContext, unsigned char *const pnAuthType);               ///<\deprecated This function type is only used for compatible reason, and will be removed soon
    typedef int (*tFunc_GetPIN)(void *const pCallbackContext, unsigned char *const pbPIN, size_t *const pnPINLen); ///<\deprecated This function type is only used for compatible reason, and will be removed soon
    typedef int (*tFunc_PutSignState)(void *const pCallbackContext, const int nSignState);                         ///<\deprecated This function type is only used for compatible reason, and will be removed soon
    /**
* \deprecated This structure is only used for compatible reason, and will be removed soon
*/
    typedef struct _signCallbacks
    {
        tFunc_GetAuthType getAuthType;   ///<when sign function is invoked, getAuthType is called firstly, to get authenticate type which user chose or set by app, and should return PAEW_SIGN_AUTH_TYPE_XXX by pnAuthType
        tFunc_GetPIN getPIN;             ///<if pnAuthType is PAEW_SIGN_AUTH_TYPE_PIN, this function is called to let app inject PIN value to sign procedure
        tFunc_PutSignState putSignState; ///<this function is called multiple times when waiting for sign procedure is completed, sign state can be one of the values of PAEW_RET_XXXX
    } signCallbacks;

///@}

/**
 * \defgroup group_devinfo_type Device info type
 */
///@{
#define PAEW_DEV_INFOTYPE_PIN_STATE 0x00000001    ///<PIN state, such as un-login / login / unset / locked
#define PAEW_DEV_INFOTYPE_COS_TYPE 0x00000002     ///<COS type, such as dragon ball or personal
#define PAEW_DEV_INFOTYPE_CHAIN_TYPE 0x00000004   ///<chain type, such as formal net or test net
#define PAEW_DEV_INFOTYPE_SN 0x00000008           ///<device serial number
#define PAEW_DEV_INFOTYPE_COS_VERSION 0x00000010  ///<COS version
#define PAEW_DEV_INFOTYPE_LIFECYCLE 0x00000020    ///<device life cycle, such as agreement / user / produce
#define PAEW_DEV_INFOTYPE_SESSKEY_HASH 0x00000040 ///<dragon ball device group hash
#define PAEW_DEV_INFOTYPE_N_T 0x00000080          ///<dragon ball device N / T
#define PAEW_DEV_INFOTYPE_LCD_STATE 0x00000100    ///<device screen state
///@}

/**
 * \defgroup group_pin_state PIN state
 */
///@{
#define PAEW_DEV_INFO_PIN_INVALID_STATE 0xFF ///<invalid PIN state
#define PAEW_DEV_INFO_PIN_LOGOUT 0x00        ///<PIN not logged-in
#define PAEW_DEV_INFO_PIN_LOGIN 0x01         ///<PIN logged-in
#define PAEW_DEV_INFO_PIN_LOCKED 0x02        ///<PIN locked
#define PAEW_DEV_INFO_PIN_UNSET 0x03         ///<PIN not initialized
///@}

/**
 * \defgroup group_chain_type Chain type
 */
///@{
#define PAEW_DEV_INFO_CHAIN_TYPE_FORMAL 0x01 ///<formal chain
#define PAEW_DEV_INFO_CHAIN_TYPE_TEST 0x02   ///<test chain
///@}

/**
 * \defgroup group_sn Device serial number
 */
/// @{
#define PAEW_DEV_INFO_SN_LEN 0x20 ///<max length of serial number
/// @}

/**
 * \defgroup group_cos_version COS version
 * 1st byte means cos architecture, usually essential cos upgrade
 * 2nd byte means cos type, currently 00 dragon ball, 01 personal wallet, 02 biometric wallet
 * 3rd and 4th bytes means minor version
 */
/// @{
#define PAEW_DEV_INFO_COS_VERSION_LEN 0x04 ///<COS version length
/// @}

/**
 * \defgroup group_cos_type COS type
 */
/// @{
#define PAEW_DEV_INFO_COS_TYPE_INDEX 0x01      ///<index of COS type
#define PAEW_DEV_INFO_COS_TYPE_INVALID 0xFF    ///<invalid COS type
#define PAEW_DEV_INFO_COS_TYPE_DRAGONBALL 0x00 ///<dragon ball wallet
#define PAEW_DEV_INFO_COS_TYPE_PERSONAL 0x01   ///<personal wallet
#define PAEW_DEV_INFO_COS_TYPE_BIO 0x02        ///<biometric wallet
/// @}

/**
 * \defgroup group_dev_lifecycle Device lifecycle
 */
/// @{
#define PAEW_DEV_INFO_LIFECYCLE_INVALID 0xFF ///<invalid lifecycle
#define PAEW_DEV_INFO_LIFECYCLE_AGREE 0x01   ///<production state
#define PAEW_DEV_INFO_LIFECYCLE_USER 0x02    ///<normal state
#define PAEW_DEV_INFO_LIFECYCLE_PRODUCE 0x04 ///<not generate seed
/// @}

/**
 * \defgroup group_dragonball_dev_info Dragon ball device info
 */
/// @{
#define PAEW_DEV_INFO_SESSKEY_HASH_LEN 0x04 ///<length of dragon ball group hash
#define PAEW_DEV_INFO_N_T_INVALID 0xFF      ///<dragon ball N/T
    /// @}

#define PAEW_DEV_INFO_LCD_NULL 0x00000000
#define PAEW_DEV_INFO_LCD_SHOWLOGO 0x00000001
#define PAEW_DEV_INFO_LCD_WAITTING 0x00000002
#define PAEW_DEV_INFO_LCD_SHOWOK 0x00000004
#define PAEW_DEV_INFO_LCD_SHOWCANCEL 0x00000008
#define PAEW_DEV_INFO_LCD_SHOWSKEYHASH 0x00000010
#define PAEW_DEV_INFO_LCD_SHOWADDRESS 0x00000020
#define PAEW_DEV_INFO_LCD_SHOWBTCSIGN 0x00000040
#define PAEW_DEV_INFO_LCD_SHOWETHSIGN 0x00000080
#define PAEW_DEV_INFO_LCD_SETNEWPIN 0x00000100
#define PAEW_DEV_INFO_LCD_CHANGEPIN 0x00000200
#define PAEW_DEV_INFO_LCD_VERIFYPIN 0x00000400
#define PAEW_DEV_INFO_LCD_PINLOCKED 0x00000800
#define PAEW_DEV_INFO_LCD_FORMAT 0x00001000
#define PAEW_DEV_INFO_LCD_REBOOT 0x00002000
#define PAEW_DEV_INFO_LCD_SHOWBIP39 0x00004000
#define PAEW_DEV_INFO_LCD_CHECKBIP39 0x00008000
#define PAEW_DEV_INFO_LCD_SHOWBTSSIGN 0x00010000
#define PAEW_DEV_INFO_LCD_PINERROR 0x00020000
#define PAEW_DEV_INFO_LCD_SELECT_MNENUM 0x00040000
#define PAEW_DEV_INFO_LCD_SHOWM 0x00080000
#define PAEW_DEV_INFO_LCD_SHOWTIMEOUT 0x00100000
#define PAEW_DEV_INFO_LCD_SHOWEOSSIGN 0x00200000
#define PAEW_DEV_INFO_LCD_SHOWFAIL 0x00400000
#define PAEW_DEV_INFO_LCD_SHOWNEOSIGN 0x00800000
#define PAEW_DEV_INFO_LCD_WAITING_TIMEOUT 0x01000000
#define PAEW_DEV_INFO_LCD_GET_MNENUM 0x02000000
#define PAEW_DEV_INFO_LCD_GETMNE_BYDEV 0x04000000

    /**
 * \brief Device info structure
 */
    typedef struct _PAEW_DevInfo
    {
        unsigned char ucPINState;                                  ///<PIN state, valid values are PAEW_DEV_INFO_PIN_XX
        unsigned char ucCOSType;                                   ///<COS type, valid values are PAEW_DEV_INFO_COS_TYPE_XXX
        unsigned char ucChainType;                                 ///<chain type, valid values are PAEW_DEV_INFO_CHAIN_TYPE_XXX
        unsigned char pbSerialNumber[PAEW_DEV_INFO_SN_LEN];        ///<device serial number, current content is ASCII string
        unsigned char pbCOSVersion[PAEW_DEV_INFO_COS_VERSION_LEN]; ///<device COS version
        unsigned char ucLifeCycle;                                 ///<device life cycle, valid values are PAEW_DEV_INFO_LIFECYCLE_XXX
        uint64_t nLcdState;                                        ///<screen state, valid values are PAEW_DEV_INFO_LCD_XXX

        //dragon ball device info
        unsigned char pbSessKeyHash[PAEW_DEV_INFO_SESSKEY_HASH_LEN]; ///<dragon ball device group hash
        uint8_t nN;                                                  ///<group device count of dragon ball device
        uint8_t nT;                                                  ///<minimum valid device count of dragon ball device
    } PAEW_DevInfo;

/**
 * \defgroup group_coin_type Coin types
 */
/// @{
#define PAEW_COIN_TYPE_INVALID 0xFF    ///<invalid coin type
#define PAEW_COIN_TYPE_BTC 0x00        ///<BTC
#define PAEW_COIN_TYPE_ETH 0x01        ///<ETH
#define PAEW_COIN_TYPE_CYB 0x02        ///<CYBEX
#define PAEW_COIN_TYPE_EOS 0x03        ///<EOS
#define PAEW_COIN_TYPE_LTC 0x04        ///<LTC
#define PAEW_COIN_TYPE_NEO 0x05        ///<NEO
#define PAEW_COIN_TYPE_ETC 0x06        ///<ETC
#define PAEW_COIN_TYPE_BTC_WIT 0x07    ///<BTC P2WPKH nested in BIP16 P2SH
#define PAEW_COIN_TYPE_BTC_SIGWIT 0x08 ///<BTC P2WPKH
#define PAEW_COIN_TYPE_XRP 0x09        ///<XRP
#define PAEW_COIN_TYPE_USDT 0x0A       ///<USDT，only used by PAEW_GetTradeAddress
/// @}

/**
 * \defgroup group_sig_constant Signature related constants
 */
/// @{
#define PAEW_BTC_SIG_MAX_LEN 0x70 ///<BTC max signature length
#define PAEW_ETH_SIG_MAX_LEN 0x45 ///<ETH max signature length
#define PAEW_ETC_SIG_MAX_LEN 0x45 ///<ETC max signature length
#define PAEW_CYB_SIG_MAX_LEN 0x41 ///<CYB max signature length

#define PAEW_EOS_SIG_MAX_LEN 0x80         ///<EOS max signature length
#define PAEW_SIG_EOS_TX_HEADER 0x00       ///<EOS header
#define PAEW_SIG_EOS_TX_ACTION_COUNT 0x01 ///<EOS action count
#define PAEW_SIG_EOS_TX_ACTION 0x02       ///<EOS action
#define PAEW_SIG_EOS_TX_CF_HASH 0x03      ///<EOS context_free hash

#define PAEW_LTC_SIG_MAX_LEN 0x70     ///<LTC max signature length
#define PAEW_NEO_SIG_MAX_LEN 0x70     ///<NEO max signature length
#define PAEW_BTC_WIT_SIG_MAX_LEN 0x70 ///<BTC WITNESS max signature length
#define PAEW_XRP_SIG_MAX_LEN 0x70     ///<XRP max signature length
/// @}

/**
 * \defgroup group_images Image and screen
 */
/// @{
#define PAEW_IMAGE_NAME_MAX_LEN 63    ///<image name max len
#define PAEW_LCD_CLEAR 0x00           ///<clear screen
#define PAEW_LCD_SHOW_LOGO 0x01       ///<show logo on screen
#define PAEW_LCD_CLEAR_SHOW_LOGO 0x02 ///<clear screen and then show logo on screen
/// @}

/**
* \defgroup group_dev_type Device type
*/
/// @{
#define PAEW_DEV_TYPE_INVALID 0xFF ///<invalid device type
#define PAEW_DEV_TYPE_HID 0x00     ///<HID device
#define PAEW_DEV_TYPE_BT 0x01      ///<blue tooth device
/// @}

/**
 * \defgroup group_sign_auth_type Signature authenticate type
 */
/// @{
#define PAEW_SIGN_AUTH_TYPE_PIN 0x00 ///<sign authenticate type: PIN
#define PAEW_SIGN_AUTH_TYPE_FP 0x01  ///<sign authenticate type: Fingerprint
/// @}

/**
 * \defgroup group_other_constant Other constant
 */
/// @{
#define INVALID_DEV_INDEX ((size_t)(-1)) ///<invalid device index
#define PAEW_COIN_ADDRESS_MAX_LEN 0x80   ///<coin address max len
#define PAEW_ROOT_SEED_LEN 0x40          ///<root seed len

#define PAEW_MNE_MAX_LEN 512        ///<mnemonic max len
#define PAEW_MNE_INDEX_MAX_COUNT 32 ///<mnemonic max count

#define PAEW_PIN_MAX_LEN 0x20 ///<PIN max len

#define PAEW_PUBLIC_KEY_MAX_LEN 0x60 ///<public key max len
    /// @}

    /**
 * \defgroup group_functions Middleware functions
 */
    ///@{

    /**
 * \brief			Get device list with device context
 * \param[in]		nDeviceType		device Type, valid values are PAEW_DEV_TYPE_XXX (\ref group_dev_type)
 * \param[out]		szDeviceNames	buffer used to store device name list when this function succeeds. Format of name list is: devName1 + \0 + devName2 + \0 + ... + devNameN + \0\0
 * \param[in,out]	pnDeviceNameLen	this value represents size of szDevNames when input, and represents valid length of name list when output, should not be NULL
 * \param[out]		pnDevCount		device count
 * \param[in]		pDevContext		device context
 * \param[in]		nDevContextLen	device context length
 * \return			#PAEW_RET_SUCCESS means success, and other value means failure (\ref group_retvalue)
 */
    int EWALLET_API PAEW_GetDeviceListWithDevContext(const unsigned char nDeviceType, char *const szDeviceNames, size_t *const pnDeviceNameLen, size_t *const pnDevCount, void *const pDevContext, const size_t nDevContextLen);

    /**
* \brief			Initialize context and connect devices
* \param[out]		ppPAEWContext	address used to store the value of address used to record initialized library context, shouldn't be NULL, and must be passed to PAEW_FreeContext() to free memory when not used anymore
* \param[out]		pnDevCount		contains device count when function success
* \param[in]        pProcCallback	callback function used to watch on processes in functions
* \param[in]        pCallbackParam	callback parameter
* \return			#PAEW_RET_SUCCESS means success, and other value means failure (\ref group_retvalue)
*/
    int EWALLET_API PAEW_InitContext(void **const ppPAEWContext, size_t *const pnDevCount, const tFunc_Proc_Callback pProcCallback, callback_param * const pCallbackParam);

    /**
* \brief			Free context and disconnect device
* \param[in]		pPAEWContext	library context, shouldn't be NULL
* \return			#PAEW_RET_SUCCESS means success, and other value means failure (\ref group_retvalue)
* \sa				PAEW_InitContext(), PAEW_InitContextWithDevContext(), PAEW_InitContextWithDevName(), PAEW_InitContextWithDevNameAndDevContext()
*/
    int EWALLET_API PAEW_FreeContext(void *const pPAEWContext);

    /**
* \brief			Get device info
* \param[in]		pPAEWContext	library context, shouldn't be NULL
* \param[in]		nDevIndex		index of device, valid range of value is [0, nDevCount-1]
* \param[in]		nDevInfoType	device info types user want to get, valid values should be ORs of PAEW_DEV_INFOTYPE_XXX (\ref group_devinfo_type)
* \param[out]		pDevInfo		returned device info, shouldn't be NULL
* \return			#PAEW_RET_SUCCESS means success, and other value means failure (\ref group_retvalue)
* \sa				\ref group_devinfo_type
*/
    int EWALLET_API PAEW_GetDevInfo(void *const pPAEWContext, const size_t nDevIndex, const uint32_t nDevInfoType, PAEW_DevInfo *const pDevInfo);

    /**
* \brief			Derive trade address, _MUST_ be invoked before PAEW_GetTradeAddress() / PAEW_GetPublicKey() / PAEW_BTC_SetTX() / PAEW_BTC_GetSignResult() / PAEW_BTC_GetSignResult_DragonBall() and signature functions for other coins
* \param[in]		pPAEWContext	library context, shouldn't be NULL
* \param[in]		nDevIndex		index of device, valid range of value is [0, nDevCount-1]
* \param[in]		nCoinType		coin type, valid values are PAEW_COIN_TYPE_XXX (\ref group_coin_type)
* \param[in]		puiDerivePath	derive path, shouldn't be NULL, and first element must be 0, indicating m (from seed to master private key), shouldn't be NULL
* \param[in]		nDerivePathLen	count of derive path elements, not less than 1
* \return			#PAEW_RET_SUCCESS means success, and other value means failure (\ref group_retvalue)
*/
    int EWALLET_API PAEW_DeriveTradeAddress(void *const pPAEWContext, const size_t nDevIndex, const unsigned char nCoinType, const uint32_t *const puiDerivePath, const size_t nDerivePathLen);

    /**
* \brief			Get trade address, _MUST_ be invoked after PAEW_DeriveTradeAddress() is called
* \param[in]		pPAEWContext	library context, shouldn't be NULL
* \param[in]		nDevIndex		index of device, valid range of value is [0, nDevCount-1]
* \param[in]		nCoinType		coin type, valid values are PAEW_COIN_TYPE_XXX (\ref group_coin_type)
* \param[in]		nShowOnScreen	whether coin address showed on device screen, 0 means not shown, 1 means show address on screen
* \param[out]		pbTradeAddress		trade address encoded according to \p nCoinType
* \param[in,out]	pnTradeAddressLen	contains size of \p pbTradeAddress when input, and contains actual length of address when output
* \return			#PAEW_RET_SUCCESS means success, and other value means failure (\ref group_retvalue)
* \sa				PAEW_DeriveTradeAddress()
*/
    int EWALLET_API PAEW_GetTradeAddress(void *const pPAEWContext, const size_t nDevIndex, const unsigned char nCoinType, const unsigned char nShowOnScreen, unsigned char *const pbTradeAddress, size_t *const pnTradeAddressLen);

    /**
* \brief			BTC signature, _MUST_ be invoked after PAEW_DeriveTradeAddress() is called
*
* This function may be blocked and wait user to check all the transaction information legal and press button
* \param[in]		pPAEWContext	library context, shouldn't be NULL
* \param[in]		nDevIndex		index of device, valid range of value is [0, nDevCount-1]
* \param[in]		nUTXOCount		count of UTXOs, must equal to input number of transaction to be singed
* \param[in]		ppbUTXO			each of which contains one UTXO data
* \param[in]		pnUTXOLen		each of which contains length of UTXO data corresponding to the same position of ppbUTXO
* \param[in]		pbCurrentTX		transaction data to be signed
* \param[in]		nCurrentTXLen	length of transaction data to be signed
* \param[out]		ppbTXSig		contains DER encoded signature data, each of which corresponds to one input of transaction data, and element count is the same to input count if shouldn't be NULL, signature structure: DERLen(1 byte) + DER + 01 + PublicKeyLen(1 byte) + PublicKey
* \param[in,out]	pnTXSigLen		contains size of buffer corresponding to the same position of ppbTXSig when input, and contains actual lengths of signature data when output
* \return			#PAEW_RET_SUCCESS means success, and other value means failure (\ref group_retvalue)
* \sa				PAEW_DeriveTradeAddress()
*/
    int EWALLET_API PAEW_BTC_TXSign(void *const pPAEWContext, const size_t nDevIndex, const size_t nUTXOCount, const unsigned char *const *const ppbUTXO, const size_t *const pnUTXOLen, const unsigned char *const pbCurrentTX, const size_t nCurrentTXLen, unsigned char *const *const ppbTXSig, size_t *const pnTXSigLen);

    /**
* \brief			ETH signature, _MUST_ be invoked after PAEW_DeriveTradeAddress() is called
*
* This function may be blocked and wait user to check all the transaction information legal and press button
* \param[in]		pPAEWContext	library context, shouldn't be NULL
* \param[in]		nDevIndex		index of device, valid range of value is [0, nDevCount-1]
* \param[in]		pbCurrentTX		transaction data to be signed
* \param[in]		nCurrentTXLen	length of transaction data to be signed
* \param[out]		pbTXSig			contains signature data, shouldn't be NULL, signature structure: R(32 byte) + S(32byte) + V(1 byte)
* \param[in,out]	pnTXSigLen		contains size of \p pbTXSig when input, and contains actual length of signature data when output
* \return			#PAEW_RET_SUCCESS means success, and other value means failure (\ref group_retvalue)
* \sa				PAEW_DeriveTradeAddress()
*/
    int EWALLET_API PAEW_ETH_TXSign(void *const pPAEWContext, const size_t nDevIndex, const unsigned char *const pbCurrentTX, const size_t nCurrentTXLen, unsigned char *const pbTXSig, size_t *const pnTXSigLen);

    /**
* \brief			EOS signature, _MUST_ be invoked after PAEW_DeriveTradeAddress() is called
*
* This function may be blocked and wait user to check all the transaction information legal and press button
* \param[in]		pPAEWContext	library context, shouldn't be NULL
* \param[in]		nDevIndex		index of device, valid range of value is [0, nDevCount-1]
* \param[in]		pbCurrentTX		transaction data to be signed
* \param[in]		nCurrentTXLen	length of transaction data to be signed
* \param[out]		pbTXSig			contains signature data, shouldn't be NULL, signature data is a string which already encoded by EOS encoder
* \param[in,out]	pnTXSigLen		contains size of \p pbTXSig when input, and contains actual length of signature data when output
* \return			#PAEW_RET_SUCCESS means success, and other value means failure (\ref group_retvalue)
* \sa				PAEW_DeriveTradeAddress()
*/
    int EWALLET_API PAEW_EOS_TXSign(void *const pPAEWContext, const size_t nDevIndex, const unsigned char *const pbCurrentTX, const size_t nCurrentTXLen, unsigned char *const pbTXSig, size_t *const pnTXSigLen);

    /**
* \brief			Change PIN
* This function may be blocked and wait user to input PIN on device
* \param[in]		pPAEWContext	library context, shouldn't be NULL
* \param[in]		nDevIndex		index of device, valid range of value is [0, nDevCount-1]
* \return			#PAEW_RET_SUCCESS means success, and other value means failure (\ref group_retvalue)
*/
    int EWALLET_API PAEW_ChangePIN(void *const pPAEWContext, const size_t nDevIndex);

    /**
* \brief			EOS transaction string (Json) serialization (implemented by software)
* \param[in]		szTransactionString	transaction string in json format, shouldn't be NULL
* \param[out]		pbTransactionData	contains binary data of transaction, shouldn't be NULL
* \param[in,out]	pnTransactionLen	contains size of \p pbTransactionData when input, and contains actual length of transaction data when output
* \return			#PAEW_RET_SUCCESS means success, and other value means failure (\ref group_retvalue)
*/
    int EWALLET_API PAEW_EOS_TX_Serialize(const char *const szTransactionString, unsigned char *const pbTransactionData, size_t *pnTransactionLen);

    /**
* \brief			EOS transaction string (Json) serialization - specific part (implemented by software)
* \param[in]		nPartIndex			EOS transaction part id, which value is one of the PAEW_SIG_EOS_TX_XXX (\ref group_sig_constant)
* \param[in]		szTransactionString	transaction string in json format, shouldn't be NULL
* \param[out]		pbTransactionData	contains binary data of transaction, shouldn't be NULL
* \param[in,out]	pnTransactionLen	contains size of \p pbTransactionData when input, and contains actual length of transaction data when output
* \return			#PAEW_RET_SUCCESS means success, and other value means failure (\ref group_retvalue)
*/
    int EWALLET_API PAEW_EOS_TX_Part_Serialize(const unsigned int nPartIndex, const char *const szTransactionString, unsigned char *const pbTransactionData, size_t *pnTransactionLen);

    ///@}

#ifdef __cplusplus
};
#endif
#endif //_PA_EWALLET_H_
