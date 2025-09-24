package app

import (
	"log/slog"

	"wms.com/internal/mailer"
)

type Config struct {
	Port    int
	Env     string
	Version string

	Smtp struct {
		Host     string
		Port     int
		Username string
		Password string
		Sender   string
	}

	Cors struct {
		TrustedOrigins []string
	}
}

type Application struct {
	Config Config
	Logger *slog.Logger
	Mailer *mailer.Mailer
}
