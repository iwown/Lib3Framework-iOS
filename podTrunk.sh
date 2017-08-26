#!/bin/bash

VERSION=$1

sed -i "s/\d.\d.\d/${VERSION}/g" BLE3Framework.podspec
git commit -am '${VERSION}' 
git push
git tag ${VERSION}
git push --tags
pod lib lint
pod trunk push BLE3Framework.podspec
