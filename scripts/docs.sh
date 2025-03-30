#!/usr/bin/env bash


PURPLE='\033[0;35m'
NC='\033[0m'

generate_docs() {
    echo -e "${PURPLE}"
    echo "📚 Generating documentation..."
    echo -e "${NC}"
    
    doxygen Doxyfile
    echo -e "\nDocumentation saved to: docs/html/"
}

open_docs() {
    if [ -f "docs/html/index.html" ]; then
        xdg-open docs/html/index.html
    else
        echo "Docs not found! Generating first..."
        generate_docs
        xdg-open docs/html/index.html
    fi
}

main() {
    generate_docs
    open_docs
}

main