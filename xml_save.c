#include "xml_save.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void new_buffer(struct Buffer *b) {
    b->data = (void*)malloc(INITIAL_SIZE);
    memset(b->data, '0', INITIAL_SIZE);
    b->size = INITIAL_SIZE;
    b->next = 0;

    return;
}

void reserve_space(struct Buffer *b, long bytes) {
    long new_size = b->next + bytes;
    if((new_size) > b->size) {
        b->data = realloc(b->data, new_size);
        b->size = new_size; 
    }
}

void serialize_string(char *eName, char *value, struct Buffer *b) {
  
  long need_size;
  char *buff;
  
  if (!value) {
    return;
  }

  /*<psp_NumPayments>1</psp_NumPayments>
   * <></> =5*/
  
  need_size=5;
  need_size+=strlen(eName)*2;
  need_size+=strlen(value);

  reserve_space(b, need_size);
 
  buff=(char *)calloc(need_size + 1, sizeof(char));
  
  sprintf(buff,"<%s>%s</%s>",eName, value, eName);
  
  memcpy(((char *)b->data) + b->next, buff, need_size);
  
  b->next += need_size;

  free(buff);
}

void serialize_open_node(char *eName, char *xsi_type, struct Buffer *b){
  int need_size;
  char *buff;
  
  if (!eName || !xsi_type) {
    return;
  }
  
  
  need_size=2+21;
  need_size+=strlen(eName);
  need_size+=strlen(xsi_type);
  reserve_space(b, need_size);
  
  buff=malloc(need_size+1);
  
  sprintf(buff,"<%s xmlns=\"\" xsi:type=\"%s\">",eName, xsi_type);
  
  memcpy(((char *)b->data) + b->next, buff, need_size);

  b->next += need_size;
  
  free(buff);
}


void serialize_close_node(char *eName, struct Buffer *b){
  int need_size;
  char *buff;
  
  if (!eName) {
    return;
  }
  
  /*</psp_AmountAdditionalDetails>
   * </eName>
   * len(</>)=3
   */
  need_size=3;
  need_size+=strlen(eName);
  reserve_space(b, need_size);
  
  buff=malloc(need_size+1);
  
  sprintf(buff,"</%s>",eName);
  memcpy(((char *)b->data) + b->next, buff, need_size);

  b->next += need_size;
  free(buff);
}

/*<eName xmlns="" xsi:type="SOAP-ENC:Array" SOAP-ENC:arrayType="tnsArrayType[count]">
 * eName=Taxes
 * tnsArrayType=tns:TaxesRequestStruct
 * count=2
 * len '< xmlns="" xsi:type="SOAP-ENC:Array" SOAP-ENC:arrayType="[]">' = 61
 * 
 */
void serialize_open_array(char *eName, char *tnsArrayType, int count, struct Buffer *b){
  int need_size, auxCount;
  char *buff;
  
  if (!eName || !tnsArrayType) {
    return;
  }
  
  need_size=61;
  need_size+=strlen(eName);
  need_size+=strlen(tnsArrayType);
  
  auxCount = count;
  while (auxCount) {
    need_size++;
    auxCount/=10;
  }
  
  reserve_space(b, need_size);
  
  buff=malloc(need_size+1);
  
  sprintf(buff,"<%s xmlns=\"\" xsi:type=\"SOAP-ENC:Array\" SOAP-ENC:arrayType=\"%s[%d]\">", eName,tnsArrayType,count);
  
  memcpy(((char *)b->data) + b->next, buff, need_size);

  b->next += need_size;
  
  free(buff);
}

void serialize_close_array(char *eName, struct Buffer *b){
  int need_size;
  char *buff;
  
  if (!eName) {
    return;
  }
  
  /*</psp_AmountAdditionalDetails>
   * </eName>
   * len(</>)=3
   */
  need_size=3;
  need_size+=strlen(eName);
  reserve_space(b, need_size);
  
  buff=malloc(need_size+1);
  
  sprintf(buff,"</%s>",eName);
  memcpy(((char *)b->data) + b->next, buff, need_size);

  b->next += need_size;
  free(buff);
}

/*<item xsi:type="tns:TaxesRequestStruct"><TypeId xsi:type="xsd:string">500</TypeId><Amount xsi:type="xsd:string">500</Amount></item>
 */
void serialize_TaxesRequestStruct(char *xmlName, TAXES_REQUEST_STRUCT *x, struct Buffer *output) {
    if (!x) 
      return;
  
    serialize_open_node(xmlName, "tns:TaxesRequestStruct", output);

    serialize_string(TYPEID_FIELD_DESC, x->TypeId, output);
    serialize_string(AMOUNT_FIELD_DESC, x->Amount, output);
    serialize_string(RATE_FIELD_DESC, x->Rate, output);
    serialize_string(BASEAMOUNT_FIELD_DESC, x->BaseAmount, output);

    serialize_close_node(xmlName, output);
}

/*<Taxes xmlns="" xsi:type="SOAP-ENC:Array" SOAP-ENC:arrayType="tns:TaxesRequestStruct[2]"><item xsi:type="tns:TaxesRequestStruct"><TypeId xsi:type="xsd:string">500</TypeId><Amount xsi:type="xsd:string">500</Amount></item><item xsi:type="tns:TaxesRequestStruct"><TypeId xsi:type="xsd:string">504</TypeId><Amount xsi:type="xsd:string">400</Amount></item></Taxes>*/
void serialize_ArrayOf_TaxesRequestStruct(char *xmlName, ARRAYOF_TAXESREQUESTSTRUCT *x, struct Buffer *output) {
    int i;
    if (!x) {
      return;
    }

    serialize_open_array(xmlName, "tns:TaxesRequestStruct", x->__size, output);
    
    for (i = 0; i < x->__size; ++i){
      serialize_TaxesRequestStruct("item", x->__ptr[i] ,output);
    }
    
    serialize_close_array(xmlName, output);
}

/*
 * <psp_AmountAdditionalDetails xmlns="" xsi:type="tns:AmountAdditionalDetailsRequestStruct">
 * <Tip xsi:type="xsd:string">1111</Tip><Discount xsi:type="xsd:string">2222</Discount>
 * <Taxes xmlns="" xsi:type="SOAP-ENC:Array" SOAP-ENC:arrayType="tns:TaxesRequestStruct[2]"><item xsi:type="tns:TaxesRequestStruct">
 * <TypeId xsi:type="xsd:string">500</TypeId><Amount xsi:type="xsd:string">500</Amount></item><item xsi:type="tns:TaxesRequestStruct">
 * <TypeId xsi:type="xsd:string">504</TypeId><Amount xsi:type="xsd:string">400</Amount></item></Taxes></psp_AmountAdditionalDetails>
 * */
