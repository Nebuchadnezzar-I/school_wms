database=postgres://michalukropec@localhost:5432/school_wms?sslmode=disable

migrate-up:
	migrate -path=./migrations -database=$(database) up

migrate-down:
	migrate -path=./migrations -database=$(database) down

migrate-force:
	migrate -path=./migrations -database=$(database) force 1

migrate:
	migrate create -seq -ext=.sql -dir=./migrations $(name)

run:
	go run ./cmd/web
