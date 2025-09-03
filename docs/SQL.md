```sql

create type equipment_status
  as enum ('available', 'rented', 'broken', 'damaged', 'maintenance', 'sold');

create table public.equipment_types (
    id              bigserial not null constraint equipment_types_pk primary key,
    name            varchar(100) not null,
    description     text not null,
    daily_rate      numeric(12,2),
    weight_kg       numeric(10,2)
);

create table public.equipment_items (
    id              bigserial not null constraint equipment_items_pk primary key,
    type_id         bigint not null constraint equipment_items_type_id_fk references public.equipment_types,
    serial          text,
    tag             varchar(50) not null unique,
    status          equipment_status default 'available' not null
);

create table public.clients (
    id              bigserial not null constraint clients_pk primary key,
    name            varchar(100) not null,
    description     text
);

create table public.orders (
    id              bigserial not null constraint orders_pk primary key,
    client_id       bigint not null constraint orders_client_id_fk references public.clients,
    discount        numeric(12,2)
);

create table public.order_lines (
    id              bigserial not null constraint order_lines_pk primary key,
    order_id        bigint not null constraint order_lines_order_id_fk references public.orders,
    type_id         bigint not null constraint order_lines_type_id_fk references public.equipment_types,
    quantity        smallint default 0 not null,
    start_at        timestamptz not null,
    end_at          timestamptz not null
);

```
