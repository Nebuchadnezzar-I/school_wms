package api

import (
	"school_wms/internal/app"
)

type API struct {
	App *app.App
}

func New(a *app.App) *API {
	return &API{App: a}
}
