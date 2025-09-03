
```sql
insert into public.equipment_types (name, description, daily_rate, weight_kg) values
('18KW MSR ARRIMAX PAR F.F.', '18KW MSR ARRIMAX PAR F.F. + CABLE + BALLAST', 200.00, 161.6),
('9KW MSR M90 PAR F.F.', '9KW MSR M90 PAR F.F. + CABLE + BALLAST', 150.00, 87.6),
('4KW MSR M40 F.F.', '4KW MSR M40 F.F. + CABLE + BALLAST', 100.00, 44.4);

insert into public.equipment_items (type_id, serial, tag, status) values
(1, 'SN-ARRIMAX-001', 'ARRIMAX-001', 'available'),
(1, 'SN-ARRIMAX-002', 'ARRIMAX-002', 'available'),
(1, 'SN-ARRIMAX-003', 'ARRIMAX-003', 'available'),
(1, 'SN-ARRIMAX-004', 'ARRIMAX-004', 'maintenance'),

(2, 'SN-M90-001', 'M90-001', 'available'),
(2, 'SN-M90-002', 'M90-002', 'available'),
(2, 'SN-M90-003', 'M90-003', 'rented'),
(2, 'SN-M90-004', 'M90-004', 'available'),
(2, 'SN-M90-005', 'M90-005', 'available'),

(3, 'SN-M40-001', 'M40-001', 'available'),
(3, 'SN-M40-002', 'M40-002', 'available'),
(3, 'SN-M40-003', 'M40-003', 'available'),
(3, 'SN-M40-004', 'M40-004', 'broken'),
(3, 'SN-M40-005', 'M40-005', 'available'),
(3, 'SN-M40-006', 'M40-006', 'available');

insert into public.clients (name, description) values
('FilmCrew Productions', 'Film production client'),
('Studio Bratislava', 'Local TV studio');

insert into public.orders (client_id, discount) values
(1, 50.00),
(2, null);

insert into public.order_lines (order_id, type_id, quantity, start_at, end_at) values
(1, 1, 2, '2025-09-10 08:00:00+00', '2025-09-20 18:00:00+00'),
(1, 2, 1, '2025-09-10 08:00:00+00', '2025-09-15 18:00:00+00'),
(2, 3, 3, '2025-09-12 09:00:00+00', '2025-09-18 20:00:00+00');
```
