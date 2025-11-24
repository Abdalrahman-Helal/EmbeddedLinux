#! /bin/bash

BATTERY_STRING=`acpi -b`
# echo $BATTERY_STRING
read -a BatteryValue <<< ${BATTERY_STRING}
val=${BatteryValue[3]::-1} 

temp=`echo $val | grep "%"` # to Handle % symbol if Battery Value is 100% , 50% , 1%
if [ $? -eq 0 ]
then 
    val=${val::-1}
fi

while [ true ]
do
    if [ ${val} -lt 50 ]
    then
        notify-send "Your Battery is less than 50"
        notify-send "Plug your charger"
        sleep 5 
        acpi -a | grep "on"
        if [ $? -eq 0 ]
        then 
            notify-send "thanks for charging and please run script again "
            break
    fi
done
