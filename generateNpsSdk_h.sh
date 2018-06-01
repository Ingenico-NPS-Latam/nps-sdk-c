###############################################################
# Input files: 
#    npsSdk_h.template
# Output file
#    npsSdk.h
###############################################################
methods=()
rm rootStructs.h

GenerateArrayOfStructs()
{
  if [ -e ${1}.tmp ]; then
    return
  fi

  local field=$(echo ${1} | cut -f2 -d"_")
  field=${field/Struct/} 

  local genStructsP1=${field} 
  local genStructsP2=${field:0:-6}Struct

  local isRootArray=$(echo ${1} | grep "ArrayOf_RequerimientoStruct_" | wc -l)
  if [ @${isRootArray} == @0 ]; then
    isRootArray=$(echo ${1} | grep "ArrayOf_RespuestaStruct_" | wc -l)
    if [ @${isRootArray} == @1 ]; then
      field=${1:8}
      genStructsP1=${field}
      genStructsP2=${field:0:-6}
    fi
  else
    field=${1:8}
    genStructsP1=${field}
    genStructsP2=${field:0:-6}
  fi
  
  local typedef=${1}
  typedef=${typedef:0:-6}
  local structDef=$(grep "typedef struct ${typedef} " NpsMethods.h)
  local structDef=$(echo ${structDef:0:-1} | cut -f4 -d" ")

  if [ -e genericArrayOf.tmp ]; then
    echo "/****************************************" > ${1}.tmp
  else
    echo "static int ArrayOf_FieldsIdx[]=" > genericArrayOf.tmp
    echo "{" >> genericArrayOf.tmp
    echo "    ARRAY_PTR," >> genericArrayOf.tmp
    echo "    ARRAY_SIZE" >> genericArrayOf.tmp
    echo "};" >> genericArrayOf.tmp
    echo "static char *ArrayOf_FieldsDesc[]=" >> genericArrayOf.tmp
    echo "{" >> genericArrayOf.tmp
    echo "    ARRAY_PTR_FIELD_DESC," >> genericArrayOf.tmp
    echo "    ARRAY_SIZE_FIELD_DESC" >> genericArrayOf.tmp
    echo "};" >> genericArrayOf.tmp
    echo "" >> genericArrayOf.tmp
    cat genericArrayOf.tmp > ${1}.tmp
    echo "/****************************************" >> ${1}.tmp
  fi

  echo " * ${1}" >> ${1}.tmp
  echo "****************************************/" >> ${1}.tmp
  echo "static size_t inicio${1}[]="  >> ${1}.tmp
  echo "{" >> ${1}.tmp
  echo "    offsetof(${structDef}, ARRAY_PTR_FIELD)," >> ${1}.tmp
  echo "    offsetof(${structDef}, ARRAY_SIZE_FIELD)" >> ${1}.tmp
  echo "};" >> ${1}.tmp
  echo "static struct nps_generics *${1}Type[]=" >> ${1}.tmp
  echo "{" >> ${1}.tmp
  echo "    &${field}," >> ${1}.tmp
  GenerateStructs ${genStructsP1} ${genStructsP2} "1"
  echo "    NULL" >> ${1}.tmp
  echo "};" >> ${1}.tmp
  echo "static struct nps_generics ${1}=" >> ${1}.tmp
  echo "{" >> ${1}.tmp
  echo "    &ArrayOf_FieldsIdx, " >> ${1}.tmp
  echo "    &ArrayOf_FieldsDesc, " >> ${1}.tmp
  echo "    &inicio${1}, " >> ${1}.tmp
  echo "    2,  " >> ${1}.tmp
  echo "    sizeof(${structDef}), " >> ${1}.tmp
  echo "    &${1}Type, " >> ${1}.tmp
  echo "};" >> ${1}.tmp
  echo "" >> ${1}.tmp

  cat structures.tmp ${1}.tmp > structures_ArrayOf.tmp
  cat structures_ArrayOf.tmp > structures.tmp

}

