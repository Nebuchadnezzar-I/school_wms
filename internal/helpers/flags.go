package helpers

import (
	"flag"
)

type Flags struct {
	Port string
	Env string
}

func GetFlags() *Flags {
	port := flag.String("port", ":8080", "API server port")
	env := flag.String("env", "development", "Environment (development|staging|production)")

	flag.Parse()

	flags := &Flags {
		Port: *port,
		Env: *env,
	}

	return flags
}

