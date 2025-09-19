#!/bin/bash

ARG_FRS=$1
ARG_SEC=$2

# Run
if [[ $ARG_FRS = "run" ]]; then
    go run ./cmd/server ${@:2}
    exit 0
fi

# Build
if [[ $ARG_FRS = "build" ]]; then
    go build ./cmd/server ${@:2}
    exit 0
fi

# Migrate
if [[ $ARG_FRS = "migrate" ]]; then
    exit 0
fi

# Debug
if [[ $ARG_FRS = "debug" ]]; then
    dlv debug ./cmd/server ${@:2}
    exit 0
fi

# Format
if [[ $ARG_FRS = "format" ]]; then
    gofmt -w .
    exit 0
fi

if [[ $ARG_FRS = "check" ]]; then
    dlv version     || echo "DLV Debug utility missing."
    go version      || echo "GO missing."
    migrate version || echo "Migrate missing."
    sqlc version    || echo "SQLc missing."
    exit 0
fi

echo "None of the options could be matched."
