# School WMS - Rental
School project for WMS.

## Flow - User

1. Highest priority user creates user. 
2. User uses higher priority user to auth prov accout. 
3. After login, session gets created lasting 240 hours. 
4. This ```SessionID``` is used for assigning responsible actions all actions are logged. 
5. All previous actions are recorded in ```change_log```. 

## Flow - API

1. ```POST /auth/init``` ```{ email: "___" }```
    <br>*Very first used is initialized via SQL. Every following one uses init.*

2. ```POST /auth/login``` ```{ email: "___", password: "___" }```
    <br>*Verification code is sent to registered email for verification.*

3. ```POST /auth/validate``` ```{ code: "___" } RETURNING { token: "___" }```

## Flow - Database