void serialize_AmountAdditionalDetailsRequestStruct(char *xmlName, AMOUNT_ADDITIONAL_DETAILS_REQUEST_STRUCT *x, struct Buffer *output){
    if (!x) 
      return;

    serialize_open_node(xmlName, "tns:AmountAdditionalDetailsRequestStruct", output);
    
    serialize_string(TIP_FIELD_DESC, x->Tip, output);
    serialize_string(DISCOUNT_FIELD_DESC, x->Discount, output);
    
    serialize_ArrayOf_TaxesRequestStruct("Taxes", x->Taxes, output);
    
    serialize_close_node(xmlName, output);
}

/*<Address xmlns="" xsi:type="tns:AddressStruct"><Street xsi:type="xsd:string">Calle falsa</Street><HouseNumber xsi:type="xsd:string">456</HouseNumber><AdditionalInfo xsi:type="xsd:string">28</AdditionalInfo><City xsi:type="xsd:string">Capital Federal</City><StateProvince xsi:type="xsd:string">Buenos Aires</StateProvince><Country xsi:type="xsd:string">032</Country><ZipCode xsi:type="xsd:string">1414</ZipCode></Address>*/
void serialize_AddressStruct(char *xmlName,ADDRESS_STRUCT *x, struct Buffer *output) {
    if (!x) 
     return;
    
    serialize_open_node(xmlName, "tns:AddressStruct", output);        
    
    serialize_string(STREET_FIELD_DESC, x->Street, output);
    serialize_string(HOUSENUMBER_FIELD_DESC, x->HouseNumber, output);
    serialize_string(ADDITIONALINFO_FIELD_DESC, x->AdditionalInfo, output);
    serialize_string(CITY_FIELD_DESC, x->City, output);
    serialize_string(STATEPROVINCE_FIELD_DESC, x->StateProvince, output);
    serialize_string(COUNTRY_FIELD_DESC, x->Country, output);
    serialize_string(ZIPCODE_FIELD_DESC, x->ZipCode, output);
    
    serialize_close_node(xmlName, output);

}

/*<SellerDetails xmlns="" xsi:type="tns:SellerDetailsStruct"><IDNumber xsi:type="xsd:string">27087764-0</IDNumber><IDType xsi:type="xsd:string">200</IDType><Name xsi:type="xsd:string">Fernando Bonifacio</Name><Invoice xsi:type="xsd:string">125447</Invoice><PurchaseDescription xsi:type="xsd:string">DENTRO DE MAD Ã±Ã ndÃº</PurchaseDescription><Address xmlns="" xsi:type="tns:AddressStruct"><Street xsi:type="xsd:string">Calle falsa</Street><HouseNumber xsi:type="xsd:string">456</HouseNumber><AdditionalInfo xsi:type="xsd:string">28</AdditionalInfo><City xsi:type="xsd:string">Capital Federal</City><StateProvince xsi:type="xsd:string">Buenos Aires</StateProvince><Country xsi:type="xsd:string">032</Country><ZipCode xsi:type="xsd:string">1414</ZipCode></Address><MCC xsi:type="xsd:string">7991</MCC><ChannelCode xsi:type="xsd:string">211</ChannelCode><GeoCode xsi:type="xsd:string">C</GeoCode></SellerDetails>*/
void serialize_SellerDetailsStruct(char *xmlName, SELLER_DETAILS_STRUCT *x, struct Buffer *output){
    if (!x) 
      return;
    
    serialize_open_node(xmlName, "tns:SellerDetailsStruct", output);    
    
    serialize_string(IDNUMBER_FIELD_DESC, x->IDNumber, output);
    serialize_string(IDTYPE_FIELD_DESC, x->IDType, output);
    serialize_string(NAME_FIELD_DESC, x->Name, output);
    serialize_string(INVOICE_FIELD_DESC, x->Invoice, output);
    serialize_string(PURCHASEDESCRIPTION_FIELD_DESC, x->PurchaseDescription, output);
    
    serialize_AddressStruct("Address", x->Address, output);
    
    serialize_string(MCC_FIELD_DESC, x->MCC, output);
    serialize_string(CHANNELCODE_FIELD_DESC, x->ChannelCode, output);
    serialize_string(GEOCODE_FIELD_DESC, x->GeoCode, output);
    
    serialize_close_node(xmlName, output);

}

void serialize_MerchantAdditionalDetailsStruct(char *xmlName, MERCHANT_ADDITIONAL_DETAILS_STRUCT *x, struct Buffer *output){
    if (!x) 
      return;

    serialize_open_node(xmlName, "tns:MerchantAdditionalDetailsStruct", output);    
    
    serialize_string(TYPE_FIELD_DESC, x->Type, output);
    
    serialize_SellerDetailsStruct("SellerDetails", x->SellerDetails, output);    
    
    serialize_string(SDKINFO_FIELD_DESC, x->SdkInfo, output);
    serialize_string(SHOPPINGCARTINFO_FIELD_DESC, x->ShoppingCartInfo, output);
    serialize_string(SHOPPINGCARTPLUGININFO_FIELD_DESC, x->ShoppingCartPluginInfo, output);
    
    serialize_close_node(xmlName, output);

}

/*<psp_CustomerAdditionalDetails xmlns="" xsi:type="tns:CustomerAdditionalDetailsStruct"><AlternativeEmailAddress xsi:type="xsd:string">PEPE@pepe.com?</AlternativeEmailAddress><IPAddress xsi:type="xsd:string">222.222.222.222</IPAddress><AccountID xsi:type="xsd:string">2</AccountID><AccountCreatedAt xsi:type="xsd:string">2014-01-01</AccountCreatedAt><AccountHasCredentials xsi:type="xsd:string">0</AccountHasCredentials><DeviceType xsi:type="xsd:string">2</DeviceType><BrowserLanguage xsi:type="xsd:string">ES</BrowserLanguage><HttpUserAgent xsi:type="xsd:string">User Agent TEST, filled by merchant</HttpUserAgent></psp_CustomerAdditionalDetails>
 */
