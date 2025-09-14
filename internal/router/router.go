package router

import (
	"net/http"

	"github.com/justinas/alice"
	"school_wms/internal/app"
	"school_wms/internal/api"
)

func New(a *app.App) http.Handler {
	mux := http.NewServeMux()

	apis := api.New(a)
	mux.HandleFunc("/", apis.RegisterUser)

	chain := alice.New(/* middleware */)
	return chain.Then(mux)
}
