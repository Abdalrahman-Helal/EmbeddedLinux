#! /bin/bash

IMG_DIR="~/path"
img=`ls ${IMG_DIR} | grep sdimg | head -n 1`

select option in flash erase
do 
    case ${option} in 

    flash)
    echo "Flashing right now "
    time sudo dd if=${IMG_DIR}/${img} of=/dev/mmcblk0 bs=300M 
    break
    ;;

    erase)
    echo "Earsing right now"
    sudo umount /dev/mmcblk0p1
    sudo umount /dev/mmcblk0p2
    time sudo dd =if/dev/zero of=/dev/mmcblk0 bs=100M 
    exit 0 # or break 
    ;;
    *)
    echo "Usage : 1 for Flash or 2 for Erase"
    esac
done
