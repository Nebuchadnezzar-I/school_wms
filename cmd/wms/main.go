package main

import (
	"os"
	"time"
	"log/slog"
	"net/http"
	"flag"

	"school_wms/internal/app"
	"school_wms/internal/vcs"
	router "school_wms/internal/router"
)

var (version = vcs.Version())

func main() {
	logger := slog.New(slog.NewTextHandler(os.Stdout, nil))

	addr := flag.String("addr", ":4000", "HTTP network address")
	flag.Parse()

	app := &app.App{
		Logger: logger,
	}

	srv := &http.Server{
		Addr: *addr,
		Handler: router.New(app),
		ErrorLog: slog.NewLogLogger(logger.Handler(), slog.LevelError),
		IdleTimeout:  time.Minute,
		ReadTimeout:  5 * time.Second,
		WriteTimeout: 10 * time.Second,
	}

	logger.Info("starting server", "addr", *addr)
	if err := srv.ListenAndServe(); err != nil {
		logger.Error("server failed", "err", err)
		os.Exit(1)
	}
}