void serialize_CustomerAdditionalDetailsStruct(char *xmlName, CUSTOMER_ADDITIONAL_DETAILS_STRUCT *x, struct Buffer *output){
    if (!x) 
      return;

    serialize_open_node(xmlName, "tns:CustomerAdditionalDetailsStruct", output);        
    
    serialize_string(EMAILADDRESS_FIELD_DESC, x->EmailAddress, output);
    serialize_string(ALTERNATIVEEMAILADDRESS_FIELD_DESC, x->AlternativeEmailAddress, output);
    serialize_string(IPADDRESS_FIELD_DESC, x->IPAddress, output);
    serialize_string(ACCOUNTID_FIELD_DESC, x->AccountID, output);
    serialize_string(ACCOUNTCREATEDAT_FIELD_DESC, x->AccountCreatedAt, output);
    serialize_string(ACCOUNTPREVIOUSACTIVITY_FIELD_DESC, x->AccountPreviousActivity, output);
    serialize_string(ACCOUNTHASCREDENTIALS_FIELD_DESC, x->AccountHasCredentials, output);
    serialize_string(DEVICETYPE_FIELD_DESC, x->DeviceType, output);
    serialize_string(DEVICEFINGERPRINT_FIELD_DESC, x->DeviceFingerPrint, output);
    serialize_string(BROWSERLANGUAGE_FIELD_DESC, x->BrowserLanguage, output);
    serialize_string(HTTPUSERAGENT_FIELD_DESC, x->HttpUserAgent, output);
    
    serialize_close_node(xmlName, output);    
}

void serialize_PersonStruct(char *xmlName, PERSON_STRUCT *x, struct Buffer *output){
    if (!x) 
      return;

    serialize_open_node(xmlName, "tns:PersonStruct", output);
      
    serialize_string(FIRSTNAME_FIELD_DESC, x->FirstName, output);
    serialize_string(LASTNAME_FIELD_DESC, x->LastName, output);
    serialize_string(MIDDLENAME_FIELD_DESC, x->MiddleName, output);
    serialize_string(PHONENUMBER1_FIELD_DESC, x->PhoneNumber1, output);
    serialize_string(PHONENUMBER2_FIELD_DESC, x->PhoneNumber2, output);
    serialize_string(GENDER_FIELD_DESC, x->Gender, output);
    serialize_string(DATEOFBIRTH_FIELD_DESC, x->DateOfBirth, output);
    serialize_string(NATIONALITY_FIELD_DESC, x->Nationality, output);
    serialize_string(IDNUMBER_FIELD_DESC, x->IDNumber, output);
    serialize_string(IDTYPE_FIELD_DESC, x->IDType, output);
    
    serialize_close_node(xmlName, output); 
}

void serialize_CardInputDetailsStruct(char *xmlName, CARD_INPUT_DETAILS_STRUCT *x, struct Buffer *output){
    if (!x) 
      return;

    serialize_open_node(xmlName, "tns:CardInputDetailsStruct", output);

    serialize_string(NUMBER_FIELD_DESC, x->Number, output);
    serialize_string(EXPIRATIONDATE_FIELD_DESC, x->ExpirationDate, output);
    serialize_string(SECURITYCODE_FIELD_DESC, x->SecurityCode, output);
    serialize_string(HOLDERNAME_FIELD_DESC, x->HolderName, output);
    
    serialize_close_node(xmlName, output); 
}

void serialize_BillingDetailsStruct(char *xmlName, BILLING_DETAILS_STRUCT *x, struct Buffer *output){
    if (!x) 
      return;

    serialize_open_node(xmlName, "tns:BillingDetailsStruct", output);        
    
    serialize_string(INVOICE_FIELD_DESC, x->Invoice, output);
    serialize_string(INVOICEDATE_FIELD_DESC, x->InvoiceDate, output);
    serialize_string(INVOICEAMOUNT_FIELD_DESC, x->InvoiceAmount, output);
    serialize_string(INVOICECURRENCY_FIELD_DESC, x->InvoiceCurrency, output);
    
    serialize_PersonStruct("Person", x->Person, output);
    serialize_AddressStruct("Address", x->Address, output);
    
    serialize_close_node(xmlName, output);    
}

void serialize_ShippingDetailsStruct(char *xmlName, SHIPPING_DETAILS_STRUCT *x, struct Buffer *output){
    if (!x) 
      return;
    
    serialize_open_node(xmlName, "tns:ShippingDetailsStruct", output);    
    
    serialize_string(TRACKINGNUMBER_FIELD_DESC, x->TrackingNumber, output);
    serialize_string(METHOD_FIELD_DESC, x->Method, output);
    serialize_string(CARRIER_FIELD_DESC, x->Carrier, output);
    serialize_string(DELIVERYDATE_FIELD_DESC, x->DeliveryDate, output);
    serialize_string(FREIGHTAMOUNT_FIELD_DESC, x->FreightAmount, output);
    serialize_string(GIFTMESSAGE_FIELD_DESC, x->GiftMessage, output);
    serialize_string(GIFTWRAPPING_FIELD_DESC, x->GiftWrapping, output);
    
    serialize_PersonStruct("PrimaryRecipient", x->PrimaryRecipient, output);
    serialize_PersonStruct("SecondaryRecipient", x->SecondaryRecipient, output);
    serialize_AddressStruct("Address", x->Address, output);
    
    serialize_close_node(xmlName, output);     
}

/*<item xsi:type="tns:OrderItemStruct"><Quantity xsi:type="xsd:string">1</Quantity><UnitPrice xsi:type="xsd:string">110</UnitPrice><Description xsi:type="xsd:string">description1</Description><Type xsi:type="xsd:string">1</Type><SkuCode xsi:type="xsd:string">1</SkuCode><ManufacturerPartNumber xsi:type="xsd:string">1</ManufacturerPartNumber><Risk xsi:type="xsd:string">H</Risk></item>
 */
