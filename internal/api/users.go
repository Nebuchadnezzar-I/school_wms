package api

import (
	"net/http"
)

func (api *API) RegisterUser(w http.ResponseWriter, r *http.Request) {
	api.App.Logger.Info("register user handler called")
	w.WriteHeader(http.StatusCreated)
	w.Write([]byte("user registered"))
}
