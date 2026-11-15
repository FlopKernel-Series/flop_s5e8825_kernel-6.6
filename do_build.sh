#!/bin/bash
set -e

all_devs=("a25x" "m34x")

# Wrap to ckbuild.sh
export WP=${WP:-$(realpath $PWD/../)}

if [ -z "$1" ]; then
    echo "ERROR: Please specify device or 'all' to build!"
    exit 1
fi

arg_target="$1"
shift

# Buffer the passed arguments
args="$*"

devices_to_process=()
if [[ "$arg_target" == "all" ]]; then
    echo -e "\n==> Selecting all valid targets: \"${all_devs[*]}\""
    devices_to_process=("${all_devs[@]}")
else
    devices_to_process=("$arg_target")
fi

for device_name in "${devices_to_process[@]}"; do
    echo -e "\n==> Building target: \"$device_name\""

    # Check if "u", "d", and "r" are in the arguments
    contains_u=false
    contains_d=false
    contains_r=false

    if [[ "$args" == *u* ]]; then
        contains_u=true
    fi
    if [[ "$args" == *d* ]]; then
        contains_d=true
    fi
    if [[ "$args" == *r* ]]; then
        contains_r=true
    fi

    if $contains_u && $contains_d; then
        echo "INFO: Will make a regular and unlocked build"
        if $contains_r; then
            echo "INFO: Two subsequent clean builds will be made"
            # Remove only "d" from arguments
            filtered_args="${args//d/}"
            ./kernel_build/ckbuild.sh "$device_name" $filtered_args
            # Remove "u" and "d" from arguments
            filtered_args="${filtered_args//u/}"
            ./kernel_build/ckbuild.sh "$device_name" $filtered_args
        else
            # Remove only "d" from arguments
            filtered_args="${args//d/}"
            ./kernel_build/ckbuild.sh "$device_name" $filtered_args
            # Remove "u" and "c" from arguments
            filtered_args="${filtered_args//u/}"
            filtered_args="${filtered_args//c/}"
            ./kernel_build/ckbuild.sh "$device_name" $filtered_args
        fi
    elif $contains_d; then
        echo "INFO: Dual build argument ignored"
        # Remove "d" from arguments
        filtered_args="${args//d/}"
        ./kernel_build/ckbuild.sh "$device_name" $filtered_args
    else
        ./kernel_build/ckbuild.sh "$device_name" "$@"
    fi
done

echo "All targets built."
