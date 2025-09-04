## Sep 3 2025

- Started working on schema
- I didnt know how to approach this, failed in 2022.
- Started from the most simple thing (physical item)
- I wasnt sure how to approach date functions but I decided, that starting
with order, equipment_type and equipment tables would be wise. I stated
with table that didnt have any foreign keys / relationships

- Sorry, I started with equipment type - right in the middle.

## Sep 4 2025

- It would be cool to use ORM
- I could design my own
```c
C_TABLE(table_name
    C_ROW(name,     props1,     props2),
    C_ROW(name,     props1,     props2),
    C_ROW(name,     props1,     props2),
    C_ROW(name,     props1,     props2)
)
```

- DB has proven to work, I could fetch items from specific timespan 
and see how from what time to which time item type has been reserved.
I can also imagine using order_lines table store multiple durations for
each type_id - for non trivial lifetimes

- Finished HTMX book and now I read POSIX perf book
- Iam reading NGNIX book bcs it allows me to support HTTP 1.1 while shipping
HTTP3
