#!/usr/bin/env bash

set -e

echo "Building in Release mode..."

cmake -B build -S . -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