void serialize_OrderItemStruct(char *xmlName, ORDER_ITEM_STRUCT *x, struct Buffer *output) {
    if (!x) 
      return;
  
    serialize_open_node(xmlName, "tns:OrderItemStruct", output);    
    
    serialize_string(QUANTITY_FIELD_DESC, x->Quantity, output);
    serialize_string(UNITPRICE_FIELD_DESC, x->UnitPrice, output);
    serialize_string(DESCRIPTION_FIELD_DESC, x->Description, output);
    serialize_string(TYPE_FIELD_DESC, x->Type, output);
    serialize_string(SKUCODE_FIELD_DESC, x->SkuCode, output);
    serialize_string(MANUFACTURERPARTNUMBER_FIELD_DESC, x->ManufacturerPartNumber, output);
    serialize_string(RISK_FIELD_DESC, x->Risk, output);

    serialize_close_node(xmlName, output);
}

/*<OrderItems xmlns="" xsi:type="SOAP-ENC:Array" SOAP-ENC:arrayType="tns:OrderItemStruct[2]"><item xsi:type="tns:OrderItemStruct"><Quantity xsi:type="xsd:string">2</Quantity><UnitPrice xsi:type="xsd:string">200</UnitPrice><Description xsi:type="xsd:string">description2</Description><Type xsi:type="xsd:string">1</Type><SkuCode xsi:type="xsd:string">1</SkuCode><ManufacturerPartNumber xsi:type="xsd:string">1</ManufacturerPartNumber><Risk xsi:type="xsd:string">H</Risk></item><item xsi:type="tns:OrderItemStruct"><Quantity xsi:type="xsd:string">3</Quantity><UnitPrice xsi:type="xsd:string">3</UnitPrice><Description xsi:type="xsd:string">description3</Description><Type xsi:type="xsd:string">1</Type><SkuCode xsi:type="xsd:string">1</SkuCode>
<ManufacturerPartNumber xsi:type="xsd:string">1</ManufacturerPartNumber><Risk xsi:type="xsd:string">L</Risk></item></OrderItems>*/
void serialize_ArrayOf_OrderItemStruct(char *xmlName, ARRAYOF_ORDERITEMSTRUCT *x, struct Buffer *output) {
    int i;
    if (!x) {
      return;
    }

    serialize_open_array(xmlName, "tns:OrderItemStruct", x->__size, output);
    
    for (i = 0; i < x->__size; ++i){
      serialize_OrderItemStruct("item", x->__ptr[i] ,output);
    }
    
    serialize_close_array(xmlName, output);
}

/*<psp_OrderDetails xmlns="" xsi:type="tns:OrderDetailsStruct"><OrderItems xmlns="" xsi:type="SOAP-ENC:Array" SOAP-ENC:arrayType="tns:OrderItemStruct[3]"><item xsi:type="tns:OrderItemStruct"><Quantity xsi:type="xsd:string">1</Quantity><UnitPrice xsi:type="xsd:string">110</UnitPrice><Description xsi:type="xsd:string">description1</Description><Type xsi:type="xsd:string">1</Type><SkuCode xsi:type="xsd:string">1</SkuCode><ManufacturerPartNumber xsi:type="xsd:string">1</ManufacturerPartNumber><Risk xsi:type="xsd:string">H</Risk></item><item xsi:type="tns:OrderItemStruct"><Quantity xsi:type="xsd:string">2</Quantity><UnitPrice xsi:type="xsd:string">200</UnitPrice><Description xsi:type="xsd:string">description2</Description><Type xsi:type="xsd:string">1</Type><SkuCode xsi:type="xsd:string">1</SkuCode><ManufacturerPartNumber xsi:type="xsd:string">1</ManufacturerPartNumber><Risk xsi:type="xsd:string">H</Risk></item><item xsi:type="tns:OrderItemStruct"><Quantity xsi:type="xsd:string">3</Quantity><UnitPrice xsi:type="
xsd:string">3</UnitPrice><Description xsi:type="xsd:string">description3</Description><Type xsi:type="xsd:string">1</Type><SkuCode xsi:type="xsd:string">1</SkuCode>
<ManufacturerPartNumber xsi:type="xsd:string">1</ManufacturerPartNumber><Risk xsi:type="xsd:string">L</Risk></item></OrderItems></psp_OrderDetails>*/
void serialize_OrderDetailsStruct(char *xmlName, ORDER_DETAILS_STRUCT *x, struct Buffer *output){
    if (!x) 
      return;
    
    serialize_open_node(xmlName, "tns:OrderDetailsStruct", output);  
   
    serialize_ArrayOf_OrderItemStruct("OrderItems", x->OrderItems, output);
   
    serialize_close_node(xmlName, output);         
}

void serialize_LegStruct(char *xmlName, LEG_STRUCT *x, struct Buffer *output) {
    if (!x) 
      return;
    
    serialize_open_node(xmlName, "tns:LegStruct", output);    

    serialize_string(DEPARTUREAIRPORT_FIELD_DESC, x->DepartureAirport, output);
    serialize_string(DEPARTUREDATETIME_FIELD_DESC, x->DepartureDatetime, output);
    serialize_string(DEPARTUREAIRPORTTIMEZONE_FIELD_DESC, x->DepartureAirportTimezone, output);
    serialize_string(ARRIVALAIRPORT_FIELD_DESC, x->ArrivalAirport, output);
    serialize_string(CARRIERCODE_FIELD_DESC, x->CarrierCode, output);
    serialize_string(FLIGHTNUMBER_FIELD_DESC, x->FlightNumber, output);
    serialize_string(FAREBASISCODE_FIELD_DESC, x->FareBasisCode, output);
    serialize_string(FARECLASSCODE_FIELD_DESC, x->FareClassCode, output);
    serialize_string(BASEFARE_FIELD_DESC, x->BaseFare, output);
    serialize_string(BASEFARECURRENCY_FIELD_DESC, x->BaseFareCurrency, output);
    
    serialize_close_node(xmlName, output);
}

void serialize_ArrayOf_LegStruct(char *xmlName, ARRAYOF_LEGSTRUCT *x, struct Buffer *output) {
    int i;
    if (!x) {
      return;
    }

    serialize_open_array(xmlName, "tns:LegStruct", x->__size, output);
    
    for (i = 0; i < x->__size; ++i){
      serialize_LegStruct("item", x->__ptr[i] ,output);
    }
    
    serialize_close_array(xmlName, output);
}

