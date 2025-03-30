#!/usr/bin/env bash


RED='\033[0;31m'
NC='\033[0m'

uninstall_app() {
    cd ..
    echo -e "${RED}🗑️  Uninstalling University Rating System...${NC}"
    
    if [ -f "bin/university_app" ]; then
        make uninstall
        echo "Application removed"
    else
        echo "Application not found!"
    fi
    
    echo -e "\n${RED}👋 Uninstall complete!${NC}"
}

main() {
    uninstall_app
}

main