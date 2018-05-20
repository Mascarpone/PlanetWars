#!/bin/bash

rm -f score.txt
rm -f err.txt

die()
{
    echo $1
    exit 1
}

[ -d client ] || die "we need clients to run them"

echo "
Here are the Challengers:
"
cd client/java/
c=0
for i in *
do
    tab+=("java -jar client/java/$i")
    echo $i: $c
    let "c=c+1"

done
cd .. # root directory

cd bin/
for i in *
do
    if [ -f $i -a -x $i ]
    then
	tab+=("./client/bin/$i")
	echo $i: $c
	let "c=c+1"
    fi
done
cd ../.. # root directory
echo ""

read -p "Choose Bot 1 (Provide its number):
" number_bot1
read -p "Choose Bot 2:
" number_bot2
bot1=${tab[number_bot1]}
bot2=${tab[number_bot2]}

# read -p 'What map do you want? [1--100]:
# ' map_number
#
# map=map$map_number

read -p '
1: for 100 tests
2: for all tests
' maps_choice



echo bot1: $bot1
echo bot2: $bot2
echo maps/$map.txt
echo GO !

if [[ $maps_choice -eq 1 ]]
then
    for i in maps/*; do
	echo $i >> score.txt 
	java -jar ./tools/PlayGame.jar $i 1000 1000 log.txt "$bot1" "$bot2" 2>&1 1>/dev/null | tail -n2  >> score.txt
    done
fi
if [[ $maps_choice -eq 2 ]]
then
    for i in maps2/*; do
	echo $i >> score.txt 
	java -jar ./tools/PlayGame.jar $i 1000 1000 log.txt "$bot1" "$bot2" 2>&1 1>/dev/null | tail -n2  >> score.txt
    done
fi
# r maps/map7.txt 1000 1000 log.txt ./client/bot1 ./client/bot1
