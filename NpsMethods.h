#ifndef NpsMethods_H
#define NpsMethods_H
#include "NpsMethods.h"

#include "NpsStructures.h"
#include "ifdefs.h"

#ifdef __cplusplus
extern "C" {
#endif

static char *npsEnvDesc[]=
{
  "",
  "PRODUCTION",
  "SANDBOX",
  "STAGING"
};

static enum log_level {
  ERROR=1,
  INFO=3,
  DEBUG=7
};

static char NpsErrDesc[200];
static int NpsConnTimeout=10;
static int NpsExecTimeout=60;
static int NpsEnvField=3;
static char pref_env[3];
static const ERR_OFFSET=-1;
static int NpsLogLevel=3;
static int debug=0;


#define SDK_ENV_COUNT                       4
#define ARR_OFFSET_COUNT                    4
#define SDK_VERSION                         "1.1"
#define SDK_NAME                            "CLANG SDK"
#define PAY_ONLINE_2P                       "PayOnLine_2p"
#define AUTHORIZE_2P                        "Authorize_2p"
#define QUERY_TXS                           "QueryTxs"
#define SIMPLE_QUERY_TX                     "SimpleQueryTx"
#define REFUND                              "Refund"
#define CAPTURE                             "Capture"
#define AUTHORIZE_3P                        "Authorize_3p"
#define BANK_PAYMENT_3P                     "BankPayment_3p"
#define CASH_PAYMENT_3P                     "CashPayment_3p"
#define CHANGE_SECRET_KEY                   "ChangeSecretKey"
#define FRAUD_SCREENING                     "FraudScreening"
#define NOTIFY_FRAUD_SCREENING_REVIEW       "NotifyFraudScreeningReview"
#define PAY_ONLINE_3P                       "PayOnLine_3p"
#define SPLIT_AUTHORIZE_3P                  "SplitAuthorize_3p"
#define SPLIT_PAY_ONLINE_3P                 "SplitPayOnLine_3p"
#define BANK_PAYMENT_2P                     "BankPayment_2p"
#define SPLIT_PAY_ONLINE_2P                 "SplitPayOnLine_2p"
#define SPLIT_AUTHORIZE_2P                  "SplitAuthorize_2p"
#define QUERY_CARD_NUMBER                   "QueryCardNumber"
#define QUERY_CARD_DETAILS                  "QueryCardDetails"
#define GET_IIN_DETAILS                     "GetIINDetails"
#define WSDL_FOLDER                         "/NpsSDK/wsdl/"
#define STAGING_WSDL_FILE                   "staging.wsdl"
#define PRODUCTION_WSDL_FILE                "production.wsdl"
#define SANDBOX_WSDL_FILE                   "sandbox.wsdl"
#define DEVELOPMENT_WSDL_FILE               "development.wsdl"
#define CREATE_PAYMENT_METHOD               "CreatePaymentMethod"
#define CREATE_PAYMENT_METHOD_FROM_PAYMENT  "CreatePaymentMethodFromPayment"
#define RETRIEVE_PAYMENT_METHOD             "RetrievePaymentMethod"
#define UPDATE_PAYMENT_METHOD               "UpdatePaymentMethod"
#define DELETE_PAYMENT_METHOD               "DeletePaymentMethod"
#define CREATE_CUSTOMER                     "CreateCustomer"
#define RETRIEVE_CUSTOMER                   "RetrieveCustomer"
#define UPDATE_CUSTOMER                     "UpdateCustomer"
#define DELETE_CUSTOMER                     "DeleteCustomer"
#define RECACHE_PAYMENT_METHOD_TOKEN        "RecachePaymentMethodToken"
#define CREATE_PAYMENT_METHOD_TOKEN         "CreatePaymentMethodToken"
#define RETRIEVE_PAYMENT_METHOD_TOKEN       "RetrievePaymentMethodToken"
#define CREATE_CLIENT_SESSION               "CreateClientSession"
#define GET_INSTALLMENTS_OPTIONS            "GetInstallmentsOptions"

#define GET_SOAP_ACTION(x) (x == PAY_ONLINE_2P_TYPE ? PAY_ONLINE_2P : \
          (x == AUTHORIZE_2P_TYPE ? AUTHORIZE_2P : \
          (x == QUERY_TXS_TYPE ? QUERY_TXS : \
          (x == SIMPLE_QUERY_TX_TYPE ? SIMPLE_QUERY_TX : \
          (x == REFUND_TYPE ? REFUND : \
          (x == CAPTURE_TYPE ? CAPTURE : \
          (x == AUTHORIZE_3P_TYPE ? AUTHORIZE_3P : \
          (x == BANK_PAYMENT_3P_TYPE ? BANK_PAYMENT_3P : \
          (x == CASH_PAYMENT_3P_TYPE ? CASH_PAYMENT_3P : \
          (x == CHANGE_SECRET_KEY_TYPE ? CHANGE_SECRET_KEY : \
          (x == FRAUD_SCREENING_TYPE ? FRAUD_SCREENING : \
          (x == NOTIFY_FRAUD_SCREENING_REVIEW_TYPE ? NOTIFY_FRAUD_SCREENING_REVIEW : \
          (x == PAY_ONLINE_3P_TYPE ? PAY_ONLINE_3P : \
          (x == SPLIT_AUTHORIZE_3P_TYPE ? SPLIT_AUTHORIZE_3P : \
          (x == SPLIT_PAY_ONLINE_3P_TYPE ? SPLIT_PAY_ONLINE_3P : \
          (x == BANK_PAYMENT_2P_TYPE ? BANK_PAYMENT_2P : \
          (x == SPLIT_PAY_ONLINE_2P_TYPE ? SPLIT_PAY_ONLINE_2P : \
          (x == SPLIT_AUTHORIZE_2P_TYPE ? SPLIT_AUTHORIZE_2P : \
          (x == QUERY_CARD_NUMBER_TYPE ? QUERY_CARD_NUMBER : \
          (x == QUERY_CARD_DETAILS_TYPE ? QUERY_CARD_DETAILS : \
          (x == GET_IIN_DETAILS_TYPE ? GET_IIN_DETAILS : \
          (x == CREATE_PAYMENT_METHOD_TYPE ? CREATE_PAYMENT_METHOD : \
          (x == CREATE_PAYMENT_METHOD_FROM_PAYMENT_TYPE ? CREATE_PAYMENT_METHOD_FROM_PAYMENT : \
          (x == RETRIEVE_PAYMENT_METHOD_TYPE ? RETRIEVE_PAYMENT_METHOD : \
          (x == UPDATE_PAYMENT_METHOD_TYPE ? UPDATE_PAYMENT_METHOD : \
          (x == DELETE_PAYMENT_METHOD_TYPE ? DELETE_PAYMENT_METHOD : \
          (x == CREATE_CUSTOMER_TYPE ? CREATE_CUSTOMER : \
          (x == RETRIEVE_CUSTOMER_TYPE ? RETRIEVE_CUSTOMER : \
          (x == UPDATE_CUSTOMER_TYPE ? UPDATE_CUSTOMER : \
          (x == DELETE_CUSTOMER_TYPE ? DELETE_CUSTOMER : \
          (x == RECACHE_PAYMENT_METHOD_TOKEN_TYPE ? RECACHE_PAYMENT_METHOD_TOKEN : \
          (x == CREATE_PAYMENT_METHOD_TOKEN_TYPE ? CREATE_PAYMENT_METHOD_TOKEN : \
          (x == RETRIEVE_PAYMENT_METHOD_TOKEN_TYPE ? RETRIEVE_PAYMENT_METHOD_TOKEN : \
          (x == CREATE_CLIENT_SESSION_TYPE ? CREATE_CLIENT_SESSION : \
          (x == GET_INSTALLMENTS_OPTIONS_TYPE ? GET_INSTALLMENTS_OPTIONS : NULL )))))))))))))))))))))))))))))))))))


#define PSP_VERSION_FIELD                        psp_Version
#define PSP_MERCHANTID_FIELD                     psp_MerchantId
#define PSP_TXSOURCE_FIELD                       psp_TxSource
#define PSP_MERCHTXREF_FIELD                     psp_MerchTxRef
#define PSP_MERCHORDERID_FIELD                   psp_MerchOrderId
#define PSP_MERCHADDITIONALREF_FIELD             psp_MerchAdditionalRef
#define PSP_AMOUNT_FIELD                         psp_Amount
#define PSP_NUMPAYMENTS_FIELD                    psp_NumPayments
#define PSP_RECURRENT_FIELD                      psp_Recurrent
#define PSP_CURRENCY_FIELD                       psp_Currency
#define PSP_COUNTRY_FIELD                        psp_Country
#define PSP_PRODUCT_FIELD                        psp_Product
#define PSP_CARDNUMBER_FIELD                     psp_CardNumber
#define PSP_CARDEXPDATE_FIELD                    psp_CardExpDate
#define PSP_CARDSECURITYCODE_FIELD               psp_CardSecurityCode
#define PSP_CARDHOLDERNAME_FIELD                 psp_CardHolderName
#define PSP_CUSTOMERMAIL_FIELD                   psp_CustomerMail
#define PSP_CUSTOMERID_FIELD                     psp_CustomerId
#define PSP_MERCHANTMAIL_FIELD                   psp_MerchantMail
#define PSP_PURCHASEDESCRIPTION_FIELD            psp_PurchaseDescription
#define PSP_SOFTDESCRIPTOR_FIELD                 psp_SoftDescriptor
#define PSP_FORCEPROCESSINGMETHOD_FIELD          psp_ForceProcessingMethod
#define PSP_POSDATETIME_FIELD                    psp_PosDateTime
#define PSP_PLAN_FIELD                           psp_Plan
#define PSP_FIRSTPAYMENTDEFERRAL_FIELD           psp_FirstPaymentDeferral
#define PSP_PROMOTIONCODE_FIELD                  psp_PromotionCode
#define PSP_PRESETCARDIIN_FIELD                  psp_PresetCardIIN
#define PSP_3DSECURE_XID_FIELD                   psp_3dSecure_XID
#define PSP_3DSECURE_CAVV_FIELD                  psp_3dSecure_CAVV
#define PSP_3DSECURE_ECI_FIELD                   psp_3dSecure_ECI
#define PSP_3DSECURE_SECURED_FIELD               psp_3dSecure_Secured
#define PSP_VISAARG_DA_DOCTYPE_FIELD             psp_VisaArg_DA_DocType
#define PSP_VISAARG_DA_DOCNUM_FIELD              psp_VisaArg_DA_DocNum
#define PSP_VISAARG_DA_DOORNUM_FIELD             psp_VisaArg_DA_DoorNum
#define PSP_VISAARG_DA_BIRTHDAY_FIELD            psp_VisaArg_DA_BirthDay
#define PSP_VISAARG_DA_NAME_FIELD                psp_VisaArg_DA_Name
#define PSP_AMEXARG_AVS_ADDRESS_FIELD            psp_AmexArg_AVS_Address
#define PSP_AMEXARG_AVS_POSTCODE_FIELD           psp_AmexArg_AVS_PostCode
#define PSP_MASTERARG_AVS_BIRTHDAY_FIELD         psp_MasterArg_AVS_BirthDay
#define PSP_MASTERARG_AVS_ADDITIONALSQTTY_FIELD  psp_MasterArg_AVS_AdditionalsQtty
#define PSP_MASTERARG_AVS_POSTALCODE_FIELD       psp_MasterArg_AVS_PostalCode
#define PSP_MASTERARG_AVS_BRANCHENTITY_FIELD     psp_MasterArg_AVS_BranchEntity
#define PSP_SECUREHASH_FIELD                     psp_SecureHash

