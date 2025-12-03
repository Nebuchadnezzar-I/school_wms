package models

import (
	"context"
	"database/sql"
	"errors"
	"strings"
	"time"

	"golang.org/x/crypto/bcrypt"
	"github.com/jackc/pgx/v5/pgconn"
	"github.com/jackc/pgx/v5/pgxpool"
)

type UserModelInterface interface {
	Insert(name, email, password string) error
	Authenticate(email, password string) (int, error)
	Exists(id int) (bool, error)
}

type User struct {
	ID             int
	Name           string
	Email          string
	HashedPassword []byte
	Created        time.Time
}

type UserModel struct {
	DB *pgxpool.Pool
}

func (m *UserModel) Insert(name, email, password string) error {
	hashedPassword, err := bcrypt.GenerateFromPassword([]byte(password), 12)
	if err != nil {
		return err
	}

	stmt := `
	INSERT INTO users (name, email, hashed_password, created)
	VALUES ($1, $2, $3, NOW());
	`

	_, err = m.DB.Exec(context.Background(), stmt, name, email, string(hashedPassword))
	if err != nil {
		var pgErr *pgconn.PgError

		// PostgreSQL duplicate key error (SQLSTATE 23505)
		if errors.As(err, &pgErr) && pgErr.Code == "23505" {
			// check constraint/index names
			if strings.Contains(pgErr.ConstraintName, "users_uc_email") ||
				strings.Contains(pgErr.ConstraintName, "users_email_key") {
				return ErrDuplicateEmail
			}
		}

		return err
	}

	return nil
}

func (m *UserModel) Authenticate(email, password string) (int, error) {
	stmt := `
	SELECT id, hashed_password
	FROM users
	WHERE email = $1;
	`

	var id int
	var hashedPassword []byte

	err := m.DB.QueryRow(context.Background(), stmt, email).Scan(&id, &hashedPassword)
	if err != nil {
		if errors.Is(err, sql.ErrNoRows) {
			return 0, ErrInvalidCredentials
		}
		return 0, err
	}

	err = bcrypt.CompareHashAndPassword(hashedPassword, []byte(password))
	if err != nil {
		return 0, ErrInvalidCredentials
	}

	return id, nil
}

func (m *UserModel) Exists(id int) (bool, error) {
	stmt := `
	SELECT EXISTS(
		SELECT 1 FROM users WHERE id = $1
	);
	`

	var exists bool
	err := m.DB.QueryRow(context.Background(), stmt, id).Scan(&exists)
	return exists, err
}

