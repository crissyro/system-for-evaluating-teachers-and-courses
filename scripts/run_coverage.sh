#!/usr/bin/env bash


CYAN='\033[0;36m'
GREEN='\033[0;32m'
NC='\033[0m'

show_coverage() {
    echo -e "${CYAN}"
    echo "╔════════════════════════════════════════╗"
    echo "╟── Code Coverage Report ────────────────╢"
    echo "╚════════════════════════════════════════╝"
    echo -e "${NC}"
    
    if [ -d "docs/coverage" ]; then
        echo -e "${GREEN}Opening report...${NC}"
        xdg-open docs/coverage/index.html
    else
        cd ..
        echo "Generating report..."
        make gcov_report
        xdg-open docs/coverage/index.html
    fi
}

main() {
    make gcov_report
    show_coverage
}

main