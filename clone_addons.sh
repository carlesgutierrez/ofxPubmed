#!/bin/bash
# Dependencies for httpRequestPubMed Addon

cd ../../../addons

if [ -z $1 ]; then
PREFIX="git clone https://github.com/"
else
PREFIX="git clone git@github.com:"
fi

${PREFIX}carlesgutierrez/ofxUI.git
${PREFIX}Flightphase/ofxFTGL.git
${PREFIX}jefftimesten/ofxJSON.git
