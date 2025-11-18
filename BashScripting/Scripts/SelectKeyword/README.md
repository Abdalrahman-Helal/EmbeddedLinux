# Bash Script Summary

This script demonstrates **Select statements, variable scopes, readonly variables, and the `shift` command** in Bash.

---

## 1. Select Statement (Menu)

```bash
select name in Abdalrahman Eslam Helal
do
    echo $name
done
```

* `select` creates a menu from the listed options.
* User chooses an option by entering its number.
* `$name` stores the selected value.
* Loops until manually broken (`break`).

### Using `case` with `select`

```bash
select name in Abdalrahman Eslam Helal
do  
    case ${name} in
    Helal)
        echo "Hello ${name}"
    ;;
    *)
        break
    ;;
    esac
endone
```

* Checks the selected value using `case`.
* Prints a message if `Helal` is selected.
* Exits the loop for any other input (`*`).

---

## 2. Global vs Local Variables

### Global Variable Example

```bash
name="Ahmed Mohamed"

DisplayGlobal() {
    name="Abdalrahman Helal"
    echo "Hello Function ${name}"
}

echo "Before ${name}"
DisplayGlobal
echo "After ${name}"
```

* Function modifies the **global variable** `name`.
* Output shows that the global variable changed.

### Local Variable Example

```bash
DisplayLocal() {
    local name="Abdalrahman Helal"
    echo "Hello Function ${name}"
}

echo "Before ${name}"
DisplayLocal
echo "After ${name}"
```

* Using `local` inside the function keeps the variable **scope local**.
* Global variable `name` remains unchanged.

---

## 3. Readonly Variables

```bash
readonly x=12
# or
x=10
readonly x
# x=12 # will give an error
```

* `readonly` prevents variable reassignment.
* Works with functions as well:

```bash
function print() { echo hi; }
readonly -f print
# Cannot redefine the function after this
```

---

## 4. Shift Command

```bash
# Total number of command-line arguments
echo "Total Arguments passed: $#"

# Show all command-line arguments
echo "The Arguments are: $*"

# Access first argument
echo "The First Argument is: $1"

# Shift arguments
shift 2
echo "The First Argument after shift 2: $1"

shift
echo "The First Argument after shift: $1"
```

* `$#` → total number of arguments.
* `$*` → all arguments as a single string.
* `$1`, `$2`, … → individual arguments.
* `shift n` → removes the first `n` arguments, shifting the rest left.
* `shift -1` is **not allowed**.

---

✅ This script covers:

* `select` menus and `case` handling
* Global vs local variable scope
* Readonly variables and functions
* Command-line argument manipulation with `shift`
