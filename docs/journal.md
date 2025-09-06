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

- So I found out that I need disposables, vehicles and rental items
- I ditched main flow but kept item -> type -> booking

- So after consulting with ChatGPT 5.0 Thinking I got thinking about designing
db in a way that would remove need for warehouse manegement and would
be self managing via this scheduler.

- AI proposed starting with scheduler core, which is equation. I need to find
out what I need for that equation and wrap my data against it - I will start
with what I want, not what I need. This sound pretty cool, I need to do more
research on this.

- If I were to use FSM (state of warehouse and next state - entering order)
it could actually become scalable by renting integrators doing the job
of drawing FSMs xDD.

- It could be cheap - I need to measure.

## Sep 5 2025

- Scheduler should: select, dispatch, advance time, get cost of this. 
- Then after finding best one, while waiting physically, try to bind other
select event in advace while this one is still going on.

- Its fucking not trivial, even getting enough data for it is hard. And
putting it all into chart is fucking hard.

- If I were to make UI good enough I will get rid of scheduler and leave
human operator do it. It would show all warnings, issues even last minute
and it would handle all possible edge cases with good saving policy.
Then it would just normalize to a stream all events and show to loading crew.

## Sep 5 2025

- As was said, UI makes huge difference, today I experimented a lot! Its
impossible to do job of CEO by machine, its super hard. Now Iam thinking
about breaking warehouse to atoms (each piece of equipment) and just zoom out
to eq_type and so on to see all underlying stuff there.
