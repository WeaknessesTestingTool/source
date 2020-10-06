#### EXPERIMENT CONFIGURATION ####
BIN_PATH=$(readlink -f "$0")
dir="$(dirname $BIN_PATH)"  

exp_folder="$dir/Files"
results_folder="results/"
testcases_folder="testcases/"

#### EXPERIMENT CONFIGURATION ####
tested_file="htdbm.c"
tester_file_ft="tester_htdbm_ft.c"
tester_file_rtc="tester_htdbm_rtc.c"
# mocked_function1="apr_vformatter"
# mocked_function2="buffer_output"
#include_folder="include/"

#### SCRIPTS CALL'S ####
echo "Executando casos de teste"
./runTestCases.sh $exp_folder $tester_file_rtc $mocked_function1 $mocked_function2 $include_folder

echo "Executando fuzzing teste"
./fuzzingTest.sh $exp_folder $results_folder $testcases_folder $tested_file $tester_file_ft $mocked_function1 $mocked_function2 $include_folder

echo "Executando casos de teste com inputs do AFL"
./rtcInputAFL.sh

echo "Processo Finalizado"