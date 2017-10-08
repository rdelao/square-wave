#!/usr/bin/env bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

OUTFILE="${DIR}/data.txt"

cd ${DIR}
hidden_amplitude=$(./white_noise_gen ${OUTFILE} | grep -Po "\d\.\d+")
./detect ${OUTFILE} ${hidden_amplitude}

rm ${OUTFILE}
