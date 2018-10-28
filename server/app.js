const express = require('express');
const cors = require('cors');
const path =  require('path');
var bodyParser = require('body-parser');

//Initialize express server
const app =  express();

//get Router
const router = express.Router();

//supports JSON
app.use(bodyParser.json());

//body parser middleware
app.use(bodyParser.urlencoded({
    extended: true
}));

//get the light status 
const lightStatus = require('./models/singletonLight');

//PORT number
const port = process.env.PORT || 8080;

//CORS middleware
app.use(cors());

//get the lights object
var lights = lightStatus.getInstance();

//get service to call from a browser to see if the server is running
app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, './public/index.html'));
});

//server starts listening
app.listen(port, () => {
    console.log('server started on port ' + port);
});

//////////////////////////////////////Services////////////////////////////////

//The service that the arduino has to call
app.get('/GET_LIGHT_STATUS', (req, res) => {
    res.send(lights.getStatus());
});

//the service that the app has to call
app.post('/setLightStatus', (req, res) => {

    let newLightStatus = {
        redLight: req.body.red,
        yellowLight: req.body.yellow
    };
    lights.setStatus(newLightStatus, (status)=>{
        console.log("changed light status to " +  JSON.stringify(status, null, 2));
        res.send(status);
    });

});
