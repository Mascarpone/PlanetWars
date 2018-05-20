#!/bin/bash

java -jar ./tools/PlayGame.jar ./maps/map102.txt 1000 1000 log.txt "./client/bin/chaine" "java -jar ./client/java/DualBot.jar" | java -jar ./tools/ShowGame.jar 