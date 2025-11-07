const express = require('express');
const app = express();
const port = 3000;

app.get('/', (req, res) => {
    throw new Error('Something is wrong inmy llineexexex');
});

app.listen(port, () => {
    console.log(`Server is running at http://localhost:${port}`);
});