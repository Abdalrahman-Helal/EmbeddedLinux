# Battery Monitor Script

This is a simple Bash script that monitors your laptop battery and sends desktop notifications if the battery level drops below 50%. It also detects when the charger is plugged in and informs the user to rerun the script.

---

## Script: `battery_monitor.sh`

```bash
#! /bin/bash

# Get battery status string
BATTERY_STRING=`acpi -b`

# Split the string into an array of words
read -a BatteryValue <<< ${BATTERY_STRING}
val=${BatteryValue[3]::-1}

# Handle the '%' symbol for all battery values like 100%, 50%, 1%
temp=`echo $val | grep "%"`
if [ $? -eq 0 ]
then
    val=${val::-1}
fi

# Infinite loop to continuously check battery
while [ true ]
do
    # If battery is less than 50%
    if [ ${val} -lt 50 ]
    then
        notify-send "Your Battery is less than 50"
        notify-send "Plug your charger"
        sleep 5
        
        # Check if AC power is connected
        acpi -a | grep "on"
        if [ $? -eq 0 ]
        then
            notify-send "Thanks for charging! Please run the script again."
            break
        fi
    fi
done
```

---

## How It Works

1. **Get battery info:**

   ```bash
   BATTERY_STRING=`acpi -b`
   ```

   * Example output: `Battery 0: Discharging, 85%, 01:23:45 remaining`

2. **Split string into array:**

   ```bash
   read -a BatteryValue <<< ${BATTERY_STRING}
   val=${BatteryValue[3]::-1}
   ```

   * `BatteryValue[3]` is the battery percentage with a trailing comma.
   * `::-1` removes the last character.

3. **Remove `%` symbol if present:**

   ```bash
   temp=`echo $val | grep "%"`
   if [ $? -eq 0 ]
   then
       val=${val::-1}
   fi
   ```

   * Checks if `%` exists in the string.
   * Removes it so `val` is numeric: `85%` → `85`.
   * `$?` checks if the last command (`grep`) succeeded.

4. **Check battery level in a loop:**

   ```bash
   while [ true ]; do
       if [ ${val} -lt 50 ]; then
           notify-send "Your Battery is less than 50"
           notify-send "Plug your charger"
           sleep 5
           acpi -a | grep "on"
           if [ $? -eq 0 ]; then
               notify-send "Thanks for charging! Please run the script again."
               break
           fi
       fi
   done
   ```

   * Sends notifications if battery is below 50%.
   * Waits 5 seconds and checks if charger is connected.
   * If charging, notifies user and exits loop.

---

## Key Points

* Handles all battery values (1%, 50%, 100%) correctly.
* `$?` is used to check if the previous command succeeded.
* `notify-send` sends desktop notifications.

---

## How to Run

1. Make the script executable:

```bash
chmod +x battery_monitor.sh
```

2. Run the script:

```bash
./battery_monitor.sh
```
