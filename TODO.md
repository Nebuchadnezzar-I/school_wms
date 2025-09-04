What I need to do is store see what I have to store about warehouse
store what I can see in database so FSM can operate on DB which
is representation of database. Include atomic operations in FSM
and prepare DB for it.

## Now
- [x] S0 Add vehicles to schema
- [x] S1 Load buffers
- [x] S2 Trips & Legs
- [ ] Equipment could be in vehicle and it needs to be adjusted in buffer
to make sure its avaliable in warehouse or add extra buffer

- [ ] Read: https://backend.orbit.dtu.dk/ws/portalfiles/portal/5280227/MinWen_PhD_thesis.pdf

---

## Cool stuff to add in future
- [x] Loading buffers - its not loaded instantly
- [ ] Highlight when equipment is scheduled back-to-back
- [ ] Show maintance notices - last inspection

## Risk stuff xD
- [ ] Regular simulations risk testing
- [ ] Client / default risk ranking
- [ ] Adjust prices for risk

## Failure impact
- [ ] If 18kW fails at job site, what orders will be affected?

## Loss - Ineffectivess
- [ ] Shows wasted resources and cost of wasting them

## Scheduler
- [ ] Inputs items for order and scheduler will tell what to buy, rent etc.

## UI
- [ ] Heatmaps, gantt chart, Scenario toggle
