package main

import (
	"fmt"
	"net/http"
	"os"

	a "wms.com/internal/app"
	h "wms.com/internal/helpers"
	r "wms.com/internal/router"
)

func main() {
	var cfg a.Config
	var app a.Application

	h.SetupFlags(&cfg)
	h.SetupApp(&app, &cfg)
	h.SetupExpvar()

	srv := &http.Server{
		Addr:    fmt.Sprintf(":%d", cfg.Port),
		Handler: r.Router(&app),
	}

	err := srv.ListenAndServeTLS("./tls/cert.pem", "./tls/key.pem")
	app.Logger.Error(err.Error())
	os.Exit(1)
}
