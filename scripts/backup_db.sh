#!/bin/bash

DATE=$(date +%Y%m%d)
BACKUP_DIR="backups"

mkdir -p $BACKUP_DIR
cp university.db $BACKUP_DIR/university_$DATE.db
echo "Backup created: $BACKUP_DIR/university_$DATE.db"