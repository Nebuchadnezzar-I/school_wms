```sql

begin transaction;

create type user_role as enum('admin', 'developer', 'operator', 'guest')

create table rental_types (
    id          bigserial constraint rental_types_pk primary key,
    name        varchar(100)    not null,
    description text            not null,
    pricing     money           not null,
    rack        varchar(50)     not null,
    rows        varchar(50)     not null,
    cols        varchar(50)     not null
);

create table vehicle_types (
    id              bigserial constraint vehicle_types_pk primary key,
    name            varchar(100)          not null,
    description     text                  not null,
    pricing         money                 not null
);

create table disposable_types (
    id          bigserial constraint disposable_types_pk primary key,
    price       money        not null,
    name        varchar(100) not null,
    description text         not null
);

create table rentals (
    id      bigserial constraint rentals_pk primary key,
    type_id bigint not null constraint rentals_type_id_fk references rental_types,
    sku     varchar(100),
    uuid    uuid default gen_random_uuid(),
    serial  varchar(100)
);

create table vehicles (
    id              bigserial constraint vehicles_pk primary key,
    type_id         bigint not null constraint vehicles_type_id_fk references vehicle_types,
    plate           varchar(50)           not null,
    stk_valid_until date                  not null,
    ek_valid_until  date                  not null,
    eco_stamp       boolean default false not null
);

create table disposables (
    id        bigserial constraint disposables_pk primary key,
    type_id   bigint not null constraint disposables_type_id_fk references disposable_types,
    sku       varchar(50),
    remaining NUMERIC(5, 2) not null
);

create table orders (
    id            bigserial constraint orders_pk primary key,
    priority      smallint NOT NULL DEFAULT 0,
    name          varchar(100) NOT NULL,
    description   text,
    starting_at   timestamptz,
    ending_at     timestamptz
);

create table order_items (
    id                  bigserial constraint order_items_pk primary key,
    order_id            bigint not null constraint order_items_orders_id_fk references orders,
    rental_type_id      bigint,
    rental_quantity     integer,
    vehicle_type_id     bigint,
    vehicle_quantity    integer,
    disposable_type_id  integer,
    disposable_quantity integer,
    starting_at         timestamptz not null,
    ending_at           timestamptz not null
);

create table clients (
    id          bigserial constraint clients_pk primary key,
    name        varchar(100)              not null,
    description text,
    created_at  timestamptz default now() not null
);

create table order_clients (
    id         bigserial constraint order_clients_pk primary key,
    order_id   bigint                    not null constraint order_clients_order_id_fk references orders,
    client_id  bigint                    not null constraint order_clients_client_id_fk references clients,
    created_at timestamptz default now() not null
);

create table loads (
    id                   bigserial constraint loads_pk primary key,
    rental_id            bigint,
    vehicle_id           bigint,
    disposable_id        bigint,
    loaded_at            timestamptz not null default now()
);

create table unloads (
    id                   bigserial constraint unloads_pk primary key,
    rental_id            bigint,
    rental_state         text,
    vehicle_id           bigint,
    vehicle_state        text,
    disposable_id        bigint,
    disposable_remaining numeric(5,2) NOT NULL DEFAULT 0.00,
    unloaded_at          timestamptz not null default now()
);

create table users (
    id              bigserial constraint users_pk primary key,
    first_name      varchar(50) not null,
    last_name       varchar(50) not null,
    email           varchar(100) not null,
    password        text,
    role            user_role not null
);

create table user_sessions (
    id             bigserial constraint user_sessions_pk primary key,
    user_id        bigint not null constraint user_sessions_user_id_fk references users,
    family         uuid default gen_random_uuid() not null constraint user_sessions_pk_2 unique,
    token          uuid default gen_random_uuid() not null constraint user_sessions_pk_3 unique,
    issued_at      timestamptz default now() not null,
    expires_at     timestamptz default now() + interval '10 days' not null,
    rotated_at     timestamptz,
    compromised_at timestamptz,
    last_used      timestamptz
);

commit transaction;

```
