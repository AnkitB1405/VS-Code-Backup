const buf = Buffer.alloc(26);
for (let j = 0; j < 26; j++) buf[j] = 97 + j; // ASCII 'a' = 97
console.log(buf.toString()); // prints: abc...z