//AmountAdditionalDetailsRequestStruct fields
#define TIP_FIELD                                Tip
#define DISCOUNT_FIELD                           Discount

#define TIP_FIELD_DESC                           "Tip"
#define DISCOUNT_FIELD_DESC                      "Discount"

//AddressStruct fields
#define STREET_FIELD                             Street
#define HOUSENUMBER_FIELD                        HouseNumber
#define ADDITIONALINFO_FIELD                     AdditionalInfo
#define CITY_FIELD                               City
#define STATEPROVINCE_FIELD                      StateProvince
#define COUNTRY_FIELD                            Country
#define ZIPCODE_FIELD                            ZipCode

#define STREET_FIELD_DESC                        "Street"
#define HOUSENUMBER_FIELD_DESC                   "HouseNumber"
#define ADDITIONALINFO_FIELD_DESC                "AdditionalInfo"
#define CITY_FIELD_DESC                          "City"
#define STATEPROVINCE_FIELD_DESC                 "StateProvince"
#define COUNTRY_FIELD_DESC                       "Country"
#define ZIPCODE_FIELD_DESC                       "ZipCode"

//SellerDetailsStruct fields
#define IDNUMBER_FIELD                           IDNumber
#define IDTYPE_FIELD                             IDType
#define NAME_FIELD                               Name
#define INVOICE_FIELD                            Invoice
#define PURCHASEDESCRIPTION_FIELD                PurchaseDescription
#define MCC_FIELD                                MCC
#define CHANNELCODE_FIELD                        ChannelCode
#define GEOCODE_FIELD                            GeoCode

#define IDNUMBER_FIELD_DESC                      "IDNumber"
#define IDTYPE_FIELD_DESC                        "IDType"
#define NAME_FIELD_DESC                          "Name"
#define INVOICE_FIELD_DESC                       "Invoice"
#define PURCHASEDESCRIPTION_FIELD_DESC           "PurchaseDescription"
#define MCC_FIELD_DESC                           "MCC"
#define CHANNELCODE_FIELD_DESC                   "ChannelCode"
#define GEOCODE_FIELD_DESC                       "GeoCode"

//MerchantAdditionalDetailsStruct fields
#define TYPE_FIELD                               Type
#define SELLERDETAILS_FIELD                      SellerDetails
#define SDKINFO_FIELD                            SdkInfo
#define SHOPPINGCARTINFO_FIELD                   ShoppingCartInfo
#define SHOPPINGCARTPLUGININFO_FIELD             ShoppingCartPluginInfo

#define TYPE_FIELD_DESC                          "Type"
#define SELLERDETAILS_FIELD_DESC                 "SellerDetails"
#define SDKINFO_FIELD_DESC                       "SdkInfo"
#define SHOPPINGCARTINFO_FIELD_DESC              "ShoppingCartInfo"
#define SHOPPINGCARTPLUGININFO_FIELD_DESC        "ShoppingCartPluginInfo"

//CustomerAdditionalDetailsStruct fields
#define EMAILADDRESS_FIELD                       EmailAddress
#define ALTERNATIVEEMAILADDRESS_FIELD            AlternativeEmailAddress
#define IPADDRESS_FIELD                          IPAddress
#define ACCOUNTID_FIELD                          AccountID
#define ACCOUNTCREATEDAT_FIELD                   AccountCreatedAt
#define ACCOUNTPREVIOUSACTIVITY_FIELD            AccountPreviousActivity
#define ACCOUNTHASCREDENTIALS_FIELD              AccountHasCredentials
#define DEVICETYPE_FIELD                         DeviceType
#define DEVICEFINGERPRINT_FIELD                  DeviceFingerPrint
#define BROWSERLANGUAGE_FIELD                    BrowserLanguage
#define HTTPUSERAGENT_FIELD                      HttpUserAgent

#define EMAILADDRESS_FIELD_DESC                  "EmailAddress"
#define ALTERNATIVEEMAILADDRESS_FIELD_DESC       "AlternativeEmailAddress"
#define IPADDRESS_FIELD_DESC                     "IPAddress"
#define ACCOUNTID_FIELD_DESC                     "AccountID"
#define ACCOUNTCREATEDAT_FIELD_DESC              "AccountCreatedAt"
#define ACCOUNTPREVIOUSACTIVITY_FIELD_DESC       "AccountPreviousActivity"
#define ACCOUNTHASCREDENTIALS_FIELD_DESC         "AccountHasCredentials"
#define DEVICETYPE_FIELD_DESC                    "DeviceType"
#define DEVICEFINGERPRINT_FIELD_DESC             "DeviceFingerPrint"
#define BROWSERLANGUAGE_FIELD_DESC               "BrowserLanguage"
#define HTTPUSERAGENT_FIELD_DESC                 "HttpUserAgent"

//PersonStruct fields
#define FIRSTNAME_FIELD                          FirstName
#define LASTNAME_FIELD                           LastName
#define MIDDLENAME_FIELD                         MiddleName
#define PHONENUMBER1_FIELD                       PhoneNumber1
#define PHONENUMBER2_FIELD                       PhoneNumber2
#define GENDER_FIELD                             Gender
#define DATEOFBIRTH_FIELD                        DateOfBirth
#define NATIONALITY_FIELD                        Nationality

#define FIRSTNAME_FIELD_DESC                     "FirstName"
#define LASTNAME_FIELD_DESC                      "LastName"
#define MIDDLENAME_FIELD_DESC                    "MiddleName"
#define PHONENUMBER1_FIELD_DESC                  "honeNumber1"
#define PHONENUMBER2_FIELD_DESC                  "PhoneNumber2"
#define GENDER_FIELD_DESC                        "Gender"
#define DATEOFBIRTH_FIELD_DESC                   "DateOfBirth"
#define NATIONALITY_FIELD_DESC                   "Nationality"

//BillingDetailsStruct fields
#define INVOICEDATE_FIELD                        InvoiceDate
#define INVOICEAMOUNT_FIELD                      InvoiceAmount
#define INVOICECURRENCY_FIELD                    InvoiceCurrency

#define INVOICEDATE_FIELD_DESC                   "InvoiceDate"
#define INVOICEAMOUNT_FIELD_DESC                 "InvoiceAmount"
#define INVOICECURRENCY_FIELD_DESC               "InvoiceCurrency"

//ShippingDetailsStruct fields
#define TRACKINGNUMBER_FIELD                     TrackingNumber
#define METHOD_FIELD                             Method
#define CARRIER_FIELD                            Carrier
#define DELIVERYDATE_FIELD                       DeliveryDate
#define FREIGHTAMOUNT_FIELD                      FreightAmount
#define GIFTMESSAGE_FIELD                        GiftMessage
#define GIFTWRAPPING_FIELD                       GiftWrapping
#define PRIMARYRECIPIENT_FIELD                   PrimaryRecipient
#define SECONDARYRECIPIENT_FIELD                 SecondaryRecipient

#define TRACKINGNUMBER_FIELD_DESC                "TrackingNumber"
#define METHOD_FIELD_DESC                        "Method"
#define CARRIER_FIELD_DESC                       "Carrier"
#define DELIVERYDATE_FIELD_DESC                  "DeliveryDate"
#define FREIGHTAMOUNT_FIELD_DESC                 "FreightAmount"
#define GIFTMESSAGE_FIELD_DESC                   "GiftMessage"
#define GIFTWRAPPING_FIELD_DESC                  "GiftWrapping"
#define PRIMARYRECIPIENT_FIELD_DESC              "PrimaryRecipient"
#define SECONDARYRECIPIENT_FIELD_DESC            "SecondaryRecipient"

//OrderItemStruct fields
#define QUANTITY_FIELD                           Quantity
#define UNITPRICE_FIELD                          UnitPrice
#define DESCRIPTION_FIELD                        Description
//#define TYPE_FIELD                               Type
#define SKUCODE_FIELD                            SkuCode
#define MANUFACTURERPARTNUMBER_FIELD             ManufacturerPartNumber
#define RISK_FIELD                               Risk

#define QUANTITY_FIELD_DESC                      "Quantity"
#define UNITPRICE_FIELD_DESC                     "UnitPrice"
#define DESCRIPTION_FIELD_DESC                   "Description"
//#define TYPE_FIELD_DESC                          "Type"
#define SKUCODE_FIELD_DESC                       "SkuCode"
#define MANUFACTURERPARTNUMBER_FIELD_DESC        "ManufacturerPartNumber"
#define RISK_FIELD_DESC                          "Risk"

//VaultReference2pStruct fields
#define PAYMENTMETHODTOKEN_FIELD                 PaymentMethodToken
#define PAYMENTMETHODID_FIELD                    PaymentMethodId
#define CUSTOMERID_FIELD                         CustomerId

#define PAYMENTMETHODTOKEN_FIELD_DESC            "PaymentMethodToken"
#define PAYMENTMETHODID_FIELD_DESC               "PaymentMethodId"
#define CUSTOMERID_FIELD_DESC                    "CustomerId"

#define RESULTCODE_FIELD                         ResultCode
#define RESULTDESCRIPTION_FIELD                  ResultDescription

#define RESULTCODE_FIELD_DESC                    "ResultCode"
#define RESULTDESCRIPTION_FIELD_DESC             "ResultDescription"

//TaxesRequestStruct fields
#define TYPEID_FIELD                             TypeId
#define AMOUNT_FIELD                             Amount
#define RATE_FIELD                               Rate
#define BASEAMOUNT_FIELD                         BaseAmount

#define TYPEID_FIELD_DESC                        "TypeId"
#define AMOUNT_FIELD_DESC                        "Amount"
#define RATE_FIELD_DESC                          "Rate"
#define BASEAMOUNT_FIELD_DESC                    "BaseAmount"

//TaxesResponseStruct fields
#define TYPEDESCRIPTION_FIELD                    TypeDescription
#define APPLIEDAMOUNT_FIELD                      AppliedAmount
#define REMARKS_FIELD                            Remarks
    

#define TYPEDESCRIPTION_FIELD_DESC               "TypeDescription"
#define APPLIEDAMOUNT_FIELD_DESC                 "AppliedAmount"
#define REMARKS_FIELD_DESC                       "Remarks"

//AirlineDetailsStruct
#define PNR_FIELD                                PNR
#define LEGS_FIELD                               Legs
#define PASSENGERS_FIELD                         Passengers
#define TICKET_FIELD                             Ticket

#define PNR_FIELD_DESC                           "PNR"
#define LEGS_FIELD_DESC                          "Legs"
#define PASSENGERS_FIELD_DESC                    "Passengers"
#define TICKET_FIELD_DESC                        "Ticket"

