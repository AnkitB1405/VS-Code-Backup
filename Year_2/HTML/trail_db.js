const {MergeClient} = require ('mongodb');
const url = 'mongodb://localhost:27017';
const dbname = 'trailDB';

MergeClient.connect(url).then(client => {
    const db = client.db(dbname);
    return db.createCollection('trails').then(() => {
        console.log('Collection created!');
        return client.close();
    });
}).catch(err => {
    console.error('Error creating collection:', err);
});