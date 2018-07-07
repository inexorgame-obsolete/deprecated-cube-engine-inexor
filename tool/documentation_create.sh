#!/bin/bash
set -e

doxygen doxygen.conf 2>&1 | grep -vF 'sqlite3_step " \
  "failed: memberdef.id_file may not be NULL'
