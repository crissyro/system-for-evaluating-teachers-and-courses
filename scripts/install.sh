#!/usr/bin/env bash


GREEN='\033[0;32m'
NC='\033[0m'

install_app() {
    cd ..
    echo -e "${GREEN}🔧 Installing University Rating System...${NC}"
    
    if [ ! -f "build/university_app" ]; then
        echo "Building project first..."
        ./build.sh
    fi
    
    echo -e "\n${GREEN}🎉 Installation complete!"
    echo "Run with: ${NC}urs"
}

main() {
    install_app
}

main