const express = require("express");
const app = express();
const port = 3000;

app.get("/", (req, res) => {
  res.send("Welcome to my Express routing!");
});

app.get('/search', (req, res) => {
  const query = req.query.q;
  res.send(`You searched for: ${query}`);
});

app.listen(port, () => {
  console.log(`Server is running at http://localhost:${port}`);
});