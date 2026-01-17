function printline(){
    console.log("Hello World!");
}
//var timer = setInterval(printline, 2000); //Uncomment to see Hello World every 2 seconds

// Importing the module
var date = require('./export_modules.js');
console.log(date.myDateTime());

var calc = require('./export_modules.js');
console.log("Addition: " + calc.add(5, 3));
console.log("Subtraction: " + calc.subtract(5, 3));
console.log("Multiplication: " + calc.multiply(5, 3));
console.log("Division: " + calc.divide(5, 3));

const assert = require('assert');
let x = 5;
let y = 3;  
try {
    assert.strictEqual(calc.add(x, y), 8);
    assert.strictEqual(calc.subtract(x, y), 2);
    assert.strictEqual(calc.multiply(x, y), 15);
    assert.strictEqual(calc.divide(x, y), 1.6666666666666667);
    console.log("All tests passed!");
} catch (error) {
    console.error("A test failed: ", error.message);
}