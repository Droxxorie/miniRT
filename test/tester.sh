#!/bin/bash

MINIRT=".././miniRT"
TEST_DIR="test_files"
TITLE="MINIRT PARSING TESTER v3.0"
EXPECTED_MSG="Error"

RUN_VALGRIND=""
if [ "$1" == "--bonus" ]; then
    MINIRT=".././miniRT_bonus"
    TEST_DIR="test_files_bonus"
    TITLE="miniRT TESTER (bonus) v3.0"
	EXPECTED_MSG="ERROR"
fi
for arg in "$@"; do
    [ "$arg" = "--valgrind" ] && RUN_VALGRIND=1
done

RESET='\033[0m'
BOLD='\033[1m'
DIM='\033[2m'
ITALIC='\033[3m'
UNDERLINE='\033[4m'

BLACK='\033[30m'
RED='\033[31m'
GREEN='\033[32m'
YELLOW='\033[33m'
BLUE='\033[34m'
MAGENTA='\033[35m'
CYAN='\033[36m'
WHITE='\033[37m'

BRIGHT_GREEN='\033[92m'
BRIGHT_MAGENTA='\033[95m'
BRIGHT_CYAN='\033[96m'

OK='\u2713'
KO='\u2717'
INFO='\u24D8'

if [ ! -f "$MINIRT" ]; then
    echo -e "${RED}Error: executable $MINIRT not found.${RESET}"
    if [ "$1" == "--bonus" ]; then
        echo -e "${YELLOW}Run 'make bonus' first.${RESET}"
    else
        echo -e "${YELLOW}Run 'make' first.${RESET}"
    fi
    exit 1
fi

if [ ! -d "$TEST_DIR" ]; then
    echo -e "${RED}Error: test dir '$TEST_DIR' not found.${RESET}"
    exit 1
fi

LOG="tester.log"
> "$LOG"

echo -e "\n${WHITE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${RESET}"
echo -e "${WHITE}${BOLD}    $TITLE     ${RESET}"
echo -e "${WHITE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${RESET}\n"
echo -e "${DIM}Executable: $MINIRT${RESET}"
echo -e "${DIM}Test dir:   $TEST_DIR${RESET}\n"

check_result() {
    test_desc=$1
    filename=$2
    exit_code=$3
    output=$4

    if [ $exit_code -ne 0 ] && echo "$output" | grep -q "$EXPECTED_MSG"; then
        echo -e "${BRIGHT_GREEN}${OK} $test_desc ${RESET}"
        echo "OK: $test_desc" >> "$LOG"
    else
        echo -e "${RED}${KO} $test_desc ${RESET}"
        echo "FAIL: $test_desc" >> "$LOG"
        echo "  File: $filename" >> "$LOG"
        echo "  Exit: $exit_code" >> "$LOG"
        echo "  Output: $output" >> "$LOG"
    fi
}

#* ==============================================================================
#* SYSTEM TESTS
#* ==============================================================================

echo -e "${BRIGHT_CYAN}${BOLD}- SYSTEM -${RESET}"

echo "A 0.2 255,255,255" > test_wrong_ext.txt
output=$($MINIRT "test_wrong_ext.txt" 2>&1)
check_result "Wrong extension (.txt)" "test_wrong_ext.txt" $? "$output"
rm -f test_wrong_ext.txt

output=$($MINIRT "i_dont_exist.rt" 2>&1)
check_result "File not found" "i_dont_exist.rt" $? "$output"

mkdir -p test_folder.rt
output=$($MINIRT "test_folder.rt" 2>&1)
check_result "Dir passed as file" "test_folder.rt" $? "$output"
rmdir test_folder.rt

echo "A 0.2 255,255,255" > test_perm.rt
chmod 000 test_perm.rt
output=$($MINIRT "test_perm.rt" 2>&1)
check_result "Permission denied (chmod 000)" "test_perm.rt" $? "$output"
rm -f test_perm.rt

#* ==============================================================================
#* .MTL TESTS
#* ==============================================================================

