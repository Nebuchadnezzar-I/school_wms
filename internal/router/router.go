package router

import (
	"net/http"

	a "wms.com/internal/app"
)

func Router(app *a.Application) http.Handler {
	mux := http.NewServeMux()

	// mux.Handle("GET /static/", http.FileServerFS(ui.Files))
	mux.HandleFunc("GET /ping", ping)

	return mux
}

func ping(w http.ResponseWriter, r *http.Request) {
	w.Write([]byte("OK"))
}
