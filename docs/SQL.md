```sql

start transaction;

create type resource_status
  as enum ('available', 'rented', 'broken', 'damaged', 'maintenance', 'sold');

create type resource_kinds
  as enum ('equipment', 'vehicle', 'truck', 'disposable');

create type billing as enum('disposable', 'rental');

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

create table public.resource_types (
    id              bigserial constraint resource_type_pk primary key,
    name            varchar(100) not null,
    description     text,
    kind            resource_kinds default 'equipment',
    pricing         money not null,
    billed_as       billing not null default 'rental'
);

create table public.resource (
    id              bigserial constraint resource_pk primary key,
    type_id         bigint not null constraint resource_type_id_fk references public.resource_types,
    sku             varchar(100) not null,
    status          resource_status not null default 'available',
    kind            resource_kinds not null default 'equipment'
);

create table public.order_bookings (
    id              bigserial constraint order_bookings_pk primary key,
    order_id        bigint not null constraint order_bookings_order_id_fk references public.orders,
    type_id         bigint not null constraint order_bookings_type_id_fk references public.resource_types,
    quantity        smallint check (quantity >= 0 and quantity < 3198),
    rental_start    timestamptz not null,
    rental_end      timestamptz not null,
    e_start         timestamptz not null check(e_start >= rental_start and e_start < rental_end)
);

create table public.vehicles (
    id              bigserial constraint vehicles_pk primary key,
    name            varchar(100) not null,
    description     text,
    number_plate    varchar(100)
);

create table public.trips (
    id              bigserial constraint trips_pk primary key,
    order_id        bigint not null constraint trip_order_id_fk references public.orders,
    booking_id      bigint not null constraint trip_booking_id_fk references public.order_bookings,
    vehicle_id      bigint not null constraint trip_vehicle_id_fk references public.vehicles
);

create table public.trip_legs (
    id              bigserial constraint trip_legs_pk primary key,
    trip_id         bigint not null constraint trip_legs_trip_id_fk references trips,
    seq             smallint not null,
    origin          text,
    destination     text,
    trip_start      timestamptz not null,
    trip_end        timestamptz not null
);

commit transaction;

```
