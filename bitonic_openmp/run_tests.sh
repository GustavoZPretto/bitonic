EXECUTABLE="./bitonic"

FILE_SIZE=$1
CNT_THRESHOLD=$3

THREAD_NUM=$2
THREAD_POWER=0
while [ $THREAD_NUM -gt 1 ]; do
    THREAD_NUM=$((THREAD_NUM / 2))
    THREAD_POWER=$((THREAD_POWER + 1))
done

for ((i=1; i<=FILE_SIZE; i++))
do
    x=$((2**i))
    for ((j=0; j<=THREAD_POWER; j++))
    do
        y=$((2**j))
        if [ $x -ge 128 ]; then
            $EXECUTABLE "../inputs/sd_${x}x7.in" $y $CNT_THRESHOLD
        fi
    done
done