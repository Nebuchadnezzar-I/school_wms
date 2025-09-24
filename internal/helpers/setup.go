package helpers

import (
	"expvar"
	"flag"
	"log/slog"
	"os"
	"runtime"
	"strings"
	"time"

	"wms.com/internal/app"
	"wms.com/internal/mailer"
)

func SetupFlags(cfg *app.Config) {
	flag.StringVar(&cfg.Env, "env", "development", "Environment (development|staging|production)")
	flag.StringVar(&cfg.Version, "version", "0.0.0", "App Version")
	flag.IntVar(&cfg.Port, "port", 4000, "Server port")

	flag.StringVar(&cfg.Smtp.Host, "smtp-host", "sandbox.smtp.mailtrap.io", "SMTP host")
	flag.IntVar(&cfg.Smtp.Port, "smtp-port", 25, "SMTP port")
	flag.StringVar(&cfg.Smtp.Username, "smtp-username", "8fb4d3499e766a", "SMTP username")
	flag.StringVar(&cfg.Smtp.Password, "smtp-password", "e8a8bdb12501a5", "SMTP password")
	flag.StringVar(&cfg.Smtp.Sender, "smtp-sender", "wms.com <no-reply@wms.capo>", "SMTP sender")

	flag.Func("cors-trusted-origins", "Trusted CORS origins (space separated)", func(val string) error {
		cfg.Cors.TrustedOrigins = strings.Fields(val)
		return nil
	})

	flag.Parse()
}

func SetupApp(a *app.Application, cfg *app.Config) {
	mailer, err := mailer.New(cfg.Smtp.Host, cfg.Smtp.Port, cfg.Smtp.Username, cfg.Smtp.Password, cfg.Smtp.Sender)
	if err != nil {
		a.Logger.Error(err.Error())
		os.Exit(1)
	}

	a.Logger = slog.New(slog.NewJSONHandler(os.Stdout, nil))
	a.Config = *cfg
	a.Mailer = mailer
}

func SetupExpvar() {
	expvar.Publish("goroutines", expvar.Func(func() any {
		return runtime.NumGoroutine()
	}))

	expvar.Publish("timestamp", expvar.Func(func() any {
		return time.Now().Unix()
	}))
}
