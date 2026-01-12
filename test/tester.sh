#!/bin/bash

MINIRT=".././miniRT"

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
    echo -e "${RED}Erreur: $MINIRT introuvable.${RESET}"
    exit 1
fi

echo -e "\n${WHITE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${RESET}"
echo -e "${WHITE}${BOLD}    TESTEUR DE PARSING MINIRT v3.0     ${RESET}"
echo -e "${WHITE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${RESET}\n"

check_result() {
    test_desc=$1
    filename=$2
    exit_code=$3
    output=$4

    if [ $exit_code -ne 0 ] && echo "$output" | grep -q "Error"; then
        echo -e "${BRIGHT_GREEN}${OK} $test_desc ${RESET}"
    else
        echo -e "${RED}${KO} $test_desc ${RESET}"
        echo -e "${YELLOW}     Fichier : $filename${RESET}"
        echo -e "     -> Exit Code: $exit_code (Attendu: != 0)"
        echo -e "     -> Sortie: $output (Doit contenir 'Error')"
    fi
}

#* ==============================================================================
#*                                  TESTS SYSTÈME
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
#*                                 TESTS DE CONTENU
#* ==============================================================================
echo -e "\n${BRIGHT_CYAN}${BOLD}- TESTS DE SYNTAXE -${RESET}"

count=0
ls test_files/err_*.rt >/dev/null 2>&1
if [ $? -ne 0 ]; then
    echo -e "${RED}Aucun fichier err_*.rt trouvé.${RESET}"
else
    for file in test_files/err_*.rt; do
        msg=$(grep "^# MSG:" "$file" | head -n 1 | sed 's/^# MSG:[[:space:]]*//')
        
        if [ -z "$msg" ]; then
            msg="Test fichier $file"
        fi
        output=$(timeout 0.1s $MINIRT "$file" 2>&1)
        exit_code=$?
        check_result "$msg" "$file" $exit_code "$output"
        ((count++))
    done
fi

echo -e "\n${YELLOW}${BOLD}- FIN DES TESTS (${INFO} $count fichiers analysés) -${RESET}\n"