void serialize_PassengerStruct(char *xmlName, PASSENGER_STRUCT *x, struct Buffer *output) {
    if (!x) 
      return;
    
    serialize_open_node(xmlName, "tns:PassengerStruct", output);    

    serialize_string(FIRSTNAME_FIELD_DESC, x->FirstName, output);
    serialize_string(LASTNAME_FIELD_DESC, x->LastName, output);
    serialize_string(MIDDLENAME_FIELD_DESC, x->MiddleName, output);
    serialize_string(TYPE_FIELD_DESC, x->Type, output);
    serialize_string(DATEOFBIRTH_FIELD_DESC, x->DateOfBirth, output);
    serialize_string(NATIONALITY_FIELD_DESC, x->Nationality, output);
    serialize_string(IDNUMBER_FIELD_DESC, x->IDNumber, output);
    serialize_string(IDTYPE_FIELD_DESC, x->IDType, output);
    serialize_string(IDCOUNTRY_FIELD_DESC, x->IDCountry, output);
    serialize_string(LOYALTYNUMBER_FIELD_DESC, x->LoyaltyNumber, output);
    serialize_string(LOYALTYTIER_FIELD_DESC, x->LoyaltyTier, output);
    
    serialize_close_node(xmlName, output);
}

void serialize_ArrayOf_PassengerStruct(char *xmlName, ARRAYOF_PASSENGERSTRUCT *x, struct Buffer *output) {
    int i;
    if (!x) {
      return;
    }

    serialize_open_array(xmlName, "tns:PassengerStruct", x->__size, output);
    
    for (i = 0; i < x->__size; ++i){
      serialize_PassengerStruct("item", x->__ptr[i] ,output);
    }
    
    serialize_close_array(xmlName, output);
}

void serialize_AirlineTicketIssueStruct(char *xmlName, AIRLINE_TICKET_ISSUE_STRUCT *x, struct Buffer *output){
    if (!x) 
    return;
    
    serialize_open_node(xmlName, "tns:AirlineTicketIssueStruct", output);        

    serialize_string(CARRIERPREFIXCODE_FIELD_DESC, x->CarrierPrefixCode, output);
    serialize_string(TRAVELAGENTCODE_FIELD_DESC, x->TravelAgentCode, output);
    serialize_string(TRAVELAGENTNAME_FIELD_DESC, x->TravelAgentName, output);
    serialize_string(DATE_FIELD_DESC, x->Date, output);
    serialize_string(COUNTRY_FIELD_DESC, x->Country, output);
    serialize_string(CITY_FIELD_DESC, x->City, output);
    serialize_string(ADDRESS_FIELD_DESC, x->Address, output);
    
    serialize_close_node(xmlName, output);     
}

void serialize_AirlineTicketStruct(char *xmlName, AIRLINE_TICKET_STRUCT *x, struct Buffer *output){
    if (!x) 
      return;
    
    serialize_open_node(xmlName, "tns:AirlineTicketStruct", output);        
    
    serialize_string(TICKETNUMBER_FIELD_DESC, x->TicketNumber, output);
    serialize_string(ETICKET_FIELD_DESC, x->Eticket, output);
    serialize_string(RESTRICTED_FIELD_DESC, x->Restricted, output);
    
    serialize_AirlineTicketIssueStruct("Issue", x->Issue, output);
    
    serialize_string(TOTALFAREAMOUNT_FIELD_DESC, x->TotalFareAmount, output);
    serialize_string(TOTALTAXAMOUNT_FIELD_DESC, x->TotalTaxAmount, output);
    serialize_string(TOTALFEEAMOUNT_FIELD_DESC, x->TotalFeeAmount, output);
    
    serialize_close_node(xmlName, output);     
}

void serialize_AirlineDetailsStruct(char *xmlName, AIRLINE_DETAILS_STRUCT *x, struct Buffer *output){
    if (!x) {
      return;
    }
    
    serialize_open_node(xmlName, "tns:AirlineDetailsStruct", output);        
    serialize_string("PNR", x->PNR, output);

    serialize_ArrayOf_LegStruct("Legs", x->Legs, output);    
    serialize_ArrayOf_PassengerStruct("Passengers", x->Passengers, output);
    serialize_AirlineTicketStruct("Ticket", x->Ticket, output);
    
    serialize_close_node(xmlName, output);     
}

void serialize_VaultReference3pStruct(char *xmlName, VAULT_REFERENCE_3P_STRUCT *x, struct Buffer *output){
    if (!x) 
      return;
    
    serialize_open_node(xmlName, "tns:VaultReference3pStruct", output);            
    
    serialize_string(CUSTOMERID_FIELD_DESC, x->CustomerId, output);
    
    serialize_close_node(xmlName, output);     
    
}

void serialize_VaultReference2pStruct(char *xmlName, VAULT_REFERENCE_2P_STRUCT *x, struct Buffer *output){
    if (!x) 
      return;
    
    serialize_open_node(xmlName, "tns:VaultReference2pStruct", output);            
    
    serialize_string(PAYMENTMETHODTOKEN_FIELD_DESC, x->PaymentMethodToken, output);
    serialize_string(PAYMENTMETHODID_FIELD_DESC, x->PaymentMethodId, output);
    serialize_string(CUSTOMERID_FIELD_DESC, x->CustomerId, output);
    
    serialize_close_node(xmlName, output);     
    
}

/*<item xsi:type="tns:RequerimientoStruct_SplitPayOnLine_2p_Transactions"><psp_MerchantId xsi:type="xsd:string">psp_test</psp_MerchantId><psp_MerchTxRef xsi:type="xsd:string">WS-CLIENT.5A79C619DF0B94.28646943</psp_MerchTxRef><psp_Product xsi:type="xsd:string">14</psp_Product><psp_CardHolderName xsi:type="xsd:string">John Doe</psp_CardHolderName><psp_Amount xsi:type="xsd:string">10000</psp_Amount><psp_NumPayments xsi:type="xsd:string">1</psp_NumPayments><psp_VaultReference xmlns="" xsi:type="tns:VaultReference2pStruct"><PaymentMethodToken xsi:type="xsd:string">pm-token_lCY303k0vHvS5W06sPwzgoSHNt0VRrkG</PaymentMethodToken></psp_VaultReference></item>
 */
