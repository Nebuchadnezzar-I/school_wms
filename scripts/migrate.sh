#!/bin/bash

migrate create -seq -ext=.sql -dir=./database/migrations $1
