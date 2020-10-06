res1=$(date +%s.%N)

## VARIABLES ##
folder="$1"
tester="$2"

## Mocked functions
#mock1="$3"
#mock2="$4"

## Inlude ##
#include="$5"

if [ -d "$folder/output" ]; then
echo "Diretorio output já existe" ;
else
`mkdir -p $folder/output`;
echo "Diretorio output criado"
fi

cd "$folder"

#touch time.txt

gcc $tester -I $include -Wl,--wrap=$mock1,--wrap=$mock2 -lcmocka 2> output/rtc_err.txt

./a.out 2> output/rtc.txt

res2=$(date +%s.%N)
dt=$(echo "$res2 - $res1" | bc)
dd=$(echo "$dt/86400" | bc)
dt2=$(echo "$dt-86400*$dd" | bc)
dh=$(echo "$dt2/3600" | bc)
dt3=$(echo "$dt2-3600*$dh" | bc)
dm=$(echo "$dt3/60" | bc)
ds=$(echo "$dt3-60*$dm" | bc)

LC_NUMERIC=C printf "Runtime RTC: %d:%02d:%02d:%02.4f\n" $dd $dh $dm $ds >> "./time.txt"