void serialize_RequerimientoStruct_SplitPayOnLine_2p_Transactions(char *xmlName, REQUERIMIENTO_STRUCT_SPLIT_PAYONLINE_2P_TRANSACTIONS *x, struct Buffer *output) {
    if (!x) 
      return;
  
    serialize_open_node(xmlName, "tns:RequerimientoStruct_SplitPayOnLine_2p_Transactions", output);    

    serialize_string(PSP_MERCHANTID_FIELD_DESC, x->psp_MerchantId, output);
    serialize_string(PSP_MERCHTXREF_FIELD_DESC, x->psp_MerchTxRef, output);
    serialize_string(PSP_MERCHADDITIONALREF_FIELD_DESC, x->psp_MerchAdditionalRef, output);
    serialize_string(PSP_PRODUCT_FIELD_DESC, x->psp_Product, output);
    serialize_string(PSP_CARDNUMBER_FIELD_DESC, x->psp_CardNumber, output);
    serialize_string(PSP_CARDEXPDATE_FIELD_DESC, x->psp_CardExpDate, output);
    serialize_string(PSP_CARDSECURITYCODE_FIELD_DESC, x->psp_CardSecurityCode, output);
    serialize_string(PSP_CARDHOLDERNAME_FIELD_DESC, x->psp_CardHolderName, output);
    serialize_string(PSP_AMOUNT_FIELD_DESC, x->psp_Amount, output);
    serialize_string(PSP_NUMPAYMENTS_FIELD_DESC, x->psp_NumPayments, output);
    serialize_string(PSP_PLAN_FIELD_DESC, x->psp_Plan, output);
    serialize_string(PSP_FIRSTPAYMENTDEFERRAL_FIELD_DESC, x->psp_FirstPaymentDeferral, output);
    serialize_string(PSP_PROMOTIONCODE_FIELD_DESC, x->psp_PromotionCode, output);
    serialize_string(PSP_PRESETCARDIIN_FIELD_DESC, x->psp_PresetCardIIN, output);
    serialize_string(PSP_SOFTDESCRIPTOR_FIELD_DESC, x->psp_SoftDescriptor, output);
    
    serialize_AmountAdditionalDetailsRequestStruct(PSP_AMOUNTADDITIONALDETAILS_FIELD_DESC, (char *)x->psp_AmountAdditionalDetails, output);
    serialize_MerchantAdditionalDetailsStruct(PSP_MERCHANTADDITIONALDETAILS_FIELD_DESC, (char *)x->psp_MerchantAdditionalDetails, output);
    serialize_BillingDetailsStruct(PSP_BILLINGDETAILS_FIELD_DESC, (char *)x->psp_BillingDetails, output);
    serialize_VaultReference2pStruct(PSP_VAULTREFERENCE_FIELD_DESC, (char *)x->psp_VaultReference, output);
    
    serialize_close_node(xmlName, output);
}

void serialize_ArrayOf_RequerimientoStruct_SplitPayOnLine_2p_Transactions(char *xmlName, ARRAYOF_REQUERIMIENTOSTRUCT_SPLITPAYONLINE_2P_TRANSACTIONS *x, 
									    struct Buffer *output) {
    int i;
    if (!x) {
      return;
    }

    serialize_open_array(xmlName, "tns:RequerimientoStruct_SplitPayOnLine_2p_Transactions", x->__size, output);
    
    for (i = 0; i < x->__size; ++i){
      serialize_RequerimientoStruct_SplitPayOnLine_2p_Transactions("item", x->__ptr[i] ,output);
    }
    
    serialize_close_array(xmlName, output);
}

void serialize_RequerimientoStruct_SplitAuthorize_2p_Transactions(char *xmlName, REQUERIMIENTO_STRUCT_SPLITAUTHORIZE_2P_TRANSACTIONS *x, struct Buffer *output) {
    if (!x) 
      return;
  
    serialize_open_node(xmlName, "tns:RequerimientoStruct_SplitAuthorize_2p_Transactions", output);    

    serialize_string(PSP_MERCHANTID_FIELD_DESC, x->psp_MerchantId, output);
    serialize_string(PSP_MERCHTXREF_FIELD_DESC, x->psp_MerchTxRef, output);
    serialize_string(PSP_MERCHADDITIONALREF_FIELD_DESC, x->psp_MerchAdditionalRef, output);
    serialize_string(PSP_PRODUCT_FIELD_DESC, x->psp_Product, output);
    serialize_string(PSP_CARDNUMBER_FIELD_DESC, x->psp_CardNumber, output);
    serialize_string(PSP_CARDEXPDATE_FIELD_DESC, x->psp_CardExpDate, output);
    serialize_string(PSP_CARDSECURITYCODE_FIELD_DESC, x->psp_CardSecurityCode, output);
    serialize_string(PSP_CARDHOLDERNAME_FIELD_DESC, x->psp_CardHolderName, output);
    serialize_string(PSP_AMOUNT_FIELD_DESC, x->psp_Amount, output);
    serialize_string(PSP_NUMPAYMENTS_FIELD_DESC, x->psp_NumPayments, output);
    serialize_string(PSP_PLAN_FIELD_DESC, x->psp_Plan, output);
    serialize_string(PSP_PROMOTIONCODE_FIELD_DESC, x->psp_PromotionCode, output);
    serialize_string(PSP_PRESETCARDIIN_FIELD_DESC, x->psp_PresetCardIIN, output);
    serialize_string(PSP_SOFTDESCRIPTOR_FIELD_DESC, x->psp_SoftDescriptor, output);
    
    serialize_AmountAdditionalDetailsRequestStruct(PSP_AMOUNTADDITIONALDETAILS_FIELD_DESC, (char *)x->psp_AmountAdditionalDetails, output);
    serialize_MerchantAdditionalDetailsStruct(PSP_MERCHANTADDITIONALDETAILS_FIELD_DESC, (char *)x->psp_MerchantAdditionalDetails, output);
    serialize_BillingDetailsStruct(PSP_BILLINGDETAILS_FIELD_DESC, (char *)x->psp_BillingDetails, output);
    serialize_VaultReference2pStruct(PSP_VAULTREFERENCE_FIELD_DESC, (char *)x->psp_VaultReference, output);
    
    serialize_close_node(xmlName, output);
}

