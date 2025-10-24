const buf1 = Buffer.alloc(10);
console.log(buf1);

const buf2 = Buffer.from('Hello');
const buf3 = Buffer.from([1,2,3,4,5]);
console.log(buf2.toString());
console.log(buf3);

const buffer2 = Buffer.from('GFG');
console.log(buffer2.toString());

const bufwrite = Buffer.alloc(10);
bufwrite.write("Hi!");
console.log("Writen Buffer: ",bufwrite.toString());

const buffersrc = Buffer.from('Hello World');
const bufferdest = Buffer.alloc(3);
buffersrc.copy(bufferdest);
console.log("Copied Buffer: ",bufferdest.toString('utf-8'));

const bufconcat1 = Buffer.from('GeeksforGeeks');
const bufconcat2 = Bufferold.slice(0,4);
console.log("Sliced Buffer: ",bufconcat2.toString());

const bufferOne = Buffer.from('Happy Learning');
const buffernoTwo = Buffer.from(' at GFG');
const bufferThree = Buffer.concat([bufferOne, buffernoTwo]);
console.log("Concatenated Buffer: ", bufferThree.toString());

console.log("is Buffer: ", Buffer.isBuffer(bufferOne));
console.log("is text a buffer" , Buffer.isBuffer("text"));

console.log("Buffer Length: ", bufferThree.length);