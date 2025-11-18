# AlAdhan Prayer Times Script

This Bash script fetches **prayer times** for a specific city and country from the [AlAdhan API](http://api.aladhan.com) and displays them in a readable format.

---

## Purpose

* Demonstrate **fetching JSON data from an API** using `curl`.
* Parse and display JSON data in **Bash** using `jq`.
* Optionally, parse JSON in **Python** (shown as a separate function).
* Learn how to handle **API responses**, **arrays**, and **environment variables** in Bash.

---

## Tools Used

* `curl` → fetch data from HTTP APIs.
* `jq` → a lightweight and flexible **command-line JSON processor**.

  * Example usage:

    ```bash
    echo $res | jq '.data.timings'
    ```

    * Prints only the `timings` part of the JSON response in a readable format.
* `json_pp` → optional pretty printer for JSON (used here to format the API response).

---

## Script Overview

```bash
#!/bin/bash


# ----------------------------
# Function: Parse JSON using Python
# ----------------------------
function json_parser_usingpython()
{
    # Fetch prayer times JSON from AlAdhan API
    res=`curl "http://api.aladhan.com/v1/timingsByCity/18-11-2025?city=Giza&country=Egypt" | json_pp -f json`
    export json_file="$res"
    python3 -c "import os,json; x=os.environ['json_file'];
body=json.loads(x)['data']['timings']
for i,j, in body.items():
    print(i,j)"
}

# ----------------------------
# Function: Parse JSON using Bash (jq)
# ----------------------------
function json_parser_usingBash()
{
    # Fetch prayer times JSON from AlAdhan API
    res=`curl "http://api.aladhan.com/v1/timingsByCity/18-11-2025?city=Giza&country=Egypt" | json_pp -f json`
    echo ${res} | jq '.data.timings'
}

# Run the Bash JSON parser
json_parser_usingBash
```

---

## How it Works

1. **Fetch data:**

   * `curl` calls the AlAdhan API for prayer times.
   * `json_pp -f json` formats the JSON nicely.
   * Result is stored in the `res` variable.

2. **Parse using Python (optional):**

   * Reads the JSON from an environment variable.
   * Converts JSON string to Python dictionary.
   * Loops over timings and prints each prayer with its time.

3. **Parse using Bash (`jq`):**

   * `jq` extracts only the `timings` part from the JSON.
   * Displays it in a readable format directly in the terminal.

---

## Purpose of `jq`

* `jq` is a **command-line JSON processor**.
* It allows you to:

  * **Pretty-print JSON** (`jq .`)
  * **Extract specific fields** (`jq '.data.timings.Fajr'`)
  * **Filter and manipulate JSON** easily in Bash scripts

---

## Example Output

```json
{
  "Fajr": "05:03",
  "Sunrise": "06:21",
  "Dhuhr": "12:00",
  "Asr": "15:30",
  "Maghrib": "18:00",
  "Isha": "19:30"
}
```

---

## Notes

* You need `jq` installed on your system:

  ```bash
  sudo apt install jq
  ```
* Python version is optional and demonstrates an alternative way to parse JSON.
* You can change the **city**, **country**, and **date** in the API URL.
