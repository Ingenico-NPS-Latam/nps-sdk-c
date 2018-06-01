#ifndef NpsSandbox_H
#define NpsSandbox_H
#include "NpsSandbox.h"

#ifdef __cplusplus
extern "C" {
#endif

struct VaultReference2pStruct
{
    char*                                PaymentMethodToken             ;	
    char*                                PaymentMethodId                ;	
    char*                                CustomerId                     ;	
};

struct TaxesRequestStruct
{
    char*                                TypeId                         ;	
    char*                                Amount                         ;	
    char*                                Rate                           ;	
    char*                                BaseAmount                     ;	
};

struct AmountAdditionalDetailsRequestStruct
{
    char*                                Tip                            ;	
    char*                                Discount                       ;	
    struct ArrayOf_TaxesRequestStruct*  Taxes                          ;	
};

struct AddressStruct
{
    char*                                Street                         ;	
    char*                                HouseNumber                    ;	
    char*                                AdditionalInfo                 ;	
    char*                                City                           ;	
    char*                                StateProvince                  ;	
    char*                                Country                        ;	
    char*                                ZipCode                        ;	
};

struct SellerDetailsStruct
{
    char*                                ExternalReferenceId            ;	
    char*                                IDNumber                       ;	
    char*                                IDType                         ;	
    char*                                Name                           ;	
    char*                                Invoice                        ;	
    char*                                PurchaseDescription            ;	
    struct AddressStruct*           Address                        ;	
    char*                                EmailAddress                   ;	
    char*                                PhoneNumber1                   ;	
    char*                                PhoneNumber2                   ;	
    char*                                MCC                            ;	
    char*                                ChannelCode                    ;	
    char*                                GeoCode                        ;	
};

struct MerchantAdditionalDetailsStruct
{
    char*                                Type                           ;	
    struct SellerDetailsStruct*     SellerDetails                  ;	
    char*                                SdkInfo                        ;	
    char*                                ShoppingCartInfo               ;	
    char*                                ShoppingCartPluginInfo         ;	
};

struct CustomerAdditionalDetailsStruct
{
    char*                                EmailAddress                   ;	
    char*                                AlternativeEmailAddress        ;	
    char*                                IPAddress                      ;	
    char*                                AccountID                      ;	
    char*                                AccountCreatedAt               ;	
    char*                                AccountPreviousActivity        ;	
    char*                                AccountHasCredentials          ;	
    char*                                DeviceType                     ;	
    char*                                DeviceFingerPrint              ;	
    char*                                BrowserLanguage                ;	
    char*                                HttpUserAgent                  ;	
};

struct PersonStruct
{
    char*                                FirstName                      ;	
    char*                                LastName                       ;	
    char*                                MiddleName                     ;	
    char*                                PhoneNumber1                   ;	
    char*                                PhoneNumber2                   ;	
    char*                                Gender                         ;	
    char*                                DateOfBirth                    ;	
    char*                                Nationality                    ;	
    char*                                IDNumber                       ;	
    char*                                IDType                         ;	
};

struct BillingDetailsStruct
{
    char*                                Invoice                        ;	
    char*                                InvoiceDate                    ;	
    char*                                InvoiceAmount                  ;	
    char*                                InvoiceCurrency                ;	
    struct PersonStruct*            Person                         ;	
    struct AddressStruct*           Address                        ;	
};

struct ShippingDetailsStruct
{
    char*                                TrackingNumber                 ;	
    char*                                Method                         ;	
    char*                                Carrier                        ;	
    char*                                DeliveryDate                   ;	
    char*                                FreightAmount                  ;	
    char*                                GiftMessage                    ;	
    char*                                GiftWrapping                   ;	
    struct PersonStruct*            PrimaryRecipient               ;	
    struct PersonStruct*            SecondaryRecipient             ;	
    struct AddressStruct*           Address                        ;	
};

struct OrderItemStruct
{
    char*                                Quantity                       ;	
    char*                                UnitPrice                      ;	
    char*                                Description                    ;	
    char*                                Type                           ;	
    char*                                SkuCode                        ;	
    char*                                ManufacturerPartNumber         ;	
    char*                                Risk                           ;	
};

struct OrderDetailsStruct
{
    struct ArrayOf_OrderItemStruct*  OrderItems                     ;	
};

struct LegStruct
{
    char*                                DepartureAirport               ;	
    char*                                DepartureDatetime              ;	
    char*                                DepartureAirportTimezone       ;	
    char*                                ArrivalAirport                 ;	
    char*                                CarrierCode                    ;	
    char*                                FlightNumber                   ;	
    char*                                FareBasisCode                  ;	
    char*                                FareClassCode                  ;	
    char*                                BaseFare                       ;	
    char*                                BaseFareCurrency               ;	
    char*                                StopoverCode                   ;	
};

struct PassengerStruct
{
    char*                                FirstName                      ;	
    char*                                LastName                       ;	
    char*                                MiddleName                     ;	
    char*                                Type                           ;	
    char*                                DateOfBirth                    ;	
    char*                                Nationality                    ;	
    char*                                IDNumber                       ;	
    char*                                IDType                         ;	
    char*                                IDCountry                      ;	
    char*                                LoyaltyNumber                  ;	
    char*                                LoyaltyTier                    ;	
};

struct AirlineTicketIssueStruct
{
    char*                                CarrierPrefixCode              ;	
    char*                                TravelAgentCode                ;	
    char*                                TravelAgentName                ;	
    char*                                Date                           ;	
    char*                                Country                        ;	
    char*                                City                           ;	
    char*                                Address                        ;	
};

struct AirlineTicketStruct
{
    char*                                TicketNumber                   ;	
    char*                                Eticket                        ;	
    char*                                Restricted                     ;	
    struct AirlineTicketIssueStruct*  Issue                          ;	
    char*                                TotalFareAmount                ;	
    char*                                TotalTaxAmount                 ;	
    char*                                TotalFeeAmount                 ;	
};

struct AirlineDetailsStruct
{
    char*                                PNR                            ;	
    struct ArrayOf_LegStruct*      Legs                           ;	
    struct ArrayOf_PassengerStruct*  Passengers                     ;	
    struct AirlineTicketStruct*     Ticket                         ;	
};

struct RequerimientoStruct_PayOnLine_2p
{
    char*                                psp_Version              ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_TxSource             ;	
    char*                                psp_MerchTxRef           ;	
    char*                                psp_MerchOrderId         ;	
    char*                                psp_MerchAdditionalRef   ;	
    char*                                psp_Amount               ;	
    char*                                psp_NumPayments          ;	
    char*                                psp_Recurrent            ;	
    char*                                psp_Currency             ;	
    char*                                psp_Country              ;	
    char*                                psp_Product              ;	
    char*                                psp_CardNumber           ;	
    char*                                psp_CardExpDate          ;	
    char*                                psp_CardSecurityCode     ;	
    char*                                psp_CardHolderName       ;	
    char*                                psp_CustomerMail         ;	
    char*                                psp_CustomerId           ;	
    char*                                psp_MerchantMail         ;	
    char*                                psp_PurchaseDescription  ;	
    char*                                psp_SoftDescriptor       ;	
    char*                                psp_ForceProcessingMethod ;	
    char*                                psp_PosDateTime          ;	
    char*                                psp_Plan                 ;	
    char*                                psp_FirstPaymentDeferral ;	
    char*                                psp_PromotionCode        ;	
    char*                                psp_PresetCardIIN        ;	
    char*                                psp_3dSecure_XID   ;	
    char*                                psp_3dSecure_CAVV  ;	
    char*                                psp_3dSecure_ECI   ;	
    char*                                psp_3dSecure_Secured ;	
    char*                                psp_VisaArg_DA_DocType ;	
    char*                                psp_VisaArg_DA_DocNum ;	
    char*                                psp_VisaArg_DA_DoorNum ;	
    char*                                psp_VisaArg_DA_BirthDay ;	
    char*                                psp_VisaArg_DA_Name ;	
    char*                                psp_AmexArg_AVS_Address ;	
    char*                                psp_AmexArg_AVS_PostCode ;	
    char*                                psp_MasterArg_AVS_BirthDay ;	
    char*                                psp_MasterArg_AVS_AdditionalsQtty ;	
    char*                                psp_MasterArg_AVS_PostalCode ;	
    char*                                psp_MasterArg_AVS_BranchEntity ;	
    char*                                psp_SecureHash           ;	
    struct VaultReference2pStruct*  psp_VaultReference       ;	
    struct AmountAdditionalDetailsRequestStruct*  psp_AmountAdditionalDetails ;	
    struct MerchantAdditionalDetailsStruct*  psp_MerchantAdditionalDetails ;	
    struct CustomerAdditionalDetailsStruct*  psp_CustomerAdditionalDetails ;	
    struct BillingDetailsStruct*    psp_BillingDetails       ;	
    struct ShippingDetailsStruct*   psp_ShippingDetails      ;	
    struct OrderDetailsStruct*      psp_OrderDetails         ;	
    struct AirlineDetailsStruct*    psp_AirlineDetails       ;	
};

struct TaxesResponseStruct
{
    char*                                TypeId                         ;	
    char*                                TypeDescription                ;	
    char*                                Amount                         ;	
    char*                                Rate                           ;	
    char*                                BaseAmount                     ;	
    char*                                AppliedAmount                  ;	
    char*                                Remarks                        ;	
};

struct AmountAdditionalDetailsResponseStruct
{
    char*                                Tip                            ;	
    char*                                Discount                       ;	
    struct ArrayOf_TaxesResponseStruct*  Taxes                          ;	
};

struct FraudScreeningResultStruct
{
    char*                                ResultCode                     ;	
    char*                                ResultDescription              ;	
    char*                                AdditionalInfo                 ;	
};

struct VerificationServicesResultStruct
{
    char*                                ResultCodeCardSecurityCode     ;	
    char*                                ResultCodeBillingAddress       ;	
    char*                                ResultCodeBillingAddressZipCode ;	
    char*                                ResultCodeBillingPersonIDType  ;	
    char*                                ResultCodeBillingPersonIDNumber ;	
    char*                                ResultCodeBillingPersonDateOfBirth ;	
    char*                                ResultCodeBillingPersonName    ;	
    char*                                ResultCodeBillingPersonPhoneNumber1 ;	
    char*                                ResultCodeCustomerEmailAddress ;	
};

struct RespuestaStruct_PayOnLine_2p
{
    char*                                psp_ResponseCod          ;	
    char*                                psp_ResponseMsg          ;	
    char*                                psp_ResponseExtended     ;	
    char*                                psp_TransactionId        ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_MerchTxRef           ;	
    char*                                psp_MerchOrderId         ;	
    char*                                psp_MerchAdditionalRef   ;	
    char*                                psp_Amount               ;	
    char*                                psp_NumPayments          ;	
    char*                                psp_PaymentAmount        ;	
    char*                                psp_Recurrent            ;	
    char*                                psp_Currency             ;	
    char*                                psp_Country              ;	
    char*                                psp_Product              ;	
    char*                                psp_CardNumber           ;	
    char*                                psp_CardExpDate          ;	
    char*                                psp_AuthorizationCode    ;	
    char*                                psp_BatchNro             ;	
    char*                                psp_TicketNumber         ;	
    char*                                psp_SequenceNumber       ;	
    char*                                psp_CustomerMail         ;	
    char*                                psp_CustomerId           ;	
    char*                                psp_MerchantMail         ;	
    char*                                psp_ClTrnId              ;	
    char*                                psp_ClExternalMerchant   ;	
    char*                                psp_ClExternalTerminal   ;	
    char*                                psp_ClResponseCod        ;	
    char*                                psp_ClResponseMsg        ;	
    char*                                psp_PosDateTime          ;	
    char*                                psp_Plan                 ;	
    char*                                psp_PromotionCode        ;	
    char*                                psp_PresetCardIIN        ;	
    char*                                psp_FirstPaymentDeferral ;	
    char*                                psp_VisaArg_DA_Result ;	
    char*                                psp_AmexArg_AVS_Result ;	
    char*                                psp_MasterArg_AVS_Result ;	
    char*                                psp_CreatedAt            ;	
    struct AmountAdditionalDetailsResponseStruct*  psp_AmountAdditionalDetails ;	
    struct FraudScreeningResultStruct*  psp_FraudScreeningResult ;	
    struct VerificationServicesResultStruct*  psp_VerificationServicesResult ;	
};

struct RequerimientoStruct_Authorize_2p
{
    char*                                psp_Version              ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_TxSource             ;	
    char*                                psp_MerchTxRef           ;	
    char*                                psp_MerchOrderId         ;	
    char*                                psp_MerchAdditionalRef   ;	
    char*                                psp_Amount               ;	
    char*                                psp_NumPayments          ;	
    char*                                psp_Recurrent            ;	
    char*                                psp_Currency             ;	
    char*                                psp_Country              ;	
    char*                                psp_Product              ;	
    char*                                psp_CardNumber           ;	
    char*                                psp_CardExpDate          ;	
    char*                                psp_CardSecurityCode     ;	
    char*                                psp_CardHolderName       ;	
    char*                                psp_CustomerMail         ;	
    char*                                psp_CustomerId           ;	
    char*                                psp_MerchantMail         ;	
    char*                                psp_PurchaseDescription  ;	
    char*                                psp_SoftDescriptor       ;	
    char*                                psp_ForceProcessingMethod ;	
    char*                                psp_PosDateTime          ;	
    char*                                psp_Plan                 ;	
    char*                                psp_PromotionCode        ;	
    char*                                psp_PresetCardIIN        ;	
    char*                                psp_3dSecure_XID   ;	
    char*                                psp_3dSecure_CAVV  ;	
    char*                                psp_3dSecure_ECI   ;	
    char*                                psp_3dSecure_Secured ;	
    char*                                psp_VisaArg_DA_DocType ;	
    char*                                psp_VisaArg_DA_DocNum ;	
    char*                                psp_VisaArg_DA_DoorNum ;	
    char*                                psp_VisaArg_DA_BirthDay ;	
    char*                                psp_VisaArg_DA_Name ;	
    char*                                psp_AmexArg_AVS_Address ;	
    char*                                psp_AmexArg_AVS_PostCode ;	
    char*                                psp_MasterArg_AVS_BirthDay ;	
    char*                                psp_MasterArg_AVS_AdditionalsQtty ;	
    char*                                psp_MasterArg_AVS_PostalCode ;	
    char*                                psp_MasterArg_AVS_BranchEntity ;	
    char*                                psp_SecureHash           ;	
    struct VaultReference2pStruct*  psp_VaultReference       ;	
    struct AmountAdditionalDetailsRequestStruct*  psp_AmountAdditionalDetails ;	
    struct MerchantAdditionalDetailsStruct*  psp_MerchantAdditionalDetails ;	
    struct CustomerAdditionalDetailsStruct*  psp_CustomerAdditionalDetails ;	
    struct BillingDetailsStruct*    psp_BillingDetails       ;	
    struct ShippingDetailsStruct*   psp_ShippingDetails      ;	
    struct OrderDetailsStruct*      psp_OrderDetails         ;	
    struct AirlineDetailsStruct*    psp_AirlineDetails       ;	
};

struct RespuestaStruct_Authorize_2p
{
    char*                                psp_ResponseCod          ;	
    char*                                psp_ResponseMsg          ;	
    char*                                psp_ResponseExtended     ;	
    char*                                psp_TransactionId        ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_MerchTxRef           ;	
    char*                                psp_MerchOrderId         ;	
    char*                                psp_MerchAdditionalRef   ;	
    char*                                psp_Amount               ;	
    char*                                psp_NumPayments          ;	
    char*                                psp_PaymentAmount        ;	
    char*                                psp_Recurrent            ;	
    char*                                psp_Currency             ;	
    char*                                psp_Country              ;	
    char*                                psp_Product              ;	
    char*                                psp_CardNumber           ;	
    char*                                psp_CardExpDate          ;	
    char*                                psp_AuthorizationCode    ;	
    char*                                psp_BatchNro             ;	
    char*                                psp_TicketNumber         ;	
    char*                                psp_SequenceNumber       ;	
    char*                                psp_CustomerMail         ;	
    char*                                psp_CustomerId           ;	
    char*                                psp_MerchantMail         ;	
    char*                                psp_ClTrnId              ;	
    char*                                psp_ClExternalMerchant   ;	
    char*                                psp_ClExternalTerminal   ;	
    char*                                psp_ClResponseCod        ;	
    char*                                psp_ClResponseMsg        ;	
    char*                                psp_PosDateTime          ;	
    char*                                psp_Plan                 ;	
    char*                                psp_PromotionCode        ;	
    char*                                psp_PresetCardIIN        ;	
    char*                                psp_VisaArg_DA_Result ;	
    char*                                psp_AmexArg_AVS_Result ;	
    char*                                psp_MasterArg_AVS_Result ;	
    char*                                psp_CreatedAt            ;	
    struct AmountAdditionalDetailsResponseStruct*  psp_AmountAdditionalDetails ;	
    struct FraudScreeningResultStruct*  psp_FraudScreeningResult ;	
    struct VerificationServicesResultStruct*  psp_VerificationServicesResult ;	
};

struct RequerimientoStruct_BankPayment_2p
{
    char*                                psp_Version              ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_TxSource             ;	
    char*                                psp_MerchTxRef           ;	
    char*                                psp_MerchOrderId         ;	
    char*                                psp_MerchAdditionalRef   ;	
    char*                                psp_ScreenDescription    ;	
    char*                                psp_TicketDescription    ;	
    char*                                psp_Currency             ;	
    char*                                psp_Country              ;	
    char*                                psp_Product              ;	
    char*                                psp_Amount1              ;	
    char*                                psp_ExpDate1             ;	
    char*                                psp_Amount2              ;	
    char*                                psp_ExpDate2             ;	
    char*                                psp_Amount3              ;	
    char*                                psp_ExpDate3             ;	
    char*                                psp_MinAmount            ;	
    char*                                psp_ExpTime              ;	
    char*                                psp_ExpMark              ;	
    char*                                psp_CustomerBankId       ;	
    char*                                psp_CustomerMail         ;	
    char*                                psp_CustomerId           ;	
    char*                                psp_MerchantMail         ;	
    char*                                psp_ForceProcessingMethod ;	
    char*                                psp_PosDateTime          ;	
    char*                                psp_SecureHash           ;	
    struct AmountAdditionalDetailsRequestStruct*  psp_AmountAdditionalDetails ;	
    struct MerchantAdditionalDetailsStruct*  psp_MerchantAdditionalDetails ;	
    struct CustomerAdditionalDetailsStruct*  psp_CustomerAdditionalDetails ;	
    struct BillingDetailsStruct*    psp_BillingDetails       ;	
    struct ShippingDetailsStruct*   psp_ShippingDetails      ;	
    struct OrderDetailsStruct*      psp_OrderDetails         ;	
    struct AirlineDetailsStruct*    psp_AirlineDetails       ;	
};

struct RespuestaStruct_BankPayment_2p
{
    char*                                psp_ResponseCod          ;	
    char*                                psp_ResponseMsg          ;	
    char*                                psp_ResponseExtended     ;	
    char*                                psp_TransactionId        ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_MerchTxRef           ;	
    char*                                psp_MerchOrderId         ;	
    char*                                psp_MerchAdditionalRef   ;	
    char*                                psp_ScreenDescription    ;	
    char*                                psp_TicketDescription    ;	
    char*                                psp_Currency             ;	
    char*                                psp_Country              ;	
    char*                                psp_Product              ;	
    char*                                psp_Amount1              ;	
    char*                                psp_ExpDate1             ;	
    char*                                psp_Amount2              ;	
    char*                                psp_ExpDate2             ;	
    char*                                psp_Amount3              ;	
    char*                                psp_ExpDate3             ;	
    char*                                psp_MinAmount            ;	
    char*                                psp_ExpTime              ;	
    char*                                psp_ExpMark              ;	
    char*                                psp_CustomerBankId       ;	
    char*                                psp_CustomerMail         ;	
    char*                                psp_CustomerId           ;	
    char*                                psp_MerchantMail         ;	
    char*                                psp_PosDateTime          ;	
    char*                                psp_CreatedAt            ;	
    struct AmountAdditionalDetailsResponseStruct*  psp_AmountAdditionalDetails ;	
};

struct RequerimientoStruct_SplitPayOnLine_2p_Transactions
{
    char*                                psp_MerchantId           ;	
    char*                                psp_MerchTxRef           ;	
    char*                                psp_MerchAdditionalRef   ;	
    char*                                psp_Product              ;	
    char*                                psp_CardNumber           ;	
    char*                                psp_CardExpDate          ;	
    char*                                psp_CardSecurityCode     ;	
    char*                                psp_CardHolderName       ;	
    char*                                psp_Amount               ;	
    char*                                psp_NumPayments          ;	
    char*                                psp_Plan                 ;	
    char*                                psp_FirstPaymentDeferral ;	
    char*                                psp_PromotionCode        ;	
    char*                                psp_PresetCardIIN        ;	
    char*                                psp_SoftDescriptor       ;	
    struct VaultReference2pStruct*  psp_VaultReference       ;	
    struct AmountAdditionalDetailsRequestStruct*  psp_AmountAdditionalDetails ;	
    struct MerchantAdditionalDetailsStruct*  psp_MerchantAdditionalDetails ;	
    struct BillingDetailsStruct*    psp_BillingDetails       ;	
};

struct RequerimientoStruct_SplitPayOnLine_2p
{
    char*                                psp_Version              ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_TxSource             ;	
    char*                                psp_MerchOrderId         ;	
    char*                                psp_Amount               ;	
    char*                                psp_Currency             ;	
    char*                                psp_Country              ;	
    char*                                psp_Recurrent            ;	
    char*                                psp_UseMultipleProducts  ;	
    char*                                psp_Product              ;	
    char*                                psp_CardNumber           ;	
    char*                                psp_CardExpDate          ;	
    char*                                psp_CardSecurityCode     ;	
    char*                                psp_CardHolderName       ;	
    char*                                psp_PurchaseDescription  ;	
    char*                                psp_SoftDescriptor       ;	
    char*                                psp_ForceProcessingMethod ;	
    char*                                psp_PosDateTime          ;	
    char*                                psp_3dSecure_XID   ;	
    char*                                psp_3dSecure_CAVV  ;	
    char*                                psp_3dSecure_ECI   ;	
    char*                                psp_3dSecure_Secured ;	
    char*                                psp_SecureHash           ;	
    struct VaultReference2pStruct*  psp_VaultReference       ;	
    struct MerchantAdditionalDetailsStruct*  psp_MerchantAdditionalDetails ;	
    struct CustomerAdditionalDetailsStruct*  psp_CustomerAdditionalDetails ;	
    struct BillingDetailsStruct*    psp_BillingDetails       ;	
    struct ShippingDetailsStruct*   psp_ShippingDetails      ;	
    struct OrderDetailsStruct*      psp_OrderDetails         ;	
    struct AirlineDetailsStruct*    psp_AirlineDetails       ;	
    struct ArrayOf_RequerimientoStruct_SplitPayOnLine_2p_Transactions*  psp_Transactions         ;	
};

struct RespuestaStruct_SplitPayOnLine_2p_Transactions
{
    char*                                psp_ResponseCod          ;	
    char*                                psp_ResponseMsg          ;	
    char*                                psp_ResponseExtended     ;	
    char*                                psp_TransactionId        ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_MerchTxRef           ;	
    char*                                psp_MerchOrderId         ;	
    char*                                psp_MerchAdditionalRef   ;	
    char*                                psp_Amount               ;	
    char*                                psp_NumPayments          ;	
    char*                                psp_PaymentAmount        ;	
    char*                                psp_Recurrent            ;	
    char*                                psp_Currency             ;	
    char*                                psp_Country              ;	
    char*                                psp_Product              ;	
    char*                                psp_CardNumber           ;	
    char*                                psp_CardExpDate          ;	
    char*                                psp_AuthorizationCode    ;	
    char*                                psp_BatchNro             ;	
    char*                                psp_TicketNumber         ;	
    char*                                psp_SequenceNumber       ;	
    char*                                psp_CustomerMail         ;	
    char*                                psp_CustomerId           ;	
    char*                                psp_MerchantMail         ;	
    char*                                psp_ClTrnId              ;	
    char*                                psp_ClExternalMerchant   ;	
    char*                                psp_ClExternalTerminal   ;	
    char*                                psp_ClResponseCod        ;	
    char*                                psp_ClResponseMsg        ;	
    char*                                psp_PosDateTime          ;	
    char*                                psp_Plan                 ;	
    char*                                psp_PromotionCode        ;	
    char*                                psp_PresetCardIIN        ;	
    char*                                psp_CreatedAt            ;	
    struct AmountAdditionalDetailsResponseStruct*  psp_AmountAdditionalDetails ;	
    struct FraudScreeningResultStruct*  psp_FraudScreeningResult ;	
    struct VerificationServicesResultStruct*  psp_VerificationServicesResult ;	
};

struct RespuestaStruct_SplitPayOnLine_2p
{
    char*                                psp_ResponseCod          ;	
    char*                                psp_ResponseMsg          ;	
    char*                                psp_ResponseExtended     ;	
    char*                                psp_TransactionId        ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_MerchTxRef           ;	
    char*                                psp_MerchOrderId         ;	
    char*                                psp_PosDateTime          ;	
    char*                                psp_UseMultipleProducts  ;	
    struct ArrayOf_RespuestaStruct_SplitPayOnLine_2p_Transactions*  psp_Transactions         ;	
};

struct RequerimientoStruct_SplitAuthorize_2p_Transactions
{
    char*                                psp_MerchantId           ;	
    char*                                psp_MerchTxRef           ;	
    char*                                psp_MerchAdditionalRef   ;	
    char*                                psp_Amount               ;	
    char*                                psp_NumPayments          ;	
    char*                                psp_Product              ;	
    char*                                psp_CardNumber           ;	
    char*                                psp_CardExpDate          ;	
    char*                                psp_CardSecurityCode     ;	
    char*                                psp_CardHolderName       ;	
    char*                                psp_SoftDescriptor       ;	
    char*                                psp_Plan                 ;	
    char*                                psp_PromotionCode        ;	
    char*                                psp_PresetCardIIN        ;	
    struct VaultReference2pStruct*  psp_VaultReference       ;	
    struct AmountAdditionalDetailsRequestStruct*  psp_AmountAdditionalDetails ;	
    struct MerchantAdditionalDetailsStruct*  psp_MerchantAdditionalDetails ;	
    struct BillingDetailsStruct*    psp_BillingDetails       ;	
};

struct RequerimientoStruct_SplitAuthorize_2p
{
    char*                                psp_Version              ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_TxSource             ;	
    char*                                psp_MerchOrderId         ;	
    char*                                psp_Amount               ;	
    char*                                psp_Currency             ;	
    char*                                psp_Country              ;	
    char*                                psp_Recurrent            ;	
    char*                                psp_UseMultipleProducts  ;	
    char*                                psp_Product              ;	
    char*                                psp_CardNumber           ;	
    char*                                psp_CardExpDate          ;	
    char*                                psp_CardSecurityCode     ;	
    char*                                psp_CardHolderName       ;	
    char*                                psp_PurchaseDescription  ;	
    char*                                psp_SoftDescriptor       ;	
    char*                                psp_ForceProcessingMethod ;	
    char*                                psp_PosDateTime          ;	
    char*                                psp_3dSecure_XID   ;	
    char*                                psp_3dSecure_CAVV  ;	
    char*                                psp_3dSecure_ECI   ;	
    char*                                psp_3dSecure_Secured ;	
    char*                                psp_SecureHash           ;	
    struct VaultReference2pStruct*  psp_VaultReference       ;	
    struct MerchantAdditionalDetailsStruct*  psp_MerchantAdditionalDetails ;	
    struct CustomerAdditionalDetailsStruct*  psp_CustomerAdditionalDetails ;	
    struct BillingDetailsStruct*    psp_BillingDetails       ;	
    struct ShippingDetailsStruct*   psp_ShippingDetails      ;	
    struct OrderDetailsStruct*      psp_OrderDetails         ;	
    struct AirlineDetailsStruct*    psp_AirlineDetails       ;	
    struct ArrayOf_RequerimientoStruct_SplitAuthorize_2p_Transactions*  psp_Transactions         ;	
};

struct RespuestaStruct_SplitAuthorize_2p
{
    char*                                psp_ResponseCod          ;	
    char*                                psp_ResponseMsg          ;	
    char*                                psp_ResponseExtended     ;	
    char*                                psp_TransactionId        ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_MerchTxRef           ;	
    char*                                psp_MerchOrderId         ;	
    char*                                psp_PosDateTime          ;	
    char*                                psp_UseMultipleProducts  ;	
    struct ArrayOf_RespuestaStruct_SplitPayOnLine_2p_Transactions*  psp_Transactions         ;	
};

struct VaultReference3pStruct
{
    char*                                CustomerId                     ;	
};

struct RequerimientoStruct_PayOnLine_3p
{
    char*                                psp_Version              ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_TxSource             ;	
    char*                                psp_MerchTxRef           ;	
    char*                                psp_MerchOrderId         ;	
    char*                                psp_MerchAdditionalRef   ;	
    char*                                psp_ReturnURL            ;	
    char*                                psp_FrmLanguage          ;	
    char*                                psp_FrmBackButtonURL     ;	
    char*                                psp_FrmTimeout           ;	
    char*                                psp_Amount               ;	
    char*                                psp_NumPayments          ;	
    char*                                psp_Currency             ;	
    char*                                psp_Country              ;	
    char*                                psp_Product              ;	
    char*                                psp_CustomerMail         ;	
    char*                                psp_CustomerId           ;	
    char*                                psp_MerchantMail         ;	
    char*                                psp_PurchaseDescription  ;	
    char*                                psp_SoftDescriptor       ;	
    char*                                psp_ForceProcessingMethod ;	
    char*                                psp_PosDateTime          ;	
    char*                                psp_Plan                 ;	
    char*                                psp_FirstPaymentDeferral ;	
    char*                                psp_PromotionCode        ;	
    char*                                psp_PresetCardIIN        ;	
    char*                                psp_3dSecureAction       ;	
    char*                                psp_VisaArg_DA_DocType ;	
    char*                                psp_VisaArg_DA_DocNum ;	
    char*                                psp_VisaArg_DA_DoorNum ;	
    char*                                psp_VisaArg_DA_BirthDay ;	
    char*                                psp_VisaArg_DA_Name ;	
    char*                                psp_AmexArg_AVS_Address ;	
    char*                                psp_AmexArg_AVS_PostCode ;	
    char*                                psp_MasterArg_AVS_BirthDay ;	
    char*                                psp_MasterArg_AVS_AdditionalsQtty ;	
    char*                                psp_MasterArg_AVS_PostalCode ;	
    char*                                psp_MasterArg_AVS_BranchEntity ;	
    char*                                psp_SecureHash           ;	
    struct VaultReference3pStruct*  psp_VaultReference       ;	
    struct AmountAdditionalDetailsRequestStruct*  psp_AmountAdditionalDetails ;	
    struct MerchantAdditionalDetailsStruct*  psp_MerchantAdditionalDetails ;	
    struct CustomerAdditionalDetailsStruct*  psp_CustomerAdditionalDetails ;	
    struct BillingDetailsStruct*    psp_BillingDetails       ;	
    struct ShippingDetailsStruct*   psp_ShippingDetails      ;	
    struct OrderDetailsStruct*      psp_OrderDetails         ;	
    struct AirlineDetailsStruct*    psp_AirlineDetails       ;	
};

struct RespuestaStruct_PayOnLine_3p
{
    char*                                psp_ResponseCod          ;	
    char*                                psp_ResponseMsg          ;	
    char*                                psp_ResponseExtended     ;	
    char*                                psp_TransactionId        ;	
    char*                                psp_Session3p            ;	
    char*                                psp_FrontPSP_URL   ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_MerchTxRef           ;	
    char*                                psp_MerchOrderId         ;	
    char*                                psp_MerchAdditionalRef   ;	
    char*                                psp_Amount               ;	
    char*                                psp_NumPayments          ;	
    char*                                psp_PaymentAmount        ;	
    char*                                psp_Currency             ;	
    char*                                psp_Country              ;	
    char*                                psp_Product              ;	
    char*                                psp_CustomerMail         ;	
    char*                                psp_CustomerId           ;	
    char*                                psp_MerchantMail         ;	
    char*                                psp_PosDateTime          ;	
    char*                                psp_Plan                 ;	
    char*                                psp_PromotionCode        ;	
    char*                                psp_PresetCardIIN        ;	
    char*                                psp_FirstPaymentDeferral ;	
    char*                                psp_CreatedAt            ;	
};

struct RequerimientoStruct_SplitPayOnLine_3p_Transactions
{
    char*                                psp_MerchantId           ;	
    char*                                psp_MerchTxRef           ;	
    char*                                psp_MerchAdditionalRef   ;	
    char*                                psp_Product              ;	
    char*                                psp_PromotionCode        ;	
    char*                                psp_PresetCardIIN        ;	
    char*                                psp_Amount               ;	
    char*                                psp_NumPayments          ;	
    char*                                psp_Plan                 ;	
    char*                                psp_FirstPaymentDeferral ;	
    char*                                psp_SoftDescriptor       ;	
    struct AmountAdditionalDetailsRequestStruct*  psp_AmountAdditionalDetails ;	
};

struct RequerimientoStruct_SplitPayOnLine_3p
{
    char*                                psp_Version              ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_TxSource             ;	
    char*                                psp_MerchOrderId         ;	
    char*                                psp_ReturnURL            ;	
    char*                                psp_FrmLanguage          ;	
    char*                                psp_FrmBackButtonURL     ;	
    char*                                psp_FrmTimeout           ;	
    char*                                psp_Amount               ;	
    char*                                psp_Currency             ;	
    char*                                psp_Country              ;	
    char*                                psp_UseMultipleProducts  ;	
    char*                                psp_Product              ;	
    char*                                psp_CustomerMail         ;	
    char*                                psp_CustomerId           ;	
    char*                                psp_MerchantMail         ;	
    char*                                psp_PurchaseDescription  ;	
    char*                                psp_SoftDescriptor       ;	
    char*                                psp_ForceProcessingMethod ;	
    char*                                psp_PosDateTime          ;	
    char*                                psp_PromotionCode        ;	
    char*                                psp_PresetCardIIN        ;	
    char*                                psp_3dSecureAction       ;	
    char*                                psp_VisaArg_DA_DocType ;	
    char*                                psp_VisaArg_DA_DocNum ;	
    char*                                psp_VisaArg_DA_DoorNum ;	
    char*                                psp_VisaArg_DA_BirthDay ;	
    char*                                psp_VisaArg_DA_Name ;	
    char*                                psp_AmexArg_AVS_Address ;	
    char*                                psp_AmexArg_AVS_PostCode ;	
    char*                                psp_MasterArg_AVS_BirthDay ;	
    char*                                psp_MasterArg_AVS_AdditionalsQtty ;	
    char*                                psp_MasterArg_AVS_PostalCode ;	
    char*                                psp_MasterArg_AVS_BranchEntity ;	
    char*                                psp_SecureHash           ;	
    struct VaultReference3pStruct*  psp_VaultReference       ;	
    struct MerchantAdditionalDetailsStruct*  psp_MerchantAdditionalDetails ;	
    struct CustomerAdditionalDetailsStruct*  psp_CustomerAdditionalDetails ;	
    struct BillingDetailsStruct*    psp_BillingDetails       ;	
    struct ShippingDetailsStruct*   psp_ShippingDetails      ;	
    struct OrderDetailsStruct*      psp_OrderDetails         ;	
    struct AirlineDetailsStruct*    psp_AirlineDetails       ;	
    struct ArrayOf_RequerimientoStruct_SplitPayOnLine_3p_Transactions*  psp_Transactions         ;	
};

struct RespuestaStruct_SplitPayOnLine_3p_Transactions
{
    char*                                psp_MerchantId           ;	
    char*                                psp_TransactionId        ;	
    char*                                psp_MerchTxRef           ;	
    char*                                psp_MerchAdditionalRef   ;	
    char*                                psp_Product              ;	
    char*                                psp_PromotionCode        ;	
    char*                                psp_PresetCardIIN        ;	
    char*                                psp_Amount               ;	
    char*                                psp_NumPayments          ;	
    char*                                psp_Plan                 ;	
    char*                                psp_FirstPaymentDeferral ;	
    char*                                psp_SoftDescriptor       ;	
    char*                                psp_CreatedAt            ;	
};

struct RespuestaStruct_SplitPayOnLine_3p
{
    char*                                psp_ResponseCod          ;	
    char*                                psp_ResponseMsg          ;	
    char*                                psp_ResponseExtended     ;	
    char*                                psp_TransactionId        ;	
    char*                                psp_Session3p            ;	
    char*                                psp_FrontPSP_URL   ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_MerchTxRef           ;	
    char*                                psp_MerchOrderId         ;	
    char*                                psp_Amount               ;	
    char*                                psp_Currency             ;	
    char*                                psp_Country              ;	
    char*                                psp_UseMultipleProducts  ;	
    char*                                psp_Product              ;	
    char*                                psp_CustomerMail         ;	
    char*                                psp_CustomerId           ;	
    char*                                psp_MerchantMail         ;	
    char*                                psp_PosDateTime          ;	
    char*                                psp_PromotionCode        ;	
    char*                                psp_PresetCardIIN        ;	
    struct ArrayOf_RespuestaStruct_SplitPayOnLine_3p_Transactions*  psp_Transactions         ;	
};

struct RequerimientoStruct_Authorize_3p
{
    char*                                psp_Version              ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_TxSource             ;	
    char*                                psp_MerchTxRef           ;	
    char*                                psp_MerchOrderId         ;	
    char*                                psp_MerchAdditionalRef   ;	
    char*                                psp_ReturnURL            ;	
    char*                                psp_FrmLanguage          ;	
    char*                                psp_FrmBackButtonURL     ;	
    char*                                psp_FrmTimeout           ;	
    char*                                psp_Amount               ;	
    char*                                psp_NumPayments          ;	
    char*                                psp_Currency             ;	
    char*                                psp_Country              ;	
    char*                                psp_Product              ;	
    char*                                psp_CustomerMail         ;	
    char*                                psp_CustomerId           ;	
    char*                                psp_MerchantMail         ;	
    char*                                psp_PurchaseDescription  ;	
    char*                                psp_SoftDescriptor       ;	
    char*                                psp_ForceProcessingMethod ;	
    char*                                psp_PosDateTime          ;	
    char*                                psp_Plan                 ;	
    char*                                psp_PromotionCode        ;	
    char*                                psp_PresetCardIIN        ;	
    char*                                psp_3dSecureAction       ;	
    char*                                psp_VisaArg_DA_DocType ;	
    char*                                psp_VisaArg_DA_DocNum ;	
    char*                                psp_VisaArg_DA_DoorNum ;	
    char*                                psp_VisaArg_DA_BirthDay ;	
    char*                                psp_VisaArg_DA_Name ;	
    char*                                psp_AmexArg_AVS_Address ;	
    char*                                psp_AmexArg_AVS_PostCode ;	
    char*                                psp_MasterArg_AVS_BirthDay ;	
    char*                                psp_MasterArg_AVS_AdditionalsQtty ;	
    char*                                psp_MasterArg_AVS_PostalCode ;	
    char*                                psp_MasterArg_AVS_BranchEntity ;	
    char*                                psp_SecureHash           ;	
    struct VaultReference3pStruct*  psp_VaultReference       ;	
    struct AmountAdditionalDetailsRequestStruct*  psp_AmountAdditionalDetails ;	
    struct MerchantAdditionalDetailsStruct*  psp_MerchantAdditionalDetails ;	
    struct CustomerAdditionalDetailsStruct*  psp_CustomerAdditionalDetails ;	
    struct BillingDetailsStruct*    psp_BillingDetails       ;	
    struct ShippingDetailsStruct*   psp_ShippingDetails      ;	
    struct OrderDetailsStruct*      psp_OrderDetails         ;	
    struct AirlineDetailsStruct*    psp_AirlineDetails       ;	
};

struct RespuestaStruct_Authorize_3p
{
    char*                                psp_ResponseCod          ;	
    char*                                psp_ResponseMsg          ;	
    char*                                psp_ResponseExtended     ;	
    char*                                psp_TransactionId        ;	
    char*                                psp_Session3p            ;	
    char*                                psp_FrontPSP_URL   ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_MerchTxRef           ;	
    char*                                psp_MerchOrderId         ;	
    char*                                psp_MerchAdditionalRef   ;	
    char*                                psp_Amount               ;	
    char*                                psp_NumPayments          ;	
    char*                                psp_PaymentAmount        ;	
    char*                                psp_Currency             ;	
    char*                                psp_Country              ;	
    char*                                psp_Product              ;	
    char*                                psp_CustomerMail         ;	
    char*                                psp_CustomerId           ;	
    char*                                psp_MerchantMail         ;	
    char*                                psp_PosDateTime          ;	
    char*                                psp_Plan                 ;	
    char*                                psp_PromotionCode        ;	
    char*                                psp_PresetCardIIN        ;	
    char*                                psp_CreatedAt            ;	
};

struct RequerimientoStruct_SplitAuthorize_3p_Transactions
{
    char*                                psp_MerchantId           ;	
    char*                                psp_MerchTxRef           ;	
    char*                                psp_MerchAdditionalRef   ;	
    char*                                psp_Product              ;	
    char*                                psp_PromotionCode        ;	
    char*                                psp_PresetCardIIN        ;	
    char*                                psp_Amount               ;	
    char*                                psp_NumPayments          ;	
    char*                                psp_Plan                 ;	
    char*                                psp_SoftDescriptor       ;	
    struct AmountAdditionalDetailsRequestStruct*  psp_AmountAdditionalDetails ;	
};

struct RequerimientoStruct_SplitAuthorize_3p
{
    char*                                psp_Version              ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_TxSource             ;	
    char*                                psp_MerchOrderId         ;	
    char*                                psp_ReturnURL            ;	
    char*                                psp_FrmLanguage          ;	
    char*                                psp_FrmBackButtonURL     ;	
    char*                                psp_FrmTimeout           ;	
    char*                                psp_Amount               ;	
    char*                                psp_Currency             ;	
    char*                                psp_Country              ;	
    char*                                psp_UseMultipleProducts  ;	
    char*                                psp_Product              ;	
    char*                                psp_CustomerMail         ;	
    char*                                psp_CustomerId           ;	
    char*                                psp_MerchantMail         ;	
    char*                                psp_PurchaseDescription  ;	
    char*                                psp_SoftDescriptor       ;	
    char*                                psp_ForceProcessingMethod ;	
    char*                                psp_PosDateTime          ;	
    char*                                psp_PromotionCode        ;	
    char*                                psp_PresetCardIIN        ;	
    char*                                psp_3dSecureAction       ;	
    char*                                psp_VisaArg_DA_DocType ;	
    char*                                psp_VisaArg_DA_DocNum ;	
    char*                                psp_VisaArg_DA_DoorNum ;	
    char*                                psp_VisaArg_DA_BirthDay ;	
    char*                                psp_VisaArg_DA_Name ;	
    char*                                psp_AmexArg_AVS_Address ;	
    char*                                psp_AmexArg_AVS_PostCode ;	
    char*                                psp_MasterArg_AVS_BirthDay ;	
    char*                                psp_MasterArg_AVS_AdditionalsQtty ;	
    char*                                psp_MasterArg_AVS_PostalCode ;	
    char*                                psp_MasterArg_AVS_BranchEntity ;	
    char*                                psp_SecureHash           ;	
    struct VaultReference3pStruct*  psp_VaultReference       ;	
    struct MerchantAdditionalDetailsStruct*  psp_MerchantAdditionalDetails ;	
    struct CustomerAdditionalDetailsStruct*  psp_CustomerAdditionalDetails ;	
    struct BillingDetailsStruct*    psp_BillingDetails       ;	
    struct ShippingDetailsStruct*   psp_ShippingDetails      ;	
    struct OrderDetailsStruct*      psp_OrderDetails         ;	
    struct AirlineDetailsStruct*    psp_AirlineDetails       ;	
    struct ArrayOf_RequerimientoStruct_SplitAuthorize_3p_Transactions*  psp_Transactions         ;	
};

struct RespuestaStruct_SplitAuthorize_3p_Transactions
{
    char*                                psp_MerchantId           ;	
    char*                                psp_TransactionId        ;	
    char*                                psp_MerchTxRef           ;	
    char*                                psp_MerchAdditionalRef   ;	
    char*                                psp_Product              ;	
    char*                                psp_PromotionCode        ;	
    char*                                psp_PresetCardIIN        ;	
    char*                                psp_Amount               ;	
    char*                                psp_NumPayments          ;	
    char*                                psp_Plan                 ;	
    char*                                psp_FirstPaymentDeferral ;	
    char*                                psp_SoftDescriptor       ;	
    char*                                psp_CreatedAt            ;	
};

struct RespuestaStruct_SplitAuthorize_3p
{
    char*                                psp_ResponseCod          ;	
    char*                                psp_ResponseMsg          ;	
    char*                                psp_ResponseExtended     ;	
    char*                                psp_TransactionId        ;	
    char*                                psp_Session3p            ;	
    char*                                psp_FrontPSP_URL   ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_MerchTxRef           ;	
    char*                                psp_MerchOrderId         ;	
    char*                                psp_Amount               ;	
    char*                                psp_Currency             ;	
    char*                                psp_Country              ;	
    char*                                psp_UseMultipleProducts  ;	
    char*                                psp_Product              ;	
    char*                                psp_CustomerMail         ;	
    char*                                psp_CustomerId           ;	
    char*                                psp_MerchantMail         ;	
    char*                                psp_PosDateTime          ;	
    char*                                psp_PromotionCode        ;	
    char*                                psp_PresetCardIIN        ;	
    struct ArrayOf_RespuestaStruct_SplitAuthorize_3p_Transactions*  psp_Transactions         ;	
};

struct RequerimientoStruct_BankPayment_3p
{
    char*                                psp_Version              ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_TxSource             ;	
    char*                                psp_MerchTxRef           ;	
    char*                                psp_MerchOrderId         ;	
    char*                                psp_MerchAdditionalRef   ;	
    char*                                psp_ReturnURL            ;	
    char*                                psp_FrmLanguage          ;	
    char*                                psp_FrmBackButtonURL     ;	
    char*                                psp_FrmTimeout           ;	
    char*                                psp_ScreenDescription    ;	
    char*                                psp_TicketDescription    ;	
    char*                                psp_Currency             ;	
    char*                                psp_Country              ;	
    char*                                psp_Product              ;	
    char*                                psp_Amount1              ;	
    char*                                psp_ExpDate1             ;	
    char*                                psp_Amount2              ;	
    char*                                psp_ExpDate2             ;	
    char*                                psp_Amount3              ;	
    char*                                psp_ExpDate3             ;	
    char*                                psp_MinAmount            ;	
    char*                                psp_ExpTime              ;	
    char*                                psp_ExpMark              ;	
    char*                                psp_CustomerMail         ;	
    char*                                psp_CustomerId           ;	
    char*                                psp_MerchantMail         ;	
    char*                                psp_ForceProcessingMethod ;	
    char*                                psp_PosDateTime          ;	
    char*                                psp_SecureHash           ;	
    struct AmountAdditionalDetailsRequestStruct*  psp_AmountAdditionalDetails ;	
    struct MerchantAdditionalDetailsStruct*  psp_MerchantAdditionalDetails ;	
    struct CustomerAdditionalDetailsStruct*  psp_CustomerAdditionalDetails ;	
    struct BillingDetailsStruct*    psp_BillingDetails       ;	
    struct ShippingDetailsStruct*   psp_ShippingDetails      ;	
    struct OrderDetailsStruct*      psp_OrderDetails         ;	
    struct AirlineDetailsStruct*    psp_AirlineDetails       ;	
};

struct RespuestaStruct_BankPayment_3p
{
    char*                                psp_ResponseCod          ;	
    char*                                psp_ResponseMsg          ;	
    char*                                psp_ResponseExtended     ;	
    char*                                psp_TransactionId        ;	
    char*                                psp_Session3p            ;	
    char*                                psp_FrontPSP_URL   ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_MerchTxRef           ;	
    char*                                psp_MerchOrderId         ;	
    char*                                psp_MerchAdditionalRef   ;	
    char*                                psp_ScreenDescription    ;	
    char*                                psp_TicketDescription    ;	
    char*                                psp_Currency             ;	
    char*                                psp_Country              ;	
    char*                                psp_Product              ;	
    char*                                psp_Amount1              ;	
    char*                                psp_ExpDate1             ;	
    char*                                psp_Amount2              ;	
    char*                                psp_ExpDate2             ;	
    char*                                psp_Amount3              ;	
    char*                                psp_ExpDate3             ;	
    char*                                psp_MinAmount            ;	
    char*                                psp_ExpTime              ;	
    char*                                psp_ExpMark              ;	
    char*                                psp_CustomerMail         ;	
    char*                                psp_CustomerId           ;	
    char*                                psp_MerchantMail         ;	
    char*                                psp_PosDateTime          ;	
    char*                                psp_CreatedAt            ;	
};

struct RequerimientoStruct_CashPayment_3p
{
    char*                                psp_Version              ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_TxSource             ;	
    char*                                psp_MerchTxRef           ;	
    char*                                psp_MerchOrderId         ;	
    char*                                psp_MerchAdditionalRef   ;	
    char*                                psp_ReturnURL            ;	
    char*                                psp_FrmLanguage          ;	
    char*                                psp_FrmBackButtonURL     ;	
    char*                                psp_Amount               ;	
    char*                                psp_Currency             ;	
    char*                                psp_Country              ;	
    char*                                psp_Product              ;	
    char*                                psp_FirstExpDate         ;	
    char*                                psp_DaysUntilSecondExpDate ;	
    char*                                psp_SurchargeAmount      ;	
    char*                                psp_DaysAvailableToPay   ;	
    char*                                psp_CustomerMail         ;	
    char*                                psp_CustomerId           ;	
    char*                                psp_MerchantMail         ;	
    char*                                psp_CustomerDocNum       ;	
    char*                                psp_PurchaseDescription  ;	
    char*                                psp_ForceProcessingMethod ;	
    char*                                psp_PosDateTime          ;	
    char*                                psp_SecureHash           ;	
    struct AmountAdditionalDetailsRequestStruct*  psp_AmountAdditionalDetails ;	
    struct MerchantAdditionalDetailsStruct*  psp_MerchantAdditionalDetails ;	
    struct CustomerAdditionalDetailsStruct*  psp_CustomerAdditionalDetails ;	
    struct BillingDetailsStruct*    psp_BillingDetails       ;	
    struct ShippingDetailsStruct*   psp_ShippingDetails      ;	
    struct OrderDetailsStruct*      psp_OrderDetails         ;	
    struct AirlineDetailsStruct*    psp_AirlineDetails       ;	
};

struct RespuestaStruct_CashPayment_3p
{
    char*                                psp_ResponseCod          ;	
    char*                                psp_ResponseMsg          ;	
    char*                                psp_ResponseExtended     ;	
    char*                                psp_TransactionId        ;	
    char*                                psp_Session3p            ;	
    char*                                psp_FrontPSP_URL   ;	
    char*                                psp_BarCode              ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_MerchTxRef           ;	
    char*                                psp_MerchOrderId         ;	
    char*                                psp_MerchAdditionalRef   ;	
    char*                                psp_Amount               ;	
    char*                                psp_Currency             ;	
    char*                                psp_Country              ;	
    char*                                psp_Product              ;	
    char*                                psp_FirstExpDate         ;	
    char*                                psp_DaysUntilSecondExpDate ;	
    char*                                psp_SurchargeAmount      ;	
    char*                                psp_DaysAvailableToPay   ;	
    char*                                psp_CustomerMail         ;	
    char*                                psp_CustomerId           ;	
    char*                                psp_MerchantMail         ;	
    char*                                psp_PosDateTime          ;	
    char*                                psp_CreatedAt            ;	
};

struct RequerimientoStruct_Capture
{
    char*                                psp_Version              ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_TxSource             ;	
    char*                                psp_MerchTxRef           ;	
    char*                                psp_MerchAdditionalRef   ;	
    char*                                psp_TransactionId_Orig ;	
    char*                                psp_AmountToCapture      ;	
    char*                                psp_UserId               ;	
    char*                                psp_PosDateTime          ;	
    char*                                psp_SecureHash           ;	
    struct AmountAdditionalDetailsRequestStruct*  psp_AmountAdditionalDetails ;	
};

struct RespuestaStruct_Capture
{
    char*                                psp_ResponseCod          ;	
    char*                                psp_ResponseMsg          ;	
    char*                                psp_ResponseExtended     ;	
    char*                                psp_TransactionId        ;	
    char*                                psp_TransactionId_Orig ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_MerchTxRef           ;	
    char*                                psp_MerchOrderId         ;	
    char*                                psp_MerchAdditionalRef   ;	
    char*                                psp_CapturedAmount       ;	
    char*                                psp_AuthorizedAmount_Orig ;	
    char*                                psp_AuthorizationCode    ;	
    char*                                psp_BatchNro             ;	
    char*                                psp_TicketNumber         ;	
    char*                                psp_SequenceNumber       ;	
    char*                                psp_Product              ;	
    char*                                psp_ClTrnId              ;	
    char*                                psp_ClExternalMerchant   ;	
    char*                                psp_ClExternalTerminal   ;	
    char*                                psp_ClResponseCod        ;	
    char*                                psp_ClResponseMsg        ;	
    char*                                psp_PosDateTime          ;	
    char*                                psp_CreatedAt            ;	
    struct AmountAdditionalDetailsResponseStruct*  psp_AmountAdditionalDetails ;	
};

struct RequerimientoStruct_Refund
{
    char*                                psp_Version              ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_TxSource             ;	
    char*                                psp_MerchTxRef           ;	
    char*                                psp_MerchAdditionalRef   ;	
    char*                                psp_TransactionId_Orig ;	
    char*                                psp_AmountToRefund       ;	
    char*                                psp_CardNumber           ;	
    char*                                psp_CardExpDate          ;	
    char*                                psp_CardSecurityCode     ;	
    char*                                psp_UserId               ;	
    char*                                psp_PosDateTime          ;	
    char*                                psp_SecureHash           ;	
};

struct RespuestaStruct_Refund
{
    char*                                psp_ResponseCod          ;	
    char*                                psp_ResponseMsg          ;	
    char*                                psp_ResponseExtended     ;	
    char*                                psp_TransactionId        ;	
    char*                                psp_TransactionId_Orig ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_MerchTxRef           ;	
    char*                                psp_MerchOrderId         ;	
    char*                                psp_MerchAdditionalRef   ;	
    char*                                psp_RefundedAmount       ;	
    char*                                psp_CapturedAmount_Orig ;	
    char*                                psp_AuthorizationCode    ;	
    char*                                psp_BatchNro             ;	
    char*                                psp_TicketNumber         ;	
    char*                                psp_SequenceNumber       ;	
    char*                                psp_Product              ;	
    char*                                psp_ClTrnId              ;	
    char*                                psp_ClExternalMerchant   ;	
    char*                                psp_ClExternalTerminal   ;	
    char*                                psp_ClResponseCod        ;	
    char*                                psp_ClResponseMsg        ;	
    char*                                psp_PosDateTime          ;	
    char*                                psp_CreatedAt            ;	
};

struct RequerimientoStruct_GetInstallmentsOptions
{
    char*                                psp_Version              ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_Amount               ;	
    char*                                psp_Product              ;	
    char*                                psp_Currency             ;	
    char*                                psp_Country              ;	
    char*                                psp_NumPayments          ;	
    char*                                psp_PaymentMethodToken   ;	
    char*                                psp_PosDateTime          ;	
    char*                                psp_SecureHash           ;	
    char*                                psp_ClientSession        ;	
};

struct InstallmentsOptionsStruct
{
    char*                                NumPayments                    ;	
    char*                                InstallmentAmount              ;	
    char*                                InterestRate                   ;	
};

struct RespuestaStruct_GetInstallmentsOptions
{
    char*                                psp_ResponseCod          ;	
    char*                                psp_ResponseMsg          ;	
    char*                                psp_ResponseExtended     ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_Amount               ;	
    char*                                psp_Product              ;	
    char*                                psp_Currency             ;	
    char*                                psp_Country              ;	
    char*                                psp_NumPayments          ;	
    struct ArrayOf_InstallmentsOptionsStruct*  psp_InstallmentsOptions  ;	
    char*                                psp_PosDateTime          ;	
};

struct CardInputDetailsStruct
{
    char*                                Number                         ;	
    char*                                ExpirationDate                 ;	
    char*                                SecurityCode                   ;	
    char*                                HolderName                     ;	
};

struct RequerimientoStruct_CreatePaymentMethodToken
{
    char*                                psp_Version              ;	
    char*                                psp_MerchantId           ;	
    struct CardInputDetailsStruct*  psp_CardInputDetails     ;	
    struct PersonStruct*            psp_Person               ;	
    struct AddressStruct*           psp_Address              ;	
    char*                                psp_ClientSession        ;	
};

struct CardOutputDetailsStruct
{
    char*                                Number                         ;	
    char*                                ExpirationDate                 ;	
    char*                                ExpirationYear                 ;	
    char*                                ExpirationMonth                ;	
    char*                                HolderName                     ;	
    char*                                IIN                            ;	
    char*                                Last4                          ;	
    char*                                NumberLength                   ;	
    char*                                MaskedNumber                   ;	
    char*                                MaskedNumberAlternative        ;	
};

struct RespuestaStruct_CreatePaymentMethodToken
{
    char*                                psp_ResponseCod          ;	
    char*                                psp_ResponseMsg          ;	
    char*                                psp_ResponseExtended     ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_PaymentMethodToken   ;	
    char*                                psp_Product              ;	
    struct CardOutputDetailsStruct*  psp_CardOutputDetails    ;	
    struct PersonStruct*            psp_Person               ;	
    struct AddressStruct*           psp_Address              ;	
    char*                                psp_AlreadyUsed          ;	
    char*                                psp_CreatedAt            ;	
    char*                                psp_UpdatedAt            ;	
};

struct RequerimientoStruct_RetrievePaymentMethodToken
{
    char*                                psp_Version              ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_PaymentMethodToken   ;	
    char*                                psp_ClientSession        ;	
};

struct RespuestaStruct_RetrievePaymentMethodToken
{
    char*                                psp_ResponseCod          ;	
    char*                                psp_ResponseMsg          ;	
    char*                                psp_ResponseExtended     ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_PaymentMethodToken   ;	
    char*                                psp_Product              ;	
    struct CardOutputDetailsStruct*  psp_CardOutputDetails    ;	
    struct PersonStruct*            psp_Person               ;	
    struct AddressStruct*           psp_Address              ;	
    char*                                psp_AlreadyUsed          ;	
    char*                                psp_CreatedAt            ;	
    char*                                psp_UpdatedAt            ;	
};

struct RequerimientoStruct_RecachePaymentMethodToken
{
    char*                                psp_Version              ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_PaymentMethodId      ;	
    char*                                psp_CardSecurityCode     ;	
    struct PersonStruct*            psp_Person               ;	
    struct AddressStruct*           psp_Address              ;	
    char*                                psp_ClientSession        ;	
};

struct RespuestaStruct_RecachePaymentMethodToken
{
    char*                                psp_ResponseCod          ;	
    char*                                psp_ResponseMsg          ;	
    char*                                psp_ResponseExtended     ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_PaymentMethodToken   ;	
    char*                                psp_Product              ;	
    struct CardOutputDetailsStruct*  psp_CardOutputDetails    ;	
    struct PersonStruct*            psp_Person               ;	
    struct AddressStruct*           psp_Address              ;	
    char*                                psp_AlreadyUsed          ;	
    char*                                psp_CreatedAt            ;	
    char*                                psp_UpdatedAt            ;	
};

struct RequerimientoStruct_CreateClientSession
{
    char*                                psp_Version              ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_CustomerId           ;	
    char*                                psp_PosDateTime          ;	
    char*                                psp_SecureHash           ;	
};

struct RespuestaStruct_CreateClientSession
{
    char*                                psp_ResponseCod          ;	
    char*                                psp_ResponseMsg          ;	
    char*                                psp_ResponseExtended     ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_ClientSession        ;	
    char*                                psp_PosDateTime          ;	
    char*                                psp_CreatedAt            ;	
};

struct PaymentMethodInputDetailsStruct
{
    char*                                PaymentMethodToken             ;	
    char*                                PaymentMethodTag               ;	
    struct CardInputDetailsStruct*  CardInputDetails               ;	
    struct PersonStruct*            Person                         ;	
    struct AddressStruct*           Address                        ;	
};

struct RequerimientoStruct_CreatePaymentMethod
{
    char*                                psp_Version              ;	
    char*                                psp_MerchantId           ;	
    struct PaymentMethodInputDetailsStruct*  psp_PaymentMethod        ;	
    char*                                psp_CustomerId           ;	
    char*                                psp_SetAsCustomerDefault ;	
    char*                                psp_PosDateTime          ;	
    char*                                psp_SecureHash           ;	
};

struct PaymentMethodOutputDetailsStruct
{
    char*                                PaymentMethodId                ;	
    char*                                PaymentMethodTag               ;	
    char*                                Product                        ;	
    struct CardOutputDetailsStruct*  CardOutputDetails              ;	
    char*                                FingerPrint                    ;	
    struct PersonStruct*            Person                         ;	
    struct AddressStruct*           Address                        ;	
    char*                                CreatedAt                      ;	
    char*                                UpdatedAt                      ;	
};

struct RespuestaStruct_CreatePaymentMethod
{
    char*                                psp_ResponseCod          ;	
    char*                                psp_ResponseMsg          ;	
    char*                                psp_ResponseExtended     ;	
    char*                                psp_MerchantId           ;	
    struct PaymentMethodOutputDetailsStruct*  psp_PaymentMethod        ;	
    char*                                psp_CustomerId           ;	
    char*                                psp_PosDateTime          ;	
};

struct RequerimientoStruct_CreatePaymentMethodFromPayment
{
    char*                                psp_Version              ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_TransactionId        ;	
    char*                                psp_PaymentMethodTag     ;	
    char*                                psp_CustomerId           ;	
    char*                                psp_SetAsCustomerDefault ;	
    char*                                psp_PosDateTime          ;	
    char*                                psp_SecureHash           ;	
};

struct RespuestaStruct_CreatePaymentMethodFromPayment
{
    char*                                psp_ResponseCod          ;	
    char*                                psp_ResponseMsg          ;	
    char*                                psp_ResponseExtended     ;	
    char*                                psp_MerchantId           ;	
    struct PaymentMethodOutputDetailsStruct*  psp_PaymentMethod        ;	
    char*                                psp_CustomerId           ;	
    char*                                psp_PosDateTime          ;	
};

struct RequerimientoStruct_RetrievePaymentMethod
{
    char*                                psp_Version              ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_PaymentMethodId      ;	
    char*                                psp_PosDateTime          ;	
    char*                                psp_SecureHash           ;	
};

struct RespuestaStruct_RetrievePaymentMethod
{
    char*                                psp_ResponseCod          ;	
    char*                                psp_ResponseMsg          ;	
    char*                                psp_ResponseExtended     ;	
    char*                                psp_MerchantId           ;	
    struct PaymentMethodOutputDetailsStruct*  psp_PaymentMethod        ;	
    char*                                psp_CustomerId           ;	
    char*                                psp_PosDateTime          ;	
};

struct CardInputUpdateDetailsStruct
{
    char*                                ExpirationDate                 ;	
    char*                                HolderName                     ;	
};

struct RequerimientoStruct_UpdatePaymentMethod
{
    char*                                psp_Version              ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_PaymentMethodId      ;	
    char*                                psp_PaymentMethodTag     ;	
    struct CardInputUpdateDetailsStruct*  psp_CardInputDetails     ;	
    struct PersonStruct*            psp_Person               ;	
    struct AddressStruct*           psp_Address              ;	
    char*                                psp_PosDateTime          ;	
    char*                                psp_SecureHash           ;	
};

struct RespuestaStruct_UpdatePaymentMethod
{
    char*                                psp_ResponseCod          ;	
    char*                                psp_ResponseMsg          ;	
    char*                                psp_ResponseExtended     ;	
    char*                                psp_MerchantId           ;	
    struct PaymentMethodOutputDetailsStruct*  psp_PaymentMethod        ;	
    char*                                psp_CustomerId           ;	
    char*                                psp_PosDateTime          ;	
};

struct RequerimientoStruct_DeletePaymentMethod
{
    char*                                psp_Version              ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_PaymentMethodId      ;	
    char*                                psp_PosDateTime          ;	
    char*                                psp_SecureHash           ;	
};

struct RespuestaStruct_DeletePaymentMethod
{
    char*                                psp_ResponseCod          ;	
    char*                                psp_ResponseMsg          ;	
    char*                                psp_ResponseExtended     ;	
    char*                                psp_MerchantId           ;	
    struct PaymentMethodOutputDetailsStruct*  psp_PaymentMethod        ;	
    char*                                psp_CustomerId           ;	
    char*                                psp_PosDateTime          ;	
};

struct RequerimientoStruct_CreateCustomer
{
    char*                                psp_Version              ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_EmailAddress         ;	
    char*                                psp_AlternativeEmailAddress ;	
    char*                                psp_AccountID            ;	
    char*                                psp_AccountCreatedAt     ;	
    struct PersonStruct*            psp_Person               ;	
    struct AddressStruct*           psp_Address              ;	
    struct PaymentMethodInputDetailsStruct*  psp_PaymentMethod        ;	
    char*                                psp_PosDateTime          ;	
    char*                                psp_SecureHash           ;	
};

struct PaymentMethodsOutputDetailsStruct
{
    char*                                PaymentMethodId                ;	
    char*                                PaymentMethodTag               ;	
    char*                                Product                        ;	
    struct CardOutputDetailsStruct*  CardOutputDetails              ;	
    char*                                FingerPrint                    ;	
    struct PersonStruct*            Person                         ;	
    struct AddressStruct*           Address                        ;	
    char*                                CreatedAt                      ;	
    char*                                UpdatedAt                      ;	
};

struct RespuestaStruct_CreateCustomer
{
    char*                                psp_ResponseCod          ;	
    char*                                psp_ResponseMsg          ;	
    char*                                psp_ResponseExtended     ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_CustomerId           ;	
    char*                                psp_EmailAddress         ;	
    char*                                psp_AlternativeEmailAddress ;	
    char*                                psp_AccountID            ;	
    char*                                psp_AccountCreatedAt     ;	
    struct PersonStruct*            psp_Person               ;	
    struct AddressStruct*           psp_Address              ;	
    char*                                psp_DefaultPaymentMethodId ;	
    struct ArrayOf_PaymentMethodsOutputDetailsStruct*  psp_PaymentMethods       ;	
    char*                                psp_PosDateTime          ;	
};

struct RequerimientoStruct_RetrieveCustomer
{
    char*                                psp_Version              ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_CustomerId           ;	
    char*                                psp_PosDateTime          ;	
    char*                                psp_SecureHash           ;	
};

struct RespuestaStruct_RetrieveCustomer
{
    char*                                psp_ResponseCod          ;	
    char*                                psp_ResponseMsg          ;	
    char*                                psp_ResponseExtended     ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_CustomerId           ;	
    char*                                psp_EmailAddress         ;	
    char*                                psp_AlternativeEmailAddress ;	
    char*                                psp_AccountID            ;	
    char*                                psp_AccountCreatedAt     ;	
    struct PersonStruct*            psp_Person               ;	
    struct AddressStruct*           psp_Address              ;	
    char*                                psp_DefaultPaymentMethodId ;	
    struct ArrayOf_PaymentMethodsOutputDetailsStruct*  psp_PaymentMethods       ;	
    char*                                psp_PosDateTime          ;	
};

struct RequerimientoStruct_UpdateCustomer
{
    char*                                psp_Version              ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_CustomerId           ;	
    char*                                psp_EmailAddress         ;	
    char*                                psp_AlternativeEmailAddress ;	
    char*                                psp_AccountID            ;	
    char*                                psp_AccountCreatedAt     ;	
    struct PersonStruct*            psp_Person               ;	
    struct AddressStruct*           psp_Address              ;	
    char*                                psp_DefaultPaymentMethodId ;	
    struct PaymentMethodInputDetailsStruct*  psp_PaymentMethod        ;	
    char*                                psp_PosDateTime          ;	
    char*                                psp_SecureHash           ;	
};

struct RespuestaStruct_UpdateCustomer
{
    char*                                psp_ResponseCod          ;	
    char*                                psp_ResponseMsg          ;	
    char*                                psp_ResponseExtended     ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_CustomerId           ;	
    char*                                psp_EmailAddress         ;	
    char*                                psp_AlternativeEmailAddress ;	
    char*                                psp_AccountID            ;	
    char*                                psp_AccountCreatedAt     ;	
    struct PersonStruct*            psp_Person               ;	
    struct AddressStruct*           psp_Address              ;	
    char*                                psp_DefaultPaymentMethodId ;	
    struct ArrayOf_PaymentMethodsOutputDetailsStruct*  psp_PaymentMethods       ;	
    char*                                psp_PosDateTime          ;	
};

struct RequerimientoStruct_DeleteCustomer
{
    char*                                psp_Version              ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_CustomerId           ;	
    char*                                psp_PosDateTime          ;	
    char*                                psp_SecureHash           ;	
};

struct RespuestaStruct_DeleteCustomer
{
    char*                                psp_ResponseCod          ;	
    char*                                psp_ResponseMsg          ;	
    char*                                psp_ResponseExtended     ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_CustomerId           ;	
    char*                                psp_EmailAddress         ;	
    char*                                psp_AlternativeEmailAddress ;	
    char*                                psp_AccountID            ;	
    char*                                psp_AccountCreatedAt     ;	
    struct PersonStruct*            psp_Person               ;	
    struct AddressStruct*           psp_Address              ;	
    char*                                psp_DefaultPaymentMethodId ;	
    struct ArrayOf_PaymentMethodsOutputDetailsStruct*  psp_PaymentMethods       ;	
    char*                                psp_PosDateTime          ;	
};

struct RequerimientoStruct_SimpleQueryTx
{
    char*                                psp_Version              ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_QueryCriteria        ;	
    char*                                psp_QueryCriteriaId      ;	
    char*                                psp_PosDateTime          ;	
    char*                                psp_SecureHash           ;	
};

struct RespuestaStruct_SimpleQueryTx_Transactions
{
    char*                                psp_ResponseCod          ;	
    char*                                psp_ResponseMsg          ;	
    char*                                psp_ResponseExtended     ;	
    char*                                psp_TransactionId        ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_TxSource             ;	
    char*                                psp_Operation            ;	
    char*                                psp_MerchTxRef           ;	
    char*                                psp_MerchOrderId         ;	
    char*                                psp_MerchAdditionalRef   ;	
    char*                                psp_Amount               ;	
    char*                                psp_NumPayments          ;	
    char*                                psp_PaymentAmount        ;	
    char*                                psp_FirstPaymentDeferral ;	
    char*                                psp_Currency             ;	
    char*                                psp_Country              ;	
    char*                                psp_Product              ;	
    char*                                psp_AuthorizationCode    ;	
    char*                                psp_BatchNro             ;	
    char*                                psp_SequenceNumber       ;	
    char*                                psp_TicketNumber         ;	
    char*                                psp_CardNumber_FSD ;	
    char*                                psp_CardNumber_LFD ;	
    char*                                psp_CardMask             ;	
    char*                                psp_CardHolderName       ;	
    char*                                psp_CustomerMail         ;	
    char*                                psp_CustomerId           ;	
    char*                                psp_CustomerIpAddress    ;	
    char*                                psp_CustomerHttpUserAgent ;	
    char*                                psp_MerchantMail         ;	
    char*                                psp_ClTrnId              ;	
    char*                                psp_ClExternalMerchant   ;	
    char*                                psp_ClExternalTerminal   ;	
    char*                                psp_ClResponseCod        ;	
    char*                                psp_ClResponseMsg        ;	
    char*                                psp_PosDateTime          ;	
    char*                                psp_PurchaseDescription  ;	
    char*                                psp_SoftDescriptor       ;	
    char*                                psp_Plan                 ;	
    char*                                psp_VisaArg_VBV_Secured ;	
    char*                                psp_3dSecure_XID   ;	
    char*                                psp_3dSecure_CAVV  ;	
    char*                                psp_3dSecure_Eci   ;	
    char*                                psp_3dSecure_EciMsg ;	
    char*                                psp_3dSecure_Secured ;	
    char*                                psp_VisaArg_DA_Result ;	
    char*                                psp_AmexArg_AVS_Result ;	
    char*                                psp_MasterArg_AVS_Result ;	
    char*                                psp_CreatedAt            ;	
    struct AmountAdditionalDetailsResponseStruct*  psp_AmountAdditionalDetails ;	
    struct FraudScreeningResultStruct*  psp_FraudScreeningResult ;	
    struct VerificationServicesResultStruct*  psp_VerificationServicesResult ;	
    struct MerchantAdditionalDetailsStruct*  psp_MerchantAdditionalDetails ;	
    struct CustomerAdditionalDetailsStruct*  psp_CustomerAdditionalDetails ;	
    struct BillingDetailsStruct*    psp_BillingDetails       ;	
    struct ShippingDetailsStruct*   psp_ShippingDetails      ;	
    struct OrderDetailsStruct*      psp_OrderDetails         ;	
    struct AirlineDetailsStruct*    psp_AirlineDetails       ;	
};

struct RespuestaStruct_SimpleQueryTx
{
    char*                                psp_ResponseCod          ;	
    char*                                psp_ResponseMsg          ;	
    char*                                psp_ResponseExtended     ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_QueryCriteria        ;	
    char*                                psp_QueryCriteriaId      ;	
    char*                                psp_PosDateTime          ;	
    struct RespuestaStruct_SimpleQueryTx_Transactions*  psp_Transaction          ;	
};

struct RequerimientoStruct_QueryCardNumber
{
    char*                                psp_Version              ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_QueryCriteria        ;	
    char*                                psp_QueryCriteriaId      ;	
    char*                                psp_PosDateTime          ;	
    char*                                psp_SecureHash           ;	
};

struct RespuestaStruct_QueryCardNumber
{
    char*                                psp_ResponseCod          ;	
    char*                                psp_ResponseMsg          ;	
    char*                                psp_ResponseExtended     ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_QueryCriteria        ;	
    char*                                psp_QueryCriteriaId      ;	
    char*                                psp_PosDateTime          ;	
    char*                                psp_CardNumber           ;	
};

struct RequerimientoStruct_QueryCardDetails
{
    char*                                psp_Version              ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_QueryCriteria        ;	
    char*                                psp_QueryCriteriaId      ;	
    char*                                psp_PosDateTime          ;	
    char*                                psp_SecureHash           ;	
};

struct RespuestaStruct_QueryCardDetails
{
    char*                                psp_ResponseCod          ;	
    char*                                psp_ResponseMsg          ;	
    char*                                psp_ResponseExtended     ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_QueryCriteria        ;	
    char*                                psp_QueryCriteriaId      ;	
    char*                                psp_PosDateTime          ;	
    struct CardOutputDetailsStruct*  psp_CardOutputDetails    ;	
};

struct RequerimientoStruct_QueryTxs
{
    char*                                psp_Version              ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_QueryCriteria        ;	
    char*                                psp_QueryCriteriaId      ;	
    char*                                psp_PosDateTime          ;	
    char*                                psp_SecureHash           ;	
};

struct RespuestaStruct_QueryTxs_Transactions
{
    char*                                psp_ResponseCod          ;	
    char*                                psp_ResponseMsg          ;	
    char*                                psp_ResponseExtended     ;	
    char*                                psp_TransactionId        ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_TxSource             ;	
    char*                                psp_Operation            ;	
    char*                                psp_MerchTxRef           ;	
    char*                                psp_MerchOrderId         ;	
    char*                                psp_MerchAdditionalRef   ;	
    char*                                psp_Amount               ;	
    char*                                psp_NumPayments          ;	
    char*                                psp_PaymentAmount        ;	
    char*                                psp_FirstPaymentDeferral ;	
    char*                                psp_Currency             ;	
    char*                                psp_Country              ;	
    char*                                psp_Product              ;	
    char*                                psp_AuthorizationCode    ;	
    char*                                psp_BatchNro             ;	
    char*                                psp_SequenceNumber       ;	
    char*                                psp_TicketNumber         ;	
    char*                                psp_CardNumber_FSD ;	
    char*                                psp_CardNumber_LFD ;	
    char*                                psp_CardMask             ;	
    char*                                psp_CardHolderName       ;	
    char*                                psp_CustomerMail         ;	
    char*                                psp_CustomerId           ;	
    char*                                psp_CustomerHttpUserAgent ;	
    char*                                psp_CustomerIpAddress    ;	
    char*                                psp_MerchantMail         ;	
    char*                                psp_ClTrnId              ;	
    char*                                psp_ClExternalMerchant   ;	
    char*                                psp_ClExternalTerminal   ;	
    char*                                psp_ClResponseCod        ;	
    char*                                psp_ClResponseMsg        ;	
    char*                                psp_PosDateTime          ;	
    char*                                psp_PurchaseDescription  ;	
    char*                                psp_SoftDescriptor       ;	
    char*                                psp_Plan                 ;	
    char*                                psp_VisaArg_VBV_Secured ;	
    char*                                psp_3dSecure_XID   ;	
    char*                                psp_3dSecure_CAVV  ;	
    char*                                psp_3dSecure_Eci   ;	
    char*                                psp_3dSecure_EciMsg ;	
    char*                                psp_3dSecure_Secured ;	
    char*                                psp_VisaArg_DA_Result ;	
    char*                                psp_AmexArg_AVS_Result ;	
    char*                                psp_MasterArg_AVS_Result ;	
    char*                                psp_CreatedAt            ;	
    struct AmountAdditionalDetailsResponseStruct*  psp_AmountAdditionalDetails ;	
    struct FraudScreeningResultStruct*  psp_FraudScreeningResult ;	
    struct VerificationServicesResultStruct*  psp_VerificationServicesResult ;	
    struct MerchantAdditionalDetailsStruct*  psp_MerchantAdditionalDetails ;	
    struct CustomerAdditionalDetailsStruct*  psp_CustomerAdditionalDetails ;	
    struct BillingDetailsStruct*    psp_BillingDetails       ;	
    struct ShippingDetailsStruct*   psp_ShippingDetails      ;	
    struct OrderDetailsStruct*      psp_OrderDetails         ;	
    struct AirlineDetailsStruct*    psp_AirlineDetails       ;	
};

struct RespuestaStruct_QueryTxs
{
    char*                                psp_ResponseCod          ;	
    char*                                psp_ResponseMsg          ;	
    char*                                psp_ResponseExtended     ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_QueryCriteria        ;	
    char*                                psp_QueryCriteriaId      ;	
    char*                                psp_PosDateTime          ;	
    struct ArrayOf_RespuestaStruct_QueryTxs_Transactions*  psp_Transactions         ;	
};

struct RequerimientoStruct_GetIINDetails
{
    char*                                psp_Version              ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_IIN                  ;	
    char*                                psp_PosDateTime          ;	
    char*                                psp_SecureHash           ;	
    char*                                psp_ClientSession        ;	
};

struct RespuestaStruct_GetIINDetails
{
    char*                                psp_ResponseCod          ;	
    char*                                psp_ResponseMsg          ;	
    char*                                psp_ResponseExtended     ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_Product              ;	
    char*                                psp_Country              ;	
    char*                                psp_FinancialInstitution ;	
    char*                                psp_PosDateTime          ;	
};

struct RequerimientoStruct_ChangeSecretKey
{
    char*                                psp_Version              ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_NewSecretKey         ;	
    char*                                psp_PosDateTime          ;	
    char*                                psp_SecureHash           ;	
};

struct RespuestaStruct_ChangeSecretKey
{
    char*                                psp_ResponseCod          ;	
    char*                                psp_ResponseMsg          ;	
    char*                                psp_ResponseExtended     ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_PosDateTime          ;	
};

struct RequerimientoStruct_FraudScreening
{
    char*                                psp_Version              ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_TxSource             ;	
    char*                                psp_MerchTxRef           ;	
    char*                                psp_MerchOrderId         ;	
    char*                                psp_MerchAdditionalRef   ;	
    char*                                psp_Amount               ;	
    char*                                psp_NumPayments          ;	
    char*                                psp_FirstPaymentDeferral ;	
    char*                                psp_Recurrent            ;	
    char*                                psp_Currency             ;	
    char*                                psp_Country              ;	
    char*                                psp_Product              ;	
    char*                                psp_CardNumber           ;	
    char*                                psp_CardExpDate          ;	
    char*                                psp_CardHolderName       ;	
    char*                                psp_PurchaseDescription  ;	
    char*                                psp_PosDateTime          ;	
    char*                                psp_SecureHash           ;	
    struct MerchantAdditionalDetailsStruct*  psp_MerchantAdditionalDetails ;	
    struct CustomerAdditionalDetailsStruct*  psp_CustomerAdditionalDetails ;	
    struct BillingDetailsStruct*    psp_BillingDetails       ;	
    struct ShippingDetailsStruct*   psp_ShippingDetails      ;	
    struct OrderDetailsStruct*      psp_OrderDetails         ;	
    struct AirlineDetailsStruct*    psp_AirlineDetails       ;	
    struct VaultReference2pStruct*  psp_VaultReference       ;	
};

struct RespuestaStruct_FraudScreening
{
    char*                                psp_ResponseCod          ;	
    char*                                psp_ResponseMsg          ;	
    char*                                psp_ResponseExtended     ;	
    struct FraudScreeningResultStruct*  psp_Result               ;	
    char*                                psp_OrderId              ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_MerchTxRef           ;	
    char*                                psp_MerchOrderId         ;	
    char*                                psp_MerchAdditionalRef   ;	
    char*                                psp_Amount               ;	
    char*                                psp_NumPayments          ;	
    char*                                psp_FirstPaymentDeferral ;	
    char*                                psp_Recurrent            ;	
    char*                                psp_Currency             ;	
    char*                                psp_Country              ;	
    char*                                psp_Product              ;	
    char*                                psp_CardNumber           ;	
    char*                                psp_CardExpDate          ;	
    char*                                psp_PosDateTime          ;	
    char*                                psp_CreatedAt            ;	
};

struct RequerimientoStruct_NotifyFraudScreeningReview
{
    char*                                psp_Version              ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_Criteria             ;	
    char*                                psp_CriteriaId           ;	
    char*                                psp_ReviewResult         ;	
    char*                                psp_UserId               ;	
    char*                                psp_PosDateTime          ;	
    char*                                psp_SecureHash           ;	
};

struct RespuestaStruct_NotifyFraudScreeningReview
{
    char*                                psp_ResponseCod          ;	
    char*                                psp_ResponseMsg          ;	
    char*                                psp_ResponseExtended     ;	
    char*                                psp_MerchantId           ;	
    char*                                psp_Criteria             ;	
    char*                                psp_CriteriaId           ;	
    char*                                psp_PosDateTime          ;	
};

struct ArrayOf_TaxesRequestStruct
{
    struct TaxesRequestStruct*     *__ptr                         ;
    int                                  __size                        ;
//  int                                  __offset                      ;
};

struct ArrayOf_OrderItemStruct
{
    struct OrderItemStruct*        *__ptr                         ;
    int                                  __size                        ;
//  int                                  __offset                      ;
};

struct ArrayOf_LegStruct
{
    struct LegStruct*              *__ptr                         ;
    int                                  __size                        ;
//  int                                  __offset                      ;
};

struct ArrayOf_PassengerStruct
{
    struct PassengerStruct*        *__ptr                         ;
    int                                  __size                        ;
//  int                                  __offset                      ;
};

struct ArrayOf_TaxesResponseStruct
{
    struct TaxesResponseStruct*    *__ptr                         ;
    int                                  __size                        ;
//  int                                  __offset                      ;
};

struct ArrayOf_RequerimientoStruct_SplitPayOnLine_2p_Transactions
{
    struct RequerimientoStruct_SplitPayOnLine_2p_Transactions* *__ptr                         ;
    int                                  __size                        ;
//  int                                  __offset                      ;
};

struct ArrayOf_RespuestaStruct_SplitPayOnLine_2p_Transactions
{
    struct RespuestaStruct_SplitPayOnLine_2p_Transactions* *__ptr                         ;
    int                                  __size                        ;
//  int                                  __offset                      ;
};

struct ArrayOf_RequerimientoStruct_SplitAuthorize_2p_Transactions
{
    struct RequerimientoStruct_SplitAuthorize_2p_Transactions* *__ptr                         ;
    int                                  __size                        ;
//  int                                  __offset                      ;
};

struct ArrayOf_RequerimientoStruct_SplitPayOnLine_3p_Transactions
{
    struct RequerimientoStruct_SplitPayOnLine_3p_Transactions* *__ptr                         ;
    int                                  __size                        ;
//  int                                  __offset                      ;
};

struct ArrayOf_RespuestaStruct_SplitPayOnLine_3p_Transactions
{
    struct RespuestaStruct_SplitPayOnLine_3p_Transactions* *__ptr                         ;
    int                                  __size                        ;
//  int                                  __offset                      ;
};

struct ArrayOf_RequerimientoStruct_SplitAuthorize_3p_Transactions
{
    struct RequerimientoStruct_SplitAuthorize_3p_Transactions* *__ptr                         ;
    int                                  __size                        ;
//  int                                  __offset                      ;
};

struct ArrayOf_RespuestaStruct_SplitAuthorize_3p_Transactions
{
    struct RespuestaStruct_SplitAuthorize_3p_Transactions* *__ptr                         ;
    int                                  __size                        ;
//  int                                  __offset                      ;
};

struct ArrayOf_InstallmentsOptionsStruct
{
    struct InstallmentsOptionsStruct* *__ptr                         ;
    int                                  __size                        ;
//  int                                  __offset                      ;
};

struct ArrayOf_PaymentMethodsOutputDetailsStruct
{
    struct PaymentMethodsOutputDetailsStruct* *__ptr                         ;
    int                                  __size                        ;
//  int                                  __offset                      ;
};

struct ArrayOf_RespuestaStruct_QueryTxs_Transactions
{
    struct RespuestaStruct_QueryTxs_Transactions* *__ptr                         ;
    int                                  __size                        ;
//  int                                  __offset                      ;
};


/* End of NpsSandbox.h */
#ifdef __cplusplus
}
#endif

#endif
