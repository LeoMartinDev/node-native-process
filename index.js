const testAddon = require('./build/Release/testaddon.node');
console.log('addon',testAddon.getProcessesByName('chrome.exe', (error, result) => {
    if (error) console.log('error : ', error);
    console.log(result);
}));
module.exports = testAddon;