//LegStruct fields
#define DEPARTUREAIRPORT_FIELD                   DepartureAirport
#define DEPARTUREDATETIME_FIELD                  DepartureDatetime
#define DEPARTUREAIRPORTTIMEZONE_FIELD           DepartureAirportTimezone
#define ARRIVALAIRPORT_FIELD                     ArrivalAirport
#define CARRIERCODE_FIELD                        CarrierCode
#define FLIGHTNUMBER_FIELD                       FlightNumber
#define FAREBASISCODE_FIELD                      FareBasisCode
#define FARECLASSCODE_FIELD                      FareClassCode
#define BASEFARE_FIELD                           BaseFare
#define BASEFARECURRENCY_FIELD                   BaseFareCurrency

#define DEPARTUREAIRPORT_FIELD_DESC              "DepartureAirport"
#define DEPARTUREDATETIME_FIELD_DESC             "DepartureDatetime"
#define DEPARTUREAIRPORTTIMEZONE_FIELD_DESC      "DepartureAirportTimezone"
#define ARRIVALAIRPORT_FIELD_DESC                "ArrivalAirport"
#define CARRIERCODE_FIELD_DESC                   "CarrierCode"
#define FLIGHTNUMBER_FIELD_DESC                  "FlightNumber"
#define FAREBASISCODE_FIELD_DESC                 "FareBasisCode"
#define FARECLASSCODE_FIELD_DESC                 "FareClassCode"
#define BASEFARE_FIELD_DESC                      "BaseFare"
#define BASEFARECURRENCY_FIELD_DESC              "BaseFareCurrency"

#define IDCOUNTRY_FIELD                          IDCountry
#define LOYALTYNUMBER_FIELD                      LoyaltyNumber
#define LOYALTYTIER_FIELD                        LoyaltyTier

#define IDCOUNTRY_FIELD_DESC                     "IDCountry"
#define LOYALTYNUMBER_FIELD_DESC                 "LoyaltyNumber"
#define LOYALTYTIER_FIELD_DESC                   "LoyaltyTier"

//AirlineTicketStruct fields
#define TICKETNUMBER_FIELD                       TicketNumber
#define ETICKET_FIELD                            Eticket
#define RESTRICTED_FIELD                         Restricted
#define ISSUE_FIELD                              Issue
#define TOTALFAREAMOUNT_FIELD                    TotalFareAmount
#define TOTALTAXAMOUNT_FIELD                     TotalTaxAmount
#define TOTALFEEAMOUNT_FIELD                     TotalFeeAmount

#define TICKETNUMBER_FIELD_DESC                  "TicketNumber"
#define ETICKET_FIELD_DESC                       "Eticket"
#define RESTRICTED_FIELD_DESC                    "Restricted"
#define ISSUE_FIELD_DESC                         "Issue"
#define TOTALFAREAMOUNT_FIELD_DESC               "TotalFareAmount"
#define TOTALTAXAMOUNT_FIELD_DESC                "TotalTaxAmount"
#define TOTALFEEAMOUNT_FIELD_DESC                "TotalFeeAmount"

//AirlineTicketIssueStruct fields
#define CARRIERPREFIXCODE_FIELD                  CarrierPrefixCode
#define TRAVELAGENTCODE_FIELD                    TravelAgentCode
#define TRAVELAGENTNAME_FIELD                    TravelAgentName
#define DATE_FIELD                               Date
#define ADDRESS_FIELD                            Address

#define CARRIERPREFIXCODE_FIELD_DESC             "CarrierPrefixCode"
#define TRAVELAGENTCODE_FIELD_DESC               "TravelAgentCode"
#define TRAVELAGENTNAME_FIELD_DESC               "TravelAgentName"
#define DATE_FIELD_DESC                          "Date"
#define ADDRESS_FIELD_DESC                       "Address"

#define RESULTCODECARDSECURITYCODE_FIELD                   ResultCodeCardSecurityCode
#define RESULTCODEBILLINGADDRESS_FIELD                     ResultCodeBillingAddress
#define RESULTCODEBILLINGADDRESSZIPCODE_FIELD              ResultCodeBillingAddressZipCode
#define RESULTCODEBILLINGPERSONIDTYPE_FIELD                ResultCodeBillingPersonIDType
#define RESULTCODEBILLINGPERSONIDNUMBER_FIELD              ResultCodeBillingPersonIDNumber
#define RESULTCODEBILLINGPERSONDATEOFBIRTH_FIELD           ResultCodeBillingPersonDateOfBirth
#define RESULTCODEBILLINGPERSONNAME_FIELD                  ResultCodeBillingPersonName
#define RESULTCODEBILLINGPERSONPHONENUMBER1_FIELD          ResultCodeBillingPersonPhoneNumber1
#define RESULTCODECUSTOMEREMAILADDRESS_FIELD               ResultCodeCustomerEmailAddress

#define RESULTCODECARDSECURITYCODE_FIELD_DESC              "ResultCodeCardSecurityCode"
#define RESULTCODEBILLINGADDRESS_FIELD_DESC                "ResultCodeBillingAddress"
#define RESULTCODEBILLINGADDRESSZIPCODE_FIELD_DESC         "ResultCodeBillingAddressZipCode"
#define RESULTCODEBILLINGPERSONIDTYPE_FIELD_DESC           "ResultCodeBillingPersonIDType"
#define RESULTCODEBILLINGPERSONIDNUMBER_FIELD_DESC         "ResultCodeBillingPersonIDNumber"
#define RESULTCODEBILLINGPERSONDATEOFBIRTH_FIELD_DESC      "ResultCodeBillingPersonDateOfBirth"
#define RESULTCODEBILLINGPERSONNAME_FIELD_DESC             "ResultCodeBillingPersonName"
#define RESULTCODEBILLINGPERSONPHONENUMBER1_FIELD_DESC     "ResultCodeBillingPersonPhoneNumber1"
#define RESULTCODECUSTOMEREMAILADDRESS_FIELD_DESC          "ResultCodeCustomerEmailAddress"

#define PSP_RESPONSECOD_FIELD             psp_ResponseCod
#define PSP_RESPONSEMSG_FIELD             psp_ResponseMsg
#define PSP_RESPONSEEXTENDED_FIELD        psp_ResponseExtended
#define PSP_TRANSACTIONID_FIELD           psp_TransactionId
#define PSP_AUTHORIZATIONCODE_FIELD       psp_AuthorizationCode
#define PSP_BATCHNRO_FIELD                psp_BatchNro
#define PSP_TICKETNUMBER_FIELD            psp_TicketNumber
#define PSP_SEQUENCENUMBER_FIELD          psp_SequenceNumber
#define PSP_CLTRNID_FIELD                 psp_ClTrnId
#define PSP_CLEXTERNALMERCHANT_FIELD      psp_ClExternalMerchant
#define PSP_CLEXTERNALTERMINAL_FIELD      psp_ClExternalTerminal
#define PSP_CLRESPONSECOD_FIELD           psp_ClResponseCod
#define PSP_CLRESPONSEMSG_FIELD           psp_ClResponseMsg
#define PSP_CREATEDAT_FIELD               psp_CreatedAt
#define PSP_VISAARG_DA_RESULT_FIELD       psp_VisaArg_DA_Result
#define PSP_AMEXARG_AVS_RESULT_FIELD      psp_AmexArg_AVS_Result
#define PSP_MASTERARG_AVS_RESULT_FIELD    psp_MasterArg_AVS_Result
#define PSP_PAYMENTAMOUNT_FIELD           psp_PaymentAmount
#define PSP_TRANSACTIONID_ORIG_FIELD      psp_TransactionId_Orig
#define PSP_AMOUNTTOREFUND_FIELD          psp_AmountToRefund
#define PSP_USERID_FIELD                  psp_UserId
#define PSP_REFUNDEDAMOUNT_FIELD          psp_RefundedAmount
#define PSP_CAPTUREDAMOUNT_ORIG_FIELD     psp_CapturedAmount_Orig
#define PSP_AMOUNTTOCAPTURE_FIELD         psp_AmountToCapture
#define PSP_CAPTUREDAMOUNT_FIELD          psp_CapturedAmount
#define PSP_AUTHORIZEDAMOUNT_ORIG_FIELD   psp_AuthorizedAmount_Orig
#define PSP_SCREENDESCRIPTION_FIELD       psp_ScreenDescription
#define PSP_TICKETDESCRIPTION_FIELD       psp_TicketDescription
#define PSP_AMOUNT1_FIELD                 psp_Amount1
#define PSP_EXPDATE1_FIELD                psp_ExpDate1
#define PSP_AMOUNT2_FIELD                 psp_Amount2
#define PSP_EXPDATE2_FIELD                psp_ExpDate2
#define PSP_AMOUNT3_FIELD                 psp_Amount3
#define PSP_EXPDATE3_FIELD                psp_ExpDate3
#define PSP_MINAMOUNT_FIELD               psp_MinAmount
#define PSP_EXPTIME_FIELD                 psp_ExpTime
#define PSP_EXPMARK_FIELD                 psp_ExpMark
#define PSP_CUSTOMERBANKID_FIELD          psp_CustomerBankId
#define PSP_USEMULTIPLEPRODUCTS_FIELD     psp_UseMultipleProducts
#define PSP_RETURNURL_FIELD               psp_ReturnURL
#define PSP_FRMLANGUAGE_FIELD             psp_FrmLanguage
#define PSP_FRMBACKBUTTONURL_FIELD        psp_FrmBackButtonURL
#define PSP_FRMTIMEOUT_FIELD              psp_FrmTimeout
#define PSP_3DSECUREACTION_FIELD          psp_3dSecureAction
#define PSP_SESSION3P_FIELD               psp_Session3p
#define PSP_FRONTPSP_URL_FIELD            psp_FrontPSP_URL
#define PSP_BARCODE_FIELD                 psp_BarCode

