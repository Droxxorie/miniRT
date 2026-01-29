#!/bin/bash

MINIRT=".././miniRT"
TEST_DIR="test_files"
TITLE="TESTEUR DE PARSING MINIRT v3.0"
EXPECTED_MSG="Error"

if [ "$1" == "--bonus" ]; then
    MINIRT=".././miniRT_bonus"
    TEST_DIR="test_files_bonus"
    TITLE="miniRT TESTER (bonus) v3.0"
	EXPECTED_MSG="ERROR"
fi

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
    echo -e "${RED}Erreur: L'exécutable $MINIRT est introuvable.${RESET}"
    if [ "$1" == "--bonus" ]; then
        echo -e "${YELLOW}Avez-vous compilé avec 'make bonus' ?${RESET}"
    else
        echo -e "${YELLOW}Avez-vous compilé avec 'make' ?${RESET}"
    fi
    exit 1
fi

if [ ! -d "$TEST_DIR" ]; then
    echo -e "${RED}Erreur: Le dossier de tests '$TEST_DIR' est introuvable.${RESET}"
    exit 1
fi

echo -e "\n${WHITE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${RESET}"
echo -e "${WHITE}${BOLD}    $TITLE     ${RESET}"
echo -e "${WHITE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${RESET}\n"
echo -e "${DIM}Exécutable : $MINIRT${RESET}"
echo -e "${DIM}Dossier tests : $TEST_DIR${RESET}\n"

check_result() {
    test_desc=$1
    filename=$2
    exit_code=$3
    output=$4

    if [ $exit_code -ne 0 ] && echo "$output" | grep -q "$EXPECTED_MSG"; then
        echo -e "${BRIGHT_GREEN}${OK} $test_desc ${RESET}"
    else
        echo -e "${RED}${KO} $test_desc ${RESET}"
        echo -e "${YELLOW}    Fichier : $filename${RESET}"
        echo -e "    -> Exit Code: $exit_code (Attendu: != 0)"
        echo -e "    -> Sortie: $output (Doit contenir 'Error')"
    fi
}

#* ==============================================================================
#* TESTS SYSTÈME
#* ==============================================================================
echo -e "${BRIGHT_CYAN}${BOLD}- TESTS SYSTÈME -${RESET}"

#* Mauvaise extension
echo "A 0.2 255,255,255" > test_wrong_ext.txt
output=$($MINIRT "test_wrong_ext.txt" 2>&1)
check_result "Extension incorrecte (.txt)" "test_wrong_ext.txt" $? "$output"
rm -f test_wrong_ext.txt

#* Fichier inexistant
output=$($MINIRT "i_dont_exist.rt" 2>&1)
check_result "Fichier inexistant" "i_dont_exist.rt" $? "$output"

#* Dossier au lieu de fichier
mkdir -p test_folder.rt
output=$($MINIRT "test_folder.rt" 2>&1)
check_result "Dossier au lieu de fichier" "test_folder.rt" $? "$output"
rmdir test_folder.rt

#* Permissions
echo "A 0.2 255,255,255" > test_perm.rt
chmod 000 test_perm.rt
output=$($MINIRT "test_perm.rt" 2>&1)
check_result "Permission refusée (chmod 000)" "test_perm.rt" $? "$output"
rm -f test_perm.rt

#* ==============================================================================
#* TESTS SYSTÈME (.MTL)
#* ==============================================================================
if [ "$1" == "--bonus" ]; then
    echo -e "\n${BRIGHT_CYAN}${BOLD}- TESTS SYSTÈME (.MTL) -${RESET}"

    SCENE_HEADER="A 0.1 255,255,255\nC 0,0,-10 0,0,1 70"

    #* 1. MTL avec mauvaise extension
    echo "newmtl Test" > bad_ext.txt
    echo -e "$SCENE_HEADER\nmtllib bad_ext.txt" > test_mtl_ext.rt
    output=$($MINIRT "test_mtl_ext.rt" 2>&1)
    check_result "MTL: Extension incorrecte (.txt)" "test_mtl_ext.rt" $? "$output"
    rm -f bad_ext.txt test_mtl_ext.rt

    #* 2. MTL Inexistant
    echo -e "$SCENE_HEADER\nmtllib ghost_file.mtl" > test_mtl_ghost.rt
    output=$($MINIRT "test_mtl_ghost.rt" 2>&1)
    check_result "MTL: Fichier inexistant" "test_mtl_ghost.rt" $? "$output"
    rm -f test_mtl_ghost.rt

    #* 3. MTL est un dossier
    mkdir -p fake_folder.mtl
    echo -e "$SCENE_HEADER\nmtllib fake_folder.mtl" > test_mtl_folder.rt
    output=$($MINIRT "test_mtl_folder.rt" 2>&1)
    check_result "MTL: Dossier au lieu de fichier" "test_mtl_folder.rt" $? "$output"
    rm -rf fake_folder.mtl test_mtl_folder.rt

    #* 4. MTL Permissions
    touch locked.mtl
    chmod 000 locked.mtl
    echo -e "$SCENE_HEADER\nmtllib locked.mtl" > test_mtl_perm.rt
    output=$($MINIRT "test_mtl_perm.rt" 2>&1)
    check_result "MTL: Permission refusée" "test_mtl_perm.rt" $? "$output"
    rm -f locked.mtl test_mtl_perm.rt
fi

#* ==============================================================================
#* TESTS DE SYNTAXE
#* ==============================================================================
echo -e "\n${BRIGHT_CYAN}${BOLD}- TESTS DE SYNTAXE -${RESET}"

count=0
files_found=$(ls $TEST_DIR/err_*.rt 2>/dev/null | wc -l)

if [ "$files_found" -eq 0 ]; then
    echo -e "${RED}Aucun fichier err_*.rt trouvé dans $TEST_DIR.${RESET}"
else
    for file in $TEST_DIR/err_*.rt; do
        msg=$(grep "^# MSG:" "$file" | head -n 1 | sed 's/^# MSG:[[:space:]]*//')
        
        if [ -z "$msg" ]; then
            msg="Test fichier $(basename "$file")"
        fi

        output=$(timeout 0.1s $MINIRT "$file" 2>&1)
        exit_code=$?

        if [ $exit_code -eq 124 ]; then
             echo -e "${RED}${KO} $msg ${RESET}"
             echo -e "${YELLOW}    -> Timeout : Le programme a mis trop de temps.${RESET}"
        else
            check_result "$msg" "$file" $exit_code "$output"
        fi
        ((count++))
    done
fi

echo -e "\n${YELLOW}${BOLD}- FIN DES TESTS (${INFO} $count fichiers analysés) -${RESET}\n"