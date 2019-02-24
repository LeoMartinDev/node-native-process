const { app, BrowserWindow } = require('electron');

function createWindow () {
  win = new BrowserWindow({ width: 800, height: 600, title: 'native-process-test' });

  process.stdout.write(`ready - ${process.pid}`);
}

app.on('ready', createWindow);

app.on('window-all-closed', app.quit);