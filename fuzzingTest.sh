res1=$(date +%s.%N)

## VARIABLES ##
folder="$1"
results="$2"
testcases="$3"
tested="$4"
tester="$5"

## Mocked functions
#mock1="$6"
#mock2="$7"

## Inlude ##
#include="$8"

echo "$folder $results $testcases $tested $tester"

cd "$folder"

#afl-gcc -fno-stack-protector -z execstack $tester -I. -lcmocka -o fuzz #retirar .c
echo "afl-gcc $tester -I $include -Wl,--wrap=$mock1,--wrap=$mock2 -lcmocka -o fuzz"
afl-gcc $tester -I $include -Wl,--wrap=$mock1,--wrap=$mock2 -lcmocka -o fuzz

afl-fuzz -i ./testcases/ -o ./results/ ./fuzz #retirar .c

res2=$(date +%s.%N)
dt=$(echo "$res2 - $res1" | bc)
dd=$(echo "$dt/86400" | bc)
dt2=$(echo "$dt-86400*$dd" | bc)
dh=$(echo "$dt2/3600" | bc)
dt3=$(echo "$dt2-3600*$dh" | bc)
dm=$(echo "$dt3/60" | bc)
ds=$(echo "$dt3-60*$dm" | bc)

LC_NUMERIC=C printf "Runtime FT: %d:%02d:%02d:%02.4f\n" $dd $dh $dm $ds >> "./time.txt"

#modificar parametros por variáveis
#Definir temporizador ou quantidade de ciclos? Ver como definir ciclos na documentação
#Ler arquivos gerados e gerar uma saída


#Step1
# -	afl-gcc -fno-stack-protector -z execstack tester_formatstring.c -I. -lcmocka -o tester_formatstring

#Step2
# -	sudo su

#Step3 - Hmm, your system is configured to send core dump notifications to an
#    external utility. This will cause issues: there will be an extended delay
#    between stumbling upon a crash and having this information relayed to the
#    fuzzer via the standard waitpid() API.

#    To avoid having crashes misinterpreted as timeouts, please log in as root
#    and temporarily modify /proc/sys/kernel/core_pattern, like so:

# -	echo core >/proc/sys/kernel/core_pattern

#Step4
# -	afl-fuzz -i ./testcases/ -o ./results/ ./tester_formatstring

#Step5
# -	sudo su

#Step6 -Whoops, your system uses on-demand CPU frequency scaling, adjusted
#    between 488 and 2929 MHz. Unfortunately, the scaling algorithm in the
#    kernel is imperfect and can miss the short-lived processes spawned by
#    afl-fuzz. To keep things moving, run these commands as root:

#    cd /sys/devices/system/cpu
#    echo performance | tee cpu*/cpufreq/scaling_governor

#    You can later go back to the original state by replacing 'performance' with
#    'ondemand'. If you don't want to change the settings, set AFL_SKIP_CPUFREQ
#    to make afl-fuzz skip this check - but expect some performance drop.

# -	cd /sys/devices/system/cpu
# -	echo performance | tee cpu*/cpufreq/scaling_governor

#Step7
# -	afl-fuzz -i ./testcases/ -o ./results/ ./tester_formatstring

###############################

# nome="$1"
# pasta_commits="$2"
# pasta_exp="$3"
# caminho_pasta="$4"
# caminho_arquivo="$5"
# versions="$6"
# meucommit="02affb4afd4a71b0c1ca6286f9b0f6bf3b10e0a1"
# counta=0
# # "$nome $pasta_commits $pasta_exp $caminho_arquivo $caminho_pasta"
# # busybox busybox-commits-hush C:\Users\Raphael\Documents\experimento_cppcheck shell shell\hush.c
# echo "$nome $pasta_commits $pasta_exp $caminho_arquivo $caminho_pasta $versions"

# echo "CRIANDO RES"
# echo "Project,File,Date_Before,Date_After,Before,After,Changed_Lines,Impacted_Macros,Macros_Not_Impacted,Configurations,Config. With CWE,ERRO,CWE,CWE_MSG" > "res_$nome.csv"
# echo "Project,File,Date_Before,Date_After,Before,After,Changed_Lines,Impacted_Macros,Macros_Not_Impacted,Configurations,Config. With CWE,ERRO,CWE,CWE_MSG" > "results.csv"
# echo "Project,File,Date_Before,Date_After,Before,After,Changed_Lines,Impacted_Macros,Macros_Not_Impacted,Configurations,Config. With CWE,ERRO,CWE,CWE_MSG" > "results_final.csv"
# mkdir "$pasta_commits"

# echo "recuperando lista"

# cd "$nome"
# pwd
# git checkout HEAD

# echo  "#debug: $caminho_arquivo"
# git rev-list --reverse HEAD "$caminho_arquivo" > "$pasta_exp"/"$pasta_commits".txt

# pwd
# echo "git rev-list --reverse HEAD $caminho_arquivo > $pasta_exp/$pasta_commits.txt"

# cd ..

# echo "#debug: iniciando checkouts"

# for line in $(tail -n $versions "$pasta_commits".txt)
# #for line in $(cat "$pasta_commits".txt)
# do
# 	conta=$(($conta+1))
# 	echo "Contador $conta"
	
# 	 echo "$line"
# 	 cd "$nome"
# 	 git clean -dfx
# 	 git checkout $line -f #-- $caminho_pasta #altera o rep. para o commit da vez
# 	 echo -e "${line:0:7}//`git show -s --format=%ci $line`" >> "$pasta_exp/datas.txt"
# 	 cd ..
# 	 mkdir -p "$pasta_commits/$nome-${line:0:7}/$caminho_pasta"
# 	 #cp -a "$nome"/. "$pasta_commits/$nome-${line:0:7}"
# 	 cp -a "$nome"/"$caminho_arquivo" "$pasta_commits/$nome-${line:0:7}/$caminho_pasta"

# 	 #Remove Includes
# 	 #sed -i 's/#include/\/\/#include/g' "$pasta_commits/$nome-${line:0:7}/$caminho_arquivo"
# 	 #sed -i 's/# include/\/\/#include/g' "$pasta_commits/$nome-${line:0:7}/$caminho_arquivo"

# 	#if [ "$line" == "$meucommit" ]; then
# 	if [ "$conta" == "$versions" ]; then
# 		break
# 	fi

# done