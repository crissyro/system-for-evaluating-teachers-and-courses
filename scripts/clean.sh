#!/usr/bin/env bash


RED='\033[0;31m'
NC='\033[0m'

prompt_clean() {
    echo -e "${RED}"
    read -p "⚠️  This will delete all build artifacts! Continue? [y/N] " -n 1 -r
    echo -e "${NC}"
    
    if [[ $REPLY =~ ^[Yy]$ ]]; then
        cd ..
        echo "🧹 Cleaning project..."
        make clean
        echo "✅ Project cleaned"
    else
        echo "🛑 Clean cancelled"
    fi
}

main() {
    prompt_clean
}

main