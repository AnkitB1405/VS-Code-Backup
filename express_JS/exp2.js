const express = require("express");
const app = express();

app.get("/", (req, res) => {
  res.send("Hello, World!");
});

app.get("/users/:id", (req, res) => {
  const userId = req.params.id;
  res.send(`User ID requested: ${userId}`);
});

app.get("/users/:id/books/:bookId", (req, res) => {
    res.send("User: ${req.params.id}, Book: ${req.params.bookId}");
});