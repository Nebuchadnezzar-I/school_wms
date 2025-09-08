```sql
create table rental_types
(
    id          bigserial
        constraint rental_types_pk
            primary key,
    name        varchar(100) not null,
    description text         not null,
    pricing     money        not null,
    rack        varchar(50)  not null,
    rows        varchar(50)  not null,
    cols        varchar(50)  not null
);

alter table rental_types
    owner to michalukropec;

create table vehicle_types
(
    id          bigserial
        constraint vehicle_types_pk
            primary key,
    name        varchar(100) not null,
    description text         not null,
    pricing     money        not null
);

alter table vehicle_types
    owner to michalukropec;

create table disposable_types
(
    id          bigserial
        constraint disposable_types_pk
            primary key,
    price       money        not null,
    name        varchar(100) not null,
    description text         not null
);

alter table disposable_types
    owner to michalukropec;

create table rentals
(
    id      bigserial
        constraint rentals_pk
            primary key,
    type_id bigint not null
        constraint rentals_type_id_fk
            references rental_types,
    sku     varchar(100),
    uuid    uuid default gen_random_uuid(),
    serial  varchar(100)
);

alter table rentals
    owner to michalukropec;

create table vehicles
(
    id              bigserial
        constraint vehicles_pk
            primary key,
    type_id         bigint                not null
        constraint vehicles_type_id_fk
            references vehicle_types,
    plate           varchar(50)           not null,
    stk_valid_until date                  not null,
    ek_valid_until  date                  not null,
    eco_stamp       boolean default false not null
);

alter table vehicles
    owner to michalukropec;

create table disposables
(
    id        bigserial
        constraint disposables_pk
            primary key,
    type_id   bigint        not null
        constraint disposables_type_id_fk
            references disposable_types,
    sku       varchar(50),
    remaining numeric(5, 2) not null
);

alter table disposables
    owner to michalukropec;

create table orders
(
    id          bigserial
        constraint orders_pk
            primary key,
    priority    smallint default 0 not null,
    name        varchar(100)       not null,
    description text,
    starting_at timestamp with time zone,
    ending_at   timestamp with time zone
);

alter table orders
    owner to michalukropec;

create table order_items
(
    id                  bigserial
        constraint order_items_pk
            primary key,
    order_id            bigint                   not null
        constraint order_items_orders_id_fk
            references orders,
    rental_type_id      bigint,
    rental_quantity     integer,
    vehicle_type_id     bigint,
    vehicle_quantity    integer,
    disposable_type_id  integer,
    disposable_quantity integer,
    starting_at         timestamp with time zone not null,
    ending_at           timestamp with time zone not null
);

alter table order_items
    owner to michalukropec;

create table clients
(
    id          bigserial
        constraint clients_pk
            primary key,
    name        varchar(100)                           not null,
    description text,
    created_at  timestamp with time zone default now() not null
);

alter table clients
    owner to michalukropec;

create table order_clients
(
    id         bigserial
        constraint order_clients_pk
            primary key,
    order_id   bigint                                 not null
        constraint order_clients_order_id_fk
            references orders,
    client_id  bigint                                 not null
        constraint order_clients_client_id_fk
            references clients,
    created_at timestamp with time zone default now() not null
);

alter table order_clients
    owner to michalukropec;

create table loads
(
    id            bigserial
        constraint loads_pk
            primary key,
    rental_id     bigint,
    vehicle_id    bigint,
    disposable_id bigint,
    loaded_at     timestamp with time zone default now() not null
);

alter table loads
    owner to michalukropec;

create table unloads
(
    id                   bigserial
        constraint unloads_pk
            primary key,
    rental_id            bigint,
    rental_state         text,
    vehicle_id           bigint,
    vehicle_state        text,
    disposable_id        bigint,
    disposable_remaining numeric(5, 2)            default 0.00  not null,
    unloaded_at          timestamp with time zone default now() not null
);

alter table unloads
    owner to michalukropec;

create table users
(
    id         bigserial
        constraint users_pk
            primary key,
    first_name varchar(50)  not null,
    last_name  varchar(50)  not null,
    email      varchar(100) not null,
    password   text,
    role       user_role    not null
);

alter table users
    owner to michalukropec;

create table user_sessions
(
    id             bigserial
        constraint user_sessions_pk
            primary key,
    user_id        bigint                                                         not null
        constraint user_sessions_user_id_fk
            references users,
    family         uuid                     default gen_random_uuid()             not null
        constraint user_sessions_pk_2
            unique,
    token          uuid                     default gen_random_uuid()             not null
        constraint user_sessions_pk_3
            unique,
    issued_at      timestamp with time zone default now()                         not null,
    expires_at     timestamp with time zone default (now() + '10 days'::interval) not null,
    rotated_at     timestamp with time zone,
    compromised_at timestamp with time zone,
    last_used      timestamp with time zone
);

alter table user_sessions
    owner to michalukropec;
```
