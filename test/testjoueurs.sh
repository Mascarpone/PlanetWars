#!/bin/bash

java -jar ./tools/PlayGame.jar ./maps/map"$2".txt 1000 1000 log.txt "./client/bin/chaine" "./autresbots/$1" | java -jar ./tools/ShowGame.jar 