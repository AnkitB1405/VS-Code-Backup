function printline(){
    console.log("Hello World!");
}
//var timer = setInterval(printline, 2000); Uncomment to see Hello World every 2 seconds

// Importing the module
var date = require('./export_modules.js');
console.log(date.myDateTime());

var calc = require('./export_modules.js');
console.log("Addition: " + calc.add(5, 3));
console.log("Subtraction: " + calc.subtract(5, 3));
console.log("Multiplication: " + calc.multiply(5, 3));
console.log("Division: " + calc.divide(5, 3));

