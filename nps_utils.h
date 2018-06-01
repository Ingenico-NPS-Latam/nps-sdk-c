#ifndef npsUtils_H
#define npsUtils_H
#include "npsSdk.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_SANITIZE_ITEM_KEY_LEN 100

typedef struct  {
    char *key;
    int max_size;
} sanitizeItemStruct;

typedef struct  {
    enum methods type;
    int noAddService;
} merchantNotAddServiceStruct;

static FILE  * LogFd      = NULL;
static char  MISC_LoggerFileName [ 512 ] ;
static enum log_level NpsLogLevel=INFO;
static int debug=0;
static int MAX_LEN_LINE=4096;

static merchantNotAddServiceStruct GetMerchDetNotAddServices[] = {
  { PAY_ONLINE_2P_TYPE, 0},
  { AUTHORIZE_2P_TYPE, 0},
  { REFUND_TYPE, 1},
  { CAPTURE_TYPE, 1},
  { BANK_PAYMENT_2P_TYPE, 0},
  { SPLIT_PAY_ONLINE_2P_TYPE, 0},  
  { SPLIT_AUTHORIZE_2P_TYPE, 0},
  { PAY_ONLINE_3P_TYPE, 0},
  { SPLIT_PAY_ONLINE_3P_TYPE, 0},
  { AUTHORIZE_3P_TYPE, 0},
  { SPLIT_AUTHORIZE_3P_TYPE, 0},  
  { BANK_PAYMENT_3P_TYPE, 0},
  { CASH_PAYMENT_3P_TYPE, 0},
  { CREATE_PAYMENT_METHOD_TYPE, 1},
  { CREATE_PAYMENT_METHOD_TOKEN_TYPE, 1},
  { RETRIEVE_PAYMENT_METHOD_TOKEN_TYPE, 1},
  { CREATE_PAYMENT_METHOD_FROM_PAYMENT_TYPE, 1},
  { RETRIEVE_PAYMENT_METHOD_TYPE, 1},
  { UPDATE_PAYMENT_METHOD_TYPE, 1},
  { DELETE_PAYMENT_METHOD_TYPE, 1},
  { RECACHE_PAYMENT_METHOD_TOKEN_TYPE, 1},
  { CREATE_CUSTOMER_TYPE, 1},
  { RETRIEVE_CUSTOMER_TYPE, 1},
  { UPDATE_CUSTOMER_TYPE, 1},
  { DELETE_CUSTOMER_TYPE, 1},
  { SIMPLE_QUERY_TX_TYPE, 1},
  { QUERY_CARD_NUMBER_TYPE, 1},
  { QUERY_CARD_DETAILS_TYPE, 1},
  { QUERY_TXS_TYPE, 1},
  { GET_IIN_DETAILS_TYPE, 1},
  { CHANGE_SECRET_KEY_TYPE, 1},
  { FRAUD_SCREENING_TYPE, 0},
  { CREATE_CLIENT_SESSION_TYPE, 1},
  { GET_INSTALLMENTS_OPTIONS_TYPE, 1}, 
  { NOTIFY_FRAUD_SCREENING_REVIEW_TYPE, 1},
};

