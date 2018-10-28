# Server Program

The server that handles the requests of clients to set the lights on and off

# To set up the server

1) nodeJS is a prerequisite, install it 
2) clone the repository
3) cd into server
```
    $ cd server
```
4) install all the npm dependencies 
```
    $ npm install
```
5) run the node server
```
    $ node app.js
```

# Services

## 1) Service to set the status of the lights

### Request

#### POST http://localhost:8080/setLightStatus
#### Content-Type: application/json

request body :
```
    {
        "red" : 1,
        "yellow" : 0
    }          
```

### Response 

#### Content-Type: application/json

response body :
```
    {
        "RED_BULB": 1,
        "YELLOW_BULB": 0
    }
```

## 2) Service to receive the current status of the lights

### Request

#### GET http://localhost:8080/GET_LIGHT_STATUS

### Response 

#### Content-Type: application/json

response body :
```
    {
        "RED_BULB": 1,
        "YELLOW_BULB": 0
    }
```