#!/usr/bin/env bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

OUTFILE="${DIR}/data.txt"

cd ${DIR}
./white_noise_gen ${OUTFILE} > tmp.txt
cat tmp.txt
hidden_amplitude=$(cat tmp.txt | grep -Po "\d\.\d+")
./detect ${OUTFILE} ${hidden_amplitude}

rm tmp.txt
rm ${OUTFILE}
