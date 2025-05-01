const admin = require('firebase-admin');

const serviceAccount = require('../firebaseconfig.json');

admin.initializeApp({
  credential: admin.credential.cert(serviceAccount),
  databaseURL: "https://projeto-final-44901-default-rtdb.firebaseio.com"
});

const db = admin.database();
module.exports = db;
