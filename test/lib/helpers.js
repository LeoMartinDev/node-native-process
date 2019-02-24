const {
  spawn
} = require('child_process');
const path = require('path');
const {
  map
} = require('async');

function spawnTestApp() {
  return new Promise((resolve, reject) => {
    try {
      const electronProcess = spawn(path.join(__dirname, '../../node_modules/.bin/electron.cmd'),
        [path.join(__dirname, './sample-electron.js')]);

      electronProcess.stdout.on('data', data => {
        if (data.toString().includes('ready')) {
          const pid = parseInt(data.toString().split(' - ')[1]);

          setTimeout(() => resolve([electronProcess, pid]), 1500);
        }
      })
    } catch (error) {
      console.log('eokeoekeoke ::: ',error);
      reject(error);
    }
  });
}

const mapPromise = (collection, next) => {
  return new Promise((resolve, reject) => {
    map(collection, next, (error, result) => {
      if (error) return reject(error);
      resolve(result);
    });
  });
}

module.exports = {
  spawnTestApp,
  mapPromise,
}