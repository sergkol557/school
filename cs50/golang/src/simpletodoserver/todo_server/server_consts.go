package todo_server

type check_logged int

const (
	ServerReadTimeout                = 10
	ServerWriteTimeout               = 10
	ServerPort                       = ":8090"
	ServerMaxHeaderByte              = 1 << 20
	InternalServerError              = 500
	DataBaseMode                     = 0644
	LogOutButton                     = "<a href='javascript:LogOut()'> logout.</a>"
	DateFormat                       = "02.01.2006 15:04:05"
	CheckLogged         check_logged = 0
	NumberOfReplace                  = 1
)
