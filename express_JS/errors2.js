const express = require('express');
const app = express();
const port = 3000;

app.get('/', (req, res, next) => {
    const err = new Error('Custon error occurred!');
    next(err);
});

app.use((err, req, res, next) => {
    console.error(err.stack);
    res.status(500).send('Something broke! ' + err.message);
});

app.listen(port, () => {
    console.log(`Server is running at http://localhost:${port}`);
}); 