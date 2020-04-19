var express = require("express");
var app = express();

// Requiring fs module in which 
// readFile function is defined. 
const fs = require('fs') 

//reads serial data from file
fs.readFile('input.txt', 'utf-8', (err, data) => { 
    if (err) throw err; 
}) 

//when HTTP GET request is made, returns last digit from file 
app.get("/wmstatus", (req, res, next) => {
 var apple = fs.readFileSync('input.txt', 'utf8')
 var onlyNumbers = apple.replace(/\D/g,'');
 var lastNumber = onlyNumbers.substring(onlyNumbers.length - 1);
 res.json(lastNumber);
});

//runs on the server
app.listen(3000, () => {
 console.log("Server running on port 3000");
});