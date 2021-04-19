#!/bin/bash
echo "Compilando"
DIR=$1
INPUT_NAME=$2
CMP_OUTPUT=$3
g++ jogoSnakeAvaliaComandos.cpp -g Snake.cpp Game.cpp Screen.cpp -o ${DIR}prog
for i in $(seq $4 $5);
do
   "${DIR}"prog < "${DIR}${INPUT_NAME}${i}.txt" > "${DIR}${CMP_OUTPUT}${i}_my.txt"
   echo "Arquivo exemplo ${i}"
   diff ${DIR}${CMP_OUTPUT}${i}_my.txt ${DIR}${CMP_OUTPUT}${i}.txt
done