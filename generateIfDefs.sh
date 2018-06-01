###############################################################
# Input files: 
#    NpsStructures.h
#    NpsProduction.h
#    NpsSandbox.h
#    NpsStaging.h
# Description: 
# for each field in each structure defined in NpsStructures.h
# check if exists in each environment and structure.
# Output file
#    ifdefs.h
###############################################################
echo "#ifndef IFDEFS_H" > ifdefs.h
echo "#define IFDEFS_H" >> ifdefs.h
echo "" >> ifdefs.h

echo "#ifdef __cplusplus" >> ifdefs.h
echo 'extern "C" {' >> ifdefs.h
echo "#endif" >> ifdefs.h
echo "" >> ifdefs.h

let i=0
let j=0
let beginStruct=0
let endStruct=0
structAux=""
structName=""
fieldAux=""
fieldName=""
cat NpsStructures.h | while read line
do
  let i=$i+1
  if [ @${beginStruct} == @0 ]; then

    if [ "${line:0:7}" == "struct " ]; then
      if [ `echo ${line} | grep "*" | wc -l` = 0 ]; then
        if [ `echo ${line} | grep "ArrayOf_" | wc -l` = 0 ]; then
          let j=$j+1
          let beginStruct=1
          let endStruct=0
          structAux=${line:7}
          impure=`grep "struct ${structAux} " NpsMethods.h | cut -f1 -d";"`
          structName="${impure##*[[:blank:]]}"
          echo "$i $j [${structAux}] [${structName}]"
          sed -n "/struct ${structAux}/,/};/p" NpsProduction.h > prd_${structAux}.h
          sed -n "/struct ${structAux}/,/};/p" NpsSandbox.h > sbx_${structAux}.h
          sed -n "/struct ${structAux}/,/};/p" NpsStaging.h > stg_${structAux}.h
        fi
      fi
    fi

  else
    if [ "${line:0:1}" != "{" ]; then
      if [ "${line:0:2}" == "};" ]; then
        let beginStruct=0
        let endStruct=1
        rm *_${structAux}.h
      else
        fieldAux=`echo ${line} | cut -f2 -d"*" | cut -f2 -d" "`
        fieldName=`grep "  ${fieldAux}$" NpsMethods.h | grep -v "//" | cut -f2 -d" "`
        if [ ${#fieldName} == 0 ]; then
          echo "            ${structName} field [${fieldAux}] [${fieldName}]len(${#fieldName})"
          echo "Campo [${fieldAux}] en struct [${structName}] no encontrado en NpsMethods.h!!!!! "
          exit
        fi
        echo "            ${structName} field [${fieldAux}] [${fieldName}]"

        exists=`grep " ${fieldAux}" prd_${structAux}.h | wc -l`
        if [ @$exists == @0 ]; then
          echo "#define PRD_${structName}_${fieldName} -1 " >> prd_ifdefs.h
        else
          echo "#define PRD_${structName}_${fieldName} 1 " >> prd_ifdefs.h        
        fi
        exists=`grep " ${fieldAux}" sbx_${structAux}.h | wc -l`
        if [ @$exists == @0 ]; then
          echo "#define SBX_${structName}_${fieldName} -1 " >> sbx_ifdefs.h
        else
          echo "#define SBX_${structName}_${fieldName} 1 " >> sbx_ifdefs.h        
        fi
        exists=`grep " ${fieldAux}" stg_${structAux}.h | wc -l`
        if [ @$exists == @0 ]; then
          echo "#define STG_${structName}_${fieldName} -1 " >> stg_ifdefs.h
        else
          echo "#define STG_${structName}_${fieldName} 1 " >> stg_ifdefs.h        
        fi

      fi
    fi
  fi
done

cat prd_ifdefs.h >> ifdefs.h
echo " " >> ifdefs.h
cat sbx_ifdefs.h >> ifdefs.h
echo " " >> ifdefs.h
cat stg_ifdefs.h >> ifdefs.h
echo " " >> ifdefs.h

rm prd_ifdefs.h
rm sbx_ifdefs.h
rm stg_ifdefs.h

echo "#ifdef __cplusplus" >> ifdefs.h
echo "}" >> ifdefs.h
echo "#endif" >> ifdefs.h

echo "#endif" >> ifdefs.h
