#!/usr/bin/env bash


RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' 

header() {
    echo -e "${YELLOW}"
    echo "╔════════════════════════════════════════╗"
    echo "╟── Building University Rating System ───╢"
    echo "╚════════════════════════════════════════╝"
    echo -e "${NC}"
}

check_dependencies() {
    cd .. 
    local deps=("g++" "make" "sqlite3" "clang-format")
    for dep in "${deps[@]}"; do
        if ! command -v $dep &> /dev/null; then
            echo -e "${RED}Error: $dep not found!${NC}"
            exit 1
        fi
    done
}

main() {
    header
    check_dependencies
    
    echo -e "${GREEN}[1/3] Cleaning previous build...${NC}"
    make clean
    
    echo -e "${GREEN}[2/3] Compiling project...${NC}"
    if ! make build; then
        echo -e "${RED}Build failed!${NC}"
        exit 1
    fi
    
    echo -e "${GREEN}[3/3] Verifying binary...${NC}"
    if [ -f "build/university_app" ]; then
        echo -e "${GREEN}✅ Build successful!${NC}"
    else
        echo -e "${RED}❌ Binary not found!${NC}"
        exit 1
    fi
}

main