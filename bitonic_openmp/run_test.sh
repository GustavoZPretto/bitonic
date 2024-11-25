EXECUTABLE="./bitonic"

FILE_SIZE=$1
MAX_THREADS=$2
CNT_THRESHOLD=$3

THREAD_NUM=1
while [ $THREAD_NUM -le $MAX_THREADS ]; do
    $EXECUTABLE "../inputs/sd_${FILE_SIZE}x7.in" $THREAD_NUM $CNT_THRESHOLD

    if [ $THREAD_NUM -eq 1 ]; then
        THREAD_NUM=2
    else
        THREAD_NUM=$((THREAD_NUM + 2))
    fi
done