if [ "$1" == "--bonus" ]; then
    echo -e "\n${BRIGHT_CYAN}${BOLD}- .MTL -${RESET}"

    SCENE_HEADER="A 0.1 255,255,255\nC 0,0,-10 0,0,1 70"

    echo "newmtl Test" > bad_ext.txt
    echo -e "$SCENE_HEADER\nmtllib bad_ext.txt" > test_mtl_ext.rt
    output=$($MINIRT "test_mtl_ext.rt" 2>&1)
    check_result "MTL: wrong extension (.txt)" "test_mtl_ext.rt" $? "$output"
    rm -f bad_ext.txt test_mtl_ext.rt

    echo -e "$SCENE_HEADER\nmtllib ghost_file.mtl" > test_mtl_ghost.rt
    output=$($MINIRT "test_mtl_ghost.rt" 2>&1)
    check_result "MTL: file not found" "test_mtl_ghost.rt" $? "$output"
    rm -f test_mtl_ghost.rt

    mkdir -p fake_folder.mtl
    echo -e "$SCENE_HEADER\nmtllib fake_folder.mtl" > test_mtl_folder.rt
    output=$($MINIRT "test_mtl_folder.rt" 2>&1)
    check_result "MTL: dir as file" "test_mtl_folder.rt" $? "$output"
    rm -rf fake_folder.mtl test_mtl_folder.rt

    touch locked.mtl
    chmod 000 locked.mtl
    echo -e "$SCENE_HEADER\nmtllib locked.mtl" > test_mtl_perm.rt
    output=$($MINIRT "test_mtl_perm.rt" 2>&1)
    check_result "MTL: permission denied" "test_mtl_perm.rt" $? "$output"
    rm -f locked.mtl test_mtl_perm.rt
fi

#* ==============================================================================
#* SAVE (--save)
#* ==============================================================================

if [ "$1" == "--bonus" ]; then
    echo -e "\n${BRIGHT_CYAN}${BOLD}- SAVE (--save) -${RESET}"

    SAVE_SCENE="../test/test_file.rt"

    rm -f output/output.bmp
    mkdir -p output 2>/dev/null
    output=$(timeout 120 $MINIRT "$SAVE_SCENE" --save 2>&1)
    exit_save=$?
    if [ $exit_save -eq 124 ]; then
        echo -e "${YELLOW}${KO} Save: timeout 120s${RESET}"
        echo "FAIL: Save (timeout 120s)" >> "$LOG"
    elif [ $exit_save -eq 0 ] && [ -f "output/output.bmp" ] && [ -s "output/output.bmp" ]; then
        echo -e "${BRIGHT_GREEN}${OK} Save: output/output.bmp created${RESET}"
        echo "OK: Save output/output.bmp" >> "$LOG"
    elif [ $exit_save -eq 1 ] && [ ! -f "output/output.bmp" ]; then
        echo -e "${DIM}${INFO} Save: skip (no display)${RESET}"
        echo "OK: Save (skip no display)" >> "$LOG"
    else
        echo -e "${RED}${KO} Save: failed (exit=$exit_save)${RESET}"
        echo "FAIL: Save exit=$exit_save" >> "$LOG"
    fi

    if [ -d "output" ]; then
        chmod 755 output 2>/dev/null
        rm -f output/output.bmp 2>/dev/null
        chmod 444 output 2>/dev/null
        output=$($MINIRT "$SAVE_SCENE" --save 2>&1)
        if [ $? -ne 0 ]; then
            echo -e "${BRIGHT_GREEN}${OK} Save: output/ read-only (444) ok${RESET}"
            echo "OK: Save output/ 444" >> "$LOG"
        else
            echo -e "${RED}${KO} Save: expected fail when output/ 444${RESET}"
            echo "FAIL: Save output/ 444" >> "$LOG"
        fi
        chmod 755 output 2>/dev/null
    fi

    rm -rf output 2>/dev/null
    touch output 2>/dev/null
    output=$($MINIRT "$SAVE_SCENE" --save 2>&1)
    if [ $? -ne 0 ]; then
        echo -e "${BRIGHT_GREEN}${OK} Save: output is file -> fail ok${RESET}"
        echo "OK: Save output is file" >> "$LOG"
    else
        echo -e "${RED}${KO} Save: expected fail when output is file${RESET}"
        echo "FAIL: Save output is file" >> "$LOG"
    fi
    rm -f output 2>/dev/null
    mkdir -p output 2>/dev/null

    rm -rf output
