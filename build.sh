#!/bin/bash

help(){
    echo "Usage: $0 [board-name]"
    echo "valid board names: AZ_W100"
    exit
}

if [[ $# -lt 1 ]]
then
    config=config_minimal
else
    case $1 in
        AZ_W100)
            config=config_minimal
            ;;
        help|--help|-h|*)
            help
            ;;
    esac
fi

echo "Building image using config: '$config'"

./scripts/feeds update -a
./scripts/feeds install -a
cp .config .config_save`date +%F_%T.%N`
cp $config .config
make defconfig
make -j4 IGNORE_ERRORS=m