void serialize_ArrayOf_RequerimientoStruct_SplitAuthorize_2p_Transactions(char *xmlName, ARRAYOF_REQUERIMIENTOSTRUCT_SPLITAUTHORIZE_2P_TRANSACTIONS *x, struct Buffer *output) {
    int i;
    if (!x) {
      return;
    }

    serialize_open_array(xmlName, "tns:RequerimientoStruct_SplitAuthorize_2p_Transactions", x->__size, output);
    
    for (i = 0; i < x->__size; ++i){
      serialize_RequerimientoStruct_SplitAuthorize_2p_Transactions("item", x->__ptr[i] ,output);
    }
    
    serialize_close_array(xmlName, output);
}
void serialize_RequerimientoStruct_SplitPayOnLine_3p_Transactions(char *xmlName, REQUERIMIENTO_STRUCT_SPLITPAYONLINE_3P_TRANSACTIONS *x, struct Buffer *output) {
    if (!x) 
      return;
  
    serialize_open_node(xmlName, "tns:RequerimientoStruct_SplitPayOnLine_3p_Transactions", output);    

    serialize_string(PSP_MERCHANTID_FIELD_DESC, x->psp_MerchantId, output);
    serialize_string(PSP_MERCHTXREF_FIELD_DESC, x->psp_MerchTxRef, output);
    serialize_string(PSP_MERCHADDITIONALREF_FIELD_DESC, x->psp_MerchAdditionalRef, output);
    serialize_string(PSP_PRODUCT_FIELD_DESC, x->psp_Product, output);
    serialize_string(PSP_PROMOTIONCODE_FIELD_DESC, x->psp_PromotionCode, output);
    serialize_string(PSP_PRESETCARDIIN_FIELD_DESC, x->psp_PresetCardIIN, output);
    serialize_string(PSP_AMOUNT_FIELD_DESC, x->psp_Amount, output);
    serialize_string(PSP_NUMPAYMENTS_FIELD_DESC, x->psp_NumPayments, output);
    serialize_string(PSP_PLAN_FIELD_DESC, x->psp_Plan, output);
    serialize_string(PSP_FIRSTPAYMENTDEFERRAL_FIELD_DESC, x->psp_FirstPaymentDeferral, output);
    serialize_string(PSP_SOFTDESCRIPTOR_FIELD_DESC, x->psp_SoftDescriptor, output);
    serialize_AmountAdditionalDetailsRequestStruct(PSP_AMOUNTADDITIONALDETAILS_FIELD_DESC, (char *)x->psp_AmountAdditionalDetails, output);
    
    serialize_close_node(xmlName, output);
}

void serialize_ArrayOf_RequerimientoStruct_SplitPayOnLine_3p_Transactions(char *xmlName, ARRAYOF_REQUERIMIENTOSTRUCT_SPLITPAYONLINE_3P_TRANSACTIONS *x, struct Buffer *output) {
    int i;
    if (!x) {
      return;
    }

    serialize_open_array(xmlName, "tns:RequerimientoStruct_SplitPayOnLine_3p_Transactions", x->__size, output);
    
    for (i = 0; i < x->__size; ++i){
      serialize_RequerimientoStruct_SplitPayOnLine_3p_Transactions("item", x->__ptr[i] ,output);
    }
    
    serialize_close_array(xmlName, output);
}

void serialize_RequerimientoStruct_SplitAuthorize_3p_Transactions(char *xmlName, REQUERIMIENTO_STRUCT_SPLITAUTHORIZE_3P_TRANSACTIONS *x, struct Buffer *output) {
    if (!x) 
      return;
  
    serialize_open_node(xmlName, "tns:RequerimientoStruct_SplitAuthorize_3p_Transactions", output);    

    serialize_string(PSP_MERCHANTID_FIELD_DESC, x->psp_MerchantId, output);
    serialize_string(PSP_MERCHTXREF_FIELD_DESC, x->psp_MerchTxRef, output);
    serialize_string(PSP_MERCHADDITIONALREF_FIELD_DESC, x->psp_MerchAdditionalRef, output);
    serialize_string(PSP_PRODUCT_FIELD_DESC, x->psp_Product, output);
    serialize_string(PSP_PROMOTIONCODE_FIELD_DESC, x->psp_PromotionCode, output);
    serialize_string(PSP_PRESETCARDIIN_FIELD_DESC, x->psp_PresetCardIIN, output);
    serialize_string(PSP_AMOUNT_FIELD_DESC, x->psp_Amount, output);
    serialize_string(PSP_NUMPAYMENTS_FIELD_DESC, x->psp_NumPayments, output);
    serialize_string(PSP_PLAN_FIELD_DESC, x->psp_Plan, output);
    serialize_string(PSP_SOFTDESCRIPTOR_FIELD_DESC, x->psp_SoftDescriptor, output);
    serialize_AmountAdditionalDetailsRequestStruct(PSP_AMOUNTADDITIONALDETAILS_FIELD_DESC, (char *)x->psp_AmountAdditionalDetails, output);
    
    serialize_close_node(xmlName, output);
}

void serialize_ArrayOf_RequerimientoStruct_SplitAuthorize_3p_Transactions(char *xmlName, ARRAYOF_REQUERIMIENTOSTRUCT_SPLITAUTHORIZE_3P_TRANSACTIONS *x, struct Buffer *output) {
    int i;
    if (!x) {
      return;
    }

    serialize_open_array(xmlName, "tns:RequerimientoStruct_SplitAuthorize_3p_Transactions", x->__size, output);
    
    for (i = 0; i < x->__size; ++i){
      serialize_RequerimientoStruct_SplitAuthorize_3p_Transactions("item", x->__ptr[i] ,output);
    }
    
    serialize_close_array(xmlName, output);
}

void serialize_PaymentMethodInputDetailsStruct(char *xmlName, PAYMENT_METHOD_INPUT_DETAILS_STRUCT *x, struct Buffer *output){
    if (!x) 
      return;
    
    serialize_open_node(xmlName, "tns:PaymentMethodInputDetailsStruct", output);    
    
    serialize_CardInputDetailsStruct("CardInputDetails", x->CardInputDetails, output);
    serialize_PersonStruct("Person", x->Person, output);
    serialize_AddressStruct("Address", x->Address, output);
    
    serialize_close_node(xmlName, output);     
}

