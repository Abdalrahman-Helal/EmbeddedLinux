# Bash Array `unset` and Index Shifting

In Bash, using `unset` on an array element **removes the element** but **does not shift the remaining elements**. This can leave gaps in the array indices.

---

## Example

```bash
ARRAY_NAME2=("Java" "Python" "HTML" "CSS" 3)
unset ARRAY_NAME2[2]

echo "${ARRAY_NAME2[@]}"   # Output: Java Python CSS 3
echo "${ARRAY_NAME2[2]}"    # Output: (empty, because index 2 was unset)
```

### Explanation

* **Original array:**

  ```
  Index: 0      1       2     3      4
  Value: Java  Python  HTML  CSS     3
  ```
* **After `unset ARRAY_NAME2[2]`:**

  ```
  Index: 0      1       3      4
  Value: Java  Python  CSS    3
  ```
* Index 2 is now empty, so accessing it gives nothing.

### Reindexing the Array

To remove the gaps and have continuous indices:

```bash
ARRAY_NAME2=("${ARRAY_NAME2[@]}")
echo "${ARRAY_NAME2[@]}"  # Output: Java Python CSS 3
echo "${!ARRAY_NAME2[@]}"  # Output: 0 1 2 3
```

---

**Rule:**

* `unset arr[index]` → removes the element **without shifting indices**.
* To fix indices, reassign: `arr=("${arr[@]}")`.

---

## String Slicing

In Bash, you can also slice strings similar to arrays. Example:

```bash
str="Abdalrahman Eslam Mohamed Helal"
echo ${str:12:5}   # Output: Eslam
```

* Syntax: `${str:start:length}`

  * `start` → starting index (0-based)
  * `length` → number of characters to extract
* **Note:** Unlike Python, the end index is **not used**; you provide the number of characters to print.

---

## Looping Through Arrays

### 1. Standard `for` loop

```bash
for i in "${ARRAY_NAME2[@]}"
do 
    echo "$i"
done
```

* `"${ARRAY[@]}"` → expands all elements, preserving spaces.
* `$i` → loop variable for each element.

### 2. Looping through array indices

```bash
for i in "${!ARRAY_NAME2[@]}"
do
    echo "$i - ${ARRAY_NAME2[$i]}"
done
```

* `"${!ARRAY[@]}"` → expands to **all indices** of the array.

  * The `!` symbol **refers to the indices** of the array, not the values.
* Useful if you need **both index and value**.

**Rule:**

* Use `"${ARRAY[@]}"` to loop over values.
* Use `"${!ARRAY[@]}"` to loop over indices and access their values.
