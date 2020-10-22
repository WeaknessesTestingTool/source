res1=$(date +%s.%N)

cd src
#javac TestingCWE.java
java TestingCWE
cd ../

res2=$(date +%s.%N)
dt=$(echo "$res2 - $res1" | bc)
dd=$(echo "$dt/86400" | bc)
dt2=$(echo "$dt-86400*$dd" | bc)
dh=$(echo "$dt2/3600" | bc)
dt3=$(echo "$dt2-3600*$dh" | bc)
dm=$(echo "$dt3/60" | bc)
ds=$(echo "$dt3-60*$dm" | bc)

LC_NUMERIC=C printf "Runtime Input AFL: %d:%02d:%02d:%02.4f\n" $dd $dh $dm $ds >> "./Files/time.txt"