fi

#* ==============================================================================
#* SYNTAX
#* ==============================================================================

echo -e "\n${BRIGHT_CYAN}${BOLD}- SYNTAX -${RESET}"

count=0
files_found=$(ls $TEST_DIR/err_*.rt 2>/dev/null | wc -l)

if [ "$files_found" -eq 0 ]; then
    echo -e "${RED}No err_*.rt in $TEST_DIR.${RESET}"
else
    for file in $TEST_DIR/err_*.rt; do
        msg=$(grep "^# MSG:" "$file" | head -n 1 | sed 's/^# MSG:[[:space:]]*//')

        if [ -z "$msg" ]; then
            msg="$(basename "$file")"
        fi

        output=$(timeout 0.1s $MINIRT "$file" 2>&1)
        exit_code=$?

        if [ $exit_code -eq 124 ]; then
             echo -e "${RED}${KO} $msg ${RESET}"
             echo -e "${YELLOW}    -> Timeout${RESET}"
             echo "FAIL: $msg (timeout)" >> "$LOG"
        else
            check_result "$msg" "$file" $exit_code "$output"
        fi
        ((count++))
    done
fi

#* ==============================================================================
#* VALGRIND (--valgrind): run all err_*.rt under valgrind, check no leaks
#* ==============================================================================

if [ -n "$RUN_VALGRIND" ]; then
    echo -e "\n${BRIGHT_CYAN}${BOLD}- VALGRIND (leaks on all err_*.rt) -${RESET}"

    VG_SUPP="valgrind.supp"
    VG_OPTS="--leak-check=full --show-leak-kinds=all --track-origins=yes"

    if [ ! -f "$VG_SUPP" ]; then
        echo -e "${YELLOW}${KO} valgrind.supp not found (run from test/)${RESET}"
    elif ! command -v valgrind >/dev/null 2>&1; then
        echo -e "${YELLOW}${KO} valgrind not installed${RESET}"
    else
        vg_ok=0
        vg_ko=0
        for file in $TEST_DIR/err_*.rt; do
            [ -f "$file" ] || continue
            out=$(mktemp)
            timeout 5 valgrind $VG_OPTS --suppressions=$VG_SUPP \
                $MINIRT "$file" > "$out" 2>&1
            if grep -q "no leaks are possible" "$out" && \
               grep -q "ERROR SUMMARY: 0 errors" "$out"; then
                echo -e "${BRIGHT_GREEN}${OK} $(basename "$file")${RESET}"
                echo "OK: valgrind $(basename "$file")" >> "$LOG"
                ((vg_ok++))
            else
                echo -e "${RED}${KO} $(basename "$file")${RESET}"
                echo "FAIL: valgrind $(basename "$file")" >> "$LOG"
                cat "$out" >> "$LOG"
                ((vg_ko++))
            fi
            rm -f "$out"
        done
        echo -e "${DIM}Valgrind: $vg_ok ok, $vg_ko leak/error${RESET}"

        if [ "$1" == "--bonus" ]; then
            echo -e "\n${BRIGHT_CYAN}${BOLD}- Helgrind (--save, threads) -${RESET}"
            echo -e "${DIM}helgrind ... (timeout 300s)${RESET}"
            out=$(mktemp)
            timeout 300 valgrind --tool=helgrind --suppressions=$VG_SUPP \
                $MINIRT "../test/test_file.rt" --save > "$out" 2>&1
            if [ $? -eq 124 ]; then
                echo -e "${YELLOW}${KO} Helgrind: timeout${RESET}"
                echo "FAIL: helgrind timeout" >> "$LOG"
            elif grep -q "ERROR SUMMARY: 0 errors" "$out"; then
                echo -e "${BRIGHT_GREEN}${OK} Helgrind: no data races${RESET}"
                echo "OK: helgrind" >> "$LOG"
            else
                echo -e "${RED}${KO} Helgrind: see $LOG${RESET}"
                echo "FAIL: helgrind" >> "$LOG"
                cat "$out" >> "$LOG"
            fi
            rm -f "$out"
        fi
    fi
fi

echo -e "\n${YELLOW}${BOLD}- DONE (${INFO} $count files) -${RESET}"
echo -e "${DIM}Log: $LOG${RESET}\n"
