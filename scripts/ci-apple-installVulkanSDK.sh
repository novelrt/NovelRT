echo "NovelRT Vulkan SDK + MoltenVK installer for macOS"
echo "This utility is only meant for CI purposes only!"
echo ""

if [[ ! -n $1 ]];
then 
    echo "No version parameter passed."
else
    if [[ ! -n $2 ]];
    then
        echo "No destination directory passed."
    else
        version=$1
        sdk_path=$2
        url=https://sdk.lunarg.com/sdk/download/$version/mac/vulkansdk-macos-$version.dmg?Human=true
        echo "Downloading Vulkan SDK v.$version"

        #Download the SDK
        cat > $RUNNER_TEMP/vulkan_sdk.dmg
        curl -L -o $RUNNER_TEMP/vulkan_sdk.dmg $url
        if test -f $RUNNER_TEMP/vulkan_sdk.dmg; then

            #Mount the dmg
            test -f $RUNNER_TEMP/vulkan_sdk.dmg
            mountpoint=$(hdiutil attach $RUNNER_TEMP/vulkan_sdk.dmg | grep -o "\S.*vulkansdk-.*" | awk 'END {print $NF}')
            if [[ -d $mountpoint ]] ; then
                echo "Mounted dmg image: '$RUNNER_TEMP/vulkan_sdk.dmg' (mountpoint=$mountpoint)" >&2
            else
                echo "Could not mount dmg image: $RUNNER_TEMP/vulkan_sdk.dmg (mountpoint=$mountpoint)" >&2
                exit -1
            fi

            sudo $mountpoint/InstallVulkan.app/Contents/MacOS/InstallVulkan --root "$sdk_path/$version" --accept-licenses --default-answer --confirm-command install
            hdiutil detach $mountpoint

            #Write the VULKAN_SDK env var to the Github Environment variables
            echo "VULKAN_SDK=$sdk_path/$version/macOS" >> $GITHUB_ENV
            if test -f $sdk_path/$version/macOS/lib/libvulkan.dylib; then
                echo "Found libvulkan.dylib!"
            else
                echo "Could not find libvulkan.dylib!"
                exit -1
            fi
            if test -f $sdk_path/$version/MoltenVK/dynamic/dylib/macOS/libMoltenVK.dylib; then
                echo "Found MoltenVK!"
            else
                if test -f $sdk_path/$version/MoltenVK/dylib/macOS/libMoltenVK.dylib; then
                    echo "Found MoltenVK in legacy path!"
                else
                    echo "Could not find MoltenVK!"
                    exit -1
            fi
        else
            echo "Could not download Vulkan SDK! Check curl output for more information."
            exit -1
        fi
    fi
fi
