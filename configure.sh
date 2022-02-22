#!/usr/bin/env bash

CHECK_FOLDERS='build'

for folder in $(echo $CHECK_FOLDERS | sed "s/,/ /g"); do
    if [[ ! -d $folder ]]; then
        echo -e "Creating $folder..."; mkdir $folder
    fi
done

