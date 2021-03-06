#!/bin/bash --login

#Verify variable is provided
if [ "$1" = "" ]; then
        echo -e "Version number not provide"
        exit 1
fi

VERSION=$1

cd /Users/leopard/GitHub/Lib3Framework-iOS/ 
sed -i "" "s/\([0-9]\)\.\([0-9]\)\.\([0-9]\)/${VERSION}/g" BLEMidAutumn.podspec
git commit -am "${VERSION}" 
git push
git tag ${VERSION}
git push --tags
pod lib lint
pod trunk push BLEMidAutumn.podspec
