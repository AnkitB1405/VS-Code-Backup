const express = require('express');
const path = require('path');
const app = express();

// Middleware to parse form data
app.use(express.urlencoded({ extended: true }));

// Serve static files (HTML, CSS)
app.use(express.static(path.join(__dirname, 'public')));

// Route to handle POST form data
app.post('/submit', (req, res) => {
  const { name, email } = req.body;
  console.log('Form Data Received:', req.body);

  res.send(`
    <h2>Thank you, ${name}!</h2>
    <p>Your email <b>${email}</b> has been received.</p>
    <a href="/">Go Back</a>
  `);
});

// Start server
app.listen(3000, () => {
  console.log('Server running on http://localhost:3000');
});