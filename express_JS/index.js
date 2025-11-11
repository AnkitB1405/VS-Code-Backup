const express = require('express');
const upload = require('express-fileupload');

const app = express();

// Enable file upload middleware
app.use(upload());

// Serve the upload form
app.get('/', (req, res) => {
  res.sendFile(__dirname+ '/index.html');
});

// Handle the file upload
app.post('/', (req, res) => {
  if (req.files) {
    console.log(req.files);

    // Access the uploaded file (the input name must match "file")
    let file = req.files.file;
    let filename = file.name;
    console.log('Uploaded File Name:', filename);

    // Move the file to the uploads folder
    file.mv('./uploads/' + filename, (err) => {
      if (err) {
        console.log(err);
        res.send('Error occurred while uploading the file.');
      } else {
        res.send('File uploaded successfully: ' + filename);
      }
    });
  } else {
    res.send('No file uploaded!');
  }
});

app.listen(5000, () => {
  console.log('Server running at http://localhost:5000');
});