GenerateStructs()
{
  if [ -e ${1}.tmp ]; then
    return
  fi

  
  local structDef=$(grep "typedef struct ${2} " NpsMethods.h)
  local structDef=$(echo ${structDef:0:-1} | cut -f4 -d" ")
  local STDOUT=$(sed -n "/struct ${2}$/,/};/{//!p;}" NpsStructures.h)

  local field=""
  echo "/****************************************" > ${1}.tmp
  echo " * ${1} " >> ${1}.tmp
  echo " ****************************************/" >> ${1}.tmp
  echo "static int ${1}Idx[]=" >> ${1}.tmp
  echo "{" >> ${1}.tmp
  local let countFields=0
  local lineStruct=""
  while read lineStruct; do

    isField=`echo ${lineStruct} | grep "{" | wc -l`

    if [ @${isField} == @0 ]; then
      #field=`echo ${lineStruct//[[:blank:]]/} | cut -f2 -d"*" | cut -f1 -d";"|tr '/a-z/' '/A-Z/'`
      field=`echo ${lineStruct//[[:blank:]]/} | cut -f2 -d"*" | cut -f1 -d";"`
      field=`grep " ${field}$" NpsMethods.h | grep -v "//" | cut -f2 -d" "`
      echo "    ${field:0:-6}," >> ${1}.tmp

      let countFields=${countFields}+1
    fi
  done <<< "${STDOUT}"
  echo "};" >> ${1}.tmp
  echo "static char *${1}Desc[]=" >> ${1}.tmp
  echo "{" >> ${1}.tmp
  while read lineStruct; do
    isField=`echo ${lineStruct} | grep "{" | wc -l`

    if [ @${isField} == @0 ]; then
      #field=`echo ${lineStruct//[[:blank:]]/} | cut -f2 -d"*" | cut -f1 -d";"|tr '/a-z/' '/A-Z/'`
      field=`echo ${lineStruct//[[:blank:]]/} | cut -f2 -d"*" | cut -f1 -d";"`
      field=`grep " ${field}$" NpsMethods.h | grep -v "//" | cut -f2 -d" "`
      echo "    ${field}_DESC," >> ${1}.tmp
    fi
  done <<< "${STDOUT}"
  echo "    NULL" >> ${1}.tmp
  echo "};" >> ${1}.tmp
  echo "static size_t inicio${1}[][ARR_OFFSET_COUNT]=" >> ${1}.tmp
  echo "{" >> ${1}.tmp
  while read lineStruct; do
    isField=`echo ${lineStruct} | grep "{" | wc -l`

    if [ @${isField} == @0 ]; then
      #field=`echo ${lineStruct//[[:blank:]]/} | cut -f2 -d"*" | cut -f1 -d";"|tr '/a-z/' '/A-Z/'`
      field=`echo ${lineStruct//[[:blank:]]/} | cut -f2 -d"*" | cut -f1 -d";"`
      field=`grep " ${field}$" NpsMethods.h | grep -v "//" |cut -f2 -d" "`
      echo "  { offsetof(${structDef}, ${field}), PRD_${structDef}_${field}, SBX_${structDef}_${field}, STG_${structDef}_${field}}," >> ${1}.tmp
    fi
  done <<< "${STDOUT}"

  echo "};" >> ${1}.tmp
  echo "static struct nps_generics *${1}Type[]="  >> ${1}.tmp
  echo "{" >> ${1}.tmp
  while read lineStruct; do
    isField=`echo ${lineStruct} | grep "{" | wc -l`
    if [ @${isField} == @0 ]; then
      isChar=`echo ${lineStruct} | grep "char\* " | wc -l`

      if [ @${isChar} == @1 ]; then
        echo "    NULL," >> ${1}.tmp
      else
        field=`echo ${lineStruct} | cut -f1 -d"*" | cut -f2 -d" "`
        isArray=`echo ${field} | grep "ArrayOf" | wc -l`

        if [ @${isArray} == @1 ]; then
          echo "    &${field}Fields," >> ${1}.tmp
          GenerateArrayOfStructs ${field}Fields
        else
          echo "    &${field/Struct/Fields}," >> ${1}.tmp
          GenerateStructs ${field/Struct/Fields} ${field}
        fi
      fi
    fi
  done <<< "${STDOUT}"

 echo "};" >> ${1}.tmp
 echo "static struct nps_generics ${1}="  >> ${1}.tmp
 echo "{" >> ${1}.tmp 
 echo "  &${1}Idx, "  >> ${1}.tmp
 echo "  &${1}Desc, "  >> ${1}.tmp
 echo "  &inicio${1}, "  >> ${1}.tmp
 echo "  ${countFields}, "  >> ${1}.tmp
 if [ $# -eq 3 ]; then
   echo "  sizeof(${structDef} *), "  >> ${1}.tmp
 else
   echo "  sizeof(${structDef}), "  >> ${1}.tmp
 fi

 echo "  &${1}Type, "  >> ${1}.tmp
 echo "};" >> ${1}.tmp
 echo "" >> ${1}.tmp

 cat structures.tmp ${1}.tmp > structures_aux.tmp
 cat structures_aux.tmp > structures.tmp
}

GenerateReqStructs()
{
  STDOUT=$(sed -n "/struct RequerimientoStruct_${2}$/,/};/{//!p;}" NpsStructures.h)

  echo "/****************************************" >> rootStructs.h
  echo "* ReqFields_${2}                           " >> rootStructs.h
  echo "****************************************/" >> rootStructs.h
  echo "static int ReqFieldsIdx_${2}[]=" >> rootStructs.h
  echo "{" >> rootStructs.h
  while read line; do
    isChar=`echo ${line} | grep "char\* " | grep -v "psp_SecureHash" | wc -l`

    if [ @${isChar} == @1 ]; then
      #field=`echo ${line//[[:blank:]]/} | cut -f1 -d";"|tr '/a-z/' '/A-Z/'`
      field=`echo ${line//[[:blank:]]/} | cut -f1 -d";" | cut -f2 -d"*"`
      field=`grep " ${field}$" NpsMethods.h | cut -f2 -d" "`
      echo "    ${field:0:-6}," >> rootStructs.h
    fi
  done <<< "${STDOUT}"
  echo "    -1" >> rootStructs.h
  echo "};" >> rootStructs.h

  echo "" >> rootStructs.h
  echo "static char *ReqFieldsDesc_${2}[]=" >> rootStructs.h
  echo "{" >> rootStructs.h
  while read line; do
    isField=`echo ${line} | grep "{" | wc -l`

    if [ @${isField} == @0 ]; then
      #field=`echo ${line//[[:blank:]]/} | cut -f2 -d"*" | cut -f1 -d";"|tr '/a-z/' '/A-Z/'`
      field=`echo ${line//[[:blank:]]/} | cut -f2 -d"*" | cut -f1 -d";" | cut -f2 -d"*"`
      field=`grep " ${field}$" NpsMethods.h | cut -f2 -d" "`

      echo "    ${field}_DESC," >> rootStructs.h
    fi
  done <<< "${STDOUT}"
  echo "};" >> rootStructs.h

  echo "" >> rootStructs.h
  echo "static size_t inicioReqStruct_${2}[][ARR_OFFSET_COUNT]=" >> rootStructs.h
  echo "{" >> rootStructs.h
  while read line; do
    isField=`echo ${line} | grep "{" | wc -l`

    if [ @${isField} == @0 ]; then
      #field=`echo ${line//[[:blank:]]/} | cut -f2 -d"*" | cut -f1 -d";"|tr '/a-z/' '/A-Z/'`
      field=`echo ${line//[[:blank:]]/} | cut -f2 -d"*" | cut -f1 -d";" | cut -f2 -d"*"`
      field=`grep " ${field}$" NpsMethods.h | cut -f2 -d" "`
      echo "  { offsetof(${1}_REQ_STRUCT, ${field}), PRD_${1}_REQ_STRUCT_${field}, SBX_${1}_REQ_STRUCT_${field}, STG_${1}_REQ_STRUCT_${field}},  " >> rootStructs.h
    fi
  done <<< "${STDOUT}"

  echo "};" >> rootStructs.h
  echo "" >> rootStructs.h
  echo "static struct nps_generics *ReqFieldsType_${2}[]=" >> rootStructs.h
  echo "{" >> rootStructs.h
  while read line; do
    isField=`echo ${line} | grep "{" | wc -l`
    if [ @${isField} == @0 ]; then
      isChar=`echo ${line} | grep "char\* " | wc -l`

      if [ @${isChar} == @1 ]; then
        echo "    NULL," >> rootStructs.h
      else
        field=`echo ${line} | cut -f1 -d"*" | cut -f2 -d" "`
        isArray=`echo ${field} | grep "ArrayOf" | wc -l`

        if [ @${isArray} == @1 ]; then
          echo "    &${field}Fields," >> rootStructs.h
          GenerateArrayOfStructs ${field}Fields
        else
          echo "    &${field/Struct/Fields}," >> rootStructs.h
          GenerateStructs ${field/Struct/Fields} ${field}
        fi
      fi
    fi
  done <<< "${STDOUT}"

  echo "};" >> rootStructs.h
  echo "" >> rootStructs.h
}

GenerateRespStructs()
{
  local STDOUT=$(sed -n "/struct RespuestaStruct_${2}$/,/};/{//!p;}" NpsStructures.h)

  local field=""
  local line=""
  echo "/****************************************" >> rootStructs.h
  echo "* RespFields_${2}                           " >> rootStructs.h
  echo "****************************************/" >> rootStructs.h
  echo "static int RespFieldsIdx_${2}[]=" >> rootStructs.h
  echo "{" >> rootStructs.h

  while read line; do
    isField=`echo ${line} | grep "{" | wc -l`

    if [ @${isField} == @0 ]; then
      #field=`echo ${line//[[:blank:]]/} | cut -f2 -d"*" | cut -f1 -d";"|tr '/a-z/' '/A-Z/'`
      field=`echo ${line//[[:blank:]]/} | cut -f2 -d"*" | cut -f1 -d";"`
      field=`grep " ${field}$" NpsMethods.h | cut -f2 -d" "`
      echo "    ${field:0:-6}," >> rootStructs.h
    fi
  done <<< "${STDOUT}"
  echo "    -1" >> rootStructs.h
  echo "};" >> rootStructs.h

  echo "" >> rootStructs.h
  echo "static char *RespFieldsDesc_${2}[]=" >> rootStructs.h
  echo "{" >> rootStructs.h
  while read line; do
    isField=`echo ${line} | grep "{" | wc -l`

    if [ @${isField} == @0 ]; then
      #field=`echo ${line//[[:blank:]]/} | cut -f2 -d"*" | cut -f1 -d";"|tr '/a-z/' '/A-Z/'`
      field=`echo ${line//[[:blank:]]/} | cut -f2 -d"*" | cut -f1 -d";"`
      field=`grep " ${field}$" NpsMethods.h | cut -f2 -d" "`
      echo "    ${field}_DESC," >> rootStructs.h
    fi
  done <<< "${STDOUT}"
  echo "    NULL" >> rootStructs.h
  echo "};" >> rootStructs.h

  echo "" >> rootStructs.h
  echo "static size_t inicioRespStruct_${2}[][ARR_OFFSET_COUNT]=" >> rootStructs.h
  echo "{" >> rootStructs.h
  while read line; do
    isField=`echo ${line} | grep "{" | wc -l`

    if [ @${isField} == @0 ]; then
      #field=`echo ${line//[[:blank:]]/} | cut -f2 -d"*" | cut -f1 -d";"|tr '/a-z/' '/A-Z/'`
      field=`echo ${line//[[:blank:]]/} | cut -f2 -d"*" | cut -f1 -d";" | cut -f2 -d"*"`
      field=`grep " ${field}$" NpsMethods.h | cut -f2 -d" "`
      echo "  { offsetof(${1}_RESP_STRUCT, ${field}), PRD_${1}_RESP_STRUCT_${field}, SBX_${1}_RESP_STRUCT_${field}, STG_${1}_RESP_STRUCT_${field}},  " >> rootStructs.h
    fi
  done <<< "${STDOUT}"

  echo "};" >> rootStructs.h
  echo "" >> rootStructs.h
  echo "static struct nps_generics *RespFieldsType_${2}[]=" >> rootStructs.h
  echo "{" >> rootStructs.h
  while read line; do

    isField=`echo ${line} | grep "{" | wc -l`
    if [ @${isField} == @0 ]; then
      isChar=`echo ${line} | grep "char\* " | wc -l`

      if [ @${isChar} == @1 ]; then
        echo "    NULL," >> rootStructs.h
      else
        local fieldArray=$( echo ${line} | cut -f1 -d"*" | cut -f2 -d" " )
        isArray=`echo ${fieldArray} | grep "ArrayOf" | wc -l`

        if [ @${isArray} == @1 ]; then
          if [ -e ${fieldArray} ]; then
            echo "    &${fieldArray:0:-4}," >> rootStructs.h
          else
            echo "    &${fieldArray}Fields," >> rootStructs.h
            GenerateArrayOfStructs ${fieldArray}Fields
          fi
        else
          echo "    &${fieldArray/Struct/Fields}," >> rootStructs.h
          GenerateStructs ${fieldArray/Struct/Fields} ${fieldArray}
        fi
      fi
    fi
  done <<< "${STDOUT}"

  echo "};" >> rootStructs.h
  echo "" >> rootStructs.h
}

GenerateRootStructs()
{
  GenerateReqStructs $1 $2
  GenerateRespStructs $1 $2
}

let n=`grep -n "enum methods {" npsSdk_h.template | cut -f1 -d":"`
let totLines=`cat npsSdk_h.template | wc -l`
let totMethods=0

let tailFrom=${totLines}-${n}
let endEnumMethods=0
let i=0
STDOUT=$(tail -n${tailFrom} npsSdk_h.template)
while read mainLine; do
  let exists=`echo ${mainLine} | grep "};" | wc -l`
  if [ @${exists} == @1 ]; then
    break;
  else
    let exists=`echo ${mainLine} | grep "TOTAL_METHODS" | wc -l`
    if [ @${exists} == @1 ]; then
      break;
    else
      let totMethods=${totMethods}+1
      field_type=`echo "${mainLine}" | cut -f1 -d"," | cut -f1 -d"="`
      methods+=(${field_type:0:-5})
    fi
  fi
done <<< "${STDOUT}"

let startMethodsFields=0
let requestMethodsFieldsDone=0
let startMethodsRespFields=0
let respMethodsFieldsDone=0

let n=`grep -n "END STRUCTURES DEFINES" npsSdk_h.template | cut -f1 -d":"`
let tailFrom=${totLines}-${n}
rm npsSdk_1.h -f
echo "" > structures.tmp
tail -n${tailFrom} npsSdk_h.template | while read mainLine; do

  if [ @${requestMethodsFieldsDone} == @0 ]; then
    if [ @${startMethodsFields} == @0 ]; then
      echo ${mainLine} >> npsSdk_1.h
      let exists=`echo ${mainLine} | grep "static struct nps_generics methodsFields" | wc -l`
      if [ @${exists} == @1 ]; then
        let startMethodsFields=1
      fi
    else

      let exists=`echo ${mainLine} | grep "RequerimientoStruct" | wc -l`
      if [ @${exists} == @0 ]; then
        echo $mainLine >> npsSdk_1.h
      else
        for (( i=0; i<${#methods[@]}; i++ )); do
          replaceTo=`grep "define ${methods[$i]} " NpsMethods.h | cut -f2 -d'"'`
          echo "  ${mainLine}" | sed "s/RequerimientoStruct/${replaceTo}/g" | sed "s/REQ_STRUCT/${methods[$i]}_REQ_STRUCT/g" >> npsSdk_1.h
          echo "  ${mainLine}" | sed "s/RequerimientoStruct/${replaceTo}/g" | sed "s/REQ_STRUCT/${methods[$i]}_REQ_STRUCT/g"
          GenerateRootStructs ${methods[$i]} ${replaceTo}
        done
        let requestMethodsFieldsDone=1
      fi
    fi
  else
    if [ @${respMethodsFieldsDone} == @0 ]; then
      if [ @${startMethodsRespFields} == @0 ]; then
        echo ${mainLine} >> npsSdk_1.h
        let exists=`echo ${mainLine} | grep "static struct nps_generics methodsRespFields" | wc -l`
        if [ @${exists} == @1 ]; then
          let startMethodsRespFields=1
        fi
      else

        let exists=`echo ${mainLine} | grep "RespuestaStruct" | wc -l`
        if [ @${exists} == @0 ]; then
          echo $mainLine >> npsSdk_1.h
        else
          for (( i=0; i<${#methods[@]}; i++ )); do
            replaceTo=`grep "define ${methods[$i]} " NpsMethods.h | cut -f2 -d'"'`
            echo "  ${mainLine}" | sed "s/RespuestaStruct/${replaceTo}/g" | sed "s/RESP_STRUCT/${methods[$i]}_RESP_STRUCT/g" >> npsSdk_1.h
            echo "  ${mainLine}" | sed "s/RespuestaStruct/${replaceTo}/g" | sed "s/RESP_STRUCT/${methods[$i]}_RESP_STRUCT/g" 
          done
          let respMethodsFieldsDone=1
        fi
      fi
    else
      echo "${mainLine}" >> npsSdk_1.h
    fi
    
  fi

done

let n=`grep -n "START STRUCTURES DEFINES" npsSdk_h.template | cut -f1 -d":"`
let n=${n}-1
head -n${n} npsSdk_h.template > npsSdk_2.h
cat structures.tmp >> npsSdk_2.h
cat rootStructs.h >> npsSdk_2.h
cat npsSdk_1.h >> npsSdk_2.h
cp npsSdk_2.h npsSdk.h
rm  rootStructs.h; rm npsSdk_1.h; rm npsSdk_2.h; rm *tmp

