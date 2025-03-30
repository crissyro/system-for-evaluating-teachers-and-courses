#!/usr/bin/env bash

RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m'

run_tests() {
    cd ..
    echo -e "${BLUE}🚀 Running test suite...${NC}"
    if ! make test; then
        echo -e "${RED}❌ Tests failed!${NC}"
        exit 1
    fi
    
    echo -e "\n${GREEN}📊 Test results:${NC}"
    cat build/test_results.xml | grep -E '<testcase|</failure>' --color=always
}

main() {
    echo -e "${GREEN}✅ Checking test dependencies...${NC}"
    if ! command -v lcov &> /dev/null; then
        echo -e "${RED}Error: lcov required for coverage${NC}"
        exit 1
    fi

    run_tests
    echo -e "\n${GREEN}🎉 All tests passed successfully!${NC}"
}

main