static sanitizeItemStruct sanitizeTable[]={ { "psp_Person.FirstName", 128 },
                                { "psp_Person.LastName", 64 },
                                { "psp_Person.MiddleName", 64 },
                                { "psp_Person.PhoneNumber1", 32 },
                                { "psp_Person.PhoneNumber2", 32 },
                                { "psp_Person.Gender", 1 },
                                { "psp_Person.Nationality", 3 },
                                { "psp_Person.IDNumber", 40 },
                                { "psp_Person.IDType", 5 },
                                { "psp_Address.Street", 128 },
                                { "psp_Address.HouseNumber", 32 },
                                { "psp_Address.AdditionalInfo", 128 },
                                { "psp_Address.City", 40 },
                                { "psp_Address.StateProvince", 40 },
                                { "psp_Address.Country", 3 },
                                { "psp_Address.ZipCode", 10 },
                                { "psp_OrderItem.Description", 127 },
                                { "psp_OrderItem.Type", 20 },
                                { "psp_OrderItem.SkuCode", 48 },
                                { "psp_OrderItem.ManufacturerPartNumber", 30 },
                                { "psp_OrderItem.Risk", 1 },
                                { "psp_Leg.DepartureAirport", 3 },
                                { "psp_Leg.ArrivalAirport", 3 },
                                { "psp_Leg.CarrierCode", 2 },
                                { "psp_Leg.FlightNumber", 5 },
                                { "psp_Leg.FareBasisCode", 15 },
                                { "psp_Leg.FareClassCode", 3 },
                                { "psp_Leg.BaseFareCurrency", 3 },
                                { "psp_Passenger.FirstName", 50 },
                                { "psp_Passenger.LastName", 30 },
                                { "psp_Passenger.MiddleName", 30 },
                                { "psp_Passenger.Type", 1 },
                                { "psp_Passenger.Nationality", 3 },
                                { "psp_Passenger.IDNumber", 40 },
                                { "psp_Passenger.IDType", 10 },
                                { "psp_Passenger.IDCountry", 3 },
                                { "psp_Passenger.LoyaltyNumber", 20 },
                                { "psp_SellerDetails.IDNumber", 40 },
                                { "psp_SellerDetails.IDType", 10 },
                                { "psp_SellerDetails.Name", 128 },
                                { "psp_SellerDetails.Invoice", 32 },
                                { "psp_SellerDetails.PurchaseDescription", 32 },
                                { "psp_SellerDetails.MCC", 5 },
                                { "psp_SellerDetails.ChannelCode", 3 },
                                { "psp_SellerDetails.GeoCode", 5 },
                                { "psp_TaxesRequest.TypeId", 5 },
                                { "psp_MerchantAdditionalDetails.Type", 1 },
                                { "psp_MerchantAdditionalDetails.SdkInfo", 48 },
                                { "psp_MerchantAdditionalDetails.ShoppingCartInfo", 48 },
                                { "psp_MerchantAdditionalDetails.ShoppingCartPluginInfo", 48 },
                                { "psp_CustomerAdditionalDetails.IPAddress", 45 },
                                { "psp_CustomerAdditionalDetails.AccountID", 128 },
                                { "psp_CustomerAdditionalDetails.DeviceFingerPrint", 4000 },
                                { "psp_CustomerAdditionalDetails.BrowserLanguage", 2 },
                                { "psp_CustomerAdditionalDetails.HttpUserAgent", 255 },
                                { "psp_BillingDetails.Invoice", 32 },
                                { "psp_BillingDetails.InvoiceCurrency", 3 },
                                { "psp_ShippingDetails.TrackingNumber", 24 },
                                { "psp_ShippingDetails.Method", 3 },
                                { "psp_ShippingDetails.Carrier", 3 },
                                { "psp_ShippingDetails.GiftMessage", 200 },
                                { "psp_AirlineDetails.TicketNumber", 14 },
                                { "psp_AirlineDetails.PNR", 10 },
                                { "psp_VaultReference.PaymentMethodToken", 64 },
                                { "psp_VaultReference.PaymentMethodId", 64 },
                                { "psp_VaultReference.CustomerId", 64 },
                                0};

int setSecureHash(int type, char *apiKey, char *pRequest);
int AddExtraInf(int type, char *pRequest);
void sanitize(int type,char *pRequest);
void showRequest(int type,char *pRequest);
void showResponse(int type,char *pResponse);
void LogInit( enum log_level LogLevel, char * LogFileName , FILE  * logFd);
void LogClose ( void );
void Log( enum log_level LogLevel,  const char *Format, ... );

#ifdef __cplusplus
}
#endif

#endif