void serializeRequest(int type, char *pRequest, char *pOut) {
  
  char **ptr=NULL;
  int i, max_fields;
  char **structFieldsDesc;
  size_t *structFieldsOffset;
  int *structFieldsIdx;
  struct nps_generics **structFieldsType;
  int envField = getEnvironment();

  Log(DEBUG,"serializeRequest Init [%s] env[%s]", GET_SOAP_ACTION(type), npsEnvDesc[envField]);
    
  structFieldsDesc=methodsFields[type-1].structFieldsDesc;
  structFieldsOffset=methodsFields[type-1].structFieldsOffset;
  structFieldsIdx=methodsFields[type-1].structFieldsIdx;
  structFieldsType=methodsFields[type-1].structFieldsType;
  max_fields=methodsFields[type-1].max_fields;
  
  for (i = 0; i < max_fields; i++)  {
    if (!structFieldsDesc[i]) {
      break;
    }
    
    if ((int)structFieldsOffset[(i*ARR_OFFSET_COUNT)+envField]<0) {
      Log(ERROR, "structFieldsDesc[%s] not exist in [%s]",structFieldsDesc[i], npsEnvDesc[envField]);
      continue;
    }    
    
    ptr=(char*) pRequest + methodsFields[type-1].structFieldsOffset[(i*ARR_OFFSET_COUNT)];
    Log(DEBUG, "%s = %s", methodsFields[type-1].structFieldsDesc[i], structFieldsDesc[i], (char *)(*ptr));
    
    if (strcmp(structFieldsDesc[i], PSP_AMOUNTADDITIONALDETAILS_FIELD_DESC)==0)
      serialize_AmountAdditionalDetailsRequestStruct(PSP_AMOUNTADDITIONALDETAILS_FIELD_DESC, (char *)(*ptr), (struct Buffer *)pOut);
    else
    if  (strcmp(structFieldsDesc[i], PSP_MERCHANTADDITIONALDETAILS_FIELD_DESC)==0)
      serialize_MerchantAdditionalDetailsStruct(PSP_MERCHANTADDITIONALDETAILS_FIELD_DESC, (char *)(*ptr), (struct Buffer *)pOut);
    else
    if (strcmp(structFieldsDesc[i], PSP_CUSTOMERADDITIONALDETAILS_FIELD_DESC)==0)
      serialize_CustomerAdditionalDetailsStruct(PSP_CUSTOMERADDITIONALDETAILS_FIELD_DESC, (char *)(*ptr), (struct Buffer *)pOut);
    else
    if (strcmp(structFieldsDesc[i], PSP_BILLINGDETAILS_FIELD_DESC)==0)
      serialize_BillingDetailsStruct(PSP_BILLINGDETAILS_FIELD_DESC, (char *)(*ptr), (struct Buffer *)pOut);
    else
    if (strcmp(structFieldsDesc[i], PSP_SHIPPINGDETAILS_FIELD_DESC)==0)
      serialize_ShippingDetailsStruct(PSP_SHIPPINGDETAILS_FIELD_DESC, (char *)(*ptr), (struct Buffer *)pOut);
    else
    if (strcmp(structFieldsDesc[i], PSP_ORDERDETAILS_FIELD_DESC)==0)
      serialize_OrderDetailsStruct(PSP_ORDERDETAILS_FIELD_DESC, (char *)(*ptr), (struct Buffer *)pOut);
    else
    if (strcmp(structFieldsDesc[i], PSP_AIRLINEDETAILS_FIELD_DESC)==0) 
      serialize_AirlineDetailsStruct(PSP_AIRLINEDETAILS_FIELD_DESC, (char *)(*ptr), (struct Buffer *)pOut);
    else
    if (strcmp(structFieldsDesc[i], PSP_VAULTREFERENCE_FIELD_DESC)==0)
      if (structFieldsType[i]->max_fields == 1) 
        serialize_VaultReference3pStruct(PSP_VAULTREFERENCE_FIELD_DESC, (char *)(*ptr), (struct Buffer *)pOut);
      else
        serialize_VaultReference2pStruct(PSP_VAULTREFERENCE_FIELD_DESC, (char *)(*ptr), (struct Buffer *)pOut);
    else      
    if (strcmp(structFieldsDesc[i], PSP_PAYMENTMETHOD_FIELD_DESC)==0)
      serialize_PaymentMethodInputDetailsStruct(PSP_PAYMENTMETHOD_FIELD_DESC, (char *)(*ptr), (struct Buffer *)pOut);
    else
    if (strcmp(structFieldsDesc[i], PSP_CARDINPUTDETAILS_FIELD_DESC)==0)
      serialize_CardInputDetailsStruct(PSP_CARDINPUTDETAILS_FIELD_DESC, (char *)(*ptr), (struct Buffer *)pOut);
    else
    if (strcmp(structFieldsDesc[i], PSP_PERSON_FIELD_DESC)==0)
      serialize_PersonStruct(PSP_PERSON_FIELD_DESC, (char *)(*ptr), (struct Buffer *)pOut);
    else
    if (strcmp(structFieldsDesc[i], PSP_ADDRESS_FIELD_DESC)==0)
      serialize_AddressStruct(PSP_ADDRESS_FIELD_DESC, (char *)(*ptr), (struct Buffer *)pOut);
    else       
    if (strcmp(structFieldsDesc[i], PSP_TRANSACTIONS_FIELD_DESC)==0)   
      switch (type) {
	case SPLIT_PAY_ONLINE_2P_TYPE:
          serialize_ArrayOf_RequerimientoStruct_SplitPayOnLine_2p_Transactions(PSP_TRANSACTIONS_FIELD_DESC, (char *)(*ptr), (struct Buffer *)pOut);
	  break;
	case SPLIT_AUTHORIZE_2P_TYPE:
          serialize_ArrayOf_RequerimientoStruct_SplitAuthorize_2p_Transactions(PSP_TRANSACTIONS_FIELD_DESC, (char *)(*ptr), (struct Buffer *)pOut);
	  break;
	case SPLIT_PAY_ONLINE_3P_TYPE:	  
	  serialize_ArrayOf_RequerimientoStruct_SplitPayOnLine_3p_Transactions(PSP_TRANSACTIONS_FIELD_DESC, (char *)(*ptr), (struct Buffer *)pOut);
	  break;
	case SPLIT_AUTHORIZE_3P_TYPE:	  
	  serialize_ArrayOf_RequerimientoStruct_SplitAuthorize_3p_Transactions(PSP_TRANSACTIONS_FIELD_DESC, (char *)(*ptr), (struct Buffer *)pOut);
	  break;
      }
    else 
      serialize_string(structFieldsDesc[i], (char *)(*ptr), (struct Buffer *)pOut);
  }
      
}
    
