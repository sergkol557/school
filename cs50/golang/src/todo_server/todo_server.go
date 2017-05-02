package todo_server

import (
	"github.com/gorilla/context"
	"log"
	"net/http"
	"time"
)

//======================================================================================================================
func RecoverHandler(next http.Handler) http.Handler {

	fn := func(w http.ResponseWriter, r *http.Request) {

		defer func() {

			if err := recover(); err != nil {

				log.Printf("panic: %+v", err)
				http.Error(w, http.StatusText(InternalServerError), InternalServerError)
			}
		}()

		next.ServeHTTP(w, r)
	}

	return http.HandlerFunc(fn)
}

//======================================================================================================================
func LoggingHandler(next http.Handler) http.Handler {

	fn := func(w http.ResponseWriter, r *http.Request) {

		t1 := time.Now()
		next.ServeHTTP(w, r)
		t2 := time.Now()
		log.Printf("%s [%s] %q %v\n", r.RemoteAddr, r.Method, r.URL, t2.Sub(t1))
	}

	return http.HandlerFunc(fn)
}

//======================================================================================================================
func AuthentificateHandler(next http.Handler) http.Handler {

	fn := func(w http.ResponseWriter, r *http.Request) {

		login, _ := r.Cookie("login")
		pas, _ := r.Cookie("pas")
		if AuthenticationUser(login.Value, pas.Value) {

			context.Set(r, CheckLogged, "logged")
		} else {

			context.Set(r, CheckLogged, "non-logged")
		}
		next.ServeHTTP(w, r)
	}

	return http.HandlerFunc(fn)
}

//======================================================================================================================
func CookieHandler(next http.Handler) http.Handler {

	fn := func(w http.ResponseWriter, r *http.Request) {

		login, err := r.Cookie("login")
		if err != nil {
			login = &http.Cookie{

				Name:  "login",
				Value: "",
			}
			r.AddCookie(login)
		}
		http.SetCookie(w, login)

		pas, err := r.Cookie("pas")
		if err != nil {

			pas = &http.Cookie{

				Name:  "pas",
				Value: "",
			}
			r.AddCookie(pas)
		}
		http.SetCookie(w, pas)

		next.ServeHTTP(w, r)
	}

	return http.HandlerFunc(fn)
}

//======================================================================================================================
