#!/bin/sh
SWAP=/tmp/swap
dd if=/dev/zero of=$SWAP bs=1M count=500
mkswap $SWAP
sudo swapon $SWAP
