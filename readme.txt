1) generacion NpsStaging.h, NpsProduction.h y NpsSandbox.h a partir del wsdl con linea de comando wsdl2h (viene con gsoap)

  1.1)
  wsdl2h -c -a -o NpsSandbox.h sandbox.wsdl -t /home/silvina/Downloads/gsoap-2.8/gsoap
  wsdl2h -c -a -o NpsStaging.h staging.wsdl -t /home/silvina/Downloads/gsoap-2.8/gsoap
  wsdl2h -c -a -o NpsProduction.h production.wsdl -t /home/silvina/Downloads/gsoap-2.8/gsoap

  1.2)
  editar archivo h generado y:
    reemplazar "ns1__" por: ""

    eliminar "USCORE"

  1.3)
  Eliminar lineas desde 1 hasta linea anterior al primer "struct " que aparezca

  1.4)
  Agregar al principio de cada archivo: (*reemplazar "Sandbox" segun el archivo*)
  #ifndef NpsSandbox_H
  #define NpsSandbox_H
  #include "NpsSandbox.h"

  #ifdef __cplusplus
  extern "C" {
  #endif

  Agrear al final del archivo:
  /* End of NpsSandbox.h */
  #ifdef __cplusplus
  }
  #endif

  #endif

  1.5) 
  sed 's/\/\/\//|/g' NpsSandbox.h | sed '/^|/d' | cut -f1 -d"|" | sed 's/1;/;/g' | sed 's/0;/;/g' > aux_sandbox.h
  sed 's/\/\/\//|/g' NpsStaging.h | sed '/^|/d' | cut -f1 -d"|" | sed 's/1;/;/g' | sed 's/0;/;/g' > aux_staging.h
  sed 's/\/\/\//|/g' NpsProduction.h | sed '/^|/d' | cut -f1 -d"|" | sed 's/1;/;/g' | sed 's/0;/;/g' > aux_production.h

  1.6) mover archivos aux_* a Nps*
    mv aux_sandbox.h NpsSandbox.h
    mv aux_staging.h NpsStaging.h
    mv aux_production.h NpsProduction.h

  1.7) 
  eliminar desde
  /******************************************************************************\
   *                                                                            *
   * Additional Top-Level Elements                                              *
   *   https://psp.localhost/ws                                                 *
   *                                                                            *
  \******************************************************************************/
  hasta 

  /* End of NpsSandbox.h */



2) Generar archivo NpsStructures.h como la union de NpsStaging.h, NpsSandbox.h y NpsProduction.h
   (Este paso aun no tiene su script. Proximamente...Mientras, a mano)
   
   cp NpsSandbox.h NpsStructures.h
   ver campos existentes en NpsStaging.h y no en NpsStructures.h y agregarlos a NpsStructures.h
   ver campos existentes en NpsProduction.h y no en NpsStructures.h y agregarlos a NpsStructures.h

   Editar NpsStructures.h y reemplar "Sandbox" x "Structures"

3)Generar archivo ifdefs.h con script generateIfDefs.sh
4)Generar archivo npsSdk.h con script generateNpsSdk_h.sh

5) Compilacion
   ===========
sudo apt-get install libcurl4-openssl-dev
sudo apt-get install libxml2-dev libxml2-doc

cd /usr/include/libxml2

con el siguiente comando se genera el archivo test que contiene la llamadas de prueba a los distintos metodos de la API.
clear;rm test;cc -o test test.c  npsSdk.c xml_save.c nps_utils.c parse_xml.c -I/usr/include/curl -I/usr/include/libxml2 -I/usr/include/openssl -lcurl -lxml2 -lcrypto 2>err.log; ls
