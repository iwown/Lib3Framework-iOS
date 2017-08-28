#!/bin/bash

#Verify variable is provided
if [ "$1" = "" ]; then
        echo -e "Version number not provide"
        exit 1
fi

VERSION=$1

sed -i "" "s/\([0-9]\)\.\([0-9]\)\.\([0-9]\)/${VERSION}/g" BLE3Framework.podspec
git commit -am '${VERSION}' 
git push
git tag ${VERSION}
git push --tags
pod lib lint
pod trunk push BLE3Framework.podspec
