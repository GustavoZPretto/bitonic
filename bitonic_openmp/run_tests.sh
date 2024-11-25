EXECUTABLE="./bitonic"

FILE_SIZE=$1
MAX_THREADS=$2
CNT_THRESHOLD=$3

for ((i=1; i<=FILE_SIZE; i++))
do
    x=$((2**i))
    THREAD_NUM=1
    while [ $THREAD_NUM -le $MAX_THREADS ]; do
        if [ $x -ge 128 ]; then
            $EXECUTABLE "../inputs/sd_${x}x7.in" $THREAD_NUM $CNT_THRESHOLD
        fi
        if [ $THREAD_NUM -eq 1 ]; then
            THREAD_NUM=2
        else
            THREAD_NUM=$((THREAD_NUM + 2))
        fi
    done
done