#define PSP_VERSION_FIELD_DESC                        "psp_Version"
#define PSP_MERCHANTID_FIELD_DESC                     "psp_MerchantId"
#define PSP_TXSOURCE_FIELD_DESC                       "psp_TxSource"
#define PSP_MERCHTXREF_FIELD_DESC                     "psp_MerchTxRef"
#define PSP_MERCHORDERID_FIELD_DESC                   "psp_MerchOrderId"
#define PSP_MERCHADDITIONALREF_FIELD_DESC             "psp_MerchAdditionalRef"
#define PSP_AMOUNT_FIELD_DESC                         "psp_Amount"
#define PSP_NUMPAYMENTS_FIELD_DESC                    "psp_NumPayments"
#define PSP_RECURRENT_FIELD_DESC                      "psp_Recurrent"
#define PSP_CURRENCY_FIELD_DESC                       "psp_Currency"
#define PSP_COUNTRY_FIELD_DESC                        "psp_Country"
#define PSP_PRODUCT_FIELD_DESC                        "psp_Product"
#define PSP_CARDNUMBER_FIELD_DESC                     "psp_CardNumber"
#define PSP_CARDEXPDATE_FIELD_DESC                    "psp_CardExpDate"
#define PSP_CARDSECURITYCODE_FIELD_DESC               "psp_CardSecurityCode"
#define PSP_CARDHOLDERNAME_FIELD_DESC                 "psp_CardHolderName"
#define PSP_CUSTOMERMAIL_FIELD_DESC                   "psp_CustomerMail"
#define PSP_CUSTOMERID_FIELD_DESC                     "psp_CustomerId"
#define PSP_MERCHANTMAIL_FIELD_DESC                   "psp_MerchantMail"
#define PSP_PURCHASEDESCRIPTION_FIELD_DESC            "psp_PurchaseDescription"
#define PSP_SOFTDESCRIPTOR_FIELD_DESC                 "psp_SoftDescriptor"
#define PSP_FORCEPROCESSINGMETHOD_FIELD_DESC          "psp_ForceProcessingMethod"
#define PSP_POSDATETIME_FIELD_DESC                    "psp_PosDateTime"
#define PSP_PLAN_FIELD_DESC                           "psp_Plan"
#define PSP_FIRSTPAYMENTDEFERRAL_FIELD_DESC           "psp_FirstPaymentDeferral"
#define PSP_PROMOTIONCODE_FIELD_DESC                  "psp_PromotionCode"
#define PSP_PRESETCARDIIN_FIELD_DESC                  "psp_PresetCardIIN"
#define PSP_3DSECURE_XID_FIELD_DESC                   "psp_3dSecure_XID"
#define PSP_3DSECURE_CAVV_FIELD_DESC                  "psp_3dSecure_CAVV"
#define PSP_3DSECURE_ECI_FIELD_DESC                   "psp_3dSecure_ECI"
#define PSP_3DSECURE_SECURED_FIELD_DESC               "psp_3dSecure_Secured"
#define PSP_VISAARG_DA_DOCTYPE_FIELD_DESC             "psp_VisaArg_DA_DocType"
#define PSP_VISAARG_DA_DOCNUM_FIELD_DESC              "psp_VisaArg_DA_DocNum"
#define PSP_VISAARG_DA_DOORNUM_FIELD_DESC             "psp_VisaArg_DA_DoorNum"
#define PSP_VISAARG_DA_BIRTHDAY_FIELD_DESC            "psp_VisaArg_DA_BirthDay"
#define PSP_VISAARG_DA_NAME_FIELD_DESC                "psp_VisaArg_DA_Name"
#define PSP_AMEXARG_AVS_ADDRESS_FIELD_DESC            "psp_AmexArg_AVS_Address"
#define PSP_AMEXARG_AVS_POSTCODE_FIELD_DESC           "psp_AmexArg_AVS_PostCode"
#define PSP_MASTERARG_AVS_BIRTHDAY_FIELD_DESC         "psp_MasterArg_AVS_BirthDay"
#define PSP_MASTERARG_AVS_ADDITIONALSQTTY_FIELD_DESC  "psp_MasterArg_AVS_AdditionalsQtty"
#define PSP_MASTERARG_AVS_POSTALCODE_FIELD_DESC       "psp_MasterArg_AVS_PostalCode"
#define PSP_MASTERARG_AVS_BRANCHENTITY_FIELD_DESC     "psp_MasterArg_AVS_BranchEntity"
#define PSP_SECUREHASH_FIELD_DESC                     "psp_SecureHash"

#define PSP_RESPONSECOD_FIELD_DESC                    "psp_ResponseCod"
#define PSP_RESPONSEMSG_FIELD_DESC                    "psp_ResponseMsg"
#define PSP_RESPONSEEXTENDED_FIELD_DESC               "psp_ResponseExtended"
#define PSP_TRANSACTIONID_FIELD_DESC                  "psp_TransactionId"
#define PSP_AUTHORIZATIONCODE_FIELD_DESC              "psp_AuthorizationCode"
#define PSP_BATCHNRO_FIELD_DESC                       "psp_BatchNro"
#define PSP_TICKETNUMBER_FIELD_DESC                   "psp_TicketNumber"
#define PSP_SEQUENCENUMBER_FIELD_DESC                 "psp_SequenceNumber"
#define PSP_CLTRNID_FIELD_DESC                        "psp_ClTrnId"
#define PSP_CLEXTERNALMERCHANT_FIELD_DESC             "psp_ClExternalMerchant"
#define PSP_CLEXTERNALTERMINAL_FIELD_DESC             "psp_ClExternalTerminal"
#define PSP_CLRESPONSECOD_FIELD_DESC                  "psp_ClResponseCod"
#define PSP_CLRESPONSEMSG_FIELD_DESC                  "psp_ClResponseMsg"
#define PSP_CREATEDAT_FIELD_DESC                      "psp_CreatedAt"
#define PSP_VISAARG_DA_RESULT_FIELD_DESC              "psp_VisaArg_DA_Result"
#define PSP_AMEXARG_AVS_RESULT_FIELD_DESC             "psp_AmexArg_AVS_Result"
#define PSP_MASTERARG_AVS_RESULT_FIELD_DESC           "psp_MasterArg_AVS_Result"
#define PSP_PAYMENTAMOUNT_FIELD_DESC                  "psp_PaymentAmount"
#define PSP_TRANSACTIONID_ORIG_FIELD_DESC             "psp_TransactionId_Orig"
#define PSP_AMOUNTTOREFUND_FIELD_DESC                 "psp_AmountToRefund"
#define PSP_USERID_FIELD_DESC                         "psp_UserId"
#define PSP_REFUNDEDAMOUNT_FIELD_DESC                 "psp_RefundedAmount"
#define PSP_CAPTUREDAMOUNT_ORIG_FIELD_DESC            "psp_CapturedAmount_Orig"
#define PSP_AMOUNTTOCAPTURE_FIELD_DESC                "psp_AmountToCapture"
#define PSP_CAPTUREDAMOUNT_FIELD_DESC                 "psp_CapturedAmount"
#define PSP_AUTHORIZEDAMOUNT_ORIG_FIELD_DESC          "psp_AuthorizedAmount_Orig"
#define PSP_SCREENDESCRIPTION_FIELD_DESC              "psp_ScreenDescription"
#define PSP_TICKETDESCRIPTION_FIELD_DESC              "psp_TicketDescription"
#define PSP_AMOUNT1_FIELD_DESC                        "psp_Amount1"
#define PSP_EXPDATE1_FIELD_DESC                       "psp_ExpDate1"
#define PSP_AMOUNT2_FIELD_DESC                        "psp_Amount2"
#define PSP_EXPDATE2_FIELD_DESC                       "psp_ExpDate2"
#define PSP_AMOUNT3_FIELD_DESC                        "psp_Amount3"
#define PSP_EXPDATE3_FIELD_DESC                       "psp_ExpDate3"
#define PSP_MINAMOUNT_FIELD_DESC                      "psp_MinAmount"
#define PSP_EXPTIME_FIELD_DESC                        "psp_ExpTime"
#define PSP_EXPMARK_FIELD_DESC                        "psp_ExpMark"
#define PSP_CUSTOMERBANKID_FIELD_DESC                 "psp_CustomerBankId"
#define PSP_USEMULTIPLEPRODUCTS_FIELD_DESC            "psp_UseMultipleProducts"
#define PSP_RETURNURL_FIELD_DESC                      "psp_ReturnURL"
#define PSP_FRMLANGUAGE_FIELD_DESC                    "psp_FrmLanguage"
#define PSP_FRMBACKBUTTONURL_FIELD_DESC               "psp_FrmBackButtonURL"
#define PSP_FRMTIMEOUT_FIELD_DESC                     "psp_FrmTimeout"
#define PSP_3DSECUREACTION_FIELD_DESC                 "psp_3dSecureAction" 
#define PSP_SESSION3P_FIELD_DESC                      "psp_Session3p"
#define PSP_FRONTPSP_URL_FIELD_DESC                   "psp_FrontPSP_URL"
#define PSP_BARCODE_FIELD_DESC                        "psp_BarCode"

#define TAXES_FIELD                                   Taxes
#define TAXES_FIELD_DESC                              "Taxes"

#define ARRAY_PTR_FIELD                               __ptr
#define ARRAY_PTR_FIELD_DESC                          "__ptr"
#define ARRAY_SIZE_FIELD                               __size
#define ARRAY_SIZE_FIELD_DESC                         "__size"

#define PERSON_FIELD                                  Person
#define PERSON_FIELD_DESC                             "Person"

#define ORDERITEMS_FIELD                              OrderItems
#define ORDERITEMS_FIELD_DESC                         "OrderItems"

#define PSP_MERCHANTADDITIONALDETAILS_FIELD           psp_MerchantAdditionalDetails
#define PSP_MERCHANTADDITIONALDETAILS_FIELD_DESC      "psp_MerchantAdditionalDetails"

#define PSP_CUSTOMERADDITIONALDETAILS_FIELD           psp_CustomerAdditionalDetails
#define PSP_CUSTOMERADDITIONALDETAILS_FIELD_DESC     "psp_CustomerAdditionalDetails" 

#define PSP_BILLINGDETAILS_FIELD                      psp_BillingDetails
#define PSP_BILLINGDETAILS_FIELD_DESC                 "psp_BillingDetails"

#define PSP_SHIPPINGDETAILS_FIELD                     psp_ShippingDetails
#define PSP_SHIPPINGDETAILS_FIELD_DESC                "psp_ShippingDetails"

#define PSP_ORDERDETAILS_FIELD                        psp_OrderDetails
#define PSP_ORDERDETAILS_FIELD_DESC                   "psp_OrderDetails"

#define PSP_AIRLINEDETAILS_FIELD                      psp_AirlineDetails
#define PSP_AIRLINEDETAILS_FIELD_DESC                 "psp_AirlineDetails"

#define PSP_VAULTREFERENCE_FIELD                      psp_VaultReference
#define PSP_VAULTREFERENCE_FIELD_DESC                 "psp_VaultReference"

#define PSP_AMOUNTADDITIONALDETAILS_FIELD             psp_AmountAdditionalDetails
#define PSP_AMOUNTADDITIONALDETAILS_FIELD_DESC        "psp_AmountAdditionalDetails"
#define PSP_FRAUDSCREENINGRESULT_FIELD                psp_FraudScreeningResult
#define PSP_FRAUDSCREENINGRESULT_FIELD_DESC           "psp_FraudScreeningResult"
#define PSP_VERIFICATIONSERVICESRESULT_FIELD          psp_VerificationServicesResult
#define PSP_VERIFICATIONSERVICESRESULT_FIELD_DESC     "psp_VerificationServicesResult"

#define PSP_TRANSACTIONS_FIELD                        psp_Transactions
#define PSP_TRANSACTIONS_FIELD_DESC                   "psp_Transactions"

#define PSP_FIRSTEXPDATE_FIELD                        psp_FirstExpDate
#define PSP_FIRSTEXPDATE_FIELD_DESC                   "psp_FirstExpDate"

#define PSP_DAYSUNTILSECONDEXPDATE_FIELD              psp_DaysUntilSecondExpDate
#define PSP_DAYSUNTILSECONDEXPDATE_FIELD_DESC         "psp_DaysUntilSecondExpDate"

#define PSP_SURCHARGEAMOUNT_FIELD                     psp_SurchargeAmount
#define PSP_SURCHARGEAMOUNT_FIELD_DESC                "psp_SurchargeAmount"

#define PSP_DAYSAVAILABLETOPAY_FIELD                  psp_DaysAvailableToPay
#define PSP_DAYSAVAILABLETOPAY_FIELD_DESC             "psp_DaysAvailableToPay"

#define PSP_CUSTOMERDOCNUM_FIELD                      psp_CustomerDocNum
#define PSP_CUSTOMERDOCNUM_FIELD_DESC                 "psp_CustomerDocNum"

#define PSP_PAYMENTMETHOD_FIELD                       psp_PaymentMethod
#define PSP_PAYMENTMETHOD_FIELD_DESC                  "psp_PaymentMethod"

#define PSP_SETASCUSTOMERDEFAULT_FIELD                psp_SetAsCustomerDefault
#define PSP_SETASCUSTOMERDEFAULT_FIELD_DESC           "psp_SetAsCustomerDefault"

#define CARDINPUTDETAILS_FIELD                        CardInputDetails
#define CARDINPUTDETAILS_FIELD_DESC                   "CardInputDetails"

#define NUMBER_FIELD                                  Number
#define NUMBER_FIELD_DESC                             "Number"

#define EXPIRATIONDATE_FIELD                          ExpirationDate
#define EXPIRATIONDATE_FIELD_DESC                     "ExpirationDate"

#define SECURITYCODE_FIELD                            SecurityCode
#define SECURITYCODE_FIELD_DESC                       "SecurityCode"

#define HOLDERNAME_FIELD                              HolderName
#define HOLDERNAME_FIELD_DESC                         "HolderName"

#define PAYMENTMETHODTAG_FIELD                        PaymentMethodTag
#define PAYMENTMETHODTAG_FIELD_DESC                   "PaymentMethodTag"

#define EXPIRATIONYEAR_FIELD                          ExpirationYear
#define EXPIRATIONYEAR_FIELD_DESC                     "ExpirationYear"

#define EXPIRATIONMONTH_FIELD                         ExpirationMonth
#define EXPIRATIONMONTH_FIELD_DESC                    "ExpirationMonth"

#define IIN_FIELD                                     IIN
#define IIN_FIELD_DESC                                "IIN"

#define LAST4_FIELD                                   Last4
#define LAST4_FIELD_DESC                              "Last4"

#define NUMBERLENGTH_FIELD                            NumberLength
#define NUMBERLENGTH_FIELD_DESC                       "NumberLength" 
 
#define MASKEDNUMBER_FIELD                            MaskedNumber
#define MASKEDNUMBER_FIELD_DESC                       "MaskedNumber"

#define MASKEDNUMBERALTERNATIVE_FIELD                 MaskedNumberAlternative
#define MASKEDNUMBERALTERNATIVE_FIELD_DESC            "MaskedNumberAlternative"

#define PRODUCT_FIELD                                 Product
#define PRODUCT_FIELD_DESC                            "Product"

#define CARDOUTPUTDETAILS_FIELD                       CardOutputDetails
#define CARDOUTPUTDETAILS_FIELD_DESC                  "CardOutputDetails"

#define FINGERPRINT_FIELD                             FingerPrint
#define FINGERPRINT_FIELD_DESC                        "FingerPrint"

#define CREATEDAT_FIELD                               CreatedAt
#define CREATEDAT_FIELD_DESC                          "CreatedAt"

#define UPDATEDAT_FIELD                               UpdatedAt
#define UPDATEDAT_FIELD_DESC                          "UpdatedAt"

#define PSP_CARDINPUTDETAILS_FIELD                    psp_CardInputDetails
#define PSP_CARDINPUTDETAILS_FIELD_DESC               "psp_CardInputDetails"

#define PSP_PERSON_FIELD                              psp_Person
#define PSP_PERSON_FIELD_DESC                         "psp_Person"

#define PSP_ADDRESS_FIELD                             psp_Address
#define PSP_ADDRESS_FIELD_DESC                        "psp_Address"

#define PSP_CLIENTSESSION_FIELD                       psp_ClientSession
#define PSP_CLIENTSESSION_FIELD_DESC                  "psp_ClientSession"

#define PSP_PAYMENTMETHODTOKEN_FIELD                  psp_PaymentMethodToken
#define PSP_PAYMENTMETHODTOKEN_FIELD_DESC             "psp_PaymentMethodToken"

#define PSP_CARDOUTPUTDETAILS_FIELD                   psp_CardOutputDetails
#define PSP_CARDOUTPUTDETAILS_FIELD_DESC              "psp_CardOutputDetails"

#define PSP_ALREADYUSED_FIELD                         psp_AlreadyUsed
#define PSP_ALREADYUSED_FIELD_DESC                    "psp_AlreadyUsed"

#define PSP_UPDATEDAT_FIELD                           psp_UpdatedAt
#define PSP_UPDATEDAT_FIELD_DESC                      "psp_UpdatedAt"

#define PSP_PAYMENTMETHODTAG_FIELD                    psp_PaymentMethodTag
#define PSP_PAYMENTMETHODTAG_FIELD_DESC               "psp_PaymentMethodTag"

#define PSP_PAYMENTMETHODID_FIELD                     psp_PaymentMethodId
#define PSP_PAYMENTMETHODID_FIELD_DESC                "psp_PaymentMethodId"

#define PSP_EMAILADDRESS_FIELD                        psp_EmailAddress
#define PSP_EMAILADDRESS_FIELD_DESC                   "psp_EmailAddress"

#define PSP_ALTERNATIVEEMAILADDRESS_FIELD             psp_AlternativeEmailAddress
#define PSP_ALTERNATIVEEMAILADDRESS_FIELD_DESC        "psp_AlternativeEmailAddress"

#define PSP_ACCOUNTID_FIELD                           psp_AccountID
#define PSP_ACCOUNTID_FIELD_DESC                      "psp_AccountID"

#define PSP_ACCOUNTCREATEDAT_FIELD                    psp_AccountCreatedAt
#define PSP_ACCOUNTCREATEDAT_FIELD_DESC               "psp_AccountCreatedAt"

#define PSP_DEFAULTPAYMENTMETHODID_FIELD              psp_DefaultPaymentMethodId          
#define PSP_DEFAULTPAYMENTMETHODID_FIELD_DESC         "psp_DefaultPaymentMethodId"

#define PSP_PAYMENTMETHODS_FIELD                      psp_PaymentMethods
#define PSP_PAYMENTMETHODS_FIELD_DESC                 "psp_PaymentMethods"

#define PSP_QUERYCRITERIA_FIELD                       psp_QueryCriteria
#define PSP_QUERYCRITERIA_FIELD_DESC                  "psp_QueryCriteria"

#define PSP_QUERYCRITERIAID_FIELD                     psp_QueryCriteriaId
#define PSP_QUERYCRITERIAID_FIELD_DESC                "psp_QueryCriteriaId"

#define PSP_TRANSACTION_FIELD                         psp_Transaction
#define PSP_TRANSACTION_FIELD_DESC                    "psp_Transaction"

#define PSP_OPERATION_FIELD                           psp_Operation
#define PSP_OPERATION_FIELD_DESC                      "psp_Operation"

#define PSP_CARDNUMBER_FSD_FIELD                      psp_CardNumber_FSD
#define PSP_CARDNUMBER_FSD_FIELD_DESC                 "psp_CardNumber_FSD"

#define PSP_CARDNUMBER_LFD_FIELD                      psp_CardNumber_LFD
#define PSP_CARDNUMBER_LFD_FIELD_DESC                 "psp_CardNumber_LFD"

#define PSP_CARDMASK_FIELD                            psp_CardMask
#define PSP_CARDMASK_FIELD_DESC                       "psp_CardMask"

#define PSP_CUSTOMERIPADDRESS_FIELD                   psp_CustomerIpAddress
#define PSP_CUSTOMERIPADDRESS_FIELD_DESC              "psp_CustomerIpAddress"

#define PSP_CUSTOMERHTTPUSERAGENT_FIELD               psp_CustomerHttpUserAgent
#define PSP_CUSTOMERHTTPUSERAGENT_FIELD_DESC          "psp_CustomerHttpUserAgent"

#define PSP_VISAARG_VBV_SECURED_FIELD                 psp_VisaArg_VBV_Secured
#define PSP_VISAARG_VBV_SECURED_FIELD_DESC            "psp_VisaArg_VBV_Secured"

#define PSP_3DSECURE_Eci_FIELD                        psp_3dSecure_Eci
#define PSP_3DSECURE_Eci_FIELD_DESC                  "psp_3dSecure_Eci"

#define PSP_3DSECURE_ECIMSG_FIELD                     psp_3dSecure_EciMsg
#define PSP_3DSECURE_ECIMSG_FIELD_DESC                "psp_3dSecure_EciMsg"

#define PSP_IIN_FIELD                                 psp_IIN
#define PSP_IIN_FIELD_DESC                            "psp_IIN"

#define PSP_FINANCIALINSTITUTION_FIELD                psp_FinancialInstitution
#define PSP_FINANCIALINSTITUTION_FIELD_DESC           "psp_FinancialInstitution"

#define PSP_NEWSECRETKEY_FIELD                        psp_NewSecretKey
#define PSP_NEWSECRETKEY_FIELD_DESC                   "psp_NewSecretKey"

#define EXTERNALREFERENCEID_FIELD                     ExternalReferenceId
#define EXTERNALREFERENCEID_FIELD_DESC                "ExternalReferenceId"

#define STOPOVERCODE_FIELD                            StopoverCode
#define STOPOVERCODE_FIELD_DESC                       "StopoverCode"

#define NUMPAYMENTS_FIELD                             NumPayments
#define NUMPAYMENTS_FIELD_DESC                        "NumPayments"

#define INSTALLMENTAMOUNT_FIELD                       InstallmentAmount
#define INSTALLMENTAMOUNT_FIELD_DESC                  "InstallmentAmount"

#define INTERESTRATE_FIELD                            InterestRate
#define INTERESTRATE_FIELD_DESC                       "InterestRate"

#define PSP_INSTALLMENTSOPTIONS_FIELD                 psp_InstallmentsOptions
#define PSP_INSTALLMENTSOPTIONS_FIELD_DESC            "psp_InstallmentsOptions"

#define PSP_DEFAULTPAYMENTMETHODID_FIELD              psp_DefaultPaymentMethodId
#define PSP_DEFAULTPAYMENTMETHODID_FIELD_DESC         "psp_DefaultPaymentMethodId"

#define PSP_RESULT_FIELD                              psp_Result
#define PSP_RESULT_FIELD_DESC                         "psp_Result"

#define PSP_ORDERID_FIELD                             psp_OrderId
#define PSP_ORDERID_FIELD_DESC                        "psp_OrderId"

#define PSP_CRITERIA_FIELD                            psp_Criteria
#define PSP_CRITERIA_FIELD_DESC                       "psp_Criteria"

#define PSP_CRITERIAID_FIELD                          psp_CriteriaId
#define PSP_CRITERIAID_FIELD_DESC                     "psp_CriteriaId"

#define PSP_REVIEWRESULT_FIELD                        psp_ReviewResult
#define PSP_REVIEWRESULT_FIELD_DESC                   "psp_ReviewResult"

#define VAULT_REFERENCE_2P_XSI_TYPE                   "VaultReference2pStruct"
#define TAXES_REQUEST_XSI_TYPE                        "TaxesRequestStruct"
#define ARRAYOF_TAXESREQUESTSTRUCT_XSI_TYPE           "TaxesRequestStruct"
#define AMOUNT_ADDITIONAL_DETAILS_REQUEST_XSI_TYPE    "AmountAdditionalDetailsRequestStruct"
#define ADDRESS_XSI_TYPE                              "AddressStruct"
#define SELLER_DETAILS_XSI_TYPE                       "SellerDetailsStruct"
#define MERCHANT_ADDITIONAL_DETAILS_XSI_TYPE          "MerchantAdditionalDetailsStruct"
#define CUSTOMER_ADDITIONAL_DETAILS_XSI_TYPE          "CustomerAdditionalDetailsStruct"
#define PERSON_XSI_TYPE                               "PersonStruct"
#define BILLING_DETAILS_XSI_TYPE                      "BillingDetailsStruct"
#define SHIPPING_DETAILS_XSI_TYPE                     "ShippingDetailsStruct"
#define ORDER_DETAILS_XSI_TYPE                        "OrderDetailsStruct"
#define ARRAYOF_ORDERITEMSTRUCT_XSI_TYPE              "OrderItemStruct"
#define ORDER_ITEM_XSI_TYPE                           "OrderItemStruct"
#define LEG_XSI_TYPE                                  "LegStruct"
#define ARRAYOF_LEGSTRUCT_XSI_TYPE                    "LegStruct"
#define PASSENGER_XSI_TYPE                            "PassengerStruct"
#define ARRAYOF_PASSENGERSTRUCT_XSI_TYPE              "PassengerStruct"
#define AIRLINE_TICKET_ISSUE_XSI_TYPE                 "AirlineTicketIssueStruct"
#define AIRLINE_TICKET_XSI_TYPE                       "AirlineTicketStruct"
#define AIRLINE_DETAILS_XSI_TYPE                      "AirlineDetailsStruct" 
#define TAXES_RESPONSE_XSI_TYPE                       "TaxesResponseStruct"
#define ARRAYOF_TAXESRESPONSESTRUCT_XSI_TYPE          "TaxesResponseStruct"
#define AMOUNT_ADDITIONAL_DETAILS_RESPONSE_XSI_TYPE   "AmountAdditionalDetailsResponseStruct"
#define FRAUD_SCREENING_RESULT_XSI_TYPE               "FraudScreeningResultStruct"
#define VERIFICATION_SERVICES_RESULT_XSI_TYPE         "VerificationServicesResultStruct"

#define VAULT_REFERENCE_3P_XSI_TYPE                   "VaultReference3pStruct"
#define CARD_INPUT_DETAILS_XSI_TYPE                   "CardInputDetailsStruct"
#define PAYMENT_METHOD_INPUT_DETAILS_XSI_TYPE         "PaymentMethodInputDetailsStruct"
#define CARD_INPUT_UPDATE_DETAILS_XSI_TYPE            "CardInputUpdateDetailsStruct"
#define INSTALLMENTS_OPTIONS_XSI_TYPE                 "InstallmentsOptionsStruct"
#define ARRAYOF_INSTALLMENTSOPTIONSSTRUCT_XSI_TYPE    "InstallmentsOptionsStruct"


#define CARD_OUTPUT_DETAILS_XSI_TYPE                  "CardOutputDetailsStruct"
#define PAYMENT_METHOD_OUTPUT_DETAILS_XSI_TYPE        "PaymentMethodOutputDetailsStruct"
#define PAYMENT_METHODS_OUTPUT_DETAILS_XSI_TYPE       "PaymentMethodsOutputDetailsStruct"
#define ARRAYOF_PAYMENTMETHODSOUTPUTDETAILSSTRUCT_XSI_TYPE "PaymentMethodsOutputDetailsStruct"
#define RESPUESTASTRUCT_SIMPLEQUERYTX_TRANSACTIONS_XSI_TYPE "RespuestaStruct_SimpleQueryTx_Transactions"
#define RESPUESTASTRUCT_QUERYTXS_TRANSACTIONS_XSI_TYPE                         "RespuestaStruct_QueryTxs_Transactions"
#define ARRAYOF_RESPUESTASTRUCT_QUERYTXS_TRANSACTIONS_XSI_TYPE                 "RespuestaStruct_QueryTxs_Transactions"

#define REQUERIMIENTO_STRUCT_SPLIT_PAYONLINE_2P_TRANSACTIONS_XSI_TYPE          "RequerimientoStruct_SplitPayOnLine_2p_Transactions"
#define ARRAYOF_REQUERIMIENTOSTRUCT_SPLITPAYONLINE_2P_TRANSACTIONS_XSI_TYPE    "RequerimientoStruct_SplitPayOnLine_2p_Transactions"
#define REQUERIMIENTO_STRUCT_SPLITAUTHORIZE_2P_TRANSACTIONS_XSI_TYPE           "RequerimientoStruct_SplitAuthorize_2p_Transactions"
#define ARRAYOF_REQUERIMIENTOSTRUCT_SPLITAUTHORIZE_2P_TRANSACTIONS_XSI_TYPE    "RequerimientoStruct_SplitAuthorize_2p_Transactions"
#define REQUERIMIENTO_STRUCT_SPLITPAYONLINE_3P_TRANSACTIONS_XSI_TYPE           "RequerimientoStruct_SplitPayOnLine_3p_Transactions"
#define ARRAYOF_REQUERIMIENTOSTRUCT_SPLITPAYONLINE_3P_TRANSACTIONS_XSI_TYPE    "RequerimientoStruct_SplitPayOnLine_3p_Transactions"
#define REQUERIMIENTO_STRUCT_SPLITAUTHORIZE_3P_TRANSACTIONS_XSI_TYPE           "RequerimientoStruct_SplitAuthorize_3p_Transactions"
#define ARRAYOF_REQUERIMIENTOSTRUCT_SPLITAUTHORIZE_3P_TRANSACTIONS_XSI_TYPE    "RequerimientoStruct_SplitAuthorize_3p_Transactions"

#define RESPUESTASTRUCT_SPLITPAYONLINE_2P_TRANSACTIONS_XSI_TYPE                "RespuestaStruct_SplitPayOnLine_2p_Transactions"
#define ARRAYOF_RESPUESTASTRUCT_SPLITPAYONLINE_2P_TRANSACTIONS_XSI_TYPE        "RespuestaStruct_SplitPayOnLine_2p_Transactions"
#define RESPUESTASTRUCT_SPLITPAYONLINE_3P_TRANSACTIONS_XSI_TYPE                "RespuestaStruct_SplitPayOnLine_3p_Transactions"
#define ARRAYOF_RESPUESTASTRUCT_SPLITPAYONLINE_3P_TRANSACTIONS_XSI_TYPE        "RespuestaStruct_SplitPayOnLine_3p_Transactions"
#define RESPUESTASTRUCT_SPLITAUTHORIZE_3P_TRANSACTIONS_XSI_TYPE                "RespuestaStruct_SplitAuthorize_3p_Transactions"
#define ARRAYOF_RESPUESTASTRUCT_SPLITAUTHORIZE_3P_TRANSACTIONS_XSI_TYPE        "RespuestaStruct_SplitAuthorize_3p_Transactions"


typedef enum fields {
    PSP_VERSION=0,
    PSP_MERCHANTID,
    PSP_TXSOURCE,
    PSP_MERCHTXREF,
    PSP_MERCHORDERID,
    PSP_MERCHADDITIONALREF,
    PSP_AMOUNT,
    PSP_NUMPAYMENTS,
    PSP_RECURRENT,
    PSP_CURRENCY,
    PSP_COUNTRY,
    PSP_PRODUCT,
    PSP_CARDNUMBER,
    PSP_CARDEXPDATE,
    PSP_CARDSECURITYCODE,
    PSP_CARDHOLDERNAME,
    PSP_CUSTOMERMAIL,
    PSP_CUSTOMERID,
    PSP_MERCHANTMAIL,
    PSP_PURCHASEDESCRIPTION,
    PSP_SOFTDESCRIPTOR,
    PSP_FORCEPROCESSINGMETHOD,
    PSP_POSDATETIME,
    PSP_PLAN,
    PSP_FIRSTPAYMENTDEFERRAL,
    PSP_PROMOTIONCODE,
    PSP_PRESETCARDIIN,
    PSP_3DSECURE_XID,
    PSP_3DSECURE_CAVV,
    PSP_3DSECURE_ECI,
    PSP_3DSECURE_SECURED,
    PSP_VISAARG_DA_DOCTYPE,
    PSP_VISAARG_DA_DOCNUM,
    PSP_VISAARG_DA_DOORNUM,
    PSP_VISAARG_DA_BIRTHDAY,
    PSP_VISAARG_DA_NAME,
    PSP_AMEXARG_AVS_ADDRESS,
    PSP_AMEXARG_AVS_POSTCODE,
    PSP_MASTERARG_AVS_BIRTHDAY,
    PSP_MASTERARG_AVS_ADDITIONALSQTTY,
    PSP_MASTERARG_AVS_POSTALCODE,
    PSP_MASTERARG_AVS_BRANCHENTITY,
    PSP_RESPONSECOD,
    PSP_RESPONSEMSG,
    PSP_RESPONSEEXTENDED,
    PSP_TRANSACTIONID,
    PSP_AUTHORIZATIONCODE,
    PSP_BATCHNRO,
    PSP_TICKETNUMBER,
    PSP_SEQUENCENUMBER,
    PSP_CLTRNID,
    PSP_CLEXTERNALMERCHANT,
    PSP_CLEXTERNALTERMINAL,
    PSP_CLRESPONSECOD,
    PSP_CLRESPONSEMSG,
    PSP_CREATEDAT,
    PSP_VISAARG_DA_RESULT,
    PSP_AMEXARG_AVS_RESULT,
    PSP_MASTERARG_AVS_RESULT,
    PSP_TRANSACTIONID_ORIG,
    PSP_AMOUNTTOREFUND,
    PSP_AMOUNTTOCAPTURE,    
    PSP_USERID,
    PSP_SCREENDESCRIPTION,    
    PSP_TICKETDESCRIPTION,
    PSP_AMOUNT1,
    PSP_EXPDATE1,
    PSP_AMOUNT2,
    PSP_EXPDATE2,
    PSP_AMOUNT3,
    PSP_EXPDATE3,
    PSP_MINAMOUNT,
    PSP_EXPTIME,
    PSP_EXPMARK,
    PSP_CUSTOMERBANKID,
    PSP_USEMULTIPLEPRODUCTS,
    PSP_RETURNURL,
    PSP_FRMLANGUAGE,
    PSP_FRMBACKBUTTONURL,
    PSP_FRMTIMEOUT,
    PSP_3DSECUREACTION,
    PSP_FIRSTEXPDATE,
    PSP_DAYSUNTILSECONDEXPDATE,
    PSP_SURCHARGEAMOUNT,
    PSP_DAYSAVAILABLETOPAY,
    PSP_CUSTOMERDOCNUM,
    PSP_PAYMENTMETHODTAG,    
    PSP_PAYMENTMETHODID,
    PSP_EMAILADDRESS,
    PSP_ALTERNATIVEEMAILADDRESS,
    PSP_ACCOUNTID,
    PSP_ACCOUNTCREATEDAT,
    PSP_QUERYCRITERIA,
    PSP_QUERYCRITERIAID,
    PSP_IIN,
    PSP_NEWSECRETKEY,
    MAX_ROOT_FIELDS,    // >> obtengo id max para calcular securehash
    PSP_PAYMENTAMOUNT,
    TIP,
    DISCOUNT,
    TAXES, 
    ARRAY_PTR,           // >> usado para los arrayof
    ARRAY_SIZE,          // >> usado para los arrayof
    TYPEID,
    AMOUNT,
    RATE, 
    BASEAMOUNT,
    TYPE,
    SELLERDETAILS,
    SDKINFO,
    SHOPPINGCARTINFO,
    SHOPPINGCARTPLUGININFO,
    IDNUMBER,
    IDTYPE,
    NAME,
    INVOICE,
    PURCHASEDESCRIPTION,
    ADDRESS,
    MCC,
    CHANNELCODE,
    GEOCODE,
    STREET,
    HOUSENUMBER,
    ADDITIONALINFO,
    CITY,
    STATEPROVINCE,
    COUNTRY,
    ZIPCODE,
    EMAILADDRESS,
    ALTERNATIVEEMAILADDRESS,
    IPADDRESS,
    ACCOUNTID,
    ACCOUNTCREATEDAT,
    ACCOUNTPREVIOUSACTIVITY,
    ACCOUNTHASCREDENTIALS,
    DEVICETYPE,
    DEVICEFINGERPRINT,
    BROWSERLANGUAGE,
    HTTPUSERAGENT,
    INVOICEDATE,
    INVOICEAMOUNT,
    INVOICECURRENCY,
    PERSON,
    FIRSTNAME,
    LASTNAME,
    MIDDLENAME,
    PHONENUMBER1,
    PHONENUMBER2,
    GENDER,
    DATEOFBIRTH,
    NATIONALITY,
    TRACKINGNUMBER,
    METHOD,
    CARRIER,
    DELIVERYDATE,
    FREIGHTAMOUNT,
    GIFTMESSAGE,
    GIFTWRAPPING,
    PRIMARYRECIPIENT,
    SECONDARYRECIPIENT,
    QUANTITY,
    UNITPRICE,
    DESCRIPTION,
    SKUCODE,
    MANUFACTURERPARTNUMBER,
    RISK,
    ORDERITEMS,
    PNR,
    LEGS,
    PASSENGERS,
    TICKET,
    DEPARTUREAIRPORT,
    DEPARTUREDATETIME,
    DEPARTUREAIRPORTTIMEZONE,
    ARRIVALAIRPORT,
    CARRIERCODE,
    FLIGHTNUMBER,
    FAREBASISCODE,
    FARECLASSCODE,
    BASEFARE,
    BASEFARECURRENCY,
    IDCOUNTRY,
    LOYALTYNUMBER,
    LOYALTYTIER,
    TICKETNUMBER,
    ETICKET,
    RESTRICTED,
    ISSUE,
    TOTALFAREAMOUNT,
    TOTALTAXAMOUNT,
    TOTALFEEAMOUNT,    
    CARRIERPREFIXCODE,
    TRAVELAGENTCODE,
    TRAVELAGENTNAME,
    DATE,
    PAYMENTMETHODTOKEN,
    PAYMENTMETHODID,
    CUSTOMERID,
    TYPEDESCRIPTION,    
    APPLIEDAMOUNT,
    REMARKS,
    RESULTCODE,
    RESULTDESCRIPTION,
    RESULTCODECARDSECURITYCODE,
    RESULTCODEBILLINGADDRESS,
    RESULTCODEBILLINGADDRESSZIPCODE,
    RESULTCODEBILLINGPERSONIDTYPE,
    RESULTCODEBILLINGPERSONIDNUMBER,
    RESULTCODEBILLINGPERSONDATEOFBIRTH,
    RESULTCODEBILLINGPERSONNAME,
    RESULTCODEBILLINGPERSONPHONENUMBER1,
    RESULTCODECUSTOMEREMAILADDRESS,
    PSP_REFUNDEDAMOUNT,
    PSP_CAPTUREDAMOUNT_ORIG,
    PSP_CAPTUREDAMOUNT,
    PSP_AUTHORIZEDAMOUNT_ORIG,
    PSP_SESSION3P,
    PSP_FRONTPSP_URL,
    PSP_BARCODE,
    NUMBER,
    EXPIRATIONDATE,
    SECURITYCODE,
    HOLDERNAME,
    PAYMENTMETHODTAG,
    CARDINPUTDETAILS,
    PSP_PAYMENTMETHOD,
    PSP_SETASCUSTOMERDEFAULT,
    EXPIRATIONYEAR,
    EXPIRATIONMONTH,
    IIN,
    LAST4,
    NUMBERLENGTH,
    MASKEDNUMBER,
    MASKEDNUMBERALTERNATIVE,
    PRODUCT,
    CARDOUTPUTDETAILS,
    FINGERPRINT,
    CREATEDAT,
    UPDATEDAT,    
    PSP_CARDINPUTDETAILS,
    PSP_PERSON,
    PSP_ADDRESS,
    PSP_CLIENTSESSION,
    PSP_PAYMENTMETHODTOKEN,
    PSP_CARDOUTPUTDETAILS,
    PSP_ALREADYUSED,
    PSP_UPDATEDAT,
    PSP_DEFAULTPAYMENTMETHODID,
    PSP_PAYMENTMETHODS,
    PSP_TRANSACTION,
    PSP_OPERATION,
    PSP_CARDNUMBER_FSD,
    PSP_CARDNUMBER_LFD,
    PSP_CARDMASK,
    PSP_CUSTOMERIPADDRESS,
    PSP_CUSTOMERHTTPUSERAGENT,
    PSP_VISAARG_VBV_SECURED,
    PSP_3DSECURE_Eci,
    PSP_3DSECURE_ECIMSG,
    PSP_AMOUNTADDITIONALDETAILS,
    PSP_FRAUDSCREENINGRESULT,
    PSP_VERIFICATIONSERVICESRESULT,
    PSP_MERCHANTADDITIONALDETAILS,
    PSP_CUSTOMERADDITIONALDETAILS,
    PSP_BILLINGDETAILS,
    PSP_SHIPPINGDETAILS,
    PSP_ORDERDETAILS,
    PSP_AIRLINEDETAILS,
    PSP_TRANSACTIONS,
    PSP_FINANCIALINSTITUTION,
    STOPOVERCODE,
    EXTERNALREFERENCEID,
    PSP_RESULT,
    PSP_ORDERID,
    NUMPAYMENTS,
    INSTALLMENTAMOUNT,
    INTERESTRATE,
    PSP_INSTALLMENTSOPTIONS,
    PSP_CRITERIA,
    PSP_CRITERIAID,
    PSP_REVIEWRESULT,
    PSP_VAULTREFERENCE
} rootFields;


typedef struct RequerimientoStruct_PayOnLine_2p                           PAY_ONLINE_2P_REQ_STRUCT;
typedef struct RequerimientoStruct_Authorize_2p                           AUTHORIZE_2P_REQ_STRUCT;
typedef struct RequerimientoStruct_QueryTxs                               QUERY_TXS_REQ_STRUCT;
typedef struct RequerimientoStruct_SimpleQueryTx                          SIMPLE_QUERY_TX_REQ_STRUCT;
typedef struct RequerimientoStruct_Refund                                 REFUND_REQ_STRUCT;
typedef struct RequerimientoStruct_Capture                                CAPTURE_REQ_STRUCT;
typedef struct RequerimientoStruct_Authorize_3p                           AUTHORIZE_3P_REQ_STRUCT;
typedef struct RequerimientoStruct_BankPayment_3p                         BANK_PAYMENT_3P_REQ_STRUCT;
typedef struct RequerimientoStruct_CashPayment_3p                         CASH_PAYMENT_3P_REQ_STRUCT;
typedef struct RequerimientoStruct_ChangeSecretKey                        CHANGE_SECRET_KEY_REQ_STRUCT;
typedef struct RequerimientoStruct_FraudScreening                         FRAUD_SCREENING_REQ_STRUCT;
typedef struct RequerimientoStruct_NotifyFraudScreeningReview             NOTIFY_FRAUD_SCREENING_REVIEW_REQ_STRUCT;
typedef struct RequerimientoStruct_PayOnLine_3p                           PAY_ONLINE_3P_REQ_STRUCT;
typedef struct RequerimientoStruct_SplitAuthorize_3p                      SPLIT_AUTHORIZE_3P_REQ_STRUCT;
typedef struct RequerimientoStruct_SplitPayOnLine_3p                      SPLIT_PAY_ONLINE_3P_REQ_STRUCT;
typedef struct RequerimientoStruct_BankPayment_2p                         BANK_PAYMENT_2P_REQ_STRUCT;
typedef struct RequerimientoStruct_SplitPayOnLine_2p                      SPLIT_PAY_ONLINE_2P_REQ_STRUCT;
typedef struct RequerimientoStruct_SplitAuthorize_2p                      SPLIT_AUTHORIZE_2P_REQ_STRUCT;
typedef struct RequerimientoStruct_QueryCardNumber                        QUERY_CARD_NUMBER_REQ_STRUCT;
typedef struct RequerimientoStruct_QueryCardDetails                       QUERY_CARD_DETAILS_REQ_STRUCT;
typedef struct RequerimientoStruct_GetIINDetails                          GET_IIN_DETAILS_REQ_STRUCT;
typedef struct RequerimientoStruct_CreatePaymentMethod                    CREATE_PAYMENT_METHOD_REQ_STRUCT;
typedef struct RequerimientoStruct_CreatePaymentMethodFromPayment         CREATE_PAYMENT_METHOD_FROM_PAYMENT_REQ_STRUCT;
typedef struct RequerimientoStruct_RetrievePaymentMethod                  RETRIEVE_PAYMENT_METHOD_REQ_STRUCT;
typedef struct RequerimientoStruct_UpdatePaymentMethod                    UPDATE_PAYMENT_METHOD_REQ_STRUCT;
typedef struct RequerimientoStruct_DeletePaymentMethod                    DELETE_PAYMENT_METHOD_REQ_STRUCT;
typedef struct RequerimientoStruct_CreateCustomer                         CREATE_CUSTOMER_REQ_STRUCT;
typedef struct RequerimientoStruct_RetrieveCustomer                       RETRIEVE_CUSTOMER_REQ_STRUCT;
typedef struct RequerimientoStruct_UpdateCustomer                         UPDATE_CUSTOMER_REQ_STRUCT;
typedef struct RequerimientoStruct_DeleteCustomer                         DELETE_CUSTOMER_REQ_STRUCT;
typedef struct RequerimientoStruct_RecachePaymentMethodToken              RECACHE_PAYMENT_METHOD_TOKEN_REQ_STRUCT;
typedef struct RequerimientoStruct_CreatePaymentMethodToken               CREATE_PAYMENT_METHOD_TOKEN_REQ_STRUCT;
typedef struct RequerimientoStruct_RetrievePaymentMethodToken             RETRIEVE_PAYMENT_METHOD_TOKEN_REQ_STRUCT;
typedef struct RequerimientoStruct_CreateClientSession                    CREATE_CLIENT_SESSION_REQ_STRUCT;
typedef struct RequerimientoStruct_GetInstallmentsOptions                 GET_INSTALLMENTS_OPTIONS_REQ_STRUCT;
typedef struct RespuestaStruct_PayOnLine_2p                               PAY_ONLINE_2P_RESP_STRUCT;
typedef struct RespuestaStruct_Authorize_2p                               AUTHORIZE_2P_RESP_STRUCT;
typedef struct RespuestaStruct_QueryTxs                                   QUERY_TXS_RESP_STRUCT;
typedef struct RespuestaStruct_SimpleQueryTx                              SIMPLE_QUERY_TX_RESP_STRUCT;
typedef struct RespuestaStruct_Refund                                     REFUND_RESP_STRUCT;
typedef struct RespuestaStruct_Capture                                    CAPTURE_RESP_STRUCT;
typedef struct RespuestaStruct_Authorize_3p                               AUTHORIZE_3P_RESP_STRUCT;
typedef struct RespuestaStruct_BankPayment_3p                             BANK_PAYMENT_3P_RESP_STRUCT;
typedef struct RespuestaStruct_CashPayment_3p                             CASH_PAYMENT_3P_RESP_STRUCT;
typedef struct RespuestaStruct_ChangeSecretKey                            CHANGE_SECRET_KEY_RESP_STRUCT;
typedef struct RespuestaStruct_FraudScreening                             FRAUD_SCREENING_RESP_STRUCT;
typedef struct RespuestaStruct_NotifyFraudScreeningReview                 NOTIFY_FRAUD_SCREENING_REVIEW_RESP_STRUCT;
typedef struct RespuestaStruct_PayOnLine_3p                               PAY_ONLINE_3P_RESP_STRUCT;
typedef struct RespuestaStruct_SplitAuthorize_3p                          SPLIT_AUTHORIZE_3P_RESP_STRUCT;
typedef struct RespuestaStruct_SplitPayOnLine_3p                          SPLIT_PAY_ONLINE_3P_RESP_STRUCT;
typedef struct RespuestaStruct_BankPayment_2p                             BANK_PAYMENT_2P_RESP_STRUCT;
typedef struct RespuestaStruct_SplitPayOnLine_2p                          SPLIT_PAY_ONLINE_2P_RESP_STRUCT;
typedef struct RespuestaStruct_SplitAuthorize_2p                          SPLIT_AUTHORIZE_2P_RESP_STRUCT;
typedef struct RespuestaStruct_QueryCardNumber                            QUERY_CARD_NUMBER_RESP_STRUCT;
typedef struct RespuestaStruct_QueryCardDetails                           QUERY_CARD_DETAILS_RESP_STRUCT;
typedef struct RespuestaStruct_GetIINDetails                              GET_IIN_DETAILS_RESP_STRUCT;
typedef struct RespuestaStruct_CreatePaymentMethod                        CREATE_PAYMENT_METHOD_RESP_STRUCT;
typedef struct RespuestaStruct_CreatePaymentMethodFromPayment             CREATE_PAYMENT_METHOD_FROM_PAYMENT_RESP_STRUCT;
typedef struct RespuestaStruct_RetrievePaymentMethod                      RETRIEVE_PAYMENT_METHOD_RESP_STRUCT;
typedef struct RespuestaStruct_UpdatePaymentMethod                        UPDATE_PAYMENT_METHOD_RESP_STRUCT;
typedef struct RespuestaStruct_DeletePaymentMethod                        DELETE_PAYMENT_METHOD_RESP_STRUCT;
typedef struct RespuestaStruct_CreateCustomer                             CREATE_CUSTOMER_RESP_STRUCT;
typedef struct RespuestaStruct_RetrieveCustomer                           RETRIEVE_CUSTOMER_RESP_STRUCT;
typedef struct RespuestaStruct_UpdateCustomer                             UPDATE_CUSTOMER_RESP_STRUCT;
typedef struct RespuestaStruct_DeleteCustomer                             DELETE_CUSTOMER_RESP_STRUCT;
typedef struct RespuestaStruct_RecachePaymentMethodToken                  RECACHE_PAYMENT_METHOD_TOKEN_RESP_STRUCT;
typedef struct RespuestaStruct_CreatePaymentMethodToken                   CREATE_PAYMENT_METHOD_TOKEN_RESP_STRUCT;
typedef struct RespuestaStruct_RetrievePaymentMethodToken                 RETRIEVE_PAYMENT_METHOD_TOKEN_RESP_STRUCT;
typedef struct RespuestaStruct_CreateClientSession                        CREATE_CLIENT_SESSION_RESP_STRUCT;
typedef struct RespuestaStruct_GetInstallmentsOptions                     GET_INSTALLMENTS_OPTIONS_RESP_STRUCT;
typedef struct TaxesRequestStruct                                         TAXES_REQUEST_STRUCT;
typedef struct ArrayOf_TaxesRequestStruct                                 ARRAYOF_TAXESREQUESTSTRUCT;
typedef struct AmountAdditionalDetailsRequestStruct                       AMOUNT_ADDITIONAL_DETAILS_REQUEST_STRUCT;
typedef struct TaxesResponseStruct                                        TAXES_RESPONSE_STRUCT;
typedef struct ArrayOf_TaxesResponseStruct                                ARRAYOF_TAXESRESPONSESTRUCT;
typedef struct AmountAdditionalDetailsResponseStruct                      AMOUNT_ADDITIONAL_DETAILS_RESPONSE_STRUCT;
typedef struct AddressStruct                                              ADDRESS_STRUCT;
typedef struct SellerDetailsStruct                                        SELLER_DETAILS_STRUCT;
typedef struct MerchantAdditionalDetailsStruct                            MERCHANT_ADDITIONAL_DETAILS_STRUCT;
typedef struct CustomerAdditionalDetailsStruct                            CUSTOMER_ADDITIONAL_DETAILS_STRUCT;
typedef struct PersonStruct                                               PERSON_STRUCT;
typedef struct CardInputDetailsStruct                                     CARD_INPUT_DETAILS_STRUCT;
typedef struct BillingDetailsStruct                                       BILLING_DETAILS_STRUCT;
typedef struct ShippingDetailsStruct                                      SHIPPING_DETAILS_STRUCT;
typedef struct OrderItemStruct                                            ORDER_ITEM_STRUCT;
typedef struct ArrayOf_OrderItemStruct                                    ARRAYOF_ORDERITEMSTRUCT;
typedef struct OrderDetailsStruct                                         ORDER_DETAILS_STRUCT;
typedef struct LegStruct                                                  LEG_STRUCT;
typedef struct ArrayOf_LegStruct                                          ARRAYOF_LEGSTRUCT;
typedef struct PassengerStruct                                            PASSENGER_STRUCT;
typedef struct ArrayOf_PassengerStruct                                    ARRAYOF_PASSENGERSTRUCT;
typedef struct AirlineTicketIssueStruct                                   AIRLINE_TICKET_ISSUE_STRUCT;
typedef struct AirlineTicketStruct                                        AIRLINE_TICKET_STRUCT;
typedef struct AirlineDetailsStruct                                       AIRLINE_DETAILS_STRUCT;
typedef struct VaultReference3pStruct                                     VAULT_REFERENCE_3P_STRUCT;
typedef struct VaultReference2pStruct                                     VAULT_REFERENCE_2P_STRUCT;
typedef struct InstallmentsOptionsStruct                                  INSTALLMENTS_OPTIONS_STRUCT;
typedef struct RequerimientoStruct_SplitPayOnLine_2p_Transactions         REQUERIMIENTO_STRUCT_SPLIT_PAYONLINE_2P_TRANSACTIONS;
typedef struct ArrayOf_RequerimientoStruct_SplitPayOnLine_2p_Transactions ARRAYOF_REQUERIMIENTOSTRUCT_SPLITPAYONLINE_2P_TRANSACTIONS;
typedef struct RequerimientoStruct_SplitAuthorize_2p_Transactions         REQUERIMIENTO_STRUCT_SPLITAUTHORIZE_2P_TRANSACTIONS;
typedef struct ArrayOf_RequerimientoStruct_SplitAuthorize_2p_Transactions ARRAYOF_REQUERIMIENTOSTRUCT_SPLITAUTHORIZE_2P_TRANSACTIONS;
typedef struct RequerimientoStruct_SplitPayOnLine_3p_Transactions         REQUERIMIENTO_STRUCT_SPLITPAYONLINE_3P_TRANSACTIONS;
typedef struct ArrayOf_RequerimientoStruct_SplitPayOnLine_3p_Transactions ARRAYOF_REQUERIMIENTOSTRUCT_SPLITPAYONLINE_3P_TRANSACTIONS;
typedef struct RequerimientoStruct_SplitAuthorize_3p_Transactions         REQUERIMIENTO_STRUCT_SPLITAUTHORIZE_3P_TRANSACTIONS;
typedef struct ArrayOf_RequerimientoStruct_SplitAuthorize_3p_Transactions ARRAYOF_REQUERIMIENTOSTRUCT_SPLITAUTHORIZE_3P_TRANSACTIONS;
typedef struct PaymentMethodInputDetailsStruct                            PAYMENT_METHOD_INPUT_DETAILS_STRUCT;
typedef struct FraudScreeningResultStruct                                 FRAUD_SCREENING_RESULT_STRUCT;
typedef struct VerificationServicesResultStruct                           VERIFICATION_SERVICES_RESULT_STRUCT;
typedef struct CardInputUpdateDetailsStruct                               CARD_INPUT_UPDATE_DETAILS_STRUCT;
typedef struct CardOutputDetailsStruct                                    CARD_OUTPUT_DETAILS_STRUCT;
typedef struct PaymentMethodOutputDetailsStruct                           PAYMENT_METHOD_OUTPUT_DETAILS_STRUCT;
typedef struct RespuestaStruct_SplitPayOnLine_2p_Transactions             RESPUESTASTRUCT_SPLITPAYONLINE_2P_TRANSACTIONS;
typedef struct ArrayOf_RespuestaStruct_SplitPayOnLine_2p_Transactions     ARRAYOF_RESPUESTASTRUCT_SPLITPAYONLINE_2P_TRANSACTIONS;
typedef struct RespuestaStruct_SplitPayOnLine_3p_Transactions             RESPUESTASTRUCT_SPLITPAYONLINE_3P_TRANSACTIONS;
typedef struct ArrayOf_RespuestaStruct_SplitPayOnLine_3p_Transactions     ARRAYOF_RESPUESTASTRUCT_SPLITPAYONLINE_3P_TRANSACTIONS;
typedef struct RespuestaStruct_SplitAuthorize_3p_Transactions             RESPUESTASTRUCT_SPLITAUTHORIZE_3P_TRANSACTIONS;
typedef struct ArrayOf_RespuestaStruct_SplitAuthorize_3p_Transactions     ARRAYOF_RESPUESTASTRUCT_SPLITAUTHORIZE_3P_TRANSACTIONS;
typedef struct PaymentMethodsOutputDetailsStruct                          PAYMENT_METHODS_OUTPUT_DETAILS_STRUCT;
typedef struct ArrayOf_PaymentMethodsOutputDetailsStruct                  ARRAYOF_PAYMENTMETHODSOUTPUTDETAILSSTRUCT;
typedef struct RespuestaStruct_SimpleQueryTx_Transactions                 RESPUESTASTRUCT_SIMPLEQUERYTX_TRANSACTIONS;
typedef struct RespuestaStruct_QueryTxs_Transactions                      RESPUESTASTRUCT_QUERYTXS_TRANSACTIONS;
typedef struct ArrayOf_RespuestaStruct_QueryTxs_Transactions              ARRAYOF_RESPUESTASTRUCT_QUERYTXS_TRANSACTIONS;
typedef struct ArrayOf_InstallmentsOptionsStruct                          ARRAYOF_INSTALLMENTSOPTIONSSTRUCT;

/* End of NpsMethods.h */
#ifdef __cplusplus
}
#endif

#endif
