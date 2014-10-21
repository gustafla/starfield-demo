#!/bin/bash

function cleanup {
    killall esfragt
    killall starfield
}

trap cleanup EXIT

./starfield -w 1920 -h 1080 -f &
sleep 1
esfragt ovl.frag -w 1920 -h 1080 -i mehuovl.tga